<?php

require_once 'BackgroundImageFormat.class.php';

class UploadPane {
  public $attributes;

  
	private $_DropFilesHereImageFormat;
	/**
	* @return BackgroundImageFormat
	*/
	public function getDropFilesHereImageFormat() {
		if (isset($this->_DropFilesHereImageFormat))
			return $this->_DropFilesHereImageFormat;
		else
			return null;
	}
	public function setDropFilesHereImageFormat($value) {
		$this->_DropFilesHereImageFormat = $value;
	}
	
	private $_DropFilesHereText;
	/**
	* @return string
	*/
	public function getDropFilesHereText() {
		if (isset($this->_DropFilesHereText))
			return $this->_DropFilesHereText;
		else
			return null;
	}
	public function setDropFilesHereText($value) {
		$this->_DropFilesHereText = $value;
	}
	
	private $_PreviewSize;
	/**
	* @return integer
	*/
	public function getPreviewSize() {
		if (isset($this->_PreviewSize))
			return $this->_PreviewSize;
		else
			return null;
	}
	public function setPreviewSize($value) {
		$this->_PreviewSize = $value;
	}
	
	private $_SortMode;
	/**
	* @return string
	*/
	public function getSortMode() {
		if (isset($this->_SortMode))
			return $this->_SortMode;
		else
			return null;
	}
	public function setSortMode($value) {
		$this->_SortMode = $value;
	}
	
	private $_ViewMode;
	/**
	* @return string
	*/
	public function getViewMode() {
		if (isset($this->_ViewMode))
			return $this->_ViewMode;
		else
			return null;
	}
	public function setViewMode($value) {
		$this->_ViewMode = $value;
	}
	

  function __construct(){
    
		$this->setDropFilesHereImageFormat(new BackgroundImageFormat());
		$this->setDropFilesHereText('Drop files here...');
		$this->setPreviewSize(96);
		$this->setSortMode('Unsorted');
		$this->setViewMode('Thumbnails');

    $this->attributes = array();
    
		$this->attributes['DropFilesHereImageFormat'] = array('jsName' => 'dropFilesHereImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['DropFilesHereText'] = array('jsName' => 'dropFilesHereText','jsType' => 'String','defaultValue' => 'Drop files here...');
		$this->attributes['PreviewSize'] = array('jsName' => 'previewSize','jsType' => 'Number','defaultValue' => 96);
		$this->attributes['SortMode'] = array('jsName' => 'sortMode','jsType' => 'String','defaultValue' => 'Unsorted');
		$this->attributes['ViewMode'] = array('jsName' => 'viewMode','jsType' => 'String','defaultValue' => 'Thumbnails');
  }

}