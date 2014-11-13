<?php

class HeaderView extends Slot {
	public $ModuleID = 5;
	public $SectionID = 6;
	public $Task = 'view';
	public $url = '';
	public $imagePath='';
	public $imageWPath='';
	public $image_type;
	
	function HeaderView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImagePath'];
		$this->imageWPath = $REGISTRY['Core']['ImageWPath'];
		
	}

	function init() {
		
		$this->Action->processEvent($this->SectionID,'settings',array('moduleid' => 1, 'paramid'=>3),$this);
		foreach ($this->PreparedTemplates['settings'] as $k => $v) {
			if ($v['paramid']=='3')
				$this->image_type = $v['value'];
		}
				
		//if (!empty($this->LocalTarget)) {$this->Scheme = 'other';} else 
		$this->Scheme = 'default';
		$this->setSchemeTemplate($this->Scheme);		
	}

	function fillElements() {
		$this->TempFillEls['headerimage'] = (isset($this->image_type)?
					($this->image_type=='swf'?
						makeSwf($this->imagePath.'/layout/header.'.$this->image_type,$this->imageWPath.'/layout/header.'.$this->image_type):
						makeImage($this->imagePath.'/layout/header.'.$this->image_type,$this->imageWPath.'/layout/header.'.$this->image_type,'','center',array(),1,' ')						
					): 
					'');
	}

}
?>
