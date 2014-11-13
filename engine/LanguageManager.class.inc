<?php

class LanguageManager extends RootRegistry {

	public $language;
	public $Langs = array();
	public $Modules = array();
	public $localContent;
	public $globalContent;

	public $DB;
	public $tables = array('contentitem as l','contentitem_lang as ll','contenttype as lt, module as m');
	public $fields = array('lt.name','l.var','ll.value');

	function LanguageManager($Langs = array(),$name = 'LanguageManager') {
		global $HOME_PATH,$DatabaseBroker;
		$this->RootRegistry($name);
		$this->language = $HOME_PATH;
		$this->DB = &$DatabaseBroker;
		count($Langs) and $this->Langs = $Langs;
		count($Langs) or $this->getLangs();
		$this->getModules();
		$this->mainContent();
	}

	function mainContent() {
		$conditions = array('l.id' => 'll.ownerid','l.module' => 1,'m.id' => 'l.module','ll.language' => $this->Langs[$this->language],'lt.id' => 'l.contenttype');
		$this->globalContent = $this->DB->SelectLang($this->tables,$this->fields,$conditions);
	}

	function moduleContent($module) {
		//if(isset($this->localContent[$module])) return $this->localContent[$module];
		$conditions = array('l.id' => 'll.ownerid','ll.language' => $this->Langs[$this->language],'lt.id' => 'l.contenttype','l.module' => $module,'m.id' => 'l.module');
		//$this->localContent[$module] = $this->DB->SelectLang($this->tables,$this->fields,$conditions);
		//return $this->localContent[$module];
		return $this->DB->SelectLang($this->tables,$this->fields,$conditions);
	}

	function getLangs() {
		$guide = $this->DB->SelectGuide('language');
		$this->Langs = getValuesToKeys($guide);
	}

	function getModules() {
		$conditions = array('m.id' => 'ml.ownerid','ml.language' => $this->Langs[$this->language]);
		$this->Modules = $this->DB->SelectGuide(array('module as m','module_lang as ml'),array('ml.ownerid as id','ml.name as name'),$conditions);
	}
}
?>