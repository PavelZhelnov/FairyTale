<?php

class MessageView extends Slot {

	public $ModuleID = 8;
	public $SectionID = 13;

	function MessageView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		$this->Action->processEvent($this->SectionID,'message',array('langid' => $this->LM->Langs[$this->language]),$this);
	}

	function fillElements() {
		if (!empty($this->PreparedTemplates['curPage']))
		{
			$this->TempFillEls['text'] = $this->PreparedTemplates['curPage'][0]['text'];
		}
	}
}
?>