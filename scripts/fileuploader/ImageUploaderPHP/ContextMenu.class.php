<?php

class ContextMenu {
  public $attributes;

  
	private $_ArrangeByDimensionsText;
	/**
	* @return string
	*/
	public function getArrangeByDimensionsText() {
		if (isset($this->_ArrangeByDimensionsText))
			return $this->_ArrangeByDimensionsText;
		else
			return null;
	}
	public function setArrangeByDimensionsText($value) {
		$this->_ArrangeByDimensionsText = $value;
	}
	
	private $_ArrangeByModifiedText;
	/**
	* @return string
	*/
	public function getArrangeByModifiedText() {
		if (isset($this->_ArrangeByModifiedText))
			return $this->_ArrangeByModifiedText;
		else
			return null;
	}
	public function setArrangeByModifiedText($value) {
		$this->_ArrangeByModifiedText = $value;
	}
	
	private $_ArrangeByNameText;
	/**
	* @return string
	*/
	public function getArrangeByNameText() {
		if (isset($this->_ArrangeByNameText))
			return $this->_ArrangeByNameText;
		else
			return null;
	}
	public function setArrangeByNameText($value) {
		$this->_ArrangeByNameText = $value;
	}
	
	private $_ArrangeByPathText;
	/**
	* @return string
	*/
	public function getArrangeByPathText() {
		if (isset($this->_ArrangeByPathText))
			return $this->_ArrangeByPathText;
		else
			return null;
	}
	public function setArrangeByPathText($value) {
		$this->_ArrangeByPathText = $value;
	}
	
	private $_ArrangeBySizeText;
	/**
	* @return string
	*/
	public function getArrangeBySizeText() {
		if (isset($this->_ArrangeBySizeText))
			return $this->_ArrangeBySizeText;
		else
			return null;
	}
	public function setArrangeBySizeText($value) {
		$this->_ArrangeBySizeText = $value;
	}
	
	private $_ArrangeByText;
	/**
	* @return string
	*/
	public function getArrangeByText() {
		if (isset($this->_ArrangeByText))
			return $this->_ArrangeByText;
		else
			return null;
	}
	public function setArrangeByText($value) {
		$this->_ArrangeByText = $value;
	}
	
	private $_ArrangeByTypeText;
	/**
	* @return string
	*/
	public function getArrangeByTypeText() {
		if (isset($this->_ArrangeByTypeText))
			return $this->_ArrangeByTypeText;
		else
			return null;
	}
	public function setArrangeByTypeText($value) {
		$this->_ArrangeByTypeText = $value;
	}
	
	private $_CheckAllText;
	/**
	* @return string
	*/
	public function getCheckAllText() {
		if (isset($this->_CheckAllText))
			return $this->_CheckAllText;
		else
			return null;
	}
	public function setCheckAllText($value) {
		$this->_CheckAllText = $value;
	}
	
	private $_CheckText;
	/**
	* @return string
	*/
	public function getCheckText() {
		if (isset($this->_CheckText))
			return $this->_CheckText;
		else
			return null;
	}
	public function setCheckText($value) {
		$this->_CheckText = $value;
	}
	
	private $_DetailsViewText;
	/**
	* @return string
	*/
	public function getDetailsViewText() {
		if (isset($this->_DetailsViewText))
			return $this->_DetailsViewText;
		else
			return null;
	}
	public function setDetailsViewText($value) {
		$this->_DetailsViewText = $value;
	}
	
	private $_EditText;
	/**
	* @return string
	*/
	public function getEditText() {
		if (isset($this->_EditText))
			return $this->_EditText;
		else
			return null;
	}
	public function setEditText($value) {
		$this->_EditText = $value;
	}
	
	private $_EditDescriptionText;
	/**
	* @return string
	*/
	public function getEditDescriptionText() {
		if (isset($this->_EditDescriptionText))
			return $this->_EditDescriptionText;
		else
			return null;
	}
	public function setEditDescriptionText($value) {
		$this->_EditDescriptionText = $value;
	}
	
	private $_ListViewText;
	/**
	* @return string
	*/
	public function getListViewText() {
		if (isset($this->_ListViewText))
			return $this->_ListViewText;
		else
			return null;
	}
	public function setListViewText($value) {
		$this->_ListViewText = $value;
	}
	
	private $_OpenText;
	/**
	* @return string
	*/
	public function getOpenText() {
		if (isset($this->_OpenText))
			return $this->_OpenText;
		else
			return null;
	}
	public function setOpenText($value) {
		$this->_OpenText = $value;
	}
	
	private $_PasteText;
	/**
	* @return string
	*/
	public function getPasteText() {
		if (isset($this->_PasteText))
			return $this->_PasteText;
		else
			return null;
	}
	public function setPasteText($value) {
		$this->_PasteText = $value;
	}
	
	private $_RemoveAllText;
	/**
	* @return string
	*/
	public function getRemoveAllText() {
		if (isset($this->_RemoveAllText))
			return $this->_RemoveAllText;
		else
			return null;
	}
	public function setRemoveAllText($value) {
		$this->_RemoveAllText = $value;
	}
	
	private $_RemoveText;
	/**
	* @return string
	*/
	public function getRemoveText() {
		if (isset($this->_RemoveText))
			return $this->_RemoveText;
		else
			return null;
	}
	public function setRemoveText($value) {
		$this->_RemoveText = $value;
	}
	
	private $_ThumbnailsViewText;
	/**
	* @return string
	*/
	public function getThumbnailsViewText() {
		if (isset($this->_ThumbnailsViewText))
			return $this->_ThumbnailsViewText;
		else
			return null;
	}
	public function setThumbnailsViewText($value) {
		$this->_ThumbnailsViewText = $value;
	}
	
	private $_TilesViewText;
	/**
	* @return string
	*/
	public function getTilesViewText() {
		if (isset($this->_TilesViewText))
			return $this->_TilesViewText;
		else
			return null;
	}
	public function setTilesViewText($value) {
		$this->_TilesViewText = $value;
	}
	
	private $_UncheckAllText;
	/**
	* @return string
	*/
	public function getUncheckAllText() {
		if (isset($this->_UncheckAllText))
			return $this->_UncheckAllText;
		else
			return null;
	}
	public function setUncheckAllText($value) {
		$this->_UncheckAllText = $value;
	}
	
	private $_UncheckText;
	/**
	* @return string
	*/
	public function getUncheckText() {
		if (isset($this->_UncheckText))
			return $this->_UncheckText;
		else
			return null;
	}
	public function setUncheckText($value) {
		$this->_UncheckText = $value;
	}
	

  function __construct(){
    
		$this->setArrangeByDimensionsText('Dimensions');
		$this->setArrangeByModifiedText('Date modified');
		$this->setArrangeByNameText('Name');
		$this->setArrangeByPathText('Path');
		$this->setArrangeBySizeText('Size');
		$this->setArrangeByText('Sort by');
		$this->setArrangeByTypeText('Type');
		$this->setCheckAllText('Check all');
		$this->setCheckText('Check');
		$this->setDetailsViewText('Details');
		$this->setEditText('Edit image...');
		$this->setEditDescriptionText('Edit description...');
		$this->setListViewText('List');
		$this->setOpenText('Open');
		$this->setPasteText('Paste');
		$this->setRemoveAllText('Remove all');
		$this->setRemoveText('Remove');
		$this->setThumbnailsViewText('Thumbnails');
		$this->setTilesViewText('Tiles');
		$this->setUncheckAllText('Uncheck all');
		$this->setUncheckText('Uncheck');

    $this->attributes = array();
    
		$this->attributes['ArrangeByDimensionsText'] = array('jsName' => 'arrangeByDimensionsText','jsType' => 'String','defaultValue' => 'Dimensions');
		$this->attributes['ArrangeByModifiedText'] = array('jsName' => 'arrangeByModifiedText','jsType' => 'String','defaultValue' => 'Date modified');
		$this->attributes['ArrangeByNameText'] = array('jsName' => 'arrangeByNameText','jsType' => 'String','defaultValue' => 'Name');
		$this->attributes['ArrangeByPathText'] = array('jsName' => 'arrangeByPathText','jsType' => 'String','defaultValue' => 'Path');
		$this->attributes['ArrangeBySizeText'] = array('jsName' => 'arrangeBySizeText','jsType' => 'String','defaultValue' => 'Size');
		$this->attributes['ArrangeByText'] = array('jsName' => 'arrangeByText','jsType' => 'String','defaultValue' => 'Sort by');
		$this->attributes['ArrangeByTypeText'] = array('jsName' => 'arrangeByTypeText','jsType' => 'String','defaultValue' => 'Type');
		$this->attributes['CheckAllText'] = array('jsName' => 'checkAllText','jsType' => 'String','defaultValue' => 'Check all');
		$this->attributes['CheckText'] = array('jsName' => 'checkText','jsType' => 'String','defaultValue' => 'Check');
		$this->attributes['DetailsViewText'] = array('jsName' => 'detailsViewText','jsType' => 'String','defaultValue' => 'Details');
		$this->attributes['EditText'] = array('jsName' => 'editText','jsType' => 'String','defaultValue' => 'Edit image...');
		$this->attributes['EditDescriptionText'] = array('jsName' => 'editDescriptionText','jsType' => 'String','defaultValue' => 'Edit description...');
		$this->attributes['ListViewText'] = array('jsName' => 'listViewText','jsType' => 'String','defaultValue' => 'List');
		$this->attributes['OpenText'] = array('jsName' => 'openText','jsType' => 'String','defaultValue' => 'Open');
		$this->attributes['PasteText'] = array('jsName' => 'pasteText','jsType' => 'String','defaultValue' => 'Paste');
		$this->attributes['RemoveAllText'] = array('jsName' => 'removeAllText','jsType' => 'String','defaultValue' => 'Remove all');
		$this->attributes['RemoveText'] = array('jsName' => 'removeText','jsType' => 'String','defaultValue' => 'Remove');
		$this->attributes['ThumbnailsViewText'] = array('jsName' => 'thumbnailsViewText','jsType' => 'String','defaultValue' => 'Thumbnails');
		$this->attributes['TilesViewText'] = array('jsName' => 'tilesViewText','jsType' => 'String','defaultValue' => 'Tiles');
		$this->attributes['UncheckAllText'] = array('jsName' => 'uncheckAllText','jsType' => 'String','defaultValue' => 'Uncheck all');
		$this->attributes['UncheckText'] = array('jsName' => 'uncheckText','jsType' => 'String','defaultValue' => 'Uncheck');
  }

}