<?php

class ThingsView extends Slot {

	public $ModuleID = 5;
	public $SectionID = 5;
	public $Task = 'view';
	public $orderby = array(
		'Date' => array(
			'sortColumn' => 'pubdate',
			'sortType' => 'desc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	public $modulesettings = array();
	public $showphotos = true;
	
	function ThingsView($pquery) {
		global $REGISTRY;
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
		$this->Slot($pquery);
	}
		
	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Action->processEvent($this->SectionID,'settings',array('moduleid' => $this->ModuleID),$this);
		$this->modulesettings = $this->PreparedTemplates;
		/*foreach ($this->modulesettings['settings'] as $k => $v) {
			if ($v['paramid']=='1' && $v['value']=='TRUE')
				$this->showphotos = true; else $this->showphotos = false;
		}*/

		if($this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete') {
				$this->curPageNumber = empty($this->LocalTarget[0]) || !validate(intval($this->LocalTarget[0]))? 0 : intval($this->LocalTarget[0]);
				switch(@$this->LocalTarget[0]) {
				case 'onlinerequest':
					$this->Scheme = 'request';
					//$this->Action->processEvent($this->SectionID,'getcontactlists',array('conditions'=>array('langid'=>$this->LM->Langs[$this->language])),$this);
				break;
				case 'vacancy':
					$this->Scheme = 'vacancy';
				break;
				
				default:
					$this->Scheme = 'default';
					$this->Task = 'view';
				break;
				}
				if(!empty($this->Request)) {
					switch($this->getRequestField('step')) {
						case 'auth':
							$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
							header("Location: ".$PHP_SELF.$this->SID);
						break;
						case 'sendonlinerequest':
							$request=$this->correctWords($this->getRequestField('form'));
							$request['langid']=$this->LM->Langs[$this->language];
							$this->containertype = mergeArrays(array('0' => ' --- No Container Type --- '),$this->Action->Server->getGuide('containertype'));
							$this->country = mergeArrays(array('0' => ' --- No Country --- '),$this->Action->Server->getGuide('country'));
							$request['containertype_str'] = $this->containertype[$request['containertype']];
							$request['country_str'] = $this->country[$request['country']];
							$request['sourcecountry_str'] = $this->country[$request['sourcecountry']];
							$request['destinationcountry_str'] = $this->country[$request['destinationcountry']];
							$this->validateForm() and $this->Action->processEvent($this->SectionID,'sendonlinerequest',$request,$this) and
							$this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
							if(!empty($this->PreparedTemplates['_error'])) {$this->Scheme = 'message'; }
						break;
						
						case 'sendvacancy':
							$request=$this->correctWords($this->getRequestField('form'));
							$request['langid']=$this->LM->Langs[$this->language];
  						$this->month = mergeArrays(array('0' => ' --- No Month --- '),$this->Action->Server->getGuide('month'));
  						$this->education = mergeArrays(array('0' => ' --- No Education --- '),$this->Action->Server->getGuide('education'));
  						$this->edform = mergeArrays(array('0' => ' --- No Education Form --- '),$this->Action->Server->getGuide('edform'));
  						$this->gender = mergeArrays(array('0' => ' --- No Gender --- '),$this->Action->Server->getGuide('gender'));
							$this->rank_pc = mergeArrays(array('0' => ' --- No Pc knowledge --- '),$this->Action->Server->getGuide('rank'));
							$this->rank_en = mergeArrays(array('0' => ' --- No English knowledge --- '),$this->Action->Server->getGuide('rank'));

							//$request['monnth_str'] = $this->month[$request['month']];
							$request['gender_str'] = $this->gender[$request['gender']];
							$request['rank_pc_str'] = $this->rank_pc[$request['pc_knowledge']];
							$request['rank_en_str'] = $this->rank_en[$request['english_knowledge']];
							$request['education1_str'] = $this->education[$request['education1']];
							$request['edform1_str'] = $this->edform[$request['edform1']];
							$request['education2_str'] = $this->education[$request['education2']];
							$request['edform2_str'] = $this->edform[$request['edform2']];							
							//$request['month_str'] = $this->month[$request['month']];
							
							$this->validateForm() and $this->Action->processEvent($this->SectionID,'sendvacancy',$request,$this) and
							$this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
							if(!empty($this->PreparedTemplates['_error'])) {$this->Scheme = 'message'; }
						break;
					}
				}
		}
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('username'),3,32)) $this->errors['username'] = $this->globalLangContent['error_view']['err_admin_email'];
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
			case 'sendonlinerequest':
				if(!is_FullText($this->getRequestFormField('contactname'),0,1024)) $this->errors['contactname'] = $this->globalLangContent['error_view']['err_firstname'];
				if(!is_FullText($this->getRequestFormField('company'),0,1024)) $this->errors['company'] = $this->globalLangContent['error_view']['err_firstname'];
				if(!is_FullText($this->getRequestFormField('phone'),0,1024)) $this->errors['phone'] = $this->globalLangContent['error_view']['err_phone'];
				
				if(!is_Email($this->getRequestFormField('email'))) $this->errors['email'] = $this->globalLangContent['error_view']['err_email'];
			break;
			case 'sendvacancy':
				if(!is_FullText($this->getRequestFormField('contactname'),0,1024)) $this->errors['contactname'] = $this->globalLangContent['error_view']['err_firstname'];
				if(!is_FullText($this->getRequestFormField('phone'),0,1024)) $this->errors['phone'] = $this->globalLangContent['error_view']['err_phone'];
				if(!is_Email($this->getRequestFormField('email'))) $this->errors['email'] = $this->globalLangContent['error_view']['err_email'];
			break;
			
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'default': $this->fillText(); break;
			case 'request': $this->fillRequest(); break;
			case 'vacancy': $this->fillVacancy(); break;
			default: $this->fillText(); break;
		}
	}

  function fillRequest() {
  	$this->containertype = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['container_type'].' --- '),$this->Action->Server->getGuide('containertype'));
  	$this->country = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['contact_country'].' --- '),$this->Action->Server->getGuide('country'));
  	$this->TempFillEls = array(
  	  'contactname' => inputText('form[contactname]',(!empty($this->Request['form']['contactname'])? $this->getRequestFormField('contactname') : $this->globalLangContent['label']['contact_person']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['contact_person'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['contact_person'].'\')" style="height:20px;width:438px" '),
  	  'company' => inputText('form[company]',(!empty($this->Request['form']['company'])? $this->getRequestFormField('company') : $this->globalLangContent['label']['contact_company']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['contact_company'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['contact_company'].'\')" style="height:20px;width:438px" '),
  	  'phone' => inputText('form[phone]',(!empty($this->Request['form']['phone'])? $this->getRequestFormField('phone') : $this->globalLangContent['label']['contact_phone']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['contact_phone'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['contact_phone'].'\')" style="height:20px;width:438px" '),
  	  'email' => inputText('form[email]',(!empty($this->Request['form']['email'])? $this->getRequestFormField('email') : $this->globalLangContent['label']['contact_email']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['contact_email'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['contact_email'].'\')" style="height:20px;width:438px" '),
  	  'cargoinfo' => inputText('form[cargoinfo]',(!empty($this->Request['form']['cargoinfo'])? $this->getRequestFormField('cargoinfo') : $this->globalLangContent['label']['cargo_name']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['cargo_name'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['cargo_name'].'\')" style="height:20px;width:438px" '),
  	  'containersize' => inputText('form[containersize]',(!empty($this->Request['form']['containersize'])? $this->getRequestFormField('containersize') : $this->globalLangContent['label']['container_size']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['container_size'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['container_size'].'\')" style="height:20px;width:438px" '),
  	  'cargoweight' => inputText('form[cargoweight]',(!empty($this->Request['form']['cargoweight'])? $this->getRequestFormField('cargoweight') : $this->globalLangContent['label']['cargo_weight']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['cargo_weight'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['cargo_weight'].'\')" style="height:20px;width:438px" '),
  	  'containerqty' => inputText('form[containerqty]',(!empty($this->Request['form']['containerqty'])? $this->getRequestFormField('containerqty') : $this->globalLangContent['label']['container_qty']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['container_qty'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['container_qty'].'\')" style="height:20px;width:438px" '),

  	  'sourcecity' => inputText('form[sourcecity]',(!empty($this->Request['form']['sourcecity'])? $this->getRequestFormField('sourcecity') : $this->globalLangContent['label']['source_city']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['source_city'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['source_city'].'\')" style="height:20px;width:438px" '),
  	  'destinationcity' => inputText('form[destinationcity]',(!empty($this->Request['form']['destinationcity'])? $this->getRequestFormField('destinationcity') : $this->globalLangContent['label']['destination_city']),$this->correctSize('68'), ' onfocus="eraseRequest(this, \''.$this->globalLangContent['label']['destination_city'].'\');" onblur="showRequest(this,\''.$this->globalLangContent['label']['destination_city'].'\')" style="height:20px;width:438px" '),
  	  

  		'country' => inputSelect('form[country]',$this->country,(isset($this->Request['form'])?$this->Request['form']['country']: 0),' style=\'width:438px\';'), 
			'containertype' => inputSelect('form[containertype]',$this->containertype,(isset($this->Request['form'])?$this->Request['form']['containertype']: 0),' style=\'width:438px\';'), 
  		'sourcecountry' => inputSelect('form[sourcecountry]',$this->country,(isset($this->Request['form'])?$this->Request['form']['sourcecountry']: 0),' style=\'width:438\';'), 
  		'destinationcountry' => inputSelect('form[destinationcountry]',$this->country,(isset($this->Request['form'])?$this->Request['form']['destinationcountry']: 0),' style=\'width:438\';'), 
  		'additionalinfo' => inputTextArea('form[additionalinfo]',(!empty($this->Request)? $this->getRequestFormField('additionalinfo') : ''),$this->correctSize('45'), $this->correctSize(5)),
  		'country' => inputSelect('form[country]',$this->country,(isset($this->Request['form'])?$this->Request['form']['country']: 0),' style=\'width:438px\';'), 
			'containertype' => inputSelect('form[containertype]',$this->containertype,(isset($this->Request['form'])?$this->Request['form']['containertype']: 0),' style=\'width:438px\';'), 
  		//'sourcecountry' => inputSelect('form[sourcecountry]',$this->country,(isset($this->Request['form'])?$this->Request['form']['sourcecountry']: 0),' style=\'width:268px\';'), 
  		//'destinationcountry' => inputSelect('form[destinationcountry]',$this->country,(isset($this->Request['form'])?$this->Request['form']['destinationcountry']: 0),' style=\'width:268px\';'), 
  		//'additionalinfo' => inputTextArea('form[additionalinfo]',(!empty($this->Request)? $this->getRequestFormField('additionalinfo') : ''),$this->correctSize('45'), $this->correctSize(5)),
  		
  	);
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);		
		$this->fillText();
  }
  
  function fillVacancy() {
  	//$this->country = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['country'].' --- '),$this->Action->Server->getGuide('country'));
  	//$this->month = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['month'].' --- '),$this->Action->Server->getGuide('month'));
  	$this->education = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['education'].' --- '),$this->Action->Server->getGuide('education'));
  	$this->edform = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['education_form'].' --- '),$this->Action->Server->getGuide('edform'));
  	$this->gender = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['gender'].' --- '),$this->Action->Server->getGuide('gender'));
		$this->rank_pc = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['pc_knowledge'].' --- '),$this->Action->Server->getGuide('rank'));
		$this->rank_en = mergeArrays(array('0' => ' --- '.$this->globalLangContent['label']['english_knowledge'].' --- '),$this->Action->Server->getGuide('rank'));

  	for ($i=1920; $i<2006; $i++) {
  		$this->year[$i] = $i;
  	}
  	for ($i=1; $i<32; $i++) {
  		$this->day[$i] = $i;
  	}
  	
  	$this->TempFillEls = array(
  		'contactname' => inputText('form[contactname]',(!empty($this->Request['form']['contactname'])? $this->getRequestFormField('contactname') : $this->globalLangContent['label']['name_surname']),$this->correctSize('68'), ' onfocus="eraseVacancy(this, \''.$this->globalLangContent['label']['name_surname'].'\');" onblur="showVacancy(this, \''.$this->globalLangContent['label']['name_surname'].'\')" style="height:20px;width:438px;" '),
  		'birthday' => inputText('form[birthday]',(!empty($this->Request['form']['birthday'])? $this->getRequestFormField('birthday') : $this->globalLangContent['label']['birthday']),$this->correctSize('68'), ' onfocus="eraseVacancy(this, \''.$this->globalLangContent['label']['birthday'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['birthday'].'\')" style="height:20px;width:438px" '),
  		
  		'company' => inputText('form[company]',(!empty($this->Request)? $this->getRequestFormField('company') : ''),$this->correctSize('43')),
  		'city' => inputText('form[city]',(!empty($this->Request['form']['city'])? $this->getRequestFormField('city') : $this->globalLangContent['label']['habit_city']),$this->correctSize('68'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['habit_city'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['habit_city'].'\')" style="height:20px;width:438px" '),
  		'phone' => inputText('form[phone]',(!empty($this->Request['form']['phone'])? $this->getRequestFormField('phone') : $this->globalLangContent['label']['contact_phone']),$this->correctSize('68'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['contact_phone'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['contact_phone'].'\')" style="height:20px;width:438px" '),
  		'email' => inputText('form[email]',(!empty($this->Request)? $this->getRequestFormField('email') : $this->globalLangContent['label']['contact_email']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['contact_email'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['contact_email'].'\')" style="height:20px;width:438px" '),
  		'interesting_vacancy' => inputText('form[interesting_vacancy]',(!empty($this->Request)? $this->getRequestFormField('interesting_vacancy') : $this->globalLangContent['label']['interesting_vacancy']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['interesting_vacancy'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['interesting_vacancy'].'\')" style="height:20px;width:438px" '),
  		'institution_name1' => inputText('form[institution_name1]',(!empty($this->Request)? $this->getRequestFormField('institution_name1') : $this->globalLangContent['label']['university_name']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['university_name'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['university_name'].'\')" style="height:20px;width:438px" '),
  		'faculty1' => inputText('form[faculty1]',(!empty($this->Request)? $this->getRequestFormField('faculty1') : $this->globalLangContent['label']['faculty']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['faculty'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['faculty'].'\')" style="height:20px;width:438px" '),
  		'qualification1' => inputText('form[qualification1]',(!empty($this->Request)? $this->getRequestFormField('qualification1') : $this->globalLangContent['label']['qualification']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['qualification'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['qualification'].'\')" style="height:20px;width:438px" '),
  		'experience' => inputTextArea('form[experience]',(!empty($this->Request)? $this->getRequestFormField('experience') : ''),$this->correctSize('43'), $this->correctSize(5)),

			'education1' => inputSelect('form[education1]',$this->education,(isset($this->Request['form'])?$this->Request['form']['education1']: 0),' style=\'width:438px\';'), 
			'edform1' => inputSelect('form[edform1]',$this->edform,(isset($this->Request['form'])?$this->Request['form']['edform1']: 0),' style=\'width:438px\';'), 
			'education2' => inputSelect('form[education2]',$this->education,(isset($this->Request['form'])?$this->Request['form']['education2']: 0),' style=\'width:438px\';'), 
			'edform2' => inputSelect('form[edform2]',$this->edform,(isset($this->Request['form'])?$this->Request['form']['edform2']: 0),' style=\'width:438px\';'), 

  		'pc_knowledge' => inputSelect('form[pc_knowledge]',$this->rank_pc,(isset($this->Request['form'])?$this->Request['form']['pc_knowledge']: 0),' style=\'width:438px\';'), 
  		'english_knowledge' => inputSelect('form[english_knowledge]',$this->rank_en,(isset($this->Request['form'])?$this->Request['form']['english_knowledge']: 0),' style=\'width:438px\';'), 

  		'institution_name2' => inputText('form[institution_name2]',(!empty($this->Request)? $this->getRequestFormField('institution_name2') : $this->globalLangContent['label']['university_name']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['university_name'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['university_name'].'\')" style="height:20px;width:438px" '),
  		'faculty2' => inputText('form[faculty2]',(!empty($this->Request)? $this->getRequestFormField('faculty2') : $this->globalLangContent['label']['faculty']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['faculty'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['faculty'].'\')" style="height:20px;width:438px" '),
  		'qualification2' => inputText('form[qualification2]',(!empty($this->Request)? $this->getRequestFormField('qualification2') : $this->globalLangContent['label']['qualification']),$this->correctSize('43'), ' onfocus="eraseVacancy(this,\''.$this->globalLangContent['label']['qualification'].'\');" onblur="showVacancy(this,\''.$this->globalLangContent['label']['qualification'].'\')" style="height:20px;width:438px" '),

  		
			//'month' => inputSelect('form[month]',$this->month,(isset($this->Request['form'])?$this->Request['form']['month']: 0),' style=\'width:249px\';'), 
			//'year' => inputSelect('form[year]',$this->year,(isset($this->Request['form'])?$this->Request['form']['year']: 0),' style=\'width:90px\';'), 
			//'day' => inputSelect('form[day]',$this->day,(isset($this->Request['form'])?$this->Request['form']['day']: 0),' style=\'width:90px\';'), 

			'gender' => inputSelect('form[gender]',$this->gender,(isset($this->Request['form']['gender'])?$this->Request['form']['gender']: 0),' style=\'width:438px\';'), 
			
  	);
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);		
		$this->fillText();
  }
  
  
	function fillText() {
		
		$request['langid']=$this->LM->Langs[$this->language];
		$request['browsePage']=(!empty($this->LocalTarget[0])?$this->LocalTarget[0]:'Home');
		$request['imagePath']=$this->imagePath;
		$request['homePath']=$this->Home;
		$this->Action->processEvent($this->SectionID,'view',$request,$this);
		$this->TempFillEls['lang'] = $this->LM->Langs[$this->language];
		$this->TempFillEls['text'] = $this->PreparedTemplates['curPage'][0]['tvalue'];
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	} 
	

	function fillMessage() {
		switch($this->Scheme) {			
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['newsubscriber_info']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_info']; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>