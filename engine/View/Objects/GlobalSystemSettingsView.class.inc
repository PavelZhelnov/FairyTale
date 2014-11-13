<?php

class GlobalSystemSettingsView extends Slot {

	public $ModuleID = 103;
	public $SectionID = 103;
	public $Task = 'open';
	public $gss;
	
	function GlobalSystemSettingsView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}
	public $orderby = array(
		'department' => array(
			'sortColumn' => 'name',
			'sortType' => 'asc',
		),
	);
	
	public $sortby = '';
	
	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		//$this->Action->processEvent($this->SectionID,'open',array('id'=>1),$this);
		//$this->gss = $this->PreparedTemplates;
		if($this->Scheme != 'finish_save' && $this->Scheme!='finish') {
			switch(@$this->LocalTarget[1]) {
				case 'edit':
					if (isset($this->LocalTarget[2])) {
						$this->Scheme = 'action';
						$this->Task = 'open';
						$request['langid']=$this->LM->Langs[$this->language];
						$this->Action->processEvent($this->SectionID,'open',array('id' => $this->LocalTarget[2]),$this);
						$this->gss = $this->PreparedTemplates;
					}
				break;
				default:
					$this->Scheme = 'default';
					$request['langid']=$this->LM->Langs[$this->language];
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'department';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					
					$this->Action->processEvent($this->SectionID,'list',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
						else {$this->getPageControl($this->Home.'Admin/GlobalSystemSettings/',$this->sortby);}
				break;
			}
				
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'update': 
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'update',$this->getRequestField('form'),$this)
						and /*$this->Action->setPage($this->SectionID,'finish_save') and*/ header("Location: ".$this->Home.'Admin/GlobalSystemSettings///saved');
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
				}
			}
		}
		if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('username'),3,32)) $this->errors['username'] = $this->globalLangContent['error_view']['username'];
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['passw'];
			break;
			case 'update' : 
				//$this->Request['form']['name_langs'][0]['name'] = trim($this->Request['form']['name_langs'][0]['name']);
				$this->gss['license_expiration_notification_method']=$this->Request['form']['license_expiration_notification_method'];
				if (!is_Num($this->Request['form']['default_city'],1,31255) || $this->Request['form']['default_city']<1) $this->errors['city'] = 'Choose the default city';
				if (!is_Num($this->Request['form']['default_state'],1,31255) || $this->Request['form']['default_state']<1) $this->errors['state'] = 'Choose the default state';
				//
				if (!is_Num($this->Request['form']['default_urgency_period'],1,7) || $this->Request['form']['default_urgency_period']<1) $this->errors['default_urgency_period'] = 'Choose the default period';
				//
				if(!is_Email($this->Request['form']['support_email'],1,255)) {$this->errors['support_email'] = 'Please, fill the Support email Field';$this->gss['_activetab']=1;}
				if(!is_Email($this->Request['form']['feedback_email'],1,255)) {$this->errors['feedback_email'] = 'Please, fill the Feedback email Field';$this->gss['_activetab']=1;}
				if(!is_Email($this->Request['form']['subscription_email'],1,255)) {$this->errors['subscription_email'] = 'Please, fill the Subscription email Field';$this->gss['_activetab']=1;}
				//if(!is_ ($this->Request['form']['offer_confirmation_email'],1,255)) {$this->errors['offer_confirmation_email'] = 'Please, fill the Offer Confirmation email Field';$this->gss['_activetab']=1;}
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {		
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': $this->fillMessage(); break;
			case 'action': $this->fillActionPage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'default': default: $this->fillDepartments(); break;
		}
	}
	
	function fillDepartments() {
		$num=1;
		if (!empty($this->PreparedTemplates['curPage'])) {
			foreach($this->PreparedTemplates['curPage'] as $key => $value) {
				$this->TempFillEls['list'][$value['id']] = array(
					'id' => $value['id'],					
					'department' => $value['department'],
					'name' => $value['name'],
					'num' => $num++,
				);
			}
		}		
		$this->sort_array = array(
			'department' => $this->sortby=='department'? '<span class=white_middle> Division Name </span>' : makeLink($this->Home.'Admin/GlobalSystemSettings/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/department',' Division Name ',array(),'','class=\'consumer\''),
		);
		$this->TempFillEls['popupmenu'][] = $this->fillPopUpMenu();
		$this->TempFillEls['sort'][] = $this->sort_array;
		$this->fillMessage();
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'offers');
		
	}

	function fillActionPage() {
		global $PHP_SELF;
		$state = (isset($this->Request['form'])?$this->Request['form']['default_state']: (isset($this->gss['default_state'])?$this->gss['default_state']:'1'));
		$this->Action->processEvent($this->SectionID,'cities',array('default_state'=>$state),$this);
		$this->city = mergeArrays(array('0' => ' --- Choose Default City --- '),$this->Action->getTemplate($this->SectionID,'cities'));
		$this->state = mergeArrays(array('0' => ' --- Choose Default State --- '),$this->Action->Server->getGuide('state'));
		$this->Action->processEvent($this->SectionID,'members',array(),$this);
		$this->members = mergeArrays(array('' => ''),$this->Action->getTemplate($this->SectionID,'members'));
		//printArray($this->gss['license_expiration_warn_period']);
		//printArray($this->gss['license_expiration_notification_method']);
		//printArray($this->Request['form']['license_expiration_notification_method']);
		$bymail=false;
		$bymsg =false;
		if(strstr($this->gss['license_expiration_notification_method'],'1')){
			$bymail=1;
			$bymail1 = 1;
		}
		if(strstr($this->gss['license_expiration_notification_method'],'2')){
			$bymail=2;
			$bymail2 = 2;
		}
		if(strstr($this->gss['license_expiration_notification_method'],'3')){
			$bymsg1 = 3;
			$bymsg=3;
		}
		if(strstr($this->gss['license_expiration_notification_method'],'4')){
			$bymsg2 = 4;
			$bymsg=4;
			
		}
		for ($t=1;$t<10;$t++) {
			$autoclose_period[$t]=$t;
		}
		for ($t=1;$t<=7;$t++) {
			$period[$t]=$t.' day'.(($t>1)?'s':'');
		}
		
		$this->license_expiration_warn_period = array('1' => '2 month','2' => '1 month','3' => '1 weeks');
		
		$this->send_mail= array('1' => 'once','2' => 'every day');
		
		$this->send_message= array('3' => 'once','4' => 'every time on login');
		
		$license_expiration_notification_method1 = array('1' => 'Notify via email');
		$license_expiration_notification_method2 = array('2' => 'Notify via message at Home page');
		
		$this->TempFillEls = array(
			'item_langs1' => inputHidden('form[name_langs][0][lang]',1),
			'item_langs2' => inputHidden('form[name_langs][1][lang]',2),
			'id' => inputHidden('form[id]', (isset($this->Request['form'])?$this->Request['form']['id']: isset($this->gss['id'])?$this->gss['id']:'')),
		
		
			'email_delimeter' => inputText('form[email_delimeter]',(isset($this->Request['form'])?$this->Request['form']['email_delimeter']: (isset($this->gss['email_delimeter'])?$this->gss['email_delimeter']:'')),$this->correctSize(2),' readonly required id="form[email_delimeter]" minlength="1" minlength="1"' ),
			'default_city' => inputSelect('form[default_city]',$this->city,(isset($this->Request['form'])?$this->Request['form']['default_city']: (isset($this->gss['default_city'])?$this->gss['default_city']:'1')),' style=\'width:200px\';'),
			'default_state' => inputSelect('form[default_state]',$this->state,(isset($this->Request['form'])?$this->Request['form']['default_state']: (isset($this->gss['default_state'])?$this->gss['default_state']:'1')),' style=\'width:200px\' onchange="document.forms.gss.step.value=\'cities\'; document.forms.gss.submit();" '),
			'support_email' => inputText('form[support_email]',(isset($this->Request['form'])?$this->Request['form']['support_email']: (isset($this->gss['support_email'])?$this->gss['support_email']:'')),$this->correctSize(30),' required id="form[support_email]" mask="email"' ),
			'feedback_email' => inputText('form[feedback_email]',(isset($this->Request['form'])?$this->Request['form']['feedback_email']: (isset($this->gss['feedback_email'])?$this->gss['feedback_email']:'')),$this->correctSize(30),' required id="form[feedback_email]" mask="email"' ),
			'subscription_email' => inputText('form[subscription_email]',(isset($this->Request['form'])?$this->Request['form']['subscription_email']: (isset($this->gss['subscription_email'])?$this->gss['subscription_email']:'')),$this->correctSize(30),' required id="form[subscription_email]" mask="email"' ),
			'autoclose_overdue_tasks_period' => inputSelect('form[autoclose_overdue_tasks_period]',$autoclose_period, (isset($this->Request['form'])?$this->Request['form']['autoclose_overdue_tasks_period']: (isset($this->gss['autoclose_overdue_tasks_period'])?$this->gss['autoclose_overdue_tasks_period']:'1')),'style="width:40px;"' ),
			'showing_app_listing_agent_first' => inputCheckBox('form[showing_app_listing_agent_first]',(isset($this->Request['form'])?$this->Request['form']['showing_app_listing_agent_first']:(isset($this->gss['showing_app_listing_agent_first'])?$this->gss['showing_app_listing_agent_first']:'1'))),		
		
			'default_listing_agent_field' => inputText('form[default_listing_agent]',$this->members[(!empty($this->Request['form']['default_listing_agent']['id'])?$this->Request['form']['default_listing_agent']['id'] : (isset($this->gss['default_listing_agent'])?$this->gss['default_listing_agent']['id']:''))],$this->correctSize(23),' id="form[default_listing_agent]"'),
			'default_listing_agent_id' => inputHidden('form[default_listing_agent][id]',(!empty($this->Request['form']['default_listing_agent']['id'])? $this->Request['form']['default_listing_agent']['id'] : (isset($this->gss['default_listing_agent']['id'])?$this->gss['default_listing_agent']['id']:'')), ' id="form[default_listing_agent][id]" '),

			'default_urgency_period' => inputSelect('form[default_urgency_period]',$period,(isset($this->Request['form'])?$this->Request['form']['default_urgency_period']: (isset($this->gss['default_urgency_period'])?$this->gss['default_urgency_period']:'1')),' style=\'width:200px\';'),
			
			'license_expiration_warn_period' => inputSelect('form[license_expiration_warn_period]',$this->license_expiration_warn_period,(isset($this->Request['form'])?$this->Request['form']['license_expiration_warn_period']: (isset($this->gss['license_expiration_warn_period'])?$this->gss['license_expiration_warn_period']:'1')),' style=\'width:200px\' id="warn_period" onchange="ch_Period()";'),
			
			'license_expiration_notification_method1' => inputCheckBox('form[license_expiration_notification_method1]',isset($bymail)?$bymail:false,' id="mail_metod" onclick="FistMetod()" '),
   			'license_expiration_notification_method2' => inputCheckBox('form[license_expiration_notification_method2]',isset($bymsg)?$bymsg:false,' id="message_metod" onclick="SecondMetod()"'),
   			
   			
			'send_mail1' => radioButton('1',$this->send_mail['1'],'form[send_mail]',isset($this->Request['form']['send_mail'])?$this->Request['form']['send_mail']:isset($bymail1)?true:false,' id ="send_mail1" onclick="changeVariantMail()"'),
			'send_mail2' => radioButton('2',$this->send_mail['2'],'form[send_mail]',isset($this->Request['form']['send_mail'])?$this->Request['form']['send_mail']:isset($bymail2)?true:false,' id ="send_mail2" onclick="changeVariantMail()"'),
			
			'send_message1' => radioButton('3',$this->send_message['3'],'form[send_message]',isset($this->Request['form']['send_message'])?$this->Request['form']['send_message']:isset($bymsg1)?true:false,' id ="send_message1" onclick="changeVariantMsg()"'),
			'send_message2' => radioButton('4',$this->send_message['4'],'form[send_message]',isset($this->Request['form']['send_message'])?$this->Request['form']['send_message']:isset($bymsg2)?true:false,' id ="send_message2" onclick="changeVariantMsg()"'),
			
			'license_expiration_notification_method'=>inputHidden('form[license_expiration_notification_method]',isset($this->gss['license_expiration_notification_method'])?$this->gss['license_expiration_notification_method']:'0',' id="license_expiration_notification_method"'),
			
			
			'offer_confirmation_email' => inputText('form[offer_confirmation_email]',(isset($this->Request['form'])?$this->Request['form']['offer_confirmation_email']: (isset($this->gss['offer_confirmation_email'])?$this->gss['offer_confirmation_email']:'')),$this->correctSize(30),' required id="form[offer_confirmation_email]" mask="email"' ),

			'em_office_steps_email' => inputText('form[em_office_steps_email]',(isset($this->Request['form'])?$this->Request['form']['em_office_steps_email']: (isset($this->gss['em_office_steps_email'])?$this->gss['em_office_steps_email']:'')),$this->correctSize(50),' required id="form[em_office_steps_email]" mask="email"' ),
			'em_step3_default_body' => inputTextArea('form[em_step3_default_body]',(isset($this->Request['form'])?$this->Request['form']['em_step3_default_body']: (isset($this->gss['em_step3_default_body'])?$this->gss['em_step3_default_body']:'')),$this->correctSize(50), $this->correctSize(8) ),

			'last_modified_date' => $this->gss['last_modified_date'],
			'last_modified_member' => $this->gss['last_modified_member']['last_name'].' '.$this->gss['last_modified_member']['first_name'],		
			'activetab' => inputHidden('form[_activetab]', (isset($this->gss['_activetab'])?$this->gss['_activetab']:(isset($this->Request['form']['_activetab'])?$this->getRequestFormField('_activetab'):0))),
		);
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}
	
	function fillPopUpMenu() {
		$perm = $this->Action->Security->getPermissionInfoForModule($this->ModuleID, $this->Action->Security->currentuser->level->id);
		$num1=0;$num2=0;
		$pop = array(
			'pop1' => array(
				$num1++ => ($perm>0? array('action' => $this->Home.'Admin/GlobalSystemSettings/edit/*1', 'button'=>'Edit Settings', 'target'=>''):null),
			),
		);
		$pop = removeNullValuesFromArray($pop);
		return $pop;
	}
	
		
	function fillMessage() {
		
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = 'The Settings has been deleted successfully'; break;
			case 'finish_save': $this->TempFillEls['message'] = 'The Settings has been saved successfully'; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = isset($this->PreparedTemplates['_error'])? $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]):''; break;
		}
		if (!empty($this->LocalTarget[3])) {
			switch ($this->LocalTarget[3]) {
				case 'saved': $this->TempFillEls['action_message'] = 'The Settings has been saved successfully';break;
				case 'deleted': $this->TempFillEls['action_message'] = 'The Settings has been deleted successfully';break;
			}
		}
		
	}

}
?>