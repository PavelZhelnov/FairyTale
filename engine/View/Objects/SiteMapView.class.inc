<?php

class SiteMapView extends Slot {

	public $ModuleID = 2;
	public $SectionID = 10;

	function SiteMapView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		$this->Action->processEvent($this->SectionID,'open',array('langid' => $this->LM->Langs[$this->language]),$this);
	}

	function sortItems($array = array(),$array2 = array(0 => ''),$flag = false) {
		foreach($array as $key => $value) {
			if(!empty($value['items'])) $array[$key]['items'] = $this->sortItems($value['items'],array(0 => ''),true);
			$array[$key]['name'] = wordwrap(trim($value['name']),19,'&nbsp;<br><img src=\"'.$this->ImageWPath.'/1.gif\" height=1 width=13>',1);
			$array2[] = $array[$key];
			if($flag) $array2[] = array('external' => '','target' => '','id' => '','url' => '','name' => addslashes(makeImage($this->ImagePath.'/menu/line1.gif',$this->ImageWPath.'/menu/line1.gif')),'items' => array());
		}
		unset($array2[0]);
		if(count($array2)%2==0 && $flag) array_pop($array2);
		return $array2;
	}

	function setTargetArray($array = array(),$k, $level = 1,$subitems = array(), $subitems=array()) {		
		foreach($array as $key => $value) {
			$this->TempFillEls['Menu'][$k]['Items'][$value['id']] = array(
				'url' => $value['url'],
				'id' => $value['id'],
				'name' => $value['name'],
				'nbsps' => str_repeat("&nbsp;&nbsp;&nbsp;&nbsp;",$level),
			);
			if(!empty($value['items'])) {$this->setTargetArray($value['items'],$k,$level+1);}
		}
		return $subitems;
	}

	function fillElements() {
		if (!empty($this->PreparedTemplates))
		{
			foreach($this->PreparedTemplates as $k => $v) {
				$this->TempFillEls['Menu'][$k] = array (
					'url' => $v['url'],
					'id' => $v['id'],
					'name' => $v['name'],
					'navibullet' => ($k % 5) +1,
				);
				if(!empty($v['items'])) $this->setTargetArray($v['items'],$k,1);
			}
		}

		//$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'open');
	}
}
?>