<?php

class MenuView extends Slot {

	public $ModuleID = 6;
	public $SectionID = 10;
	
	public $topmenuy=250;
	public $submenuy=0;
	public $imagePath ='';


	function MenuView($pquery) {
		global $REGISTRY;
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
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

	function setTargetArray($array = array(),$k, $level = 1,$subitems = array(), $subitems=array(), $column) {		
		$size =  round ((sizeof($array) / 3));
		$num = 0;
		//echo $column;
		foreach($array as $key => $v) {
			$this->TempFillEls['Menu'][$k]['Items'][$v['id']] = array(
				'url' => (strpos($v['url'],'fairytale')>0)? $v['url']:$this->Home.'/'.$v['url'],
				'id' => $v['id'],
				'name' => $v['name'],
				'pointer' => $this->isActive($v['url'])?'<img alt=fairytale src=\''.$this->imagePath.'/elements/pointer_right.gif\' width="5"':'',
				'menuclass' => $this->isActive($v['url'])?'menuitem_active':'menuitem',
				'divider' => ( ($num++ ==4) && ($column=='div') && (strpos($this->LocalTarget[0],'ncoterm')>0) )?'</td><td>':'',
			);
			if ($num==5) {$num=0;}
		}
		return $subitems;
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'bottom': $this->fillBottom(); break;
			default: $this->fillDefault(); break;
		} 
		//printArray($this->TempFillEls);

		//$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'open');
	}
	
	function fillDefault() {
		if (!empty($this->PreparedTemplates))
		{
			foreach($this->PreparedTemplates as $k => $v) {
				$fill=1;
				$lt= (isset($this->LocalTarget[0])?$this->LocalTarget[0]:'home');
				/*if (strpos($lt, 'ncoterm')>0 && $v['itorder']>5) {
					$fill=0;
				}*/
				if ($fill==1) {
					$this->TempFillEls['Menu'][$k] = array (
						'url' => (strpos($v['url'],'fairytale')>0)? $v['url']:$this->Home.'/'.$v['url'],
						'id' => $v['id'],
						'name' => $v['name'],
						'pointer' => $this->isActive($v['url'])?'<img alt=fairytale src=\''.$this->imagePath.'/elements/pointer_right.gif\' width="5">':'',
						'menuclass' => $this->isActive($v['url'])?'menuitem_active': (strpos($lt, 'ncoterm')>0 && $v['itorder']==5)?'menuitem_active':'menuitem',
					);
				}
				if((!empty($v['items']) && 
					(isset($this->LocalTarget[0]) && $this->LocalTarget[0]==strtolower($v['url']))) || 
					($this->parentContainsUrl($v['items']))) {
					 $this->setTargetArray($v['items'],$k,1, array(), array(), 'div');
				}
			}
		}
	}
	
	function parentContainsUrl($vitems) {
		if (empty($vitems)) return false;
		foreach ($vitems as $k=>$v) {
			if (isset($this->LocalTarget[0]) && $this->LocalTarget[0] == $v['url']) return true;
		}
		return false;
	}
	
	function isActive($url) {
		$lt= (isset($this->LocalTarget[0])?$this->LocalTarget[0]:'home');
		return ($url == $lt);
	}
	
	
	function fillBottom() {
		if (!empty($this->PreparedTemplates))
		{
			foreach($this->PreparedTemplates as $k => $v) {
				$this->TempFillEls['Menu'][$k] = array (
					'url' => $v['url'],
					'id' => $v['id'],
					'name' => $v['name'],
					'menuclass' => $this->isActive($v['url'])?'bottommenuitem_active':'bottommenuitem',
				);
			}
		}

	}
}
?>