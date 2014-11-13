<?php

class AdminPagesView extends Slot {

	public $ModuleID = 51;
	public $SectionID = 15;
	public $Task = 'view';
	public $orderby = array(
		'Date' => array(
			'sortColumn' => 'date',
			'sortType' => 'desc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	public $imagePath;
	
	function AdminPagesView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImagePath'];
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				case 'EditPage':
					if (isset($this->LocalTarget[2])) {
						$this->Scheme = 'action';
						$this->Task = 'view';
						$request['langid']=$this->LM->Langs[$this->language];
						$this->Action->processEvent($this->SectionID,'edit',array('id' => $this->LocalTarget[2]),$this);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					} else
					if(empty($this->PreparedTemplates['curPage'])) header("Location: ".$this->Home.'AdminPages');
				break;
				case 'DeletePage':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'action';
						$this->Task="view";
						$this->Action->processEvent($this->SectionID,'edit',array('id' => $this->LocalTarget[2]),$this);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					}					
					else header("Location: ".$this->Home.'AdminPages');
				break;
				default:
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) $this->Scheme = 'empty';
				break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'edit': case 'add':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'update',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'AdminPages');
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'delete':
						$this->Scheme="delete";
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'delete',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$this->Home.'AdminPages');
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
			case 'edit' : case 'add':
				if(!_is_valid($this->Request['form']['name'],1,50, "[a-zA-Z]+")) $this->errors['name'] = $this->globalLangContent['error_view']['err_name'];
				//if(!is_FullText($this->Request['form']['name_langs']['1']['header'],1,255)) $this->errors['rusheader'] = $this->globalLangContent['error_view']['err_header'];
				if(!is_FullText($this->Request['form']['name_langs']['0']['header'],1,255)) $this->errors['engheader'] = $this->globalLangContent['error_view']['err_header'];
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {		
		switch($this->Scheme) {			
			case 'save': case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'action': $this->fillActionPage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'default': case 'view': $this->fillView(); break;			
		}
	}

	function fillView() {
		foreach($this->PreparedTemplates['curPage'] as $key => $value) {
			$this->TempFillEls['pages'][$value['textid']] = array(
				'textid' => $value['textid'],
				'textname' => $value['textname'],
				'textheader' => $value['theader'],
			);
		}
		$this->TempFillEls['item_langs1'] = inputHidden('form[name_langs][0][language]',1);
		$this->TempFillEls['item_langs2'] = inputHidden('form[name_langs][1][language]',2);
		$this->TempFillEls['eng_text'] = inputTextArea('form[name_langs][0][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['value'] : ''),$this->correctSize('120'), $this->correctSize('25'));
		//$this->TempFillEls['rus_text'] = inputTextArea('form[name_langs][1][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['value'] : ''),$this->correctSize('50'), $this->correctSize('25'));
		$this->TempFillEls['name'] = inputText('form[name]',(!empty($this->Request)? $this->Request['form']['name'] : ''),$this->correctSize('50'));
		$this->TempFillEls['eng_header'] = inputText('form[name_langs][0][header]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['header'] : ''),$this->correctSize('80'));
		//$this->TempFillEls['rus_header'] = inputText('form[name_langs][1][header]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['header'] : ''),$this->correctSize('50'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillActionPage() {
		global $PHP_SELF;
		$action = ($this->LocalTarget[1]=="DeletePage"?'delete':'edit');
		$this->TempFillEls = array(
			'action' => $action,
			'item_langs1' => inputHidden('form[name_langs][0][language]',1),
			'item_langs2' => inputHidden('form[name_langs][1][language]',2),
			'idn' => $this->PreparedTemplates['curPage'][0]['textid'],
			'pagename' => $this->PreparedTemplates['curPage'][$this->LM->Langs[$this->language]-1]['theader'],
			'id' => inputHidden('form[id]',(!empty($this->Request)? $this->getRequestFormField('id') : $this->PreparedTemplates['curPage'][0]['textid'])),			
			'eng_text' => ($action=='delete'?'':inputTextArea('form[name_langs][0][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['value'] : $this->PreparedTemplates['curPage'][0]['tvalue']),$this->correctSize('150'), $this->correctSize('25'))),
			//'rus_text' => ($action=='delete'?'':inputTextArea('form[name_langs][1][value]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['value'] : $this->PreparedTemplates['curPage'][1]['tvalue']),$this->correctSize('50'), $this->correctSize('25'))),
			'name' => ($action=='delete'?$this->PreparedTemplates['curPage'][0]['textname']:inputText('form[name]',(!empty($this->Request)? $this->Request['form']['name'] : $this->PreparedTemplates['curPage'][0]['textname']),$this->correctSize('70'),' readonly="false" ')),
			'eng_header' => ($action=='delete'?$this->PreparedTemplates['curPage'][0]['theader']:inputText('form[name_langs][0][header]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['header'] : $this->PreparedTemplates['curPage'][0]['theader']),$this->correctSize('50'))),
			//'rus_header' => ($action=='delete'?$this->PreparedTemplates['curPage'][1]['theader']: inputText('form[name_langs][1][header]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['header'] : $this->PreparedTemplates['curPage'][1]['theader']),$this->correctSize('50'))),
			'actionbutton' => ($action=='delete'?$this->globalLangContent['button']['admin_bt_delete']:$this->globalLangContent['button']['admin_bt_update']),
		);
		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,'save');
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'save');
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'page');
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