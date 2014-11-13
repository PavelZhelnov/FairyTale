<?php

class DetailsViewColumns {
  public $attributes;

  
	private $_DimensionsText;
	/**
	* @return string
	*/
	public function getDimensionsText() {
		if (isset($this->_DimensionsText))
			return $this->_DimensionsText;
		else
			return null;
	}
	public function setDimensionsText($value) {
		$this->_DimensionsText = $value;
	}
	
	private $_FileNameText;
	/**
	* @return string
	*/
	public function getFileNameText() {
		if (isset($this->_FileNameText))
			return $this->_FileNameText;
		else
			return null;
	}
	public function setFileNameText($value) {
		$this->_FileNameText = $value;
	}
	
	private $_FileSizeText;
	/**
	* @return string
	*/
	public function getFileSizeText() {
		if (isset($this->_FileSizeText))
			return $this->_FileSizeText;
		else
			return null;
	}
	public function setFileSizeText($value) {
		$this->_FileSizeText = $value;
	}
	
	private $_FileTypeText;
	/**
	* @return string
	*/
	public function getFileTypeText() {
		if (isset($this->_FileTypeText))
			return $this->_FileTypeText;
		else
			return null;
	}
	public function setFileTypeText($value) {
		$this->_FileTypeText = $value;
	}
	
	private $_InfoText;
	/**
	* @return string
	*/
	public function getInfoText() {
		if (isset($this->_InfoText))
			return $this->_InfoText;
		else
			return null;
	}
	public function setInfoText($value) {
		$this->_InfoText = $value;
	}
	
	private $_LastModifiedText;
	/**
	* @return string
	*/
	public function getLastModifiedText() {
		if (isset($this->_LastModifiedText))
			return $this->_LastModifiedText;
		else
			return null;
	}
	public function setLastModifiedText($value) {
		$this->_LastModifiedText = $value;
	}
	

  function __construct(){
    
		$this->setDimensionsText('Image dimensions');
		$this->setFileNameText('Name');
		$this->setFileSizeText('Size');
		$this->setFileTypeText('Type');
		$this->setInfoText('Info');
		$this->setLastModifiedText('Date modified');

    $this->attributes = array();
    
		$this->attributes['DimensionsText'] = array('jsName' => 'dimensionsText','jsType' => 'String','defaultValue' => 'Image dimensions');
		$this->attributes['FileNameText'] = array('jsName' => 'fileNameText','jsType' => 'String','defaultValue' => 'Name');
		$this->attributes['FileSizeText'] = array('jsName' => 'fileSizeText','jsType' => 'String','defaultValue' => 'Size');
		$this->attributes['FileTypeText'] = array('jsName' => 'fileTypeText','jsType' => 'String','defaultValue' => 'Type');
		$this->attributes['InfoText'] = array('jsName' => 'infoText','jsType' => 'String','defaultValue' => 'Info');
		$this->attributes['LastModifiedText'] = array('jsName' => 'lastModifiedText','jsType' => 'String','defaultValue' => 'Date modified');
  }

}