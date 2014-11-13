<?php

class UploadSettings {
  public $attributes;

  
	private $_ActionUrl;
	/**
	* @return string
	*/
	public function getActionUrl() {
		if (isset($this->_ActionUrl))
			return $this->_ActionUrl;
		else
			return null;
	}
	public function setActionUrl($value) {
		$this->_ActionUrl = $value;
	}
	
	private $_AutoRecoveryMaxAttemptCount;
	/**
	* @return integer
	*/
	public function getAutoRecoveryMaxAttemptCount() {
		if (isset($this->_AutoRecoveryMaxAttemptCount))
			return $this->_AutoRecoveryMaxAttemptCount;
		else
			return null;
	}
	public function setAutoRecoveryMaxAttemptCount($value) {
		$this->_AutoRecoveryMaxAttemptCount = $value;
	}
	
	private $_AutoRecoveryTimeout;
	/**
	* @return integer
	*/
	public function getAutoRecoveryTimeout() {
		if (isset($this->_AutoRecoveryTimeout))
			return $this->_AutoRecoveryTimeout;
		else
			return null;
	}
	public function setAutoRecoveryTimeout($value) {
		$this->_AutoRecoveryTimeout = $value;
	}
	
	private $_Charset;
	/**
	* @return string
	*/
	public function getCharset() {
		if (isset($this->_Charset))
			return $this->_Charset;
		else
			return null;
	}
	public function setCharset($value) {
		$this->_Charset = $value;
	}
	
	private $_ChunkSize;
	/**
	* @return integer
	*/
	public function getChunkSize() {
		if (isset($this->_ChunkSize))
			return $this->_ChunkSize;
		else
			return null;
	}
	public function setChunkSize($value) {
		$this->_ChunkSize = $value;
	}
	
	private $_ConnectionTimeout;
	/**
	* @return integer
	*/
	public function getConnectionTimeout() {
		if (isset($this->_ConnectionTimeout))
			return $this->_ConnectionTimeout;
		else
			return null;
	}
	public function setConnectionTimeout($value) {
		$this->_ConnectionTimeout = $value;
	}
	
	private $_EnableInstantUpload;
	/**
	* @return boolean
	*/
	public function getEnableInstantUpload() {
		if (isset($this->_EnableInstantUpload))
			return $this->_EnableInstantUpload;
		else
			return null;
	}
	public function setEnableInstantUpload($value) {
		$this->_EnableInstantUpload = $value;
	}
	
	private $_FilesPerPackage;
	/**
	* @return integer
	*/
	public function getFilesPerPackage() {
		if (isset($this->_FilesPerPackage))
			return $this->_FilesPerPackage;
		else
			return null;
	}
	public function setFilesPerPackage($value) {
		$this->_FilesPerPackage = $value;
	}
	
	private $_ProgressBytesMode;
	/**
	* @return string
	*/
	public function getProgressBytesMode() {
		if (isset($this->_ProgressBytesMode))
			return $this->_ProgressBytesMode;
		else
			return null;
	}
	public function setProgressBytesMode($value) {
		$this->_ProgressBytesMode = $value;
	}
	
	private $_RedirectUrl;
	/**
	* @return string
	*/
	public function getRedirectUrl() {
		if (isset($this->_RedirectUrl))
			return $this->_RedirectUrl;
		else
			return null;
	}
	public function setRedirectUrl($value) {
		$this->_RedirectUrl = $value;
	}
	
	private $_UploadConverterOutputSeparately;
	/**
	* @return boolean
	*/
	public function getUploadConverterOutputSeparately() {
		if (isset($this->_UploadConverterOutputSeparately))
			return $this->_UploadConverterOutputSeparately;
		else
			return null;
	}
	public function setUploadConverterOutputSeparately($value) {
		$this->_UploadConverterOutputSeparately = $value;
	}
	

  function __construct(){
    
		$this->setActionUrl('.');
		$this->setAutoRecoveryMaxAttemptCount(1);
		$this->setAutoRecoveryTimeout(5000);
		$this->setCharset('UTF-8');
		$this->setChunkSize(0);
		$this->setConnectionTimeout(0);
		$this->setEnableInstantUpload(false);
		$this->setFilesPerPackage(0);
		$this->setProgressBytesMode('ByPackageSize');
		$this->setUploadConverterOutputSeparately(false);

    $this->attributes = array();
    
		$this->attributes['ActionUrl'] = array('jsName' => 'actionUrl','jsType' => 'String','defaultValue' => '.');
		$this->attributes['AutoRecoveryMaxAttemptCount'] = array('jsName' => 'autoRecoveryMaxAttemptCount','jsType' => 'Number','defaultValue' => 1);
		$this->attributes['AutoRecoveryTimeout'] = array('jsName' => 'autoRecoveryTimeout','jsType' => 'Number','defaultValue' => 5000);
		$this->attributes['Charset'] = array('jsName' => 'charset','jsType' => 'String','defaultValue' => 'UTF-8');
		$this->attributes['ChunkSize'] = array('jsName' => 'chunkSize','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['ConnectionTimeout'] = array('jsName' => 'connectionTimeout','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['EnableInstantUpload'] = array('jsName' => 'enableInstantUpload','jsType' => 'Boolean','defaultValue' => false);
		$this->attributes['FilesPerPackage'] = array('jsName' => 'filesPerPackage','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['ProgressBytesMode'] = array('jsName' => 'progressBytesMode','jsType' => 'String','defaultValue' => 'ByPackageSize');
		$this->attributes['RedirectUrl'] = array('jsName' => 'redirectUrl','jsType' => 'String','defaultValue' => '');
		$this->attributes['UploadConverterOutputSeparately'] = array('jsName' => 'uploadConverterOutputSeparately','jsType' => 'Boolean','defaultValue' => false);
  }

}