<?php

class ImageListingViewerView extends Slot {

	function ImageListingViewerView($pquery) {
		$this->Slot($pquery);
	}

	function fillElements() {
		$this->TempFillEls = array(
			'id' => @$this->LocalTarget[0],
			'folder' => @$this->LocalTarget[1],
			'number' => @$this->LocalTarget[2],
		);
	}
}
?>