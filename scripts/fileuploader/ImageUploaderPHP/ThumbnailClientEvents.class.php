<?php

class ThumbnailClientEvents {
  public $attributes;

  
	private $_Click;
	/**
	* @return array
	*/
	public function &getClick() {
		return $this->_Click;
	}
	public function setClick($value) {
		if (is_array($value)) {
			$this->_Click = $value;
		} else {
			$this->_Click = array($value);
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
	

  function __construct(){
    

    $this->attributes = array();
    
		$this->attributes['Click'] = array('jsName' => 'click','jsType' => 'event');
		$this->attributes['InitComplete'] = array('jsName' => 'initComplete','jsType' => 'event');
		$this->attributes['PreRender'] = array('jsName' => 'preRender','jsType' => 'event');
  }

}