<?php

class AddFilesProgressDialog {
  public $attributes;

  
	private $_CancelButtonText;
	/**
	* @return string
	*/
	public function getCancelButtonText() {
		if (isset($this->_CancelButtonText))
			return $this->_CancelButtonText;
		else
			return null;
	}
	public function setCancelButtonText($value) {
		$this->_CancelButtonText = $value;
	}
	
	private $_CurrentFileText;
	/**
	* @return string
	*/
	public function getCurrentFileText() {
		if (isset($this->_CurrentFileText))
			return $this->_CurrentFileText;
		else
			return null;
	}
	public function setCurrentFileText($value) {
		$this->_CurrentFileText = $value;
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
	
	private $_TotalFilesText;
	/**
	* @return string
	*/
	public function getTotalFilesText() {
		if (isset($this->_TotalFilesText))
			return $this->_TotalFilesText;
		else
			return null;
	}
	public function setTotalFilesText($value) {
		$this->_TotalFilesText = $value;
	}
	
	private $_WaitText;
	/**
	* @return string
	*/
	public function getWaitText() {
		if (isset($this->_WaitText))
			return $this->_WaitText;
		else
			return null;
	}
	public function setWaitText($value) {
		$this->_WaitText = $value;
	}
	

  function __construct(){
    
		$this->setCancelButtonText('Cancel');
		$this->setCurrentFileText('Processing file: \'[name]\'');
		$this->setTitleText('Adding files to upload queue');
		$this->setTotalFilesText('already processed files: [count]');
		$this->setWaitText('Please wait, it may take some time...');

    $this->attributes = array();
    
		$this->attributes['CancelButtonText'] = array('jsName' => 'cancelButtonText','jsType' => 'String','defaultValue' => 'Cancel');
		$this->attributes['CurrentFileText'] = array('jsName' => 'currentFileText','jsType' => 'String','defaultValue' => 'Processing file: \'[name]\'');
		$this->attributes['TitleText'] = array('jsName' => 'titleText','jsType' => 'String','defaultValue' => 'Adding files to upload queue');
		$this->attributes['TotalFilesText'] = array('jsName' => 'totalFilesText','jsType' => 'String','defaultValue' => 'already processed files: [count]');
		$this->attributes['WaitText'] = array('jsName' => 'waitText','jsType' => 'String','defaultValue' => 'Please wait, it may take some time...');
  }

}