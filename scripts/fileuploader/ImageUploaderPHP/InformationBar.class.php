<?php

class InformationBar {
  public $attributes;

  
	private $_CloseIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getCloseIconImageFormat() {
		if (isset($this->_CloseIconImageFormat))
			return $this->_CloseIconImageFormat;
		else
			return null;
	}
	public function setCloseIconImageFormat($value) {
		$this->_CloseIconImageFormat = $value;
	}
	
	private $_ErrorColor;
	/**
	* @return string
	*/
	public function getErrorColor() {
		if (isset($this->_ErrorColor))
			return $this->_ErrorColor;
		else
			return null;
	}
	public function setErrorColor($value) {
		$this->_ErrorColor = $value;
	}
	
	private $_MessageColor;
	/**
	* @return string
	*/
	public function getMessageColor() {
		if (isset($this->_MessageColor))
			return $this->_MessageColor;
		else
			return null;
	}
	public function setMessageColor($value) {
		$this->_MessageColor = $value;
	}
	
	private $_WarningColor;
	/**
	* @return string
	*/
	public function getWarningColor() {
		if (isset($this->_WarningColor))
			return $this->_WarningColor;
		else
			return null;
	}
	public function setWarningColor($value) {
		$this->_WarningColor = $value;
	}
	

  function __construct(){
    
		$this->setCloseIconImageFormat(new ImageFormat());
		$this->setErrorColor('#f14b54');
		$this->setMessageColor('#a3ffa8');
		$this->setWarningColor('#fde2a6');

    $this->attributes = array();
    
		$this->attributes['CloseIconImageFormat'] = array('jsName' => 'closeIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['ErrorColor'] = array('jsName' => 'errorColor','jsType' => 'String','defaultValue' => '#f14b54');
		$this->attributes['MessageColor'] = array('jsName' => 'messageColor','jsType' => 'String','defaultValue' => '#a3ffa8');
		$this->attributes['WarningColor'] = array('jsName' => 'warningColor','jsType' => 'String','defaultValue' => '#fde2a6');
  }

}