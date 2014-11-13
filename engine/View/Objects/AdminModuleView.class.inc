<?php

class AdminModuleView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 24;
	public $search_params;
	public $amount = array('10' => '10', '50' => '50', '100' => '100');

	function AdminModuleView($pquery) {
		$this->Slot($pquery);
	}

	function init() {
		$this->Action->processEvent($this->SectionID,'modules',array(),$this);
		$this->Action->processEvent($this->SectionID,'get_search',$this->getRequestField('form'),$this);
		$this->search_params = $this->PreparedTemplates; 
		switch(@$this->LocalTarget[1]) {
			case 'Edit':
				if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
					$this->Action->processEvent($this->SectionID,'open',array('id' => intval($this->LocalTarget[2])),$this);
					$this->Scheme = 'action';
				}
				else header("Location: ".$this->Home.'/Admin/LanguageAdmin'.$this->SID);
			break;
			case 'Add': $this->Scheme = 'action'; break;
			case 'View':
				$this->curPageNumber = empty($this->LocalTarget[2]) || !validate(intval($this->LocalTarget[2]))? 0 : intval($this->LocalTarget[2]);
				$this->Action->processEvent($this->SectionID,'select',array('pageRecordsQty' => '100','curPageNumber' => $this->curPageNumber+1),$this);
				$this->getPageControl($this->Home.'/Admin/AdminModule/View');
				$this->Scheme = 'viewmodule';
			break;
			case 'ViewModule':
				$this->Request['form']['module'] = (isset($this->LocalTarget[2])? array(0=>$this->LocalTarget[2]):array())
				and $this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
				and header("Location: ".$this->Home.'/Admin/AdminModule/View'.$this->SID);
			break;
			default:
				$request['lang'] = $this->LM->Langs[$this->language];
				$this->Action->processEvent($this->SectionID,'getmodules',$request,$this);
				$this->Scheme = 'default';
			break;
		}
		if(!empty($this->Request)) {
			switch($this->getRequestField('step')) {
				case 'Save':
					$this->Action->isAuthorizeAdmin() and $this->Action->processEvent($this->SectionID,'save',$this->getRequestField('form'),$this)
					and header("Location: ".$this->Home.'/Admin/AdminModule/View'.$this->SID);
				break;
				case 'search':
					$this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
					and header("Location: ".$this->Home.'/Admin/AdminModule/View/');
				break;
			}
		}
		$this->setSchemeTemplate($this->Scheme);
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'action': $this->fillAction(); break;
			case 'viewmodule': $this->fillViewModule(); break;
			default: $this->fillDefault(); break;
		}
	}

	function fillViewModule() {
		//printArray($this->LM->Langs);
		//echo $this->language;
		//printArray($this->PreparedTemplates);

		$this->modules = mergeArrays(array(0=>'All Modules'),$this->Action->getTemplate($this->SectionID,'modules'));

		//$this->TempFillEls['amount'] = inputSelect('form[amount]',$this->amount,(!empty($this->search_params['amount'])? $this->search_params['amount'] : 100));
		//$this->TempFillEls['public '] = inputText('form[public ]',(!empty($this->search_params['public '])? $this->search_params['public '] : ''),$this->correctSize('10'));
		//$this->TempFillEls['module'] = inputSelect('form[module][]',$this->modules,(!empty($this->search_params['module'])? $this->search_params['module'] : 0),' size=1');

		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,'select');
		foreach($this->PreparedTemplates['curPage'] as $key => $value)
			$this->TempFillEls['items'][] = array(
				'id' => makeLink($this->Home.'/Admin/AdminModule/Edit/'.$value['id'],$value['id']),
				'module' => $value['module_name'],
				'name' => makeLink($this->Home.'/Admin/AdminModule/Edit/'.$value['id'],$value['name']),
				'value' => $value['value'],
				'bgcolor' => $key%2? '#FFFFFF' : '#F0F0FF',
			);
	}

	function fillDefault() {
		$this->modules = mergeArrays(array(0=>'All Modules'),$this->Action->getTemplate($this->SectionID,'modules'));

		//$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,'select');
		$this->TempFillEls['amount'] = inputSelect('form[amount]',$this->amount,(!empty($this->search_params['amount'])? $this->search_params['amount'] : 100));
		//$this->TempFillEls['public '] = inputText('form[public ]',(!empty($this->search_params['public '])? $this->search_params['public '] : ''),$this->correctSize('10'));
		//$this->TempFillEls['type'] = inputSelect('form[type][]',$this->types,(!empty($this->search_params['type'])? $this->search_params['type'] : 0),' size=1');
		//$this->TempFillEls['module'] = inputSelect('form[module][]',$this->modules,(!empty($this->search_params['module'])? $this->search_params['module'] : 0),' size=1');

		foreach($this->PreparedTemplates['curPage'] as $key => $value)
			$this->TempFillEls['modules'][] = array(
				'id' => makeLink($this->Home.'/Admin/AdminModule/ViewModule/'.$value['id'],$value['id']),
				'path' => $value['path'],
				'modulename' => makeLink($this->Home.'/Admin/AdminModule/ViewModule/'.$value['id'],$value['modulename']),
				'msid' => $value['msid'],
				'bgcolor' => $key%2? '#FFFFFF' : '#F0F0FF',
			);

	}

	function fillAction() {
		global $PHP_SELF;
		$action = $this->LocalTarget[0];
		$this->modules = $this->Action->getTemplate($this->SectionID,'modules');
		if($action!='Add') $this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,'open');
		$this->TempFillEls = array(
			'formaction' => $PHP_SELF,
			'id' => @$this->PreparedTemplates['id'],
			'name' => @$this->PreparedTemplates['name'],
			'module' => inputSelect('form[module]',$this->modules,(!empty($this->Request)? $this->getRequestFormField('module') : @$this->PreparedTemplates['module'])),
		);
		if (isset($this->PreparedTemplates['value'])) {
			if ($this->PreparedTemplates['value']=='TRUE' || $this->PreparedTemplates['value']=='FALSE') 
			{
				$this->TempFillEls['value'] = inputCheckbox('form[value]',(!empty($this->Request)? ($this->getRequestFormField('value')=='TRUE'?true:false) : ($this->PreparedTemplates['value']=='TRUE'?true:false) ),'','TRUE');
				$this->TempFillEls['valuehidd'] = inputHidden('form[value]', 'FALSE');
			} else 
			{
				$this->TempFillEls['value'] = inputText('form[value]',(!empty($this->Request)? $this->getRequestFormField('value') : @$this->PreparedTemplates['value']),$this->correctSize('38'));
			}
		} else 
		$this->TempFillEls['value'] = inputText('form[value]',(!empty($this->Request)? $this->getRequestFormField('value') : @$this->PreparedTemplates['value']),$this->correctSize('38'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = 'There were some errors. Please see below for details';
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'save');
	}


	function getItemLang($lang) {
		foreach ($this->PreparedTemplates['item_langs'] as $k=>$v) {
			if ($v['language'] == $lang) return $v['value'];
		}
		return '';
	}
}
?>