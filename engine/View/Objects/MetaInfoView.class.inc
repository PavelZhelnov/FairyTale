<?php

class MetaInfoView extends Slot {
	public $ModuleID = 6;
	public $SectionID = 8;
	public $Task = 'view';
	public $url = '';
	public $imagePath='';
	public $imageWPath='';
	public $image_type;
	

	function MetaInfoView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
		$this->serviceinfo = array(
			'hostname' => $REGISTRY['Core']['HostName'].$REGISTRY['Core']['WebHome'],
			'frommail' => $this->fromMail = $REGISTRY['Core']['frommail'],
			'sitename' => $REGISTRY['Core']['SiteName'],
			);
	}
		
	function init() {
		global $PHP_SELF;
		$request['url'] = (!empty($this->LocalTarget[0])?$this->LocalTarget[0]:'home');
		$request['langid']=$this->LM->Langs[$this->language];		
		$this->Action->processEvent($this->SectionID,'getmeta',$request,$this);
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'default': case 'keywords':$this->fillViewKeywords(); break;
			case 'description': $this->fillViewDescription(); break;
			case 'title': $this->fillViewTitle(); break;
		}
	}
	
	function fillViewDescription() {
		$desc = 'Fairy Tale';
		
		$this->TempFillEls = array(
			'value' => $desc,
		);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}


	function fillViewKeywords() {
		$key = 'Fairy Tale';

		if (!empty($this->PreparedTemplates['keywords'])) {
			$key = $this->PreparedTemplates['keywords'];
		}
		$this->TempFillEls = array(
			//'id' => $this->PreparedTemplates['curPage'][$num]['id'],
			'value' => $key,
		);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}
	
	function fillViewTitle() {
		$title = 'Fairy Tale';

		if (!empty($this->PreparedTemplates['title'])) {
			$title = 'Fairy Tale - '.$this->PreparedTemplates['title'];
		}
			
		$this->TempFillEls = array(
			//'id' => $this->PreparedTemplates['curPage'][$num]['id'],
			'value' => $title,
		);
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
