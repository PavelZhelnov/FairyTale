<?php

class AdminView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 3;

	function AdminView($pquery) {
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		//printArray(ObjToArray($this->Security->currentuser));
		//phpinfo();
		
		if(!$this->Action->isAuthorizeAdmin()) {
			//if(!$this->Action->isAuthorizeUser())
			 $this->Scheme = 'auth';
			//else $this->Scheme = 'message';
		}
		else {
			if(!empty($this->LocalTarget[1]) && in_array($this->LocalTarget[1],$this->Properties['Tasks'])) {
				if(!empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],$this->Properties['Clear']))
					$this->Scheme ='default';
				$localTarget = $this->LocalTarget;
				switch(@$this->LocalTarget[1]) {
					case 'Logoff':
						$this->Action->logoff($this->SectionID,array(),$this) and header("Location: ".$this->Home.'/Admin/');
						$this->Scheme = 'auth';
					break;
				}
				array_shift($localTarget);
				$this->render = array (
					'Name' => $this->LocalTarget[1].'View',
					'Type' => 'object',
					'LocalTarget' => $localTarget,
					'Properties' => array(),
					'Template' => $this->LocalTarget[1].'View',
				);
			}
		}
		if(!empty($this->Request)) {
			switch($this->getRequestField('step')) {
				case 'auth':
					$this->Scheme = 'auth';
					$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and header("Location: ".$PHP_SELF.$this->SID);
				break;
			}
		}
		$this->setSchemeTemplate($this->Scheme);
	}

	function validateForm() {
		switch($this->Scheme) {
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
			case 'auth': $this->fillAuth(); break;
			default: $this->fillBody(); break;
		}
	}

	function fillBody() {
		if(!empty($this->render))
			$this->TempFillEls['body'] = renderSlot($this->render,'',TRUE);
	}
}
?>