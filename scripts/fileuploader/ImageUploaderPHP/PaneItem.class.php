<?php

require_once 'ImageFormat.class.php';
require_once 'QualityMeter.class.php';

class PaneItem {
  public $attributes;

  
	private $_DescriptionAddedIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getDescriptionAddedIconImageFormat() {
		if (isset($this->_DescriptionAddedIconImageFormat))
			return $this->_DescriptionAddedIconImageFormat;
		else
			return null;
	}
	public function setDescriptionAddedIconImageFormat($value) {
		$this->_DescriptionAddedIconImageFormat = $value;
	}
	
	private $_DescriptionEditorIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getDescriptionEditorIconImageFormat() {
		if (isset($this->_DescriptionEditorIconImageFormat))
			return $this->_DescriptionEditorIconImageFormat;
		else
			return null;
	}
	public function setDescriptionEditorIconImageFormat($value) {
		$this->_DescriptionEditorIconImageFormat = $value;
	}
	
	private $_DescriptionEditorIconTooltip;
	/**
	* @return string
	*/
	public function getDescriptionEditorIconTooltip() {
		if (isset($this->_DescriptionEditorIconTooltip))
			return $this->_DescriptionEditorIconTooltip;
		else
			return null;
	}
	public function setDescriptionEditorIconTooltip($value) {
		$this->_DescriptionEditorIconTooltip = $value;
	}
	
	private $_EnableDisproportionalExifThumbnails;
	/**
	* @return boolean
	*/
	public function getEnableDisproportionalExifThumbnails() {
		if (isset($this->_EnableDisproportionalExifThumbnails))
			return $this->_EnableDisproportionalExifThumbnails;
		else
			return null;
	}
	public function setEnableDisproportionalExifThumbnails($value) {
		$this->_EnableDisproportionalExifThumbnails = $value;
	}
	
	private $_EnableFileNameTooltip;
	/**
	* @return boolean
	*/
	public function getEnableFileNameTooltip() {
		if (isset($this->_EnableFileNameTooltip))
			return $this->_EnableFileNameTooltip;
		else
			return null;
	}
	public function setEnableFileNameTooltip($value) {
		$this->_EnableFileNameTooltip = $value;
	}
	
	private $_HoverBorderColor;
	/**
	* @return string
	*/
	public function getHoverBorderColor() {
		if (isset($this->_HoverBorderColor))
			return $this->_HoverBorderColor;
		else
			return null;
	}
	public function setHoverBorderColor($value) {
		$this->_HoverBorderColor = $value;
	}
	
	private $_HoverColor;
	/**
	* @return string
	*/
	public function getHoverColor() {
		if (isset($this->_HoverColor))
			return $this->_HoverColor;
		else
			return null;
	}
	public function setHoverColor($value) {
		$this->_HoverColor = $value;
	}
	
	private $_ImageCroppedIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getImageCroppedIconImageFormat() {
		if (isset($this->_ImageCroppedIconImageFormat))
			return $this->_ImageCroppedIconImageFormat;
		else
			return null;
	}
	public function setImageCroppedIconImageFormat($value) {
		$this->_ImageCroppedIconImageFormat = $value;
	}
	
	private $_ImageCroppedIconTooltip;
	/**
	* @return string
	*/
	public function getImageCroppedIconTooltip() {
		if (isset($this->_ImageCroppedIconTooltip))
			return $this->_ImageCroppedIconTooltip;
		else
			return null;
	}
	public function setImageCroppedIconTooltip($value) {
		$this->_ImageCroppedIconTooltip = $value;
	}
	
	private $_ImageEditorIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getImageEditorIconImageFormat() {
		if (isset($this->_ImageEditorIconImageFormat))
			return $this->_ImageEditorIconImageFormat;
		else
			return null;
	}
	public function setImageEditorIconImageFormat($value) {
		$this->_ImageEditorIconImageFormat = $value;
	}
	
	private $_ImageEditorIconTooltip;
	/**
	* @return string
	*/
	public function getImageEditorIconTooltip() {
		if (isset($this->_ImageEditorIconTooltip))
			return $this->_ImageEditorIconTooltip;
		else
			return null;
	}
	public function setImageEditorIconTooltip($value) {
		$this->_ImageEditorIconTooltip = $value;
	}
	
	private $_InactiveSelectionBorderColor;
	/**
	* @return string
	*/
	public function getInactiveSelectionBorderColor() {
		if (isset($this->_InactiveSelectionBorderColor))
			return $this->_InactiveSelectionBorderColor;
		else
			return null;
	}
	public function setInactiveSelectionBorderColor($value) {
		$this->_InactiveSelectionBorderColor = $value;
	}
	
	private $_InactiveSelectionColor;
	/**
	* @return string
	*/
	public function getInactiveSelectionColor() {
		if (isset($this->_InactiveSelectionColor))
			return $this->_InactiveSelectionColor;
		else
			return null;
	}
	public function setInactiveSelectionColor($value) {
		$this->_InactiveSelectionColor = $value;
	}
	
	private $_PreviewQuality;
	/**
	* @return string
	*/
	public function getPreviewQuality() {
		if (isset($this->_PreviewQuality))
			return $this->_PreviewQuality;
		else
			return null;
	}
	public function setPreviewQuality($value) {
		$this->_PreviewQuality = $value;
	}
	
	private $_QualityMeter;
	/**
	* @return QualityMeter
	*/
	public function getQualityMeter() {
		if (isset($this->_QualityMeter))
			return $this->_QualityMeter;
		else
			return null;
	}
	public function setQualityMeter($value) {
		$this->_QualityMeter = $value;
	}
	
	private $_RemovalIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getRemovalIconImageFormat() {
		if (isset($this->_RemovalIconImageFormat))
			return $this->_RemovalIconImageFormat;
		else
			return null;
	}
	public function setRemovalIconImageFormat($value) {
		$this->_RemovalIconImageFormat = $value;
	}
	
	private $_RemovalIconTooltip;
	/**
	* @return string
	*/
	public function getRemovalIconTooltip() {
		if (isset($this->_RemovalIconTooltip))
			return $this->_RemovalIconTooltip;
		else
			return null;
	}
	public function setRemovalIconTooltip($value) {
		$this->_RemovalIconTooltip = $value;
	}
	
	private $_RotationIconImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getRotationIconImageFormat() {
		if (isset($this->_RotationIconImageFormat))
			return $this->_RotationIconImageFormat;
		else
			return null;
	}
	public function setRotationIconImageFormat($value) {
		$this->_RotationIconImageFormat = $value;
	}
	
	private $_RotationIconTooltip;
	/**
	* @return string
	*/
	public function getRotationIconTooltip() {
		if (isset($this->_RotationIconTooltip))
			return $this->_RotationIconTooltip;
		else
			return null;
	}
	public function setRotationIconTooltip($value) {
		$this->_RotationIconTooltip = $value;
	}
	
	private $_SelectedTextColor;
	/**
	* @return string
	*/
	public function getSelectedTextColor() {
		if (isset($this->_SelectedTextColor))
			return $this->_SelectedTextColor;
		else
			return null;
	}
	public function setSelectedTextColor($value) {
		$this->_SelectedTextColor = $value;
	}
	
	private $_SelectionBorderColor;
	/**
	* @return string
	*/
	public function getSelectionBorderColor() {
		if (isset($this->_SelectionBorderColor))
			return $this->_SelectionBorderColor;
		else
			return null;
	}
	public function setSelectionBorderColor($value) {
		$this->_SelectionBorderColor = $value;
	}
	
	private $_SelectionColor;
	/**
	* @return string
	*/
	public function getSelectionColor() {
		if (isset($this->_SelectionColor))
			return $this->_SelectionColor;
		else
			return null;
	}
	public function setSelectionColor($value) {
		$this->_SelectionColor = $value;
	}
	
	private $_SelectionHoverBorderColor;
	/**
	* @return string
	*/
	public function getSelectionHoverBorderColor() {
		if (isset($this->_SelectionHoverBorderColor))
			return $this->_SelectionHoverBorderColor;
		else
			return null;
	}
	public function setSelectionHoverBorderColor($value) {
		$this->_SelectionHoverBorderColor = $value;
	}
	
	private $_SelectionHoverColor;
	/**
	* @return string
	*/
	public function getSelectionHoverColor() {
		if (isset($this->_SelectionHoverColor))
			return $this->_SelectionHoverColor;
		else
			return null;
	}
	public function setSelectionHoverColor($value) {
		$this->_SelectionHoverColor = $value;
	}
	
	private $_ShowFileNameInThumbnailsView;
	/**
	* @return boolean
	*/
	public function getShowFileNameInThumbnailsView() {
		if (isset($this->_ShowFileNameInThumbnailsView))
			return $this->_ShowFileNameInThumbnailsView;
		else
			return null;
	}
	public function setShowFileNameInThumbnailsView($value) {
		$this->_ShowFileNameInThumbnailsView = $value;
	}
	

  function __construct(){
    
		$this->setDescriptionAddedIconImageFormat(new ImageFormat());
		$this->setDescriptionEditorIconImageFormat(new ImageFormat());
		$this->setDescriptionEditorIconTooltip('Edit description');
		$this->setEnableDisproportionalExifThumbnails(true);
		$this->setEnableFileNameTooltip(false);
		$this->setHoverBorderColor('#99DEFD');
		$this->setHoverColor('#F5FAFD;#EDF8FE');
		$this->setImageCroppedIconImageFormat(new ImageFormat());
		$this->setImageCroppedIconTooltip('The image is cropped.');
		$this->setImageEditorIconImageFormat(new ImageFormat());
		$this->setImageEditorIconTooltip('Preview / edit image');
		$this->setInactiveSelectionBorderColor('#D9D9D9');
		$this->setInactiveSelectionColor('#f8f8f8;#e5e5e5');
		$this->setPreviewQuality('Medium');
		$this->setQualityMeter(new QualityMeter());
		$this->setRemovalIconImageFormat(new ImageFormat());
		$this->setRemovalIconTooltip('Remove');
		$this->setRotationIconImageFormat(new ImageFormat());
		$this->setRotationIconTooltip('Rotate');
		$this->setSelectedTextColor('#000000');
		$this->setSelectionBorderColor('#99defd');
		$this->setSelectionColor('#f0f8fd;#d5effc');
		$this->setSelectionHoverBorderColor('#99defd');
		$this->setSelectionHoverColor('#e8f6fd;#c4e8fa');
		$this->setShowFileNameInThumbnailsView(false);

    $this->attributes = array();
    
		$this->attributes['DescriptionAddedIconImageFormat'] = array('jsName' => 'descriptionAddedIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['DescriptionEditorIconImageFormat'] = array('jsName' => 'descriptionEditorIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['DescriptionEditorIconTooltip'] = array('jsName' => 'descriptionEditorIconTooltip','jsType' => 'String','defaultValue' => 'Edit description');
		$this->attributes['EnableDisproportionalExifThumbnails'] = array('jsName' => 'enableDisproportionalExifThumbnails','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableFileNameTooltip'] = array('jsName' => 'enableFileNameTooltip','jsType' => 'Boolean','defaultValue' => false);
		$this->attributes['HoverBorderColor'] = array('jsName' => 'hoverBorderColor','jsType' => 'String','defaultValue' => '#99DEFD');
		$this->attributes['HoverColor'] = array('jsName' => 'hoverColor','jsType' => 'String','defaultValue' => '#F5FAFD;#EDF8FE');
		$this->attributes['ImageCroppedIconImageFormat'] = array('jsName' => 'imageCroppedIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['ImageCroppedIconTooltip'] = array('jsName' => 'imageCroppedIconTooltip','jsType' => 'String','defaultValue' => 'The image is cropped.');
		$this->attributes['ImageEditorIconImageFormat'] = array('jsName' => 'imageEditorIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['ImageEditorIconTooltip'] = array('jsName' => 'imageEditorIconTooltip','jsType' => 'String','defaultValue' => 'Preview / edit image');
		$this->attributes['InactiveSelectionBorderColor'] = array('jsName' => 'inactiveSelectionBorderColor','jsType' => 'String','defaultValue' => '#D9D9D9');
		$this->attributes['InactiveSelectionColor'] = array('jsName' => 'inactiveSelectionColor','jsType' => 'String','defaultValue' => '#f8f8f8;#e5e5e5');
		$this->attributes['PreviewQuality'] = array('jsName' => 'previewQuality','jsType' => 'String','defaultValue' => 'Medium');
		$this->attributes['QualityMeter'] = array('jsName' => 'qualityMeter','jsType' => 'qualityMeter','defaultValue' => '[new]');
		$this->attributes['RemovalIconImageFormat'] = array('jsName' => 'removalIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['RemovalIconTooltip'] = array('jsName' => 'removalIconTooltip','jsType' => 'String','defaultValue' => 'Remove');
		$this->attributes['RotationIconImageFormat'] = array('jsName' => 'rotationIconImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['RotationIconTooltip'] = array('jsName' => 'rotationIconTooltip','jsType' => 'String','defaultValue' => 'Rotate');
		$this->attributes['SelectedTextColor'] = array('jsName' => 'selectedTextColor','jsType' => 'String','defaultValue' => '#000000');
		$this->attributes['SelectionBorderColor'] = array('jsName' => 'selectionBorderColor','jsType' => 'String','defaultValue' => '#99defd');
		$this->attributes['SelectionColor'] = array('jsName' => 'selectionColor','jsType' => 'String','defaultValue' => '#f0f8fd;#d5effc');
		$this->attributes['SelectionHoverBorderColor'] = array('jsName' => 'selectionHoverBorderColor','jsType' => 'String','defaultValue' => '#99defd');
		$this->attributes['SelectionHoverColor'] = array('jsName' => 'selectionHoverColor','jsType' => 'String','defaultValue' => '#e8f6fd;#c4e8fa');
		$this->attributes['ShowFileNameInThumbnailsView'] = array('jsName' => 'showFileNameInThumbnailsView','jsType' => 'Boolean','defaultValue' => false);
  }

}