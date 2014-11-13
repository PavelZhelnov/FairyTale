<?php

class Messages {
  public $attributes;

  
	private $_CmykImagesNotAllowed;
	/**
	* @return string
	*/
	public function getCmykImagesNotAllowed() {
		if (isset($this->_CmykImagesNotAllowed))
			return $this->_CmykImagesNotAllowed;
		else
			return null;
	}
	public function setCmykImagesNotAllowed($value) {
		$this->_CmykImagesNotAllowed = $value;
	}
	
	private $_DeletingFilesError;
	/**
	* @return string
	*/
	public function getDeletingFilesError() {
		if (isset($this->_DeletingFilesError))
			return $this->_DeletingFilesError;
		else
			return null;
	}
	public function setDeletingFilesError($value) {
		$this->_DeletingFilesError = $value;
	}
	
	private $_DimensionsTooLarge;
	/**
	* @return string
	*/
	public function getDimensionsTooLarge() {
		if (isset($this->_DimensionsTooLarge))
			return $this->_DimensionsTooLarge;
		else
			return null;
	}
	public function setDimensionsTooLarge($value) {
		$this->_DimensionsTooLarge = $value;
	}
	
	private $_DimensionsTooSmall;
	/**
	* @return string
	*/
	public function getDimensionsTooSmall() {
		if (isset($this->_DimensionsTooSmall))
			return $this->_DimensionsTooSmall;
		else
			return null;
	}
	public function setDimensionsTooSmall($value) {
		$this->_DimensionsTooSmall = $value;
	}
	
	private $_FileNameNotAllowed;
	/**
	* @return string
	*/
	public function getFileNameNotAllowed() {
		if (isset($this->_FileNameNotAllowed))
			return $this->_FileNameNotAllowed;
		else
			return null;
	}
	public function setFileNameNotAllowed($value) {
		$this->_FileNameNotAllowed = $value;
	}
	
	private $_FileSizeTooSmall;
	/**
	* @return string
	*/
	public function getFileSizeTooSmall() {
		if (isset($this->_FileSizeTooSmall))
			return $this->_FileSizeTooSmall;
		else
			return null;
	}
	public function setFileSizeTooSmall($value) {
		$this->_FileSizeTooSmall = $value;
	}
	
	private $_FilesNotAdded;
	/**
	* @return string
	*/
	public function getFilesNotAdded() {
		if (isset($this->_FilesNotAdded))
			return $this->_FilesNotAdded;
		else
			return null;
	}
	public function setFilesNotAdded($value) {
		$this->_FilesNotAdded = $value;
	}
	
	private $_MaxFileCountExceeded;
	/**
	* @return string
	*/
	public function getMaxFileCountExceeded() {
		if (isset($this->_MaxFileCountExceeded))
			return $this->_MaxFileCountExceeded;
		else
			return null;
	}
	public function setMaxFileCountExceeded($value) {
		$this->_MaxFileCountExceeded = $value;
	}
	
	private $_MaxFileSizeExceeded;
	/**
	* @return string
	*/
	public function getMaxFileSizeExceeded() {
		if (isset($this->_MaxFileSizeExceeded))
			return $this->_MaxFileSizeExceeded;
		else
			return null;
	}
	public function setMaxFileSizeExceeded($value) {
		$this->_MaxFileSizeExceeded = $value;
	}
	
	private $_MaxTotalFileSizeExceeded;
	/**
	* @return string
	*/
	public function getMaxTotalFileSizeExceeded() {
		if (isset($this->_MaxTotalFileSizeExceeded))
			return $this->_MaxTotalFileSizeExceeded;
		else
			return null;
	}
	public function setMaxTotalFileSizeExceeded($value) {
		$this->_MaxTotalFileSizeExceeded = $value;
	}
	
	private $_NoResponseFromServer;
	/**
	* @return string
	*/
	public function getNoResponseFromServer() {
		if (isset($this->_NoResponseFromServer))
			return $this->_NoResponseFromServer;
		else
			return null;
	}
	public function setNoResponseFromServer($value) {
		$this->_NoResponseFromServer = $value;
	}
	
	private $_ServerNotFound;
	/**
	* @return string
	*/
	public function getServerNotFound() {
		if (isset($this->_ServerNotFound))
			return $this->_ServerNotFound;
		else
			return null;
	}
	public function setServerNotFound($value) {
		$this->_ServerNotFound = $value;
	}
	
	private $_UnexpectedError;
	/**
	* @return string
	*/
	public function getUnexpectedError() {
		if (isset($this->_UnexpectedError))
			return $this->_UnexpectedError;
		else
			return null;
	}
	public function setUnexpectedError($value) {
		$this->_UnexpectedError = $value;
	}
	
	private $_UploadCancelled;
	/**
	* @return string
	*/
	public function getUploadCancelled() {
		if (isset($this->_UploadCancelled))
			return $this->_UploadCancelled;
		else
			return null;
	}
	public function setUploadCancelled($value) {
		$this->_UploadCancelled = $value;
	}
	
	private $_UploadCompleted;
	/**
	* @return string
	*/
	public function getUploadCompleted() {
		if (isset($this->_UploadCompleted))
			return $this->_UploadCompleted;
		else
			return null;
	}
	public function setUploadCompleted($value) {
		$this->_UploadCompleted = $value;
	}
	
	private $_UploadFailed;
	/**
	* @return string
	*/
	public function getUploadFailed() {
		if (isset($this->_UploadFailed))
			return $this->_UploadFailed;
		else
			return null;
	}
	public function setUploadFailed($value) {
		$this->_UploadFailed = $value;
	}
	

  function __construct(){
    
		$this->setCmykImagesNotAllowed('CMYK images are not allowed.');
		$this->setDeletingFilesError('The file \'[name]\' cannot be deleted');
		$this->setDimensionsTooLarge('The image \'[name]\' is too large to be selected.');
		$this->setDimensionsTooSmall('The image \'[name]\' is too small to be selected.');
		$this->setFileNameNotAllowed('The file \'[name]\' cannot be selected. This file has inadmissible name.');
		$this->setFileSizeTooSmall('The file \'[name]\' cannot be selected. This file size is smaller than the limit.');
		$this->setFilesNotAdded('[count] files were not added due to restrictions.');
		$this->setMaxFileCountExceeded('The file \'[name]\' cannot be selected. Amount of files exceeds the limit.');
		$this->setMaxFileSizeExceeded('The file \'[name]\' cannot be selected. This file size exceeds the limit.');
		$this->setMaxTotalFileSizeExceeded('The file \'[name]\' cannot be selected. Total upload data size exceeds the limit.');
		$this->setNoResponseFromServer('No response from server.');
		$this->setServerNotFound('The server or proxy [name] cannot be found.');
		$this->setUnexpectedError('Image Uploader encountered some problem. If you see this message, contact web master.');
		$this->setUploadCancelled('Upload is cancelled.');
		$this->setUploadCompleted('Upload complete.');
		$this->setUploadFailed('Upload failed (the connection was interrupted).');

    $this->attributes = array();
    
		$this->attributes['CmykImagesNotAllowed'] = array('jsName' => 'cmykImagesNotAllowed','jsType' => 'String','defaultValue' => 'CMYK images are not allowed.');
		$this->attributes['DeletingFilesError'] = array('jsName' => 'deletingFilesError','jsType' => 'String','defaultValue' => 'The file \'[name]\' cannot be deleted');
		$this->attributes['DimensionsTooLarge'] = array('jsName' => 'dimensionsTooLarge','jsType' => 'String','defaultValue' => 'The image \'[name]\' is too large to be selected.');
		$this->attributes['DimensionsTooSmall'] = array('jsName' => 'dimensionsTooSmall','jsType' => 'String','defaultValue' => 'The image \'[name]\' is too small to be selected.');
		$this->attributes['FileNameNotAllowed'] = array('jsName' => 'fileNameNotAllowed','jsType' => 'String','defaultValue' => 'The file \'[name]\' cannot be selected. This file has inadmissible name.');
		$this->attributes['FileSizeTooSmall'] = array('jsName' => 'fileSizeTooSmall','jsType' => 'String','defaultValue' => 'The file \'[name]\' cannot be selected. This file size is smaller than the limit.');
		$this->attributes['FilesNotAdded'] = array('jsName' => 'filesNotAdded','jsType' => 'String','defaultValue' => '[count] files were not added due to restrictions.');
		$this->attributes['MaxFileCountExceeded'] = array('jsName' => 'maxFileCountExceeded','jsType' => 'String','defaultValue' => 'The file \'[name]\' cannot be selected. Amount of files exceeds the limit.');
		$this->attributes['MaxFileSizeExceeded'] = array('jsName' => 'maxFileSizeExceeded','jsType' => 'String','defaultValue' => 'The file \'[name]\' cannot be selected. This file size exceeds the limit.');
		$this->attributes['MaxTotalFileSizeExceeded'] = array('jsName' => 'maxTotalFileSizeExceeded','jsType' => 'String','defaultValue' => 'The file \'[name]\' cannot be selected. Total upload data size exceeds the limit.');
		$this->attributes['NoResponseFromServer'] = array('jsName' => 'noResponseFromServer','jsType' => 'String','defaultValue' => 'No response from server.');
		$this->attributes['ServerNotFound'] = array('jsName' => 'serverNotFound','jsType' => 'String','defaultValue' => 'The server or proxy [name] cannot be found.');
		$this->attributes['UnexpectedError'] = array('jsName' => 'unexpectedError','jsType' => 'String','defaultValue' => 'Image Uploader encountered some problem. If you see this message, contact web master.');
		$this->attributes['UploadCancelled'] = array('jsName' => 'uploadCancelled','jsType' => 'String','defaultValue' => 'Upload is cancelled.');
		$this->attributes['UploadCompleted'] = array('jsName' => 'uploadCompleted','jsType' => 'String','defaultValue' => 'Upload complete.');
		$this->attributes['UploadFailed'] = array('jsName' => 'uploadFailed','jsType' => 'String','defaultValue' => 'Upload failed (the connection was interrupted).');
  }

}