<?php

class AdminQuotationView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 19;
	public $Task = 'view';
	public $orderby = array(
		'Id' => array(
			'sortColumn' => 'id',
			'sortType' => 'desc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	
	function AdminQuotationView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				case 'EditQuotation':
					if (isset($this->LocalTarget[2])) {
						$this->Scheme = 'action';
						$this->Task = 'get';
						$request['langid']=$this->LM->Langs[$this->language];
						$request['id']=@$this->LocalTarget[2];
						$this->Action->processEvent($this->SectionID,'get',$request,$this);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					} else
					if(empty($this->PreparedTemplates)) header("Location: ".$this->Home.'/Admin/AdminMenuItems'.$this->SID);
				break;
				case 'DeleteQuotation':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'action';
						$this->Task="get";
						$this->Action->processEvent($this->SectionID,'get',array('id' => $this->LocalTarget[2]),$this);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					}
					else header("Location: ".$this->Home.'/Admin/AdminMenuItems'.$this->SID);
				break;
				default:					
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request = array('pageRecordsQty'=>'100','curPageNumber'=>(isset($this->LocalTarget[2])? $this->LocalTarget[2]+1 : 1));
					$this->sortby = 'Id';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];					
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
					 else {$this->getPageControl($this->Home.'/Admin/AdminQuotation/'.(!empty($this->LocalTarget[1])?$this->LocalTarget[1]:0),0);}
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'add':	case 'edit':				
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'save',$this->correctWords($this->getRequestField('form')),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'/Admin/AdminQuotation'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'delete':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'delete',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$this->Home.'/Admin/AdminQuotation'.$this->SID);
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
			case 'add': case 'edit':
				if(!is_FullText($this->Request['form']['name_langs']['0']['value'],1,512)) $this->errors['engvalue'] = $this->globalLangContent['error_view']['err_name'];
				if(!is_FullText($this->Request['form']['name_langs']['1']['value'],1,512)) $this->errors['rusvalue'] = $this->globalLangContent['error_view']['err_name'];
				if(!is_FullText($this->Request['form']['name_langs']['2']['value'],1,512)) $this->errors['ukrvalue'] = $this->globalLangContent['error_view']['err_name'];
			break;

		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'action': $this->fillAction(); break;
			case 'empty': case 'default': case 'view': $this->fillView(); break;			
		}
	}

	function fillView() {
		foreach($this->PreparedTemplates['curPage'] as $key => $value) {
			$this->TempFillEls['quotations'][$value['id']] = array(
				'id' => $value['id'],
				'value' =>  substr($this->getWordWrap($value['value'], 30, " "), 0, 200),
			);
		}
		$this->TempFillEls['item_langs1'] = inputHidden('form[name_langs][0][language]',1);
		$this->TempFillEls['item_langs2'] = inputHidden('form[name_langs][1][language]',2);
		$this->TempFillEls['item_langs3'] = inputHidden('form[name_langs][2][language]',3);
		
		$this->TempFillEls['eng_value'] = inputText('form[name_langs][0][value]',(!empty($this->Request)? $this->getRequestFormField('eng_value') : ''),$this->correctSize('40'));
		$this->TempFillEls['rus_value'] = inputText('form[name_langs][1][value]',(!empty($this->Request)? $this->getRequestFormField('rus_value') : ''),$this->correctSize('40'));
		$this->TempFillEls['ukr_value'] = inputText('form[name_langs][2][value]',(!empty($this->Request)? $this->getRequestFormField('ukr_value') : ''),$this->correctSize('40'));

		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillAction() {
		global $PHP_SELF;
		$action = ($this->LocalTarget[1]=='DeleteQuotation'?'delete':'edit');
		$this->TempFillEls = array(
			'action' => $action,
			'item_langs1' => inputHidden('form[name_langs][0][language]',1),
			'item_langs2' => inputHidden('form[name_langs][1][language]',2),
			'item_langs3' => inputHidden('form[name_langs][2][language]',3),
			'id' => $this->PreparedTemplates['id'],
			'idhidden' => inputHidden('form[id]',(!empty($this->Request)? $this->getRequestFormField('id') : $this->PreparedTemplates['id'])),
			'eng_value' => ($action=='delete'?$this->PreparedTemplates['name_langs'][0]['value'] : inputText('form[name_langs][0][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['value'] : $this->PreparedTemplates['name_langs'][0]['value']),$this->correctSize('40'))),
			'rus_value' => ($action=='delete'?$this->PreparedTemplates['name_langs'][1]['value'] : inputText('form[name_langs][1][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['value'] : $this->PreparedTemplates['name_langs'][1]['value']),$this->correctSize('40'))),			
			'ukr_value' => ($action=='delete'?$this->PreparedTemplates['name_langs'][2]['value'] : inputText('form[name_langs][2][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['2']['value'] : $this->PreparedTemplates['name_langs'][2]['value']),$this->correctSize('40'))),
			'actionbutton' => ($action=='delete'?$this->globalLangContent['button']['admin_bt_delete']:$this->globalLangContent['button']['admin_bt_update']),
		);
		//$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,($action == 'delete'? 'delete' : 'save'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);		
	}

	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_quotation']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_quotation']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->globalLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); 
				 break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>
