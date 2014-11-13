<?php

class AdminEmailView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 19;
	public $Task = 'view';
	
	function AdminEmailView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				default:
					$this->Scheme = 'edit';
					$this->Task = 'view';
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'edit',$request,$this);
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'edit':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'updateemail',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
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
			case 'edit':
				if(!is_Email($this->getRequestFormField('email'))) $this->errors['email'] = $this->globalLangContent['error_view']['err_admin_email'];
			break;

		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {		
		switch($this->Scheme) {			
			case 'save': case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'default': case 'edit': $this->fillEditEmail(); break;
			case 'auth': $this->fillAuth(); break;
		}
	}

	function fillEditEmail() {
		$this->TempFillEls = array(
			'email' => inputText('form[email]',(!empty($this->Request)? $this->getRequestFormField('email') : $this->PreparedTemplates['adminemail']),$this->correctSize('50')),
		);
		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,'save');
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'save');
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'edit');
	}
		
	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_info']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_info']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->localLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]);
				 break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>