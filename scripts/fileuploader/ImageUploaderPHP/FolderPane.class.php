<?php

class FolderPane {
  public $attributes;

  
	private $_FilterClearIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getFilterClearIconImageFormat() {
		if (isset($this->_FilterClearIconImageFormat))
			return $this->_FilterClearIconImageFormat;
		else
			return null;
	}
	public function setFilterClearIconImageFormat($value) {
		$this->_FilterClearIconImageFormat = $value;
	}
	
	private $_FilterHintText;
	/**
	* @return string
	*/
	public function getFilterHintText() {
		if (isset($this->_FilterHintText))
			return $this->_FilterHintText;
		else
			return null;
	}
	public function setFilterHintText($value) {
		$this->_FilterHintText = $value;
	}
	
	private $_HeaderAllowedText;
	/**
	* @return string
	*/
	public function getHeaderAllowedText() {
		if (isset($this->_HeaderAllowedText))
			return $this->_HeaderAllowedText;
		else
			return null;
	}
	public function setHeaderAllowedText($value) {
		$this->_HeaderAllowedText = $value;
	}
	
	private $_HeaderAllText;
	/**
	* @return string
	*/
	public function getHeaderAllText() {
		if (isset($this->_HeaderAllText))
			return $this->_HeaderAllText;
		else
			return null;
	}
	public function setHeaderAllText($value) {
		$this->_HeaderAllText = $value;
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
	
	private $_ShowAllowedItemsOnly;
	/**
	* @return boolean
	*/
	public function getShowAllowedItemsOnly() {
		if (isset($this->_ShowAllowedItemsOnly))
			return $this->_ShowAllowedItemsOnly;
		else
			return null;
	}
	public function setShowAllowedItemsOnly($value) {
		$this->_ShowAllowedItemsOnly = $value;
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
    
		$this->setFilterClearIconImageFormat(new ImageFormat());
		$this->setFilterHintText('Search ');
		$this->setHeaderAllowedText('allowed: [count]');
		$this->setHeaderAllText('Total files: [count], ');
		$this->setHeight(300);
		$this->setPreviewSize(96);
		$this->setShowAllowedItemsOnly(true);
		$this->setSortMode('Name');
		$this->setViewMode('Thumbnails');

    $this->attributes = array();
    
		$this->attributes['FilterClearIconImageFormat'] = array('jsName' => 'filterClearIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['FilterHintText'] = array('jsName' => 'filterHintText','jsType' => 'String','defaultValue' => 'Search ');
		$this->attributes['HeaderAllowedText'] = array('jsName' => 'headerAllowedText','jsType' => 'String','defaultValue' => 'allowed: [count]');
		$this->attributes['HeaderAllText'] = array('jsName' => 'headerAllText','jsType' => 'String','defaultValue' => 'Total files: [count], ');
		$this->attributes['Height'] = array('jsName' => 'height','jsType' => 'Number','defaultValue' => 300);
		$this->attributes['PreviewSize'] = array('jsName' => 'previewSize','jsType' => 'Number','defaultValue' => 96);
		$this->attributes['ShowAllowedItemsOnly'] = array('jsName' => 'showAllowedItemsOnly','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['SortMode'] = array('jsName' => 'sortMode','jsType' => 'String','defaultValue' => 'Name');
		$this->attributes['ViewMode'] = array('jsName' => 'viewMode','jsType' => 'String','defaultValue' => 'Thumbnails');
  }

}