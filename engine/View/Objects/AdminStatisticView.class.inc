<?php

class AdminStatisticView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 28;
	public $Task = 'view';
	public $sort_array = array();
	public $sortby = '';

	function AdminStatisticView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}
		
	function init() {
		global $PHP_SELF;		

		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete' && $this->Scheme!='closed') {
		$this->curPageNumber = empty($this->LocalTarget[0]) || !validate(intval($this->LocalTarget[0]))? 0 : intval($this->LocalTarget[0]);
			if (!$this->Action->isAuthorizeAdmin()) {$this->Scheme = 'empty';} else
			switch(@$this->LocalTarget[0]) {
				default:
					$this->Action->processEvent($this->SectionID,'get_status',array(),$this);
					$this->Scheme = 'default';
					break;
			}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
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
			case 'empty': $this->fillEmpty(); break;
			case 'default': $this->FillStatus(); break;
		}
	}

	function fillStatus() {
		$docs=0;$pages=0;$menus=0;
		foreach ($this->PreparedTemplates['docs'] as $k=>$v) {
			$this->TempFillEls['documents'][] = array(
				'name' => makeLink($this->Home.'/Admin/AdminDocument/'.$v['colname'], $v['colname'].'  ',array()),
				'qty' => makeLink($this->Home.'/Admin/AdminDocument/'.$v['colname'], ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $docs = $docs + $v['qty'];	
		}
		foreach ($this->PreparedTemplates['pages'] as $k=>$v) {
			$this->TempFillEls['pages'][] = array(
				'name' => makeLink($this->Home.'/Admin/AdminPages/'.$v['colname'], $v['colname'].'  ',array()),
				'qty' => makeLink($this->Home.'/Admin/AdminPages/'.$v['colname'], ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $pages = $pages + $v['qty'];	
		}
		foreach ($this->PreparedTemplates['menus'] as $k=>$v) {
			$this->TempFillEls['documents'][] = array(
				'name' => makeLink($this->Home.'/Admin/AdminMenuItems/'.$v['colname'], $v['colname'].'  ',array()),
				'qty' => makeLink($this->Home.'/Admin/AdminMenuItems/'.$v['colname'], ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $menus = $menus + $v['qty'];	
		}

		$this->TempFillEls['docs'] = makeLink($this->Home.'/Admin/AdminDocument/Add', ' '.$docs.' ',array());
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'get_status');
	}
	
	function fillEmpty() {
		$this->TempFillEls = array();
	}
	
	function fillMessage() {
		switch($this->Scheme) {			
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_invoice']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_invoice']; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>