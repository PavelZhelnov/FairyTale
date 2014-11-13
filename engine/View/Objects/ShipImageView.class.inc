<?php

class ShipImageView extends Slot {

	public $imagePath='';
	
	function ShipImageView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
	}

	function init() {
		
	}

	function fillElements() {
		$img_num=rand(1,2);
		$this->TempFillEls['image'] = 
			'<img src=\''.$this->imagePath.'/elements/autos/auto'.$img_num.'.jpg\' border=0 width=212 height=336 alt=fairytale>';
	}
}
?>
