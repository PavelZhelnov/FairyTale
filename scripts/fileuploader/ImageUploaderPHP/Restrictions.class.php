<?php

require_once("BaseClientControl.class.php");

class Restrictions {
  public $attributes;

  
	private $_DeniedFileMask;
	/**
	* @return string
	*/
	public function getDeniedFileMask() {
		if (isset($this->_DeniedFileMask))
			return $this->_DeniedFileMask;
		else
			return null;
	}
	public function setDeniedFileMask($value) {
		$this->_DeniedFileMask = $value;
	}
	
	private $_EnableCmyk;
	/**
	* @return boolean
	*/
	public function getEnableCmyk() {
		if (isset($this->_EnableCmyk))
			return $this->_EnableCmyk;
		else
			return null;
	}
	public function setEnableCmyk($value) {
		$this->_EnableCmyk = $value;
	}
	
	private $_FileMask;
	/**
	* @return string
	*/
	public function getFileMask() {
		if (isset($this->_FileMask))
			return $this->_FileMask;
		else
			return null;
	}
	public function setFileMask($value) {
		$this->_FileMask = $value;
	}
	
	private $_MaxFileCount;
	/**
	* @return integer
	*/
	public function getMaxFileCount() {
		if (isset($this->_MaxFileCount))
			return $this->_MaxFileCount;
		else
			return null;
	}
	public function setMaxFileCount($value) {
		$this->_MaxFileCount = $value;
	}
	
	private $_MaxFileSize;
	/**
	* @return integer
	*/
	public function getMaxFileSize() {
		if (isset($this->_MaxFileSize))
			return $this->_MaxFileSize;
		else
			return null;
	}
	public function setMaxFileSize($value) {
		$this->_MaxFileSize = $value;
	}
	
	private $_MaxImageHeight;
	/**
	* @return integer
	*/
	public function getMaxImageHeight() {
		if (isset($this->_MaxImageHeight))
			return $this->_MaxImageHeight;
		else
			return null;
	}
	public function setMaxImageHeight($value) {
		$this->_MaxImageHeight = $value;
	}
	
	private $_MaxImageWidth;
	/**
	* @return integer
	*/
	public function getMaxImageWidth() {
		if (isset($this->_MaxImageWidth))
			return $this->_MaxImageWidth;
		else
			return null;
	}
	public function setMaxImageWidth($value) {
		$this->_MaxImageWidth = $value;
	}
	
	private $_MaxTotalFileSize;
	/**
	* @return integer
	*/
	public function getMaxTotalFileSize() {
		if (isset($this->_MaxTotalFileSize))
			return $this->_MaxTotalFileSize;
		else
			return null;
	}
	public function setMaxTotalFileSize($value) {
		$this->_MaxTotalFileSize = $value;
	}
	
	private $_MinFileCount;
	/**
	* @return integer
	*/
	public function getMinFileCount() {
		if (isset($this->_MinFileCount))
			return $this->_MinFileCount;
		else
			return null;
	}
	public function setMinFileCount($value) {
		$this->_MinFileCount = $value;
	}
	
	private $_MinFileSize;
	/**
	* @return integer
	*/
	public function getMinFileSize() {
		if (isset($this->_MinFileSize))
			return $this->_MinFileSize;
		else
			return null;
	}
	public function setMinFileSize($value) {
		$this->_MinFileSize = $value;
	}
	
	private $_MinImageHeight;
	/**
	* @return integer
	*/
	public function getMinImageHeight() {
		if (isset($this->_MinImageHeight))
			return $this->_MinImageHeight;
		else
			return null;
	}
	public function setMinImageHeight($value) {
		$this->_MinImageHeight = $value;
	}
	
	private $_MinImageWidth;
	/**
	* @return integer
	*/
	public function getMinImageWidth() {
		if (isset($this->_MinImageWidth))
			return $this->_MinImageWidth;
		else
			return null;
	}
	public function setMinImageWidth($value) {
		$this->_MinImageWidth = $value;
	}
	

  function __construct(){
    
		$this->setEnableCmyk(true);
		$this->setFileMask('*.*');
		$this->setMaxFileCount(0);
		$this->setMaxFileSize(0);
		$this->setMaxImageHeight(0);
		$this->setMaxImageWidth(0);
		$this->setMaxTotalFileSize(0);
		$this->setMinFileCount(1);
		$this->setMinFileSize(0);
		$this->setMinImageHeight(0);
		$this->setMinImageWidth(0);

    $this->attributes = array();
    
		$this->attributes['DeniedFileMask'] = array('jsName' => 'deniedFileMask','jsType' => 'String','defaultValue' => '');
		$this->attributes['EnableCmyk'] = array('jsName' => 'enableCmyk','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['FileMask'] = array('jsName' => 'fileMask','jsType' => 'String','defaultValue' => '*.*');
		$this->attributes['MaxFileCount'] = array('jsName' => 'maxFileCount','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['MaxFileSize'] = array('jsName' => 'maxFileSize','jsType' => 'String','defaultValue' => '0');
		$this->attributes['MaxImageHeight'] = array('jsName' => 'maxImageHeight','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['MaxImageWidth'] = array('jsName' => 'maxImageWidth','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['MaxTotalFileSize'] = array('jsName' => 'maxTotalFileSize','jsType' => 'String','defaultValue' => '0');
		$this->attributes['MinFileCount'] = array('jsName' => 'minFileCount','jsType' => 'Number','defaultValue' => 1);
		$this->attributes['MinFileSize'] = array('jsName' => 'minFileSize','jsType' => 'String','defaultValue' => '0');
		$this->attributes['MinImageHeight'] = array('jsName' => 'minImageHeight','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['MinImageWidth'] = array('jsName' => 'minImageWidth','jsType' => 'Number','defaultValue' => 0);
  }

}