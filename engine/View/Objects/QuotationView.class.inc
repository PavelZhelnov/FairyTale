<?php

class QuotationView extends Slot {

	public $ModuleID = 101;
	public $SectionID = 101;
	public $Task = 'view';
	public $orderby = array(
		'Id' => array(
			'sortColumn' => 'id',
			'sortType' => 'asc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	public $imagePath ='';
	public $serviceinfo = array();

	function QuotationView($pquery) {
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
		$request['scheme']=$this->Scheme;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Task = 'getquotes';				
		$this->sortby = 'Id';
		$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
		$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
		$request['langid']=$this->LM->Langs[$this->language];		
		$this->Action->processEvent($this->SectionID,'view',$request,$this);
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'default': $this->fillView(); break;
		}
	}

	function fillView() {
		$num=rand(0,sizeof($this->PreparedTemplates['curPage'])-1);
		$this->TempFillEls = array(
			'id' => $this->PreparedTemplates['curPage'][$num]['id'],
			'value' => $this->getWordWrap($this->PreparedTemplates['curPage'][$num]['value'], 30, " "),
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