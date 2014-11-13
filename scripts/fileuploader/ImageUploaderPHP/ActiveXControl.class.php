<?php

require_once ("BaseClientControl.class.php");

class ActiveXControl extends BaseClientControl
{
  
	private $_ClassId;
	/**
	* @return string
	*/
	public function getClassId() {
		if (isset($this->_ClassId))
			return $this->_ClassId;
		else
			return null;
	}
	public function setClassId($value) {
		$this->_ClassId = $value;
	}
	
	private $_ProgId;
	/**
	* @return string
	*/
	public function getProgId() {
		if (isset($this->_ProgId))
			return $this->_ProgId;
		else
			return null;
	}
	public function setProgId($value) {
		$this->_ProgId = $value;
	}
	

  function __construct()
  {
    parent::__construct();

    
		$this->setCodeBase('Scripts/ImageUploader7.cab');

    
		$this->attributes['ClassId'] = array('jsName' => 'classId','jsType' => 'String','defaultValue' => '');
		$this->attributes['CodeBase'] = array('jsName' => 'codeBase','jsType' => 'String','defaultValue' => 'Scripts/ImageUploader7.cab');
		$this->attributes['ProgId'] = array('jsName' => 'progId','jsType' => 'String','defaultValue' => '');
		$this->attributes['Version'] = array('jsName' => 'version','jsType' => 'string','defaultValue' => '');

    if ($this->getCodeBase())
    {
      $this->setCodeBase(Utils::getPhpLibraryDirectory() . "/" . $this->getCodeBase());
    }
  }

}