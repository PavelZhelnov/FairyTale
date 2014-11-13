<?php

class ClientEvents {
  public $attributes;

  
	private $_AfterPackageUpload;
	/**
	* @return array
	*/
	public function &getAfterPackageUpload() {
		return $this->_AfterPackageUpload;
	}
	public function setAfterPackageUpload($value) {
		if (is_array($value)) {
			$this->_AfterPackageUpload = $value;
		} else {
			$this->_AfterPackageUpload = array($value);
		}
	}
	
	private $_AfterSendRequest;
	/**
	* @return array
	*/
	public function &getAfterSendRequest() {
		return $this->_AfterSendRequest;
	}
	public function setAfterSendRequest($value) {
		if (is_array($value)) {
			$this->_AfterSendRequest = $value;
		} else {
			$this->_AfterSendRequest = array($value);
		}
	}
	
	private $_AfterUpload;
	/**
	* @return array
	*/
	public function &getAfterUpload() {
		return $this->_AfterUpload;
	}
	public function setAfterUpload($value) {
		if (is_array($value)) {
			$this->_AfterUpload = $value;
		} else {
			$this->_AfterUpload = array($value);
		}
	}
	
	private $_BeforePackageUpload;
	/**
	* @return array
	*/
	public function &getBeforePackageUpload() {
		return $this->_BeforePackageUpload;
	}
	public function setBeforePackageUpload($value) {
		if (is_array($value)) {
			$this->_BeforePackageUpload = $value;
		} else {
			$this->_BeforePackageUpload = array($value);
		}
	}
	
	private $_BeforeSendRequest;
	/**
	* @return array
	*/
	public function &getBeforeSendRequest() {
		return $this->_BeforeSendRequest;
	}
	public function setBeforeSendRequest($value) {
		if (is_array($value)) {
			$this->_BeforeSendRequest = $value;
		} else {
			$this->_BeforeSendRequest = array($value);
		}
	}
	
	private $_BeforeUpload;
	/**
	* @return array
	*/
	public function &getBeforeUpload() {
		return $this->_BeforeUpload;
	}
	public function setBeforeUpload($value) {
		if (is_array($value)) {
			$this->_BeforeUpload = $value;
		} else {
			$this->_BeforeUpload = array($value);
		}
	}
	
	private $_Error;
	/**
	* @return array
	*/
	public function &getError() {
		return $this->_Error;
	}
	public function setError($value) {
		if (is_array($value)) {
			$this->_Error = $value;
		} else {
			$this->_Error = array($value);
		}
	}
	
	private $_FolderChange;
	/**
	* @return array
	*/
	public function &getFolderChange() {
		return $this->_FolderChange;
	}
	public function setFolderChange($value) {
		if (is_array($value)) {
			$this->_FolderChange = $value;
		} else {
			$this->_FolderChange = array($value);
		}
	}
	
	private $_InitComplete;
	/**
	* @return array
	*/
	public function &getInitComplete() {
		return $this->_InitComplete;
	}
	public function setInitComplete($value) {
		if (is_array($value)) {
			$this->_InitComplete = $value;
		} else {
			$this->_InitComplete = array($value);
		}
	}
	
	private $_PreRender;
	/**
	* @return array
	*/
	public function &getPreRender() {
		return $this->_PreRender;
	}
	public function setPreRender($value) {
		if (is_array($value)) {
			$this->_PreRender = $value;
		} else {
			$this->_PreRender = array($value);
		}
	}
	
	private $_Progress;
	/**
	* @return array
	*/
	public function &getProgress() {
		return $this->_Progress;
	}
	public function setProgress($value) {
		if (is_array($value)) {
			$this->_Progress = $value;
		} else {
			$this->_Progress = array($value);
		}
	}
	
	private $_RestrictionFailed;
	/**
	* @return array
	*/
	public function &getRestrictionFailed() {
		return $this->_RestrictionFailed;
	}
	public function setRestrictionFailed($value) {
		if (is_array($value)) {
			$this->_RestrictionFailed = $value;
		} else {
			$this->_RestrictionFailed = array($value);
		}
	}
	
	private $_SelectionChange;
	/**
	* @return array
	*/
	public function &getSelectionChange() {
		return $this->_SelectionChange;
	}
	public function setSelectionChange($value) {
		if (is_array($value)) {
			$this->_SelectionChange = $value;
		} else {
			$this->_SelectionChange = array($value);
		}
	}
	
	private $_Trace;
	/**
	* @return array
	*/
	public function getTrace() {
		if (isset($this->_Trace))
			return $this->_Trace;
		else
			return null;
	}
	public function setTrace($value) {
		if (is_array($value)) {
			$this->_Trace = $value;
		} else {
			$this->_Trace = array($value);
		}
	}
	
	private $_UploadFileCountChange;
	/**
	* @return array
	*/
	public function &getUploadFileCountChange() {
		return $this->_UploadFileCountChange;
	}
	public function setUploadFileCountChange($value) {
		if (is_array($value)) {
			$this->_UploadFileCountChange = $value;
		} else {
			$this->_UploadFileCountChange = array($value);
		}
	}
	
	private $_ViewChange;
	/**
	* @return array
	*/
	public function &getViewChange() {
		return $this->_ViewChange;
	}
	public function setViewChange($value) {
		if (is_array($value)) {
			$this->_ViewChange = $value;
		} else {
			$this->_ViewChange = array($value);
		}
	}
	

  function __construct(){
    

    $this->attributes = array();
    
		$this->attributes['AfterPackageUpload'] = array('jsName' => 'afterPackageUpload','jsType' => 'event');
		$this->attributes['AfterSendRequest'] = array('jsName' => 'afterSendRequest','jsType' => 'event');
		$this->attributes['AfterUpload'] = array('jsName' => 'afterUpload','jsType' => 'event');
		$this->attributes['BeforePackageUpload'] = array('jsName' => 'beforePackageUpload','jsType' => 'event');
		$this->attributes['BeforeSendRequest'] = array('jsName' => 'beforeSendRequest','jsType' => 'event');
		$this->attributes['BeforeUpload'] = array('jsName' => 'beforeUpload','jsType' => 'event');
		$this->attributes['Error'] = array('jsName' => 'error','jsType' => 'event');
		$this->attributes['FolderChange'] = array('jsName' => 'folderChange','jsType' => 'event');
		$this->attributes['InitComplete'] = array('jsName' => 'initComplete','jsType' => 'event');
		$this->attributes['PreRender'] = array('jsName' => 'preRender','jsType' => 'event');
		$this->attributes['Progress'] = array('jsName' => 'progress','jsType' => 'event');
		$this->attributes['RestrictionFailed'] = array('jsName' => 'restrictionFailed','jsType' => 'event');
		$this->attributes['SelectionChange'] = array('jsName' => 'selectionChange','jsType' => 'event');
		$this->attributes['Trace'] = array('jsName' => 'trace','jsType' => 'event');
		$this->attributes['UploadFileCountChange'] = array('jsName' => 'uploadFileCountChange','jsType' => 'event');
		$this->attributes['ViewChange'] = array('jsName' => 'viewChange','jsType' => 'event');
  }

}