<?php

require_once "Utils.class.php";

abstract class BaseClientControl {
  public $attributes;

  
	private $_CodeBase;
	/**
	* @return string
	*/
	public function getCodeBase() {
		if (isset($this->_CodeBase))
			return $this->_CodeBase;
		else
			return null;
	}
	public function setCodeBase($value) {
		$this->_CodeBase = $value;
	}
	
	private $_Version;
	/**
	* @return string
	*/
	public function getVersion() {
		if (isset($this->_Version))
			return $this->_Version;
		else
			return null;
	}
	public function setVersion($value) {
		$this->_Version = $value;
	}
	

  function __construct(){
    

    $this->attributes = array();
    
  }

}