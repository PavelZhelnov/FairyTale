<?php

class DeleteFilesDialog {
  public $attributes;

  
	private $_Message;
	/**
	* @return string
	*/
	public function getMessage() {
		if (isset($this->_Message))
			return $this->_Message;
		else
			return null;
	}
	public function setMessage($value) {
		$this->_Message = $value;
	}
	
	private $_TitleText;
	/**
	* @return string
	*/
	public function getTitleText() {
		if (isset($this->_TitleText))
			return $this->_TitleText;
		else
			return null;
	}
	public function setTitleText($value) {
		$this->_TitleText = $value;
	}
	

  function __construct(){
    
		$this->setMessage('Are you sure you want to permanently delete uploaded items?');
		$this->setTitleText('Delete File');

    $this->attributes = array();
    
		$this->attributes['Message'] = array('jsName' => 'message','jsType' => 'String','defaultValue' => 'Are you sure you want to permanently delete uploaded items?');
		$this->attributes['TitleText'] = array('jsName' => 'titleText','jsType' => 'String','defaultValue' => 'Delete File');
  }

}