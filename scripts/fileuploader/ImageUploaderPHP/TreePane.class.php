<?php

class TreePane {
  public $attributes;

  
	private $_TitleText;
	/**
	* @return string
	*/
	public function getTitleText() {
		if (isset($this->_TitleText))
			return $this->_TitleText;
		else
			return null;
	}
	public function setTitleText($value) {
		$this->_TitleText = $value;
	}
	
	private $_UnixFileSystemRootText;
	/**
	* @return string
	*/
	public function getUnixFileSystemRootText() {
		if (isset($this->_UnixFileSystemRootText))
			return $this->_UnixFileSystemRootText;
		else
			return null;
	}
	public function setUnixFileSystemRootText($value) {
		$this->_UnixFileSystemRootText = $value;
	}
	
	private $_UnixHomeDirectoryText;
	/**
	* @return string
	*/
	public function getUnixHomeDirectoryText() {
		if (isset($this->_UnixHomeDirectoryText))
			return $this->_UnixHomeDirectoryText;
		else
			return null;
	}
	public function setUnixHomeDirectoryText($value) {
		$this->_UnixHomeDirectoryText = $value;
	}
	
	private $_Width;
	/**
	* @return integer
	*/
	public function getWidth() {
		if (isset($this->_Width))
			return $this->_Width;
		else
			return null;
	}
	public function setWidth($value) {
		$this->_Width = $value;
	}
	

  function __construct(){
    
		$this->setTitleText('Folders');
		$this->setUnixFileSystemRootText('Filesystem');
		$this->setUnixHomeDirectoryText('Home Folder');
		$this->setWidth(200);

    $this->attributes = array();
    
		$this->attributes['TitleText'] = array('jsName' => 'titleText','jsType' => 'String','defaultValue' => 'Folders');
		$this->attributes['UnixFileSystemRootText'] = array('jsName' => 'unixFileSystemRootText','jsType' => 'String','defaultValue' => 'Filesystem');
		$this->attributes['UnixHomeDirectoryText'] = array('jsName' => 'unixHomeDirectoryText','jsType' => 'String','defaultValue' => 'Home Folder');
		$this->attributes['Width'] = array('jsName' => 'width','jsType' => 'Number','defaultValue' => 200);
  }

}