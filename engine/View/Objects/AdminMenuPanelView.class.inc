<?php

class AdminMenuPanelView extends Slot {
	public $ModuleID = 3;
	public $SectionID = 3;
	
	public $url = '';

	function AdminMenuPanelView($pquery) {
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		if(!$this->Action->isAuthorizeAdmin()) $this->Scheme = 'auth'; 
		else {
			$url = parse_url(getenv('REQUEST_URI'));
			$this->encodeUrl($this->LocalTarget);
			$this->url = $this->Home.'/'.implode('/',$this->LocalTarget).(!empty($url['query'])? '?'.$url['query'] : '');
		}
		$this->setSchemeTemplate($this->Scheme);
	}

	function fillElements() {
		switch ($this->Scheme) {
			case 'auth': $this->fillAuth(); break;
			default: $this->fillMenu(); break;
		}
			
	}

	function fillAuth() {
		$this->TempFillEls = array();
	}
	
	function fillMenu() {
		foreach($this->Properties as $key => $value)
			//$this->TempFillEls[$key] = $this->language == $key? '<span class=yellow2>'.$value.'</span>' : makeLink($this->langReplace($key),$value);
			$this->TempFillEls['langid']=$value;			
	}
	
	function langReplace($lang) {
		global $WEB_ROOT;
		return eregi_replace('^'.$WEB_ROOT.'/'.$this->language,$WEB_ROOT.'/'.$lang,$this->url);
	}

	function encodeUrl(&$array) {
		foreach($array as $key => $value) $array[$key] = urlencode($value);
	}
}
?>
