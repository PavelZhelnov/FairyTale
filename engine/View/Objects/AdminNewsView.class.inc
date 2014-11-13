<?php

class AdminNewsView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 16;
	public $Task = 'view';
	public $orderby = array(
		'Date' => array(
			'sortColumn' => 'pubdate',
			'sortType' => 'desc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	
	function AdminNewsView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				case 'EditNews': case 'DeleteNews':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'action';
						$this->Task = 'edit';
						$this->Action->processEvent($this->SectionID,'edit',array('id' => intval($this->LocalTarget[2]), 'langid' => $this->LM->Langs[$this->language]),$this);
						if(empty($this->PreparedTemplates['curPage'])) 
						{
							header("Location: ".$this->Home.'/Admin/AdminNews'.$this->SID);
						}
					}
					else header("Location: ".$this->Home.'/Admin/AdminNews'.$this->SID);
				break;
				default:					
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request = array('pageRecordsQty'=>'5','curPageNumber'=>(isset($this->LocalTarget[2])? $this->LocalTarget[2]+1 : 1));
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'Date';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];					
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
					 else {$this->getPageControl($this->Home.'/Admin/AdminNews/'.(!empty($this->LocalTarget[1])?$this->LocalTarget[1]:0),0);}
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'add':	case 'edit':				
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'save',$this->correctWords($this->getRequestField('form')),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'/Admin/AdminNews'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'delete':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'delete',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$this->Home.'/Admin/AdminNews'.$this->SID);
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
			case 'add': case 'edit':
				if(!is_FullText($this->Request['form']['name_langs']['0']['header'],1,255)) $this->errors['header1'] = $this->globalLangContent['error_view']['err_news_header'];
				if(!is_FullText($this->Request['form']['name_langs']['1']['header'],1,255)) $this->errors['header2'] = $this->globalLangContent['error_view']['err_news_header'];
				if(!is_FullText($this->Request['form']['name_langs']['0']['description'],1,31255)) $this->errors['descr1'] = $this->globalLangContent['error_view']['err_news_descr'];
				if(!is_FullText($this->Request['form']['name_langs']['1']['description'],1,31255)) $this->errors['descr2'] = $this->globalLangContent['error_view']['err_news_descr'];
			break;

		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'action': $this->fillAction(); break;
			case 'empty': case 'default': case 'view': $this->fillView(); break;			
		}
	}

	function fillView() {
		foreach($this->PreparedTemplates['curPage'] as $key => $value) {
			$this->TempFillEls['news'][$value['newsid']] = array(
				'newsid' => $value['newsid'],
				'newstext' =>  substr($this->getWordWrap($value['ndescription'], 30, " "), 0, 200),
				'newsheader' => $this->getWordWrap($value['nheader'], 30, " "),
				'newsdate' => $value['publicatedate'],
			);
		}		
		$this->TempFillEls['eng_header'] = inputText('form[name_langs][0][header]',(!empty($this->Request['form']['name_langs'])? $this->Request['form']['name_langs']['0']['header'] : ''),$this->correctSize('70'));		
		$this->TempFillEls['rus_header'] = inputText('form[name_langs][1][header]',(!empty($this->Request['form']['name_langs'])? $this->Request['form']['name_langs']['1']['header'] : ''),$this->correctSize('70'));
		$this->TempFillEls['eng_description'] = inputTextArea('form[name_langs][0][description]',(!empty($this->Request['form']['name_langs'])? $this->Request['form']['name_langs']['0']['description'] : ''),$this->correctSize('70'), $this->correctSize('10'));
		$this->TempFillEls['rus_description'] = inputTextArea('form[name_langs][1][description]',(!empty($this->Request['form']['name_langs'])? $this->Request['form']['name_langs']['1']['description'] : ''),$this->correctSize('70'), $this->correctSize('10'));
		$this->TempFillEls['item_langs1'] = inputHidden('form[name_langs][0][language]',1);
		$this->TempFillEls['item_langs2'] = inputHidden('form[name_langs][1][language]',2);
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'viewnews');
	}

	function fillAction() {
		global $PHP_SELF;
		$action = ($this->LocalTarget[1]=='DeleteNews'?'delete':'edit');
		$this->TempFillEls = array(
			'item_langs1' => inputHidden('form[name_langs][0][language]',1),
			'item_langs2' => inputHidden('form[name_langs][1][language]',2),
			'id' => $action=='Add'? '' : $this->PreparedTemplates['id'],
			'action' => $action,
			'actionbutton' => ($action == 'delete'? $this->globalLangContent['button']['admin_bt_delete'] : $this->globalLangContent['button']['admin_bt_update']),
			'eng_header' => $action == 'delete'? $this->PreparedTemplates['curPage'][0]['nheader'] : inputText('form[name_langs][0][header]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['header'] : $this->PreparedTemplates['curPage'][0]['nheader']),$this->correctSize('70')),
			'rus_header' => $action == 'delete'? $this->PreparedTemplates['curPage'][1]['nheader'] : inputText('form[name_langs][1][header]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['header'] : $this->PreparedTemplates['curPage'][1]['nheader']),$this->correctSize('70')),
			'eng_description' => $action == 'delete'? $this->PreparedTemplates['curPage'][0]['ndescription'] : inputTextArea('form[name_langs][0][description]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['description'] : $this->PreparedTemplates['curPage'][0]['ndescription']),$this->correctSize('70'),$this->correctSize('10')),
			'rus_description' => $action == 'delete'? $this->PreparedTemplates['curPage'][1]['ndescription'] : inputTextArea('form[name_langs][1][description]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['description'] : $this->PreparedTemplates['curPage'][1]['ndescription']),$this->correctSize('70'),$this->correctSize('10')),
		);
		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
	}

	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_news']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_news']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->globalLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); 
				 break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>
