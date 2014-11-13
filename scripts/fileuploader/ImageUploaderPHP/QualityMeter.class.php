<?php

class QualityMeter {
  public $attributes;

  
	private $_AcceptableQualityColor;
	/**
	* @return string
	*/
	public function getAcceptableQualityColor() {
		if (isset($this->_AcceptableQualityColor))
			return $this->_AcceptableQualityColor;
		else
			return null;
	}
	public function setAcceptableQualityColor($value) {
		$this->_AcceptableQualityColor = $value;
	}
	
	private $_BackgroundColor;
	/**
	* @return string
	*/
	public function getBackgroundColor() {
		if (isset($this->_BackgroundColor))
			return $this->_BackgroundColor;
		else
			return null;
	}
	public function setBackgroundColor($value) {
		$this->_BackgroundColor = $value;
	}
	
	private $_BorderColor;
	/**
	* @return string
	*/
	public function getBorderColor() {
		if (isset($this->_BorderColor))
			return $this->_BorderColor;
		else
			return null;
	}
	public function setBorderColor($value) {
		$this->_BorderColor = $value;
	}
	
	private $_Formats;
	/**
	* @return string
	*/
	public function getFormats() {
		if (isset($this->_Formats))
			return $this->_Formats;
		else
			return null;
	}
	public function setFormats($value) {
		$this->_Formats = $value;
	}
	
	private $_Height;
	/**
	* @return integer
	*/
	public function getHeight() {
		if (isset($this->_Height))
			return $this->_Height;
		else
			return null;
	}
	public function setHeight($value) {
		$this->_Height = $value;
	}
	
	private $_HighQualityColor;
	/**
	* @return string
	*/
	public function getHighQualityColor() {
		if (isset($this->_HighQualityColor))
			return $this->_HighQualityColor;
		else
			return null;
	}
	public function setHighQualityColor($value) {
		$this->_HighQualityColor = $value;
	}
	
	private $_LowQualityColor;
	/**
	* @return string
	*/
	public function getLowQualityColor() {
		if (isset($this->_LowQualityColor))
			return $this->_LowQualityColor;
		else
			return null;
	}
	public function setLowQualityColor($value) {
		$this->_LowQualityColor = $value;
	}
	

  function __construct(){
    
		$this->setAcceptableQualityColor('#ffc600');
		$this->setBackgroundColor('#ffffff');
		$this->setBorderColor('#154575');
		$this->setHeight(11);
		$this->setHighQualityColor('#5bc529');
		$this->setLowQualityColor('#ececec');

    $this->attributes = array();
    
		$this->attributes['AcceptableQualityColor'] = array('jsName' => 'acceptableQualityColor','jsType' => 'String','defaultValue' => '#ffc600');
		$this->attributes['BackgroundColor'] = array('jsName' => 'backgroundColor','jsType' => 'String','defaultValue' => '#ffffff');
		$this->attributes['BorderColor'] = array('jsName' => 'borderColor','jsType' => 'String','defaultValue' => '#154575');
		$this->attributes['Formats'] = array('jsName' => 'formats','jsType' => 'String','defaultValue' => '');
		$this->attributes['Height'] = array('jsName' => 'height','jsType' => 'Number','defaultValue' => 11);
		$this->attributes['HighQualityColor'] = array('jsName' => 'highQualityColor','jsType' => 'String','defaultValue' => '#5bc529');
		$this->attributes['LowQualityColor'] = array('jsName' => 'lowQualityColor','jsType' => 'String','defaultValue' => '#ececec');
  }

}