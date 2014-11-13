<?php

class LangPanelView extends Slot {

	public $url = '';
	public $imagePath='';
	
	function LangPanelView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
	}

	function init() {
		$url = parse_url(getenv('REQUEST_URI'));
		$this->encodeUrl($this->LocalTarget);
		$this->url = $this->Home.'/'.implode('/',$this->LocalTarget).(!empty($url['query'])? '?'.$url['query'] : '');
	}

	function fillElements() {
		foreach($this->Properties as $key => $value)
			$this->TempFillEls[$key] = $this->language == $key? 
			  '<span class="langitem">'.strtoupper($value).'</span>' :
			   '<a class="langitem" href="'.$this->langReplace($key).'">'.strtoupper($value).'</a>';
			//$this->TempFillEls[$key] = $this->language == $key? '<img src="">'.$value.'</span>' : '<span class=gray>'.makeLink($this->langReplace($key),$value).'</span>';
			//$this->TempFillEls['langid']=$value;			
			//makeLink($this->langReplace($key),$value)
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
