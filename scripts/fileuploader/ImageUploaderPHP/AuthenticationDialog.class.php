<?php

class AuthenticationDialog {
  public $attributes;

  
	private $_CancelButtonText;
	/**
	* @return string
	*/
	public function getCancelButtonText() {
		if (isset($this->_CancelButtonText))
			return $this->_CancelButtonText;
		else
			return null;
	}
	public function setCancelButtonText($value) {
		$this->_CancelButtonText = $value;
	}
	
	private $_LoginText;
	/**
	* @return string
	*/
	public function getLoginText() {
		if (isset($this->_LoginText))
			return $this->_LoginText;
		else
			return null;
	}
	public function setLoginText($value) {
		$this->_LoginText = $value;
	}
	
	private $_OkButtonText;
	/**
	* @return string
	*/
	public function getOkButtonText() {
		if (isset($this->_OkButtonText))
			return $this->_OkButtonText;
		else
			return null;
	}
	public function setOkButtonText($value) {
		$this->_OkButtonText = $value;
	}
	
	private $_PasswordText;
	/**
	* @return string
	*/
	public function getPasswordText() {
		if (isset($this->_PasswordText))
			return $this->_PasswordText;
		else
			return null;
	}
	public function setPasswordText($value) {
		$this->_PasswordText = $value;
	}
	
	private $_RealmText;
	/**
	* @return string
	*/
	public function getRealmText() {
		if (isset($this->_RealmText))
			return $this->_RealmText;
		else
			return null;
	}
	public function setRealmText($value) {
		$this->_RealmText = $value;
	}
	
	private $_Text;
	/**
	* @return string
	*/
	public function getText() {
		if (isset($this->_Text))
			return $this->_Text;
		else
			return null;
	}
	public function setText($value) {
		$this->_Text = $value;
	}
	

  function __construct(){
    
		$this->setCancelButtonText('Cancel');
		$this->setLoginText('Login:');
		$this->setOkButtonText('Ok');
		$this->setPasswordText('Password:');
		$this->setRealmText('Realm:');
		$this->setText('Host [name] requires authentication');

    $this->attributes = array();
    
		$this->attributes['CancelButtonText'] = array('jsName' => 'cancelButtonText','jsType' => 'String','defaultValue' => 'Cancel');
		$this->attributes['LoginText'] = array('jsName' => 'loginText','jsType' => 'String','defaultValue' => 'Login:');
		$this->attributes['OkButtonText'] = array('jsName' => 'okButtonText','jsType' => 'String','defaultValue' => 'Ok');
		$this->attributes['PasswordText'] = array('jsName' => 'passwordText','jsType' => 'String','defaultValue' => 'Password:');
		$this->attributes['RealmText'] = array('jsName' => 'realmText','jsType' => 'String','defaultValue' => 'Realm:');
		$this->attributes['Text'] = array('jsName' => 'text','jsType' => 'String','defaultValue' => 'Host [name] requires authentication');
  }

}