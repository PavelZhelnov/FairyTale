<?php

class SearchView extends Slot {

	public $ModuleID = 5;
	public $SectionID = 200;
	public $Task = 'search';
	public $amount = array('3' => '3', '5' => '5', '10' => '10', '20' => '20','30' => '30','40'=>'40','50'=>'50','60'=>'60','70'=>'70','80'=>'80','90'=>'90','100'=>'100');
	public $WebPath;
	
	public $orderby = array(
		'name' => array(
			'sortColumn' => 'name',
			'sortType' => 'asc',
		),
	);

	public $sortby = '';
	public $search_params = array();

	function SearchView($pquery) {
		global $REGISTRY;
		$this->WebPath = $REGISTRY['Core']['WebHome'];
		$this->Slot($pquery);
	}
		
	function init() {
		global $PHP_SELF;
		if ($this->Scheme == 'preview') return;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		
		if($this->Scheme != 'preview' && $this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete') {
			$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
			switch(@$this->LocalTarget[1]) {

				default:
					$this->Scheme = 'default';
					$this->Task = 'viewinfo';
					$request['langid']=$this->LM->Langs[$this->language];					
				break; 
			}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;

					case 'search':
							if (!empty($this->Request['form']['search'])) {
								$request['search'] = $this->Request['form']['search'];
							}
							$request['langid']=$this->LM->Langs[$this->language];					
							$this->validateForm()
							and $this->Action->processEvent($this->SectionID,'search',$request,$this);
							//and header("Location: ".$this->Home.'/search');
					break;
				}
			}
		}
		$this->setSchemeTemplate($this->Scheme);
	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('login'),1,50)) $this->errors['login'] = $this->globalLangContent['error_view']['err_login'];
				if(!is_AlphaNumDefis($this->getRequestFormField('password'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'empty': case 'default': $this->fillView(); break;
			case 'preview': break;
			default: $this->fillView(); break;
		}
	}


	function FillView() {
		$i=1;$size=0;
		if (!empty($this->PreparedTemplates['curPage'])) {
			$this->TempFillEls['result_label'] = $this->globalLangContent['label']['search_found'];
			foreach ($this->PreparedTemplates['curPage'] as $k=>$v) {
				$this->TempFillEls['search_results'][] = array(
					'url'=>$v['url'],
					//'description' => $v['description'],
					'name' => $v['name'],
					'link' => makeLink($this->Home.'/'.$v['url'], 'http://www.fairytale.com.ua/'.$v['url'], array(), '', 'class="textlink"' ),
					'num' => $i++,
				);
			}
		} else $this->TempFillEls['result_label'] = $this->globalLangContent['label']['search_no_results'];
	}
	
	
	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = 'The Document is deleted successfully'; break;
			case 'finish_save': $this->TempFillEls['message'] = 'The Document is saved succesfully'; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}


}
?>