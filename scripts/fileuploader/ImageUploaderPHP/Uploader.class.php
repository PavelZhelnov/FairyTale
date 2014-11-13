<?php

require_once 'BaseControl.class.php';
require_once 'ImageFormat.class.php';
require_once 'FontFormat.class.php';
require_once 'ActiveXControl.class.php';
require_once 'AddFilesProgressDialog.class.php';
require_once 'AuthenticationDialog.class.php';
require_once 'ClientEvents.class.php';
require_once 'ContextMenu.class.php';
require_once 'Converter.class.php';
require_once 'DeleteFilesDialog.class.php';
require_once 'DescriptionEditor.class.php';
require_once 'FolderPane.class.php';
require_once 'ImageEditor.class.php';
require_once 'InformationBar.class.php';
require_once 'JavaControl.class.php';
require_once 'Messages.class.php';
require_once 'Metadata.class.php';
require_once 'DetailsViewColumns.class.php';
require_once 'PaneItem.class.php';
require_once 'Restrictions.class.php';
require_once 'StatusPane.class.php';
require_once 'TreePane.class.php';
require_once 'UploadPane.class.php';
require_once 'UploadProgressDialog.class.php';
require_once 'UploadSettings.class.php';
require_once 'Utils.class.php';

final class Uploader extends BaseControl {
  public $attributes;

  
	private $_ActiveXControl;
	/**
	* @return ActiveXControl
	*/
	public function getActiveXControl() {
		if (isset($this->_ActiveXControl))
			return $this->_ActiveXControl;
		else
			return null;
	}
	public function setActiveXControl($value) {
		$this->_ActiveXControl = $value;
	}
	
	private $_AddFilesProgressDialog;
	/**
	* @return AddFilesProgressDialog
	*/
	public function getAddFilesProgressDialog() {
		if (isset($this->_AddFilesProgressDialog))
			return $this->_AddFilesProgressDialog;
		else
			return null;
	}
	public function setAddFilesProgressDialog($value) {
		$this->_AddFilesProgressDialog = $value;
	}
	
	private $_AuthenticationDialog;
	/**
	* @return AuthenticationDialog
	*/
	public function getAuthenticationDialog() {
		if (isset($this->_AuthenticationDialog))
			return $this->_AuthenticationDialog;
		else
			return null;
	}
	public function setAuthenticationDialog($value) {
		$this->_AuthenticationDialog = $value;
	}
	
	private $_AuxiliaryTextColor;
	/**
	* @return string
	*/
	public function getAuxiliaryTextColor() {
		if (isset($this->_AuxiliaryTextColor))
			return $this->_AuxiliaryTextColor;
		else
			return null;
	}
	public function setAuxiliaryTextColor($value) {
		$this->_AuxiliaryTextColor = $value;
	}
	
	private $_BackgroundColor;
	/**
	* @return string
	*/
	public function getBackgroundColor() {
		if (isset($this->_BackgroundColor))
			return $this->_BackgroundColor;
		else
			return null;
	}
	public function setBackgroundColor($value) {
		$this->_BackgroundColor = $value;
	}
	
	private $_BorderStyle;
	/**
	* @return string
	*/
	public function getBorderStyle() {
		if (isset($this->_BorderStyle))
			return $this->_BorderStyle;
		else
			return null;
	}
	public function setBorderStyle($value) {
		$this->_BorderStyle = $value;
	}
	
	private $_CancelUploadButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getCancelUploadButtonImageFormat() {
		if (isset($this->_CancelUploadButtonImageFormat))
			return $this->_CancelUploadButtonImageFormat;
		else
			return null;
	}
	public function setCancelUploadButtonImageFormat($value) {
		$this->_CancelUploadButtonImageFormat = $value;
	}
	
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
	
	private $_ClientEvents;
	/**
	* @return ClientEvents
	*/
	public function getClientEvents() {
		if (isset($this->_ClientEvents))
			return $this->_ClientEvents;
		else
			return null;
	}
	public function setClientEvents($value) {
		$this->_ClientEvents = $value;
	}
	
	private $_ContextMenu;
	/**
	* @return ContextMenu
	*/
	public function getContextMenu() {
		if (isset($this->_ContextMenu))
			return $this->_ContextMenu;
		else
			return null;
	}
	public function setContextMenu($value) {
		$this->_ContextMenu = $value;
	}
	
	private $_Converters;
	/**
	* @return array
	*/
	public function &getConverters() {
		return $this->_Converters;
	}
	public function setConverters($value) {
		if (is_array($value)) {
			$this->_Converters = $value;
		} else {
			$this->_Converters = array($value);
		}
	}
	
	private $_DeleteFilesDialog;
	/**
	* @return DeleteFilesDialog
	*/
	public function getDeleteFilesDialog() {
		if (isset($this->_DeleteFilesDialog))
			return $this->_DeleteFilesDialog;
		else
			return null;
	}
	public function setDeleteFilesDialog($value) {
		$this->_DeleteFilesDialog = $value;
	}
	
	private $_DescriptionEditor;
	/**
	* @return DescriptionEditor
	*/
	public function getDescriptionEditor() {
		if (isset($this->_DescriptionEditor))
			return $this->_DescriptionEditor;
		else
			return null;
	}
	public function setDescriptionEditor($value) {
		$this->_DescriptionEditor = $value;
	}
	
	private $_DetailsViewColumns;
	/**
	* @return DetailsViewColumns
	*/
	public function getDetailsViewColumns() {
		if (isset($this->_DetailsViewColumns))
			return $this->_DetailsViewColumns;
		else
			return null;
	}
	public function setDetailsViewColumns($value) {
		$this->_DetailsViewColumns = $value;
	}
	
	private $_DialogColor;
	/**
	* @return string
	*/
	public function getDialogColor() {
		if (isset($this->_DialogColor))
			return $this->_DialogColor;
		else
			return null;
	}
	public function setDialogColor($value) {
		$this->_DialogColor = $value;
	}
	
	private $_DialogBorderColor;
	/**
	* @return string
	*/
	public function getDialogBorderColor() {
		if (isset($this->_DialogBorderColor))
			return $this->_DialogBorderColor;
		else
			return null;
	}
	public function setDialogBorderColor($value) {
		$this->_DialogBorderColor = $value;
	}
	
	private $_EnableAutoRotation;
	/**
	* @return boolean
	*/
	public function getEnableAutoRotation() {
		if (isset($this->_EnableAutoRotation))
			return $this->_EnableAutoRotation;
		else
			return null;
	}
	public function setEnableAutoRotation($value) {
		$this->_EnableAutoRotation = $value;
	}
	
	private $_EnableContextMenu;
	/**
	* @return boolean
	*/
	public function getEnableContextMenu() {
		if (isset($this->_EnableContextMenu))
			return $this->_EnableContextMenu;
		else
			return null;
	}
	public function setEnableContextMenu($value) {
		$this->_EnableContextMenu = $value;
	}
	
	private $_EnableDescriptionEditor;
	/**
	* @return boolean
	*/
	public function getEnableDescriptionEditor() {
		if (isset($this->_EnableDescriptionEditor))
			return $this->_EnableDescriptionEditor;
		else
			return null;
	}
	public function setEnableDescriptionEditor($value) {
		$this->_EnableDescriptionEditor = $value;
	}
	
	private $_EnableDragAndDrop;
	/**
	* @return boolean
	*/
	public function getEnableDragAndDrop() {
		if (isset($this->_EnableDragAndDrop))
			return $this->_EnableDragAndDrop;
		else
			return null;
	}
	public function setEnableDragAndDrop($value) {
		$this->_EnableDragAndDrop = $value;
	}
	
	private $_EnableImageEditor;
	/**
	* @return boolean
	*/
	public function getEnableImageEditor() {
		if (isset($this->_EnableImageEditor))
			return $this->_EnableImageEditor;
		else
			return null;
	}
	public function setEnableImageEditor($value) {
		$this->_EnableImageEditor = $value;
	}
	
	private $_EnableFileViewer;
	/**
	* @return boolean
	*/
	public function getEnableFileViewer() {
		if (isset($this->_EnableFileViewer))
			return $this->_EnableFileViewer;
		else
			return null;
	}
	public function setEnableFileViewer($value) {
		$this->_EnableFileViewer = $value;
	}
	
	private $_EnableOriginalFilesDeletion;
	/**
	* @return boolean
	*/
	public function getEnableOriginalFilesDeletion() {
		if (isset($this->_EnableOriginalFilesDeletion))
			return $this->_EnableOriginalFilesDeletion;
		else
			return null;
	}
	public function setEnableOriginalFilesDeletion($value) {
		$this->_EnableOriginalFilesDeletion = $value;
	}
	
	private $_EnableRotation;
	/**
	* @return boolean
	*/
	public function getEnableRotation() {
		if (isset($this->_EnableRotation))
			return $this->_EnableRotation;
		else
			return null;
	}
	public function setEnableRotation($value) {
		$this->_EnableRotation = $value;
	}
	
	private $_EnableStatusPane;
	/**
	* @return boolean
	*/
	public function getEnableStatusPane() {
		if (isset($this->_EnableStatusPane))
			return $this->_EnableStatusPane;
		else
			return null;
	}
	public function setEnableStatusPane($value) {
		$this->_EnableStatusPane = $value;
	}
	
	private $_EnableUploadPane;
	/**
	* @return boolean
	*/
	public function getEnableUploadPane() {
		if (isset($this->_EnableUploadPane))
			return $this->_EnableUploadPane;
		else
			return null;
	}
	public function setEnableUploadPane($value) {
		$this->_EnableUploadPane = $value;
	}
	
	private $_EnableUploadProgress;
	/**
	* @return boolean
	*/
	public function getEnableUploadProgress() {
		if (isset($this->_EnableUploadProgress))
			return $this->_EnableUploadProgress;
		else
			return null;
	}
	public function setEnableUploadProgress($value) {
		$this->_EnableUploadProgress = $value;
	}
	
	private $_FolderPane;
	/**
	* @return FolderPane
	*/
	public function getFolderPane() {
		if (isset($this->_FolderPane))
			return $this->_FolderPane;
		else
			return null;
	}
	public function setFolderPane($value) {
		$this->_FolderPane = $value;
	}
	
	private $_FolderProcessingMode;
	/**
	* @return string
	*/
	public function getFolderProcessingMode() {
		if (isset($this->_FolderProcessingMode))
			return $this->_FolderProcessingMode;
		else
			return null;
	}
	public function setFolderProcessingMode($value) {
		$this->_FolderProcessingMode = $value;
	}
	
	private $_HeaderColor;
	/**
	* @return string
	*/
	public function getHeaderColor() {
		if (isset($this->_HeaderColor))
			return $this->_HeaderColor;
		else
			return null;
	}
	public function setHeaderColor($value) {
		$this->_HeaderColor = $value;
	}
	
	private $_HeaderTextColor;
	/**
	* @return string
	*/
	public function getHeaderTextColor() {
		if (isset($this->_HeaderTextColor))
			return $this->_HeaderTextColor;
		else
			return null;
	}
	public function setHeaderTextColor($value) {
		$this->_HeaderTextColor = $value;
	}
	
	private $_Height;
	/**
	* @return string
	*/
	public function getHeight() {
		if (isset($this->_Height))
			return $this->_Height;
		else
			return null;
	}
	public function setHeight($value) {
		$this->_Height = $value;
	}
	
	private $_HyperlinkColor;
	/**
	* @return string
	*/
	public function getHyperlinkColor() {
		if (isset($this->_HyperlinkColor))
			return $this->_HyperlinkColor;
		else
			return null;
	}
	public function setHyperlinkColor($value) {
		$this->_HyperlinkColor = $value;
	}
	
	private $_ImageEditor;
	/**
	* @return ImageEditor
	*/
	public function getImageEditor() {
		if (isset($this->_ImageEditor))
			return $this->_ImageEditor;
		else
			return null;
	}
	public function setImageEditor($value) {
		$this->_ImageEditor = $value;
	}
	
	private $_InformationBar;
	/**
	* @return InformationBar
	*/
	public function getInformationBar() {
		if (isset($this->_InformationBar))
			return $this->_InformationBar;
		else
			return null;
	}
	public function setInformationBar($value) {
		$this->_InformationBar = $value;
	}
	
	private $_JavaControl;
	/**
	* @return JavaControl
	*/
	public function getJavaControl() {
		if (isset($this->_JavaControl))
			return $this->_JavaControl;
		else
			return null;
	}
	public function setJavaControl($value) {
		$this->_JavaControl = $value;
	}
	
	private $_LicenseKey;
	/**
	* @return string
	*/
	public function getLicenseKey() {
		if (isset($this->_LicenseKey))
			return $this->_LicenseKey;
		else
			return null;
	}
	public function setLicenseKey($value) {
		$this->_LicenseKey = $value;
	}
	
	private $_LoadingFolderContentText;
	/**
	* @return string
	*/
	public function getLoadingFolderContentText() {
		if (isset($this->_LoadingFolderContentText))
			return $this->_LoadingFolderContentText;
		else
			return null;
	}
	public function setLoadingFolderContentText($value) {
		$this->_LoadingFolderContentText = $value;
	}
	
	private $_Messages;
	/**
	* @return Messages
	*/
	public function getMessages() {
		if (isset($this->_Messages))
			return $this->_Messages;
		else
			return null;
	}
	public function setMessages($value) {
		$this->_Messages = $value;
	}
	
	private $_Metadata;
	/**
	* @return Metadata
	*/
	public function getMetadata() {
		if (isset($this->_Metadata))
			return $this->_Metadata;
		else
			return null;
	}
	public function setMetadata($value) {
		$this->_Metadata = $value;
	}
	
	private $_PaneFont;
	/**
	* @return FontFormat
	*/
	public function getPaneFont() {
		if (isset($this->_PaneFont))
			return $this->_PaneFont;
		else
			return null;
	}
	public function setPaneFont($value) {
		$this->_PaneFont = $value;
	}
	
	private $_PaneItem;
	/**
	* @return PaneItem
	*/
	public function getPaneItem() {
		if (isset($this->_PaneItem))
			return $this->_PaneItem;
		else
			return null;
	}
	public function setPaneItem($value) {
		$this->_PaneItem = $value;
	}
	
	private $_PaneLayout;
	/**
	* @return string
	*/
	public function getPaneLayout() {
		if (isset($this->_PaneLayout))
			return $this->_PaneLayout;
		else
			return null;
	}
	public function setPaneLayout($value) {
		$this->_PaneLayout = $value;
	}
	
	private $_PanelColor;
	/**
	* @return string
	*/
	public function getPanelColor() {
		if (isset($this->_PanelColor))
			return $this->_PanelColor;
		else
			return null;
	}
	public function setPanelColor($value) {
		$this->_PanelColor = $value;
	}
	
	private $_PanelBorderColor;
	/**
	* @return string
	*/
	public function getPanelBorderColor() {
		if (isset($this->_PanelBorderColor))
			return $this->_PanelBorderColor;
		else
			return null;
	}
	public function setPanelBorderColor($value) {
		$this->_PanelBorderColor = $value;
	}
	
	private $_PasteFileNameTemplate;
	/**
	* @return string
	*/
	public function getPasteFileNameTemplate() {
		if (isset($this->_PasteFileNameTemplate))
			return $this->_PasteFileNameTemplate;
		else
			return null;
	}
	public function setPasteFileNameTemplate($value) {
		$this->_PasteFileNameTemplate = $value;
	}
	
	private $_Restrictions;
	/**
	* @return Restrictions
	*/
	public function getRestrictions() {
		if (isset($this->_Restrictions))
			return $this->_Restrictions;
		else
			return null;
	}
	public function setRestrictions($value) {
		$this->_Restrictions = $value;
	}
	
	private $_StatusPane;
	/**
	* @return StatusPane
	*/
	public function getStatusPane() {
		if (isset($this->_StatusPane))
			return $this->_StatusPane;
		else
			return null;
	}
	public function setStatusPane($value) {
		$this->_StatusPane = $value;
	}
	
	private $_TextColor;
	/**
	* @return string
	*/
	public function getTextColor() {
		if (isset($this->_TextColor))
			return $this->_TextColor;
		else
			return null;
	}
	public function setTextColor($value) {
		$this->_TextColor = $value;
	}
	
	private $_TitleFont;
	/**
	* @return FontFormat
	*/
	public function getTitleFont() {
		if (isset($this->_TitleFont))
			return $this->_TitleFont;
		else
			return null;
	}
	public function setTitleFont($value) {
		$this->_TitleFont = $value;
	}
	
	private $_TreePane;
	/**
	* @return TreePane
	*/
	public function getTreePane() {
		if (isset($this->_TreePane))
			return $this->_TreePane;
		else
			return null;
	}
	public function setTreePane($value) {
		$this->_TreePane = $value;
	}
	
	private $_UploadButtonImageFormat;
	/**
	* @return ImageFormat
	*/
	public function getUploadButtonImageFormat() {
		if (isset($this->_UploadButtonImageFormat))
			return $this->_UploadButtonImageFormat;
		else
			return null;
	}
	public function setUploadButtonImageFormat($value) {
		$this->_UploadButtonImageFormat = $value;
	}
	
	private $_UploadButtonText;
	/**
	* @return string
	*/
	public function getUploadButtonText() {
		if (isset($this->_UploadButtonText))
			return $this->_UploadButtonText;
		else
			return null;
	}
	public function setUploadButtonText($value) {
		$this->_UploadButtonText = $value;
	}
	
	private $_UploadPane;
	/**
	* @return UploadPane
	*/
	public function getUploadPane() {
		if (isset($this->_UploadPane))
			return $this->_UploadPane;
		else
			return null;
	}
	public function setUploadPane($value) {
		$this->_UploadPane = $value;
	}
	
	private $_UploadProgressDialog;
	/**
	* @return UploadProgressDialog
	*/
	public function getUploadProgressDialog() {
		if (isset($this->_UploadProgressDialog))
			return $this->_UploadProgressDialog;
		else
			return null;
	}
	public function setUploadProgressDialog($value) {
		$this->_UploadProgressDialog = $value;
	}
	
	private $_UploadSettings;
	/**
	* @return UploadSettings
	*/
	public function getUploadSettings() {
		if (isset($this->_UploadSettings))
			return $this->_UploadSettings;
		else
			return null;
	}
	public function setUploadSettings($value) {
		$this->_UploadSettings = $value;
	}
	
	private $_Width;
	/**
	* @return string
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
	
	private $_Language;
	/**
	* @return string
	*/
	public function getLanguage() {
		if (isset($this->_Language))
			return $this->_Language;
		else
			return null;
	}
	public function setLanguage($value) {
		$this->_Language = $value;
	}
	

  function __construct($id = NULL) {
    parent::__construct($id);
    $this->_Converters = array();

    
		$this->setActiveXControl(new ActiveXControl());
		$this->setAddFilesProgressDialog(new AddFilesProgressDialog());
		$this->setAuthenticationDialog(new AuthenticationDialog());
		$this->setAuxiliaryTextColor('#8b8b8b');
		$this->setBackgroundColor('#ffffff');
		$this->setBorderStyle('Fixed3D');
		$this->setCancelUploadButtonImageFormat(new ImageFormat());
		$this->setCancelUploadButtonText('Cancel');
		$this->setClientEvents(new ClientEvents());
		$this->setContextMenu(new ContextMenu());
		$this->setDeleteFilesDialog(new DeleteFilesDialog());
		$this->setDescriptionEditor(new DescriptionEditor());
		$this->setDetailsViewColumns(new DetailsViewColumns());
		$this->setDialogColor('#e7f7ff');
		$this->setDialogBorderColor('#98b6ca');
		$this->setEnableAutoRotation(false);
		$this->setEnableContextMenu(true);
		$this->setEnableDescriptionEditor(true);
		$this->setEnableDragAndDrop(true);
		$this->setEnableImageEditor(true);
		$this->setEnableFileViewer(true);
		$this->setEnableOriginalFilesDeletion(false);
		$this->setEnableRotation(true);
		$this->setEnableStatusPane(true);
		$this->setEnableUploadPane(true);
		$this->setEnableUploadProgress(true);
		$this->setFolderPane(new FolderPane());
		$this->setFolderProcessingMode('Skip');
		$this->setHeaderColor('#f2f6fb;#c4defb');
		$this->setHeaderTextColor('#1a64a8');
		$this->setHeight('400px');
		$this->setHyperlinkColor('#0066cc');
		$this->setImageEditor(new ImageEditor());
		$this->setInformationBar(new InformationBar());
		$this->setJavaControl(new JavaControl());
		$this->setLoadingFolderContentText('Loading content...');
		$this->setMessages(new Messages());
		$this->setMetadata(new Metadata());
		$this->setPaneFont(new FontFormat());
		$this->setPaneItem(new PaneItem());
		$this->setPaneLayout('TreePanes');
		$this->setPanelColor('#f5f5f5');
		$this->setPanelBorderColor('#aaaaaa');
		$this->setPasteFileNameTemplate('Paste_[date]_[time]');
		$this->setRestrictions(new Restrictions());
		$this->setStatusPane(new StatusPane());
		$this->setTextColor('#000000');
		$this->setTitleFont(new FontFormat());
		$this->setTreePane(new TreePane());
		$this->setUploadButtonImageFormat(new ImageFormat());
		$this->setUploadButtonText('Upload');
		$this->setUploadPane(new UploadPane());
		$this->setUploadProgressDialog(new UploadProgressDialog());
		$this->setUploadSettings(new UploadSettings());
		$this->setWidth('600px');

    
		$this->attributes['ActiveXControl'] = array('jsName' => 'activeXControl','jsType' => 'activeXControl','defaultValue' => '[new]');
		$this->attributes['AddFilesProgressDialog'] = array('jsName' => 'addFilesProgressDialog','jsType' => 'addFilesProgressDialog','defaultValue' => '[new]');
		$this->attributes['AuthenticationDialog'] = array('jsName' => 'authenticationDialog','jsType' => 'authenticationDialog','defaultValue' => '[new]');
		$this->attributes['AuxiliaryTextColor'] = array('jsName' => 'auxiliaryTextColor','jsType' => 'String','defaultValue' => '#8b8b8b');
		$this->attributes['BackgroundColor'] = array('jsName' => 'backgroundColor','jsType' => 'String','defaultValue' => '#ffffff');
		$this->attributes['BorderStyle'] = array('jsName' => 'borderStyle','jsType' => 'String','defaultValue' => 'Fixed3D');
		$this->attributes['CancelUploadButtonImageFormat'] = array('jsName' => 'cancelUploadButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['CancelUploadButtonText'] = array('jsName' => 'cancelUploadButtonText','jsType' => 'String','defaultValue' => 'Cancel');
		$this->attributes['ClientEvents'] = array('jsName' => 'events','jsType' => 'events','defaultValue' => '[new]');
		$this->attributes['ContextMenu'] = array('jsName' => 'contextMenu','jsType' => 'contextMenu','defaultValue' => '[new]');
		$this->attributes['Converters'] = array('jsName' => 'converters','jsType' => 'converters','defaultValue' => '[new]');
		$this->attributes['DeleteFilesDialog'] = array('jsName' => 'deleteFilesDialog','jsType' => 'deleteFilesDialog','defaultValue' => '[new]');
		$this->attributes['DescriptionEditor'] = array('jsName' => 'descriptionEditor','jsType' => 'descriptionEditor','defaultValue' => '[new]');
		$this->attributes['DetailsViewColumns'] = array('jsName' => 'detailsViewColumns','jsType' => 'detailsViewColumns','defaultValue' => '[new]');
		$this->attributes['DialogColor'] = array('jsName' => 'dialogColor','jsType' => 'String','defaultValue' => '#e7f7ff');
		$this->attributes['DialogBorderColor'] = array('jsName' => 'dialogBorderColor','jsType' => 'String','defaultValue' => '#98b6ca');
		$this->attributes['EnableAutoRotation'] = array('jsName' => 'enableAutoRotation','jsType' => 'Boolean','defaultValue' => false);
		$this->attributes['EnableContextMenu'] = array('jsName' => 'enableContextMenu','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableDescriptionEditor'] = array('jsName' => 'enableDescriptionEditor','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableDragAndDrop'] = array('jsName' => 'enableDragAndDrop','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableImageEditor'] = array('jsName' => 'enableImageEditor','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableFileViewer'] = array('jsName' => 'enableFileViewer','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableOriginalFilesDeletion'] = array('jsName' => 'enableOriginalFilesDeletion','jsType' => 'Boolean','defaultValue' => false);
		$this->attributes['EnableRotation'] = array('jsName' => 'enableRotation','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableStatusPane'] = array('jsName' => 'enableStatusPane','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableUploadPane'] = array('jsName' => 'enableUploadPane','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['EnableUploadProgress'] = array('jsName' => 'enableUploadProgress','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['FolderPane'] = array('jsName' => 'folderPane','jsType' => 'folderPane','defaultValue' => '[new]');
		$this->attributes['FolderProcessingMode'] = array('jsName' => 'folderProcessingMode','jsType' => 'String','defaultValue' => 'Skip');
		$this->attributes['HeaderColor'] = array('jsName' => 'headerColor','jsType' => 'String','defaultValue' => '#f2f6fb;#c4defb');
		$this->attributes['HeaderTextColor'] = array('jsName' => 'headerTextColor','jsType' => 'String','defaultValue' => '#1a64a8');
		$this->attributes['Height'] = array('jsName' => 'height','jsType' => 'String','defaultValue' => '400px');
		$this->attributes['HyperlinkColor'] = array('jsName' => 'hyperlinkColor','jsType' => 'String','defaultValue' => '#0066cc');
		$this->attributes['ID'] = array('jsName' => 'id','jsType' => 'String','defaultValue' => '');
		$this->attributes['ImageEditor'] = array('jsName' => 'imageEditor','jsType' => 'imageEditor','defaultValue' => '[new]');
		$this->attributes['InformationBar'] = array('jsName' => 'informationBar','jsType' => 'informationBar','defaultValue' => '[new]');
		$this->attributes['JavaControl'] = array('jsName' => 'javaControl','jsType' => 'javaControl','defaultValue' => '[new]');
		$this->attributes['LicenseKey'] = array('jsName' => 'licenseKey','jsType' => 'String','defaultValue' => '');
		$this->attributes['LoadingFolderContentText'] = array('jsName' => 'loadingFolderContentText','jsType' => 'String','defaultValue' => 'Loading content...');
		$this->attributes['Messages'] = array('jsName' => 'messages','jsType' => 'messages','defaultValue' => '[new]');
		$this->attributes['Metadata'] = array('jsName' => 'metadata','jsType' => 'metadata','defaultValue' => '[new]');
		$this->attributes['PaneFont'] = array('jsName' => 'paneFont','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['PaneItem'] = array('jsName' => 'paneItem','jsType' => 'paneItem','defaultValue' => '[new]');
		$this->attributes['PaneLayout'] = array('jsName' => 'paneLayout','jsType' => 'String','defaultValue' => 'TreePanes');
		$this->attributes['PanelColor'] = array('jsName' => 'panelColor','jsType' => 'String','defaultValue' => '#f5f5f5');
		$this->attributes['PanelBorderColor'] = array('jsName' => 'panelBorderColor','jsType' => 'String','defaultValue' => '#aaaaaa');
		$this->attributes['PasteFileNameTemplate'] = array('jsName' => 'pasteFileNameTemplate','jsType' => 'String','defaultValue' => 'Paste_[date]_[time]');
		$this->attributes['Restrictions'] = array('jsName' => 'restrictions','jsType' => 'restrictions','defaultValue' => '[new]');
		$this->attributes['StatusPane'] = array('jsName' => 'statusPane','jsType' => 'statusPane','defaultValue' => '[new]');
		$this->attributes['TextColor'] = array('jsName' => 'textColor','jsType' => 'String','defaultValue' => '#000000');
		$this->attributes['TitleFont'] = array('jsName' => 'titleFont','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['TreePane'] = array('jsName' => 'treePane','jsType' => 'treePane','defaultValue' => '[new]');
		$this->attributes['UploadButtonImageFormat'] = array('jsName' => 'uploadButtonImageFormat','jsType' => 'String','defaultValue' => '[new]');
		$this->attributes['UploadButtonText'] = array('jsName' => 'uploadButtonText','jsType' => 'String','defaultValue' => 'Upload');
		$this->attributes['UploadPane'] = array('jsName' => 'uploadPane','jsType' => 'uploadPane','defaultValue' => '[new]');
		$this->attributes['UploadProgressDialog'] = array('jsName' => 'uploadProgressDialog','jsType' => 'uploadProgressDialog','defaultValue' => '[new]');
		$this->attributes['UploadSettings'] = array('jsName' => 'uploadSettings','jsType' => 'uploadSettings','defaultValue' => '[new]');
		$this->attributes['Width'] = array('jsName' => 'width','jsType' => 'String','defaultValue' => '600px');
  }

  protected function getClientClassName() {
    return 'uploader';
  }

  function render() {

    if (isset($this->_preRenderCallbacks)) {
      foreach ($this->_preRenderCallbacks as $callback) {
        call_user_func($callback);
      }
    }

    $this->renderClientScripts();

    $html = array ();
    $html[] = "<script type=\"text/javascript\">";
    $html[] = "//<![CDATA[";

    //keep global namespace clean. wrap all script in anonymous function.
    $html[] = '(function() {';

    if ($this->getDebugScriptLevel() > 0) {
      $html[] = '$au.debug().level(' . $this->getDebugScriptLevel() . ');';
    }

    if ($this->getDebugScriptMode()) {
      $mode = $this->getDebugScriptMode();
      $values = explode(',', strtolower($mode));
      if (count($values) > 1) {
        $rg = '#console|popup|alert#';
        for ($i = 0, $imax = count($values); $i < $imax; $i++) {
          $m = NULL;
          if (preg_match($rg, $values[$i], $m)) {
            $values[$i] = "'" . $m[0] . "'";
          }
        }
        $mode = '[' . implode(',', $values) . ']';
      } else {
        $mode = "'$mode'";
      }
      $html[] = '$au.debug().mode(' . $mode . ');';
    }

    $html[] = 'var u = $au.uploader({id: "' . $this->getID() . '"});';

    $lang = $this->getLanguage();
    // add apply localization script
    if ($lang) {
      $html[] = 'u.set(' . $lang . '_localization);';
    }

    // add properties script
    $html[] = 'u.set(' . $this->getJson() . ');';

    //add session cookie
    $session_name = SESSION_PARAM_NAME;
    $sessin_id = session_id();
    $html[] = "u.metadata().addCustomField('$session_name', '$sessin_id')";

    // add write markup script
    if (!$this->getManualRendering()) {
      $html[] = 'u.writeHtml();';
    }

    $html[] = '})();';

    $html[] = "//]]>";
    $html[] = "</script>";

    echo implode("\n", $html);
  }
}