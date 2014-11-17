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
			if (strpos(@$this->LocalTarget[1], 'ssoauthret')!==false && strlen(@$this->LocalTarget[1])>20) {
				$this->Scheme = 'auth';
				$this->Action->ssoAuthorizeReturn($this->SectionID,$this->getRequestField('form'),$this) and header("Location: ".$this->Home.'Admin');
			}
			if (@$this->LocalTarget[1] == 'password') {
				if(!empty($this->LocalTarget[2])){
					switch($this->LocalTarget[2]){
						case 'changerequest':
							$this->Scheme = 'lostpassword';
							break;
						case 'new':
							if(empty($this->LocalTarget[3]))
								break;
							$this->Action->processEvent($this->SectionID,'check_hash',array('hashcode' => $this->LocalTarget[3]),$this);
							if(!empty($this->PreparedTemplates['_error'])){
								$this->Scheme = 'lostpassword';
								$this->Relocate($this->Home.'Admin/password/changerequest');
								$this->PreparedTemplates['action_message_error'] = (empty($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']])?'':$this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]);
							}
							else{
								$this->Scheme = 'new_pswd';
							}
							break;
					}
				}
			}
		}
		else {
			if(!empty($this->LocalTarget[1])) {

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
					$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and header("Location: ".$PHP_SELF);
				break;
				case 'ssoauth':
					$this->Scheme = 'auth';
					$this->Action->ssoAuthorize($this->SectionID,array('url'=>"http://fairytale.com/"),$this);
					
				break;
				case 'lostpassword':
					//$this->Scheme = 'text_notification';//Show success message screen. If recapcha or login\email check fails, show lostpassword screen
						$this->Scheme = 'auth';
					if(!$this->recapcha_check()){
						$this->Scheme = 'lostpassword';
						$error = 'recapcha_mismatch';
						$this->PreparedTemplates['recaptcha_error'] = (empty($this->globalLangContent['error_view'][$error])?'':$this->globalLangContent['error_view'][$error]);
						break;
					}
					$this->Action->processEvent($this->SectionID,'lostpassword',$this->getRequestField('form'),$this);
					if(!empty($this->PreparedTemplates['_error'])){
						$this->Scheme = 'lostpassword';
						$error_name = 'login_email_not_found';
						if($this->PreparedTemplates['_error'] == $error_name)
						{
							$this->PreparedTemplates['email_error'] = (empty($this->globalLangContent['error_model'][$error_name])?'':$this->globalLangContent['error_model'][$error_name]);
							$this->PreparedTemplates['_error']= '';
						}
						else
							$this->PreparedTemplates['action_message_error'] = (empty($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']])?'':$this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]);
					}
					else
					{
						$this->Relocate($this->Home.'Admin///sent');
						//$this->PreparedTemplates['action_message'] = $this->globalLangContent['text']['email_sent_notification'];
					}

					//$this->PreparedTemplates['action_message'] = $this->globalLangContent['text']['email_sent_notification'];
						
					break;
				case 'new_pswd':
					$this->Scheme = 'new_pswd';
					$this->PreparedTemplates = array('hashcode' => $this->getRequestFormField('hashcode'));
					$this->validateForm()
					and $this->Action->processEvent($this->SectionID,'new_pswd',$this->getRequestField('form'),$this)
					and $this->Relocate($this->Home.'/Admin///changed')
					;
					break;
			}
		}
		$this->setSchemeTemplate($this->Scheme);
		if(!empty($this->PreparedTemplates['_error'])) {
			$this->Action->setError($this->Task,$this->PreparedTemplates['_error']);
		}
	}

	function validateForm() {
		switch($this->Scheme) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('login'),1,50)) $this->errors['login'] = $this->globalLangContent['error_view']['err_login'];
				if(!is_AlphaNumDefis($this->getRequestFormField('password'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
			case 'ssoauth':
				if(!is_Email($this->getRequestFormField('login'),1,50)) $this->errors['login'] = $this->globalLangContent['error_view']['err_login'];
				if(!is_AlphaNumDefis($this->getRequestFormField('password'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
				break;
			case 'new_pswd':
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}
	
	function recapcha_check() {
		$challenge = (empty($this->Request['recaptcha_challenge_field']))?'':$this->Request['recaptcha_challenge_field'];
		$response = (empty($this->Request['recaptcha_response_field']))?'':$this->Request['recaptcha_response_field'];
		$resp = recaptcha_check_answer(CommonConstants::RECAPTCHA_PRIVATE, $_SERVER['REMOTE_ADDR'], $challenge, $response);
		if (!$resp->is_valid)
			return false;
		return true;
	}
	
	function fillElements() {
		switch($this->Scheme) {
			case 'auth': case 'ssoauth': $this->fillAuth(); break;
			case 'lostpassword': $this->fillLostPassword(); break;
			case 'new_pswd' : $this->fillNewPassword(); break;
			default: $this->fillBody(); break;
		}
		if (!empty($this->LocalTarget[3])) {
			$this->TempFillEls['formaction']=$this->Home.'Admin';
			switch ($this->LocalTarget[3]) {
				case 'changed': $this->TempFillEls['action_message'] = $this->globalLangContent['text']['lp_success'];break;
				case 'sent' : $this->TempFillEls['action_message'] = $this->globalLangContent['text']['email_sent_notification'];break;
			}
		}
		
	}
	
	function fillNewPassword() {
		$this->TempFillEls = array(
			'hidden' => inputHidden('o',$this->Name),
			'passw_text' => $this->globalLangContent['label']['type_new_pass'],
			'passw' => inputPassword('form[passw]','',$this->correctSize('25'),' id="form[passw]" required minlength=3 '),
			'passw_error' => (empty($this->errors['passw'])?'':$this->errors['passw']),
			'hashcode_hidden' => inputHidden('form[hashcode]',$this->PreparedTemplates['hashcode']),
		);
	}
	
	function fillBody() {
		if(!empty($this->render))
			$this->TempFillEls['body'] = renderSlot($this->render,'',TRUE);
	}
	function fillLostPassword(){
		global $PHP_SELF;
		$this->TempFillEls = array(
			'hidden' => inputHidden('o',$this->Name),
			'login' => inputText('form[login]',''/*(empty($this->PreparedTemplates['login'])?'':$this->PreparedTemplates['login'])*/,$this->correctSize('25'),' id="form[login]" minlength=3 required '),
			'email' => inputText('form[email]',''/*(empty($this->PreparedTemplates['email'])?'':$this->PreparedTemplates['email'])*/,$this->correctSize('25'),' id="form[email]" mask="email" required '),
			'recaptcha_field' =>recaptcha_get_html(CommonConstants::RECAPTCHA_PUBLIC, 'error'),
			'email_error' => (empty($this->PreparedTemplates['email_error'])?'':$this->PreparedTemplates['email_error']),
			'recaptcha_error' => (empty($this->PreparedTemplates['recaptcha_error'])?'':$this->PreparedTemplates['recaptcha_error']),
			'action_message_error' => (empty($this->PreparedTemplates['action_message_error'])?'':$this->PreparedTemplates['action_message_error']),
			'action_message' => (empty($this->PreparedTemplates['action_message'])?'':$this->PreparedTemplates['action_message']),
		);
		(!empty($this->PreparedTemplates['_error'])) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
	}
}
?>