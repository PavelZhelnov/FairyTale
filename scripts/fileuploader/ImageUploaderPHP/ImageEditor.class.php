<?php

require_once 'ImageFormat.class.php';

class ImageEditor {
  public $attributes;

  
	private $_CancelButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getCancelButtonImageFormat() {
		if (isset($this->_CancelButtonImageFormat))
			return $this->_CancelButtonImageFormat;
		else
			return null;
	}
	public function setCancelButtonImageFormat($value) {
		$this->_CancelButtonImageFormat = $value;
	}
	
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
	
	private $_CancelCropButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getCancelCropButtonImageFormat() {
		if (isset($this->_CancelCropButtonImageFormat))
			return $this->_CancelCropButtonImageFormat;
		else
			return null;
	}
	public function setCancelCropButtonImageFormat($value) {
		$this->_CancelCropButtonImageFormat = $value;
	}
	
	private $_CancelCropButtonText;
	/**
	* @return string
	*/
	public function getCancelCropButtonText() {
		if (isset($this->_CancelCropButtonText))
			return $this->_CancelCropButtonText;
		else
			return null;
	}
	public function setCancelCropButtonText($value) {
		$this->_CancelCropButtonText = $value;
	}
	
	private $_CropButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getCropButtonImageFormat() {
		if (isset($this->_CropButtonImageFormat))
			return $this->_CropButtonImageFormat;
		else
			return null;
	}
	public function setCropButtonImageFormat($value) {
		$this->_CropButtonImageFormat = $value;
	}
	
	private $_CropButtonText;
	/**
	* @return string
	*/
	public function getCropButtonText() {
		if (isset($this->_CropButtonText))
			return $this->_CropButtonText;
		else
			return null;
	}
	public function setCropButtonText($value) {
		$this->_CropButtonText = $value;
	}
	
	private $_CropMinSize;
	/**
	* @return integer
	*/
	public function getCropMinSize() {
		if (isset($this->_CropMinSize))
			return $this->_CropMinSize;
		else
			return null;
	}
	public function setCropMinSize($value) {
		$this->_CropMinSize = $value;
	}
	
	private $_CropRatio;
	/**
	* @return undefined
	*/
	public function getCropRatio() {
		if (isset($this->_CropRatio))
			return $this->_CropRatio;
		else
			return null;
	}
	public function setCropRatio($value) {
		$this->_CropRatio = $value;
	}
	
	private $_DescriptionHintText;
	/**
	* @return string
	*/
	public function getDescriptionHintText() {
		if (isset($this->_DescriptionHintText))
			return $this->_DescriptionHintText;
		else
			return null;
	}
	public function setDescriptionHintText($value) {
		$this->_DescriptionHintText = $value;
	}
	
	private $_EnableCrop;
	/**
	* @return boolean
	*/
	public function getEnableCrop() {
		if (isset($this->_EnableCrop))
			return $this->_EnableCrop;
		else
			return null;
	}
	public function setEnableCrop($value) {
		$this->_EnableCrop = $value;
	}
	
	private $_RotateButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getRotateButtonImageFormat() {
		if (isset($this->_RotateButtonImageFormat))
			return $this->_RotateButtonImageFormat;
		else
			return null;
	}
	public function setRotateButtonImageFormat($value) {
		$this->_RotateButtonImageFormat = $value;
	}
	
	private $_RotateButtonText;
	/**
	* @return string
	*/
	public function getRotateButtonText() {
		if (isset($this->_RotateButtonText))
			return $this->_RotateButtonText;
		else
			return null;
	}
	public function setRotateButtonText($value) {
		$this->_RotateButtonText = $value;
	}
	
	private $_SaveButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getSaveButtonImageFormat() {
		if (isset($this->_SaveButtonImageFormat))
			return $this->_SaveButtonImageFormat;
		else
			return null;
	}
	public function setSaveButtonImageFormat($value) {
		$this->_SaveButtonImageFormat = $value;
	}
	
	private $_SaveButtonText;
	/**
	* @return string
	*/
	public function getSaveButtonText() {
		if (isset($this->_SaveButtonText))
			return $this->_SaveButtonText;
		else
			return null;
	}
	public function setSaveButtonText($value) {
		$this->_SaveButtonText = $value;
	}
	

  function __construct(){
    
		$this->setCancelButtonImageFormat(new ImageFormat());
		$this->setCancelButtonText('Cancel');
		$this->setCancelCropButtonImageFormat(new ImageFormat());
		$this->setCancelCropButtonText('Cancel crop');
		$this->setCropButtonImageFormat(new ImageFormat());
		$this->setCropButtonText('Crop');
		$this->setCropMinSize(50);
		$this->setCropRatio(0);
		$this->setDescriptionHintText('Type description here...');
		$this->setEnableCrop(true);
		$this->setRotateButtonImageFormat(new ImageFormat());
		$this->setRotateButtonText('Rotate');
		$this->setSaveButtonImageFormat(new ImageFormat());
		$this->setSaveButtonText('Save and close');

    $this->attributes = array();
    
		$this->attributes['CancelButtonImageFormat'] = array('jsName' => 'cancelButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['CancelButtonText'] = array('jsName' => 'cancelButtonText','jsType' => 'String','defaultValue' => 'Cancel');
		$this->attributes['CancelCropButtonImageFormat'] = array('jsName' => 'cancelCropButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['CancelCropButtonText'] = array('jsName' => 'cancelCropButtonText','jsType' => 'String','defaultValue' => 'Cancel crop');
		$this->attributes['CropButtonImageFormat'] = array('jsName' => 'cropButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['CropButtonText'] = array('jsName' => 'cropButtonText','jsType' => 'String','defaultValue' => 'Crop');
		$this->attributes['CropMinSize'] = array('jsName' => 'cropMinSize','jsType' => 'Number','defaultValue' => 50);
		$this->attributes['CropRatio'] = array('jsName' => 'cropRatio','jsType' => 'Number','defaultValue' => 0);
		$this->attributes['DescriptionHintText'] = array('jsName' => 'descriptionHintText','jsType' => 'String','defaultValue' => 'Type description here...');
		$this->attributes['EnableCrop'] = array('jsName' => 'enableCrop','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['RotateButtonImageFormat'] = array('jsName' => 'rotateButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['RotateButtonText'] = array('jsName' => 'rotateButtonText','jsType' => 'String','defaultValue' => 'Rotate');
		$this->attributes['SaveButtonImageFormat'] = array('jsName' => 'saveButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['SaveButtonText'] = array('jsName' => 'saveButtonText','jsType' => 'String','defaultValue' => 'Save and close');
  }

}