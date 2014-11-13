<?php

class LogView extends Slot {

	public $ModuleID = 104;
	public $SectionID = 104;
	public $Task = 'view';
	public $amount = array('3' => '3', '5' => '5', '10' => '10', '20' => '20','30' => '30','40'=>'40','50'=>'50','60'=>'60','70'=>'70','80'=>'80','90'=>'90','100'=>'100');

	public $orderby = array(
		'action_type' => array(
			'sortColumn' => 'action_name',
			'sortType' => 'asc',
		),
		'action_time' => array(
			'sortColumn' => 'action_time',
			'sortType' => 'desc',
		),
		'section' => array(
			'sortColumn' => 'section_name',
			'sortType' => 'asc',
		),
		'owner' => array(
			'sortColumn' => 'owner',
			'sortType' => 'asc',
		),

	);

	public $sortby = '';
	public $search_params = array();

	function LogView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Action->processEvent($this->SectionID,'get_search',$this->getRequestField('form'),$this);
		$this->search_params = $this->PreparedTemplates;
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
			$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
			switch(@$this->LocalTarget[1]) {
				case 'viewall':
					$this->Scheme = 'default';
					$this->Action->processEvent($this->SectionID,'clear_search',$this->getRequestField('form'),$this);
					$this->search_params = $this->PreparedTemplates;
					header("Location: ".$this->Home.'Admin/Log/');
				break;
				default:
					$request = array('pageRecordsQty'=>'50','curPageNumber'=>(isset($this->LocalTarget[1])? $this->LocalTarget[1]+1 : 1));
					$this->Scheme = 'default';
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'action_time';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'view',$request,$this);

					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
						else {$this->getPageControl($this->Home.'Admin/Log',$this->sortby);}
				break; 
			}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF);
					break;
					case 'search':
						if (isset($this->Request['form']['goToPage']) && (!empty($this->Request['form']['goToPage'])) && is_Num($this->Request['form']['goToPage'])) {
							$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'pubdate';
							header("Location: ".$this->Home.'Admin/Log/'.($this->Request['form']['goToPage']-1).'/'.$this->sortby);
						} else {
							$this->validateForm()
							and $this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
							and header("Location: ".$this->Home.'Admin/Log');
						}
					break;
				}
			}
		}
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('username'),3,32)) $this->errors['username'] = $this->globalLangContent['error_view']['username'];
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['passw'];
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'message': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'empty': case 'default': $this->fillView(); break;
			default: $this->fillView(); break;
		}
	}

	function getFormattedDate($field) {
		if ( ($field!="-1") && ($field!=""))
			return date('m-d-Y h:i:s A', $field);
		else return '';
			
	}

	function fillView() {
		$action_type = mergeArrays(array('0'=>' All Actions') , $this->Action->Server->getGuide('log_action'));
		$section = mergeArrays(array('0'=>' All Sections') ,$this->Action->Server->getGuide('action_log_section'));
		$num=1;
		if (!empty($this->PreparedTemplates['curPage'])) {
			foreach($this->PreparedTemplates['curPage'] as $key => $value) {
				$this->TempFillEls['list'][$value['id']] = array(
					'id' => $value['id'],					
					'action' => $value['action_name'],
					'section' => $value['section_name'],
					'action_time' => $value['action_time'],
					'owner' => $value['owner'],
					'url' => !empty($value['url'])?makeLink($this->Home.$value['url'], 'Open Details', array(), '', ' target="_blank"'): (!empty($value['description'])?$value['description']:''),
					'num' => ( (isset($this->LocalTarget[1])?$this->LocalTarget[1]:0)*(!empty($this->search_params['amount'])?$this->search_params['amount']:50) +$num++),
				);
			}
		}
		$this->sort_array = array();
		$this->TempFillEls['amount'] = inputSelect('form[amount]',$this->amount,(!empty($this->search_params['amount'])? $this->search_params['amount'] : 50), ' onchange="document.forms.search.submit();" ');
		$this->TempFillEls['date_from'] = inputText('form[date_from]',(!empty($this->search_params['date_from'])? ($this->search_params['date_from']) : ''), $this->correctSize(10), ' readonly=\'true\'');
		$this->TempFillEls['date_to'] = inputText('form[date_to]',(!empty($this->search_params['date_to'])? ($this->search_params['date_to']) : ''), $this->correctSize(10), ' readonly=\'true\'');
		$this->TempFillEls['action_type'] = inputSelect('form[action_type]',$action_type,(!empty($this->search_params['action_type'])? ($this->search_params['action_type']) : 0),' onchange="document.forms.search.submit();" style=\'width:120px;\'');
		$this->TempFillEls['first_name'] = inputText('form[first_name]',(!empty($this->search_params['first_name'])? ($this->search_params['first_name']) : ''), $this->correctSize(20));
		$this->TempFillEls['last_name'] = inputText('form[last_name]',(!empty($this->search_params['last_name'])? ($this->search_params['last_name']) : ''), $this->correctSize(20));

		$this->TempFillEls['section'] = inputSelect('form[section]',$section,(!empty($this->search_params['section'])? ($this->search_params['section']) : 0),' onchange="document.forms.search.submit();" style=\'width:140px;\'');
		$this->sort_array = array(
			'action_time' => $this->sortby=='action_time'? '<span class=white_middle>Action Time</span>' : makeLink($this->Home.'Admin/Log/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/action_time',' Action Time ',array(),'','class=\'consumer\''),
			'action_type' => $this->sortby=='action_type'? '<span class=white_middle>Action Type</span>' : makeLink($this->Home.'Admin/Log/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/action_type',' Action Type ',array(),'','class=\'consumer\''),
			'section' => $this->sortby=='section'? '<span class=white_middle>Section</span>' : makeLink($this->Home.'Admin/Log/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/section',' Section ',array(),'','class=\'consumer\''),
			'owner' => $this->sortby=='owner'? '<span class=white_middle>Member</span>' : makeLink($this->Home.'Admin/Log/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/owner',' Member ',array(),'','class=\'consumer\''),		
		);
		$this->TempFillEls['sort'][] = $this->sort_array;
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = 'The Offer is deleted successfully'; break;
			case 'finish_save': $this->TempFillEls['message'] = 'The Offer is saved successfully'; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>