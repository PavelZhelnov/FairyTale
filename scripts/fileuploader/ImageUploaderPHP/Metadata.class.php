<?php

class Metadata {
  public $attributes;

  
	private $_AdditionalFormName;
	/**
	* @return string
	*/
	public function getAdditionalFormName() {
		if (isset($this->_AdditionalFormName))
			return $this->_AdditionalFormName;
		else
			return null;
	}
	public function setAdditionalFormName($value) {
		$this->_AdditionalFormName = $value;
	}
	
	private $_Exif;
	/**
	* @return string
	*/
	public function getExif() {
		if (isset($this->_Exif))
			return $this->_Exif;
		else
			return null;
	}
	public function setExif($value) {
		$this->_Exif = $value;
	}
	
	private $_Hash;
	/**
	* @return string
	*/
	public function getHash() {
		if (isset($this->_Hash))
			return $this->_Hash;
		else
			return null;
	}
	public function setHash($value) {
		$this->_Hash = $value;
	}
	
	private $_Iptc;
	/**
	* @return string
	*/
	public function getIptc() {
		if (isset($this->_Iptc))
			return $this->_Iptc;
		else
			return null;
	}
	public function setIptc($value) {
		$this->_Iptc = $value;
	}
	
	private $_UserAgent;
	/**
	* @return string
	*/
	public function getUserAgent() {
		if (isset($this->_UserAgent))
			return $this->_UserAgent;
		else
			return null;
	}
	public function setUserAgent($value) {
		$this->_UserAgent = $value;
	}
	
	private $_ValueSeparator;
	/**
	* @return string
	*/
	public function getValueSeparator() {
		if (isset($this->_ValueSeparator))
			return $this->_ValueSeparator;
		else
			return null;
	}
	public function setValueSeparator($value) {
		$this->_ValueSeparator = $value;
	}
	

  function __construct(){
    
		$this->setValueSeparator(' ');

    $this->attributes = array();
    
		$this->attributes['AdditionalFormName'] = array('jsName' => 'additionalFormName','jsType' => 'String','defaultValue' => '');
		$this->attributes['Exif'] = array('jsName' => 'exif','jsType' => 'String','defaultValue' => '');
		$this->attributes['Hash'] = array('jsName' => 'hash','jsType' => 'String','defaultValue' => '');
		$this->attributes['Iptc'] = array('jsName' => 'iptc','jsType' => 'String','defaultValue' => '');
		$this->attributes['UserAgent'] = array('jsName' => 'userAgent','jsType' => 'String','defaultValue' => '');
		$this->attributes['ValueSeparator'] = array('jsName' => 'valueSeparator','jsType' => 'String','defaultValue' => ' ');
  }

}