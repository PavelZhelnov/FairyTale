<?php

class TrackingView extends Slot {

	public $ModuleID = 11;
	public $SectionID = 31;
	public $Task = 'view';

	function TrackingView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}
		
	function init() {
		global $PHP_SELF;
		if ($this->Scheme == 'preview') return;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme!='preview' && $this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				default:		
					$this->Scheme = 'default';
					$this->Task = 'viewinfo';
					$request['langid']=$this->LM->Langs[$this->language];					
					//$this->Action->processEvent($this->SectionID,'viewinfo',$request,$this);
					//if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
					 //else {$this->getPageControl($this->Home.'/Admin/AdminQuotation/'.(!empty($this->LocalTarget[1])?$this->LocalTarget[1]:0),0);}
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'view':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'getinfo',$this->correctWords($this->getRequestField('form')),$this)
						and $this->Scheme='view';
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
			case 'view':
				//if(!is_FullText($this->Request['form']['service'],1,3)) $this->errors['service'] = $this->globalLangContent['error_view']['err_name'];
				if(!empty($this->Request['form']['trackingnum']) && (!is_AlphaNumDefis($this->Request['form']['trackingnum'],1,11) || strlen($this->Request['form']['trackingnum'])<11)) $this->errors['trackingnum'] = $this->globalLangContent['error_view']['err_container_number'];
				if(!empty($this->Request['form']['presence']) && (!is_AlphaNumDefis($this->Request['form']['presence'],1,11) || strlen($this->Request['form']['presence'])<11)) $this->errors['presence'] = $this->globalLangContent['error_view']['err_container_number'];
				if(empty($this->Request['form']['trackingnum']) && empty($this->Request['form']['presence'])) $this->errors['trackingnum'] = $this->globalLangContent['error_view']['err_container_number'];
				if (is_FullText($this->Request['form']['presence'],1,11)) {
					$this->Request['form']['id']='15';
					$this->Request['form']['trackingnum'] = $this->Request['form']['presence'];
				}

			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'view': $this->fillInfo(); break;
			case 'preview': case 'empty': case 'default': $this->fillDefault(); break;			
		}
	}

	function fillInfo() {
		$info = (!empty($this->PreparedTemplates['info'])?$this->PreparedTemplates['info']:'');
		$pres = (!empty($this->PreparedTemplates['pres'])?$this->globalLangContent['label'][$this->PreparedTemplates['pres']]:'');
		$siteurl = $this->PreparedTemplates['siteurl'];
		$this->fillDefault();
		$info = trim($info, "\r\n\t .");
		//echo "=".$info.'=';
		if ($info=='' && $pres=='') {
			$info = $this->globalLangContent['label']['no_data_for_container'];
		}
		$this->TempFillEls['info']= $info;
		$this->TempFillEls['pres']= $pres;
		$this->TempFillEls['siteurl'] = $siteurl;
	}

	function fillDefault() {
		global $PHP_SELF;
		$this->Action->processEvent($this->SectionID,'services',array(),$this);
		$this->services = $this->Action->getTemplate($this->SectionID,'services');
		$trackings = array();
		$siteurls = array();
		foreach ($this->services as $k=>$v) {
			$trackings[$v['id']] = $v['trackingname'];
			$siteurls[$v['id']] = $v['siteurl'];
		}
		$this->TempFillEls = array(
			'service' => inputSelect('form[id]',$trackings,(isset($this->Request['form'])?$this->Request['form']['id']:0),' style=\'width:150px\' onchange=\'changeSiteUrl()\''),
			//'siteurls' => $siteurls,
			'trackingnum' => inputText('form[trackingnum]',(!empty($this->Request['form']['trackingnum'])?$this->Request['form']['trackingnum']:'')),
			'presencenum' => inputText('form[presence]',''),
			'texttrnum' => !empty($this->Request['form']['trackingnum'])?$this->Request['form']['trackingnum']:  (!empty($this->Request['form']['presence'])?$this->Request['form']['presence']:''),
		);
		foreach ($this->services as $k=>$v) {
			$this->TempFillEls['SiteUrls'][$k] = array(
				'name' => $v['showurl']==1? $v['siteurl']:'',
				'id' => $v['id'],
			);
		}
		
		//printArray($this->TempFillEls);
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