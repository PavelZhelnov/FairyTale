<?php

class GlobalSystemSettingsView extends Slot {

	public $ModuleID = 103;
	public $SectionID = 103;
	public $Task = 'open';
	public $gss;

    const HOME_URL = '/Admin/GlobalSystemSettings/';
	
	function GlobalSystemSettingsView($pquery) {
		global $REGISTRY;
        $this->handleModel = 'Global_System_Settings';
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
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
					$this->Action->processEvent($this->SectionID,'list',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
				break;
			}
				
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'update':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'update',$this->getRequestField('form'),$this) and
						header("Location: ".$this->Home.self::HOME_URL.'//saved');
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
			case 'update' :
                $this->errors = $this->validateByModel($this->handleModel,$this->Request['form'], array());
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
        $this->fillMessage();
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': $this->fillMessage(); break;
			case 'action': $this->fillActionPage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'default': default: $this->fillSettingList(); break;
		}
	}
	
	function fillSettingList() {
		$num=1;
		if (!empty($this->PreparedTemplates['curPage'])) {
			foreach($this->PreparedTemplates['curPage'] as $key => $value) {
				$this->TempFillEls['list'][$value['id']] = array(
					'id' => $value['id'],
                    'setting_name' => $value['setting_name'],
					'num' => $num++,
				);
			}
		}
        $this->TempFillEls['popupmenu'][] = $this->fillPopUpMenu();
		$this->fillMessage();
	}

    function fillPopUpMenu() {
        $perm = $this->Action->Security->getPermissionInfoForModule($this->ModuleID, $this->Action->Security->currentuser->level->id);
        $num1=0;$num2=0;
        $pop = array(
            'pop1' => array(
                $num1++ => ($perm>0?array('action' => $this->Home.self::HOME_URL.'edit/*1', 'button'=>'Edit Settings', 'target'=>''):null),
            ),
        );
        $pop = removeNullValuesFromArray($pop);
        return $pop;
    }

	function fillActionPage() {
		global $PHP_SELF;
		$this->Action->processEvent($this->SectionID,'members',array(),$this);

        $this->prepareEditForm("edit");

	}

    function prepareEditForm($action) {
        $tempFillEls = $this->fillModel($this->handleModel,
            $this->gss,
            $action,
            $selectArrays = array()
        );

        $this->TempFillEls['Edit'][] = $tempFillEls;

    }



    function fillMessage() {
        switch($this->Scheme) {
            default: $this->TempFillEls['message'] = isset($this->PreparedTemplates['_error'])? $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]):''; break;
        }
        if (!empty($this->LocalTarget[1])) {
			switch ($this->LocalTarget[1]) {
				case 'saved': $this->TempFillEls['action_message'] = 'The Settings has been saved successfully';break;
				case 'deleted': $this->TempFillEls['action_message'] = 'The Settings has been deleted successfully';break;
			}
		}
		
	}

}
?>