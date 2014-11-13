<?php

class StatisticView extends Slot {

	public $ModuleID = 11;
	public $SectionID = 26;
	public $Task = 'view';
	public $lgroup;

	function StatisticView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->lgroup = (isset($REGISTRY['Request']['LocalTarget'][1])?$REGISTRY['Request']['LocalTarget'][1]:'1');
	}
		
	function init() {
		global $PHP_SELF;		

		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete' && $this->Scheme!='closed') {
		$this->curPageNumber = empty($this->LocalTarget[0]) || !validate(intval($this->LocalTarget[0]))? 0 : intval($this->LocalTarget[0]);
			if (!$this->Action->isAuthorizeUserForModule($this->ModuleID)) {$this->Scheme = 'empty';} else
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
		$props=0; $people = 0; $mlss = 0; $tasks = 0;
		foreach ($this->PreparedTemplates['properties'] as $k=>$v) {
			$this->TempFillEls['statuses'][] = array(
				'name' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewByStatus/'.$v['status'], $v['name'].' Listing',array()),
				'qty' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewByStatus/'.$v['status'], ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $props = $props + $v['qty'];	
		}
		foreach ($this->PreparedTemplates['mlss'] as $k=>$v) {
			$this->TempFillEls['mlss'][] = array(
				'name' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewByStatus/'.$v['status'], $v['name'].' Listing',array()),
				'qty' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewByStatus/'.$v['status'], ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $mlss = $mlss + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['people'] as $k=>$v) {
			$this->TempFillEls['peoples'][] = array(			
				'name' => ($v['id']>3?makeLink($this->Home.'/'.$this->lgroup.'/Register/Proprietors/', $v['name'],array()):$v['name']),
				'qty' => ($v['id']>3?makeLink($this->Home.'/'.$this->lgroup.'/Register/Proprietors/', ' '.$v['qty'].' ',array()):' '.$v['qty'].' '),
			);
			if (!empty($v['qty'])) $people = $people + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['duetasks'] as $k=>$v) {
			$this->TempFillEls['duetasks'][] = array(
				'name' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewTasks/', $v['name'],array()),
				'qty' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewTasks/', ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $tasks = $tasks + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['overduetasks'] as $k=>$v) {
			$this->TempFillEls['overduetasks'][] = array(
				'name' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewTasks/', $v['name'],array()),
				'qty' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewTasks/', ' '.$v['qty'],array()),
			);
			if (!empty($v['qty'])) $tasks = $tasks + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['notes'] as $k=>$v) {
			$this->TempFillEls['notes'][] = array(
				'name' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewNotes/', $v['name'],array()),
				'qty' => makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/ViewNotes/', ' '.$v['qty'].' ',array()),
			);
			if (!empty($v['qty'])) $tasks = $tasks + $v['qty'];
		}

		$this->TempFillEls['lgroup'] = $this->lgroup;
		$this->TempFillEls['properties'] = makeLink($this->Home.'/'.$this->lgroup.'/ListingAgent/', ' '.$props.' ',array());
		$this->TempFillEls['mls'] = ' '.$mlss.' ';
		$this->TempFillEls['people'] = ' '.$people.' ';
		$this->TempFillEls['tasks'] = ' '.$tasks.' ';
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