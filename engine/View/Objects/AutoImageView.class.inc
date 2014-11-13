<?php

class AutoImageView extends Slot {

	public $imagePath='';
	
	function AutoImageView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
	}

	function init() {
		
	}

	function fillElements() {
		$img_num=rand(1,6);
		$this->TempFillEls['image'] = 
			'<img src=\''.$this->imagePath.'/elements/autos/header'.$img_num.'.jpg\' border=0 width=355 height=194 alt=fairytale>';
	}
}
?>
