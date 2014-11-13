<?php

class AdminHeaderView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 11;
	public $Task = 'view';
	public $document;
	public $amount = array('3' => '3', '5' => '5', '10' => '10', '20' => '20','30' => '30','40'=>'40','50'=>'50','60'=>'60','70'=>'70','80'=>'80','90'=>'90','100'=>'100');
	public $imagePath ='';
	public $docPath = '';
	public $image_type;
	public $modulesettings = array();
	public $upload_formats = array(
		'image/gif' => 'gif',
		'image/jpeg' => 'jpg',
		'image/pjpeg' => 'jpg',
		'application/x-shockwave-flash' => 'swf',
		'image/png' => 'png',
		'' => '',
	);
	public $orderby = array(
		'name' => array(
			'sortColumn' => 'name',
			'sortType' => 'asc',
		),
	);

	public $sortby = '';
	public $search_params = array();

	function AdminHeaderView($pquery) {
		global $REGISTRY;		
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImagePath'];
		$this->imageWPath = $REGISTRY['Core']['ImageWPath'];
	}
		
	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Action->processEvent($this->SectionID,'settings',array('moduleid' => 1, 'paramid'=>3),$this);
		foreach ($this->PreparedTemplates['settings'] as $k => $v) {
			if ($v['paramid']=='3')
				$this->image_type = $v['value'];
		}
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				default:
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() 
						and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'save':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'save',$this->Request['form'],$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
				}
			}
		}
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('username'),3,32)) $this->errors['username'] = $this->globalLangContent['error_view']['username'];
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['passw'];
			break;
			case 'save':
				$image = $this->getRequestField('image');
				if(empty($image['name'])) $this->errors['image'] = 'Image is empty';
				else {
					if(!$image['size']) $this->errors['image'] = 'Image is empty';
					else {
						$size = GetImageSize($image['tmp_name']);
						$this->Request['form']['file_name'] = $image['name'];
						$this->Request['form']['size'] = $image['size'];
						$this->Request['form']['doctype'] = $image['type'];
						$this->Request['form']['image_type'] = $this->upload_formats[$size['mime']];
					}
				}
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {		
		switch($this->Scheme) {			
			case 'save': case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'default': $this->fillViewHeader(); break;
			case 'auth': $this->fillAuth(); break;
		}
	}

	function fillViewHeader() {		
		$this->TempFillEls = array(
			'image' => inputFile('image'),			
			'headerimage' => (isset($this->image_type)?
					($this->image_type=='swf'?
						makeSwf($this->imagePath.'/layout/header.'.$this->image_type,$this->imageWPath.'/layout/header.'.$this->image_type):
						makeImage($this->imagePath.'/layout/header.'.$this->image_type,$this->imageWPath.'/layout/header.'.$this->image_type,'','center',array(),1,' ')						
					): 
					''));//makeImage($this->imagePath.'/layout/header.'.$this->image_type,$this->imageWPath.'/layout/header.'.$this->image_type,'','center',array(),1, ' ')), 
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'viewnews');
	} 		
	
	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_info']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_info']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->localLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]);
				 break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

	function saveHeader($array) {
		$photo = $this->getRequestField('image');
		if(!empty($photo['tmp_name'])) {
			if(file_exists($this->imagePath.'/layout/header.'.$this->image_type)) {
				unlink($this->imagePath.'/layout/header.'.$this->image_type);
			}
			$size = GetImageSize($photo['tmp_name']);
			copy($photo['tmp_name'],$this->ImagePath.'/layout/header.'.$array['image_type']);
			chmod($this->imagePath.'/layout/header.'.$array['image_type'],0664);			
		}
	}
 
}
?>