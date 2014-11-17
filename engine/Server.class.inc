<?php
include_once($CORE_PATH.'/LanguageManager.class.inc');
include_once($TOOLS_PATH.'/Sniff.class.inc');

include_once($MODEL_PATH.'/Handler.class.inc');
include_once($MODEL_PATH.'/Modules/Common/CommonUtilsHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Common/GlobalSystemSettingsHandler.class.inc');
include_once($MODEL_PATH.'/Security/SecurityHandler.class.inc'); 
include_once($MODEL_PATH.'/Modules/LanguageAccessibility/LangHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Things/ThingsHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/AdminHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Workflow/Document/DocumentHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Menu/MenuHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Quotation/QuotationHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Workflow/Counter/CounterHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Common/LogHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Statistic/StatisticHandler.class.inc');
include_once($MODEL_PATH.'/Modules/AdminModule/AdminModuleHandler.class.inc');
include_once($MODEL_PATH.'/Modules/Things/SearchHandler.class.inc');

include_once($CONTROL_PATH.'/Action.class.inc');
include_once($CONTROL_PATH.'/LogAction.class.inc');
include_once($CONTROL_PATH.'/GlobalSystemSettingsAction.class.inc');
include_once($CONTROL_PATH.'/SecurityAction.class.inc'); 
include_once($CONTROL_PATH.'/SearchAction.class.inc'); 

include_once($CONTROL_PATH.'/ThingsAction.class.inc');
include_once($CONTROL_PATH.'/MessageAction.class.inc');
include_once($CONTROL_PATH.'/MenuAction.class.inc');
include_once($CONTROL_PATH.'/CounterAction.class.inc');
include_once($CONTROL_PATH.'/DocsAction.class.inc');
include_once($CONTROL_PATH.'/HeaderAction.class.inc');
include_once($CONTROL_PATH.'/MetaInfoAction.class.inc');
include_once($CONTROL_PATH.'/QuotationAction.class.inc');
include_once($CONTROL_PATH.'/StatisticAction.class.inc');
include_once($CONTROL_PATH.'/AdminAction.class.inc');
include_once($CONTROL_PATH.'/AdminEmailAction.class.inc');
include_once($CONTROL_PATH.'/AdminDocumentAction.class.inc');
include_once($CONTROL_PATH.'/AdminQuotationAction.class.inc');
include_once($CONTROL_PATH.'/AdminHeaderAction.class.inc');
include_once($CONTROL_PATH.'/AdminStatisticAction.class.inc');
include_once($CONTROL_PATH.'/AdminModuleAction.class.inc');
include_once($CONTROL_PATH.'/AdminMessageAction.class.inc');
include_once($CONTROL_PATH.'/AdminNewsAction.class.inc');
include_once($CONTROL_PATH.'/AdminMemberAction.class.inc');
include_once($CONTROL_PATH.'/AdminPagesAction.class.inc');
include_once($CONTROL_PATH.'/QuotationAction.class.inc');
include_once($CONTROL_PATH.'/AdminSubscriptionAction.class.inc');
include_once($CONTROL_PATH.'/AdminMenuItemsAction.class.inc');
include_once($CONTROL_PATH.'/AdminContentItemAction.class.inc');

class Server extends RootRegistry{

	public $Model = array();
	public $Control = array();

	public $Guides = array();

	public $UserAgent = array();

	public $LM;

	public $settings = array(
		'ModuleAdminSearch' => array(),
		'AdminMemberSearch' => array(),
		'AdminDocumentSearch' => array(),
        'LanguageAdminSearch' => array()
	);

	function Server($name='Server') {
		$this->RootRegistry($name);
		$this->setLM();
		$this->setUserAgent();
	}

	function &getAction($sectionid = 1) {
		if(isset($this->Control[$sectionid])) return $this->Control[$sectionid];
		else {
			$key = $this->findAction($sectionid);
			if(!empty($key)) return $this->Control[$key];
			else {
				$this->setAction($sectionid);
				return $this->Control[$sectionid];
			}
		}
	}

	function setAction($sectionid = 1) {
		$action = $this->Properties['Sections'][$sectionid]['a'].'Action';
		$this->Control[$sectionid] = new $action();
		$this->Control[$sectionid]->ModuleID = $this->Properties['Sections'][$sectionid]['m'];
		$this->Control[$sectionid]->Handler = &$this->getHandler($sectionid);
		$this->Control[$sectionid]->Security = &$this->getHandler(2);
		$this->Control[$sectionid]->Server = &$this;
	}

	function findAction($sectionid = 1) {
		$action = strtolower($this->Properties['Sections'][$sectionid]['a'].'Action');
		foreach($this->Control as $key => $value) if(get_class($value)==$action) return $key;
		return 0;
	}

	function &getHandler($sectionid = 1) {
		if(isset($this->Model[$sectionid])) return $this->Model[$sectionid];
		else {
			$key = $this->findHandler($sectionid);
			if(!empty($key)) return $this->Model[$key];
			else {
				$this->setHandler($sectionid);
				return $this->Model[$sectionid];
			}
		}
	}

	function setHandler($sectionid = 1) {
		$handler = $this->Properties['Sections'][$sectionid]['h'].'Handler';
		$this->Model[$sectionid] = new $handler();
	}

	function findHandler($sectionid = 1) {
		$handler = strtolower($this->Properties['Sections'][$sectionid]['h'].'Handler');
		foreach($this->Model as $key => $value) if(get_class($value)==$handler) return $key;
		return 0;
	}

	function &getUserAgent() {
		return $this->UserAgent;
	}

	function setUserAgent() {
		$UserAgent = new Sniff();
		$this->UserAgent = array(
			'browser' => $UserAgent->_browser_info['browser'],
			'IP' => $UserAgent->_browser_info['ip'],
			'OS' => $UserAgent->_browser_info['platform'].' '.$UserAgent->_browser_info['os'],
		);
	}

	function &getLM() {
		return $this->LM;
	}

	function setLM($langs = array()) {
		$this->LM = new LanguageManager($langs);
		$this->Guides = array();
	}

	function &getGuide($key) {
		$value = $this->Properties['Guides'][$key];
		$cond = array('g.id' => 'gl.ownerid','gl.lang' => $this->LM->Langs[$this->LM->language]);
		//if(!isset($this->Guides[$key])) 
			$this->Guides[$key] = $this->LM->DB->SelectGuide(array($value['table'].' as g',$value['table'].'_lang as gl'),array('g.id','gl.name'),$cond);		
		return $this->Guides[$key];
	}

	function clearAll() {
		foreach($this->Model as $key => $value)
			if(get_class($value)!='securityhandler')
				unset($this->Model[$key]);
		foreach($this->Control as $key => $value)
			if(get_class($value)!='securityaction' && get_class($value)!='memberaccountaction')
				unset($this->Control[$key]);
	} 
}
?>