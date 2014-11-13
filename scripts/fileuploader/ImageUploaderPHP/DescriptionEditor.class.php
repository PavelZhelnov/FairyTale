<?php

class DescriptionEditor {
  public $attributes;

  
	private $_CancelHyperlinkText;
	/**
	* @return string
	*/
	public function getCancelHyperlinkText() {
		if (isset($this->_CancelHyperlinkText))
			return $this->_CancelHyperlinkText;
		else
			return null;
	}
	public function setCancelHyperlinkText($value) {
		$this->_CancelHyperlinkText = $value;
	}
	
	private $_MaxTextLength;
	/**
	* @return integer
	*/
	public function getMaxTextLength() {
		if (isset($this->_MaxTextLength))
			return $this->_MaxTextLength;
		else
			return null;
	}
	public function setMaxTextLength($value) {
		$this->_MaxTextLength = $value;
	}
	
	private $_OrEscLabelText;
	/**
	* @return string
	*/
	public function getOrEscLabelText() {
		if (isset($this->_OrEscLabelText))
			return $this->_OrEscLabelText;
		else
			return null;
	}
	public function setOrEscLabelText($value) {
		$this->_OrEscLabelText = $value;
	}
	
	private $_SaveButtonText;
	/**
	* @return string
	*/
	public function getSaveButtonText() {
		if (isset($this->_SaveButtonText))
			return $this->_SaveButtonText;
		else
			return null;
	}
	public function setSaveButtonText($value) {
		$this->_SaveButtonText = $value;
	}
	

  function __construct(){
    
		$this->setCancelHyperlinkText('Cancel');
		$this->setMaxTextLength(512);
		$this->setOrEscLabelText(' (or Esc)');
		$this->setSaveButtonText('Save');

    $this->attributes = array();
    
		$this->attributes['CancelHyperlinkText'] = array('jsName' => 'cancelHyperlinkText','jsType' => 'String','defaultValue' => 'Cancel');
		$this->attributes['MaxTextLength'] = array('jsName' => 'maxTextLength','jsType' => 'Number','defaultValue' => 512);
		$this->attributes['OrEscLabelText'] = array('jsName' => 'orEscLabelText','jsType' => 'String','defaultValue' => ' (or Esc)');
		$this->attributes['SaveButtonText'] = array('jsName' => 'saveButtonText','jsType' => 'String','defaultValue' => 'Save');
  }

}