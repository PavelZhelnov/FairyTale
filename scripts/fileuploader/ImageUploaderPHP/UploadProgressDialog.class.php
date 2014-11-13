<?php

class UploadProgressDialog {
  public $attributes;

  
	private $_CancelUploadButtonText;
	/**
	* @return string
	*/
	public function getCancelUploadButtonText() {
		if (isset($this->_CancelUploadButtonText))
			return $this->_CancelUploadButtonText;
		else
			return null;
	}
	public function setCancelUploadButtonText($value) {
		$this->_CancelUploadButtonText = $value;
	}
	
	private $_EstimationText;
	/**
	* @return string
	*/
	public function getEstimationText() {
		if (isset($this->_EstimationText))
			return $this->_EstimationText;
		else
			return null;
	}
	public function setEstimationText($value) {
		$this->_EstimationText = $value;
	}
	
	private $_HideButtonText;
	/**
	* @return string
	*/
	public function getHideButtonText() {
		if (isset($this->_HideButtonText))
			return $this->_HideButtonText;
		else
			return null;
	}
	public function setHideButtonText($value) {
		$this->_HideButtonText = $value;
	}
	
	private $_HoursText;
	/**
	* @return string
	*/
	public function getHoursText() {
		if (isset($this->_HoursText))
			return $this->_HoursText;
		else
			return null;
	}
	public function setHoursText($value) {
		$this->_HoursText = $value;
	}
	
	private $_InfoText;
	/**
	* @return string
	*/
	public function getInfoText() {
		if (isset($this->_InfoText))
			return $this->_InfoText;
		else
			return null;
	}
	public function setInfoText($value) {
		$this->_InfoText = $value;
	}
	
	private $_KilobytesText;
	/**
	* @return string
	*/
	public function getKilobytesText() {
		if (isset($this->_KilobytesText))
			return $this->_KilobytesText;
		else
			return null;
	}
	public function setKilobytesText($value) {
		$this->_KilobytesText = $value;
	}
	
	private $_MegabytesText;
	/**
	* @return string
	*/
	public function getMegabytesText() {
		if (isset($this->_MegabytesText))
			return $this->_MegabytesText;
		else
			return null;
	}
	public function setMegabytesText($value) {
		$this->_MegabytesText = $value;
	}
	
	private $_MinutesText;
	/**
	* @return string
	*/
	public function getMinutesText() {
		if (isset($this->_MinutesText))
			return $this->_MinutesText;
		else
			return null;
	}
	public function setMinutesText($value) {
		$this->_MinutesText = $value;
	}
	
	private $_SecondsText;
	/**
	* @return string
	*/
	public function getSecondsText() {
		if (isset($this->_SecondsText))
			return $this->_SecondsText;
		else
			return null;
	}
	public function setSecondsText($value) {
		$this->_SecondsText = $value;
	}
	
	private $_TimeFormat;
	/**
	* @return string
	*/
	public function getTimeFormat() {
		if (isset($this->_TimeFormat))
			return $this->_TimeFormat;
		else
			return null;
	}
	public function setTimeFormat($value) {
		$this->_TimeFormat = $value;
	}
	
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
	

  function __construct(){
    
		$this->setCancelUploadButtonText('Cancel');
		$this->setEstimationText('Estimated remaining time: [time]');
		$this->setHideButtonText('Hide');
		$this->setHoursText('hours');
		$this->setInfoText('Files uploaded [files]/[totalFiles] ([bytes] of [totalBytes])');
		$this->setKilobytesText('Kb');
		$this->setMegabytesText('Mb');
		$this->setMinutesText('minutes');
		$this->setSecondsText('seconds');
		$this->setTimeFormat('Appearance=ColonSeparated; PresentDirection=HMS; DigitsFormat=NN; HideZero=FALSE');
		$this->setTitleText('Uploading files to server');

    $this->attributes = array();
    
		$this->attributes['CancelUploadButtonText'] = array('jsName' => 'cancelUploadButtonText','jsType' => 'String','defaultValue' => 'Cancel');
		$this->attributes['EstimationText'] = array('jsName' => 'estimationText','jsType' => 'String','defaultValue' => 'Estimated remaining time: [time]');
		$this->attributes['HideButtonText'] = array('jsName' => 'hideButtonText','jsType' => 'String','defaultValue' => 'Hide');
		$this->attributes['HoursText'] = array('jsName' => 'hoursText','jsType' => 'String','defaultValue' => 'hours');
		$this->attributes['InfoText'] = array('jsName' => 'infoText','jsType' => 'String','defaultValue' => 'Files uploaded [files]/[totalFiles] ([bytes] of [totalBytes])');
		$this->attributes['KilobytesText'] = array('jsName' => 'kilobytesText','jsType' => 'String','defaultValue' => 'Kb');
		$this->attributes['MegabytesText'] = array('jsName' => 'megabytesText','jsType' => 'String','defaultValue' => 'Mb');
		$this->attributes['MinutesText'] = array('jsName' => 'minutesText','jsType' => 'String','defaultValue' => 'minutes');
		$this->attributes['SecondsText'] = array('jsName' => 'secondsText','jsType' => 'String','defaultValue' => 'seconds');
		$this->attributes['TimeFormat'] = array('jsName' => 'timeFormat','jsType' => 'String','defaultValue' => 'Appearance=ColonSeparated; PresentDirection=HMS; DigitsFormat=NN; HideZero=FALSE');
		$this->attributes['TitleText'] = array('jsName' => 'titleText','jsType' => 'String','defaultValue' => 'Uploading files to server');
  }

}