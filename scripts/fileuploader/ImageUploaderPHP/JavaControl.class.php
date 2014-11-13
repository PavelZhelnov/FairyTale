<?php

require_once("BaseClientControl.class.php");

class JavaControl extends BaseClientControl {
  public $attributes;

  
	private $_Cached;
	/**
	* @return boolean
	*/
	public function getCached() {
		if (isset($this->_Cached))
			return $this->_Cached;
		else
			return null;
	}
	public function setCached($value) {
		$this->_Cached = $value;
	}
	
	private $_ClassName;
	/**
	* @return string
	*/
	public function getClassName() {
		if (isset($this->_ClassName))
			return $this->_ClassName;
		else
			return null;
	}
	public function setClassName($value) {
		$this->_ClassName = $value;
	}
	

  function __construct(){
    
		$this->setCached(true);
		$this->setCodeBase('Scripts/ImageUploader7.jar');

    $this->attributes = array();
    
		$this->attributes['Cached'] = array('jsName' => 'cached','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['ClassName'] = array('jsName' => 'className','jsType' => 'String','defaultValue' => '');
		$this->attributes['CodeBase'] = array('jsName' => 'codeBase','jsType' => 'String','defaultValue' => 'Scripts/ImageUploader7.jar');
		$this->attributes['Version'] = array('jsName' => 'version','jsType' => 'String','defaultValue' => '');

    if ($this->getCodeBase())
    {
      $this->setCodeBase(Utils::getPhpLibraryDirectory() . "/" . $this->getCodeBase());
    }
  }

}