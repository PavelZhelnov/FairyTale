<?php

class StatusPane {
  public $attributes;

  
	private $_ClearAllHyperlinkText;
	/**
	* @return string
	*/
	public function getClearAllHyperlinkText() {
		if (isset($this->_ClearAllHyperlinkText))
			return $this->_ClearAllHyperlinkText;
		else
			return null;
	}
	public function setClearAllHyperlinkText($value) {
		$this->_ClearAllHyperlinkText = $value;
	}
	
	private $_Color;
	/**
	* @return string
	*/
	public function getColor() {
		if (isset($this->_Color))
			return $this->_Color;
		else
			return null;
	}
	public function setColor($value) {
		$this->_Color = $value;
	}
	
	private $_FilesToUploadText;
	/**
	* @return string
	*/
	public function getFilesToUploadText() {
		if (isset($this->_FilesToUploadText))
			return $this->_FilesToUploadText;
		else
			return null;
	}
	public function setFilesToUploadText($value) {
		$this->_FilesToUploadText = $value;
	}
	
	private $_NoFilesToUploadText;
	/**
	* @return string
	*/
	public function getNoFilesToUploadText() {
		if (isset($this->_NoFilesToUploadText))
			return $this->_NoFilesToUploadText;
		else
			return null;
	}
	public function setNoFilesToUploadText($value) {
		$this->_NoFilesToUploadText = $value;
	}
	
	private $_ProgressBarText;
	/**
	* @return string
	*/
	public function getProgressBarText() {
		if (isset($this->_ProgressBarText))
			return $this->_ProgressBarText;
		else
			return null;
	}
	public function setProgressBarText($value) {
		$this->_ProgressBarText = $value;
	}
	

  function __construct(){
    
		$this->setClearAllHyperlinkText('clear all');
		$this->setColor('#f7f7f7;#efefef');
		$this->setFilesToUploadText('Files selected to upload: [count]');
		$this->setNoFilesToUploadText('No files to upload');
		$this->setProgressBarText('Uploading ([percents]%)');

    $this->attributes = array();
    
		$this->attributes['ClearAllHyperlinkText'] = array('jsName' => 'clearAllHyperlinkText','jsType' => 'String','defaultValue' => 'clear all');
		$this->attributes['Color'] = array('jsName' => 'color','jsType' => 'String','defaultValue' => '#f7f7f7;#efefef');
		$this->attributes['FilesToUploadText'] = array('jsName' => 'filesToUploadText','jsType' => 'String','defaultValue' => 'Files selected to upload: [count]');
		$this->attributes['NoFilesToUploadText'] = array('jsName' => 'noFilesToUploadText','jsType' => 'String','defaultValue' => 'No files to upload');
		$this->attributes['ProgressBarText'] = array('jsName' => 'progressBarText','jsType' => 'String','defaultValue' => 'Uploading ([percents]%)');
  }

}