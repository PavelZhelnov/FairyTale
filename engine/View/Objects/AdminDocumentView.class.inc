<?php

class AdminDocumentView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 29;
	public $Task = 'view';
	public $document;
	public $amount = array('3' => '3', '5' => '5', '10' => '10', '20' => '20','30' => '30','40'=>'40','50'=>'50','60'=>'60','70'=>'70','80'=>'80','90'=>'90','100'=>'100');
	public $imagePath ='';
	public $docPath = '';
	public $upload_formats = array(
		'image/gif' => 'gif',
		'image/jpeg' => 'jpg',
		'image/pjpeg' => 'jpg',
		'image/bmp' => 'bmp',
		'image/vnd.wap.wbmp' => 'bmp',
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

	function AdminDocumentView($pquery) {
		global $REGISTRY;		
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
		$this->docPath = $REGISTRY['Core']['ImagePath'].'/documents/';
	}
		
	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Action->processEvent($this->SectionID,'get_search',$this->getRequestField('form'),$this);
		$this->search_params = $this->PreparedTemplates;

		$this->Action->processEvent($this->SectionID,'get',array(),$this);
		$this->document = $this->PreparedTemplates;

		if($this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete') {
		$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
			switch(@$this->LocalTarget[1]) {

				case 'Delete':
					if (isset($this->LocalTarget[2])) {
						$this->Action->processEvent($this->SectionID,'delete',array('id'=>$this->LocalTarget[2]),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') 
						and header("Location: ".$this->Home.'/Admin/AdminDocument'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					} else $this->Scheme='default';
				break;

				default:
					//$this->Action->processEvent($this->SectionID,'new',array(),$this);
					//$this->Scheme = 'action';
					$request = array('pageRecordsQty'=>'5','curPageNumber'=>(isset($this->LocalTarget[1])? $this->LocalTarget[1]+1 : 1));
					$this->Scheme = 'default';
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'name';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'list',$request,$this);

					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
						else {$this->getPageControl($this->Home.'/Admin/AdminDocument',$this->sortby);}
				break; 
			}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'add_document':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'save',$this->Request['form'],$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;

					case 'search':
						if (isset($this->Request['form']['goToPage']) && (!empty($this->Request['form']['goToPage'])) && is_Num($this->Request['form']['goToPage'])) {
							$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'name';
							header("Location: ".$this->Home.'/Admin/AdminDocument/'.($this->Request['form']['goToPage']-1).'/'.$this->sortby);
						} else {
							$this->validateForm()
							and $this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
							and header("Location: ".$this->Home.'/Admin/AdminDocument'.$this->SID);
						}
					break;
				}
			}
		}
		$this->setSchemeTemplate($this->Scheme);

	}

	function clearSearchParams() {
		$this->Request['form']['documentid'] = ''; 
	}

	function getFormattedDate($field) {
		if ( ($field!="-1") && ($field!=""))
			return date('m-d-Y h:i:s A', $field);
		else return '';
			
	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('login'),1,50)) $this->errors['login'] = $this->globalLangContent['error_view']['err_login'];
				if(!is_AlphaNumDefis($this->getRequestFormField('password'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
			case 'save':
				
			break;
			case 'add_document':
				$doc = $this->getRequestField('document');
				if(empty($doc['name'])) $this->errors['document'] = 'Document is empty';
				else {
					if(!$doc['size']) $this->errors['document'] = 'Document is empty';
					else {
						$this->Request['form']['file_name'] = $doc['name'];
						$this->Request['form']['size'] = $doc['size'];
						$this->Request['form']['doctype'] = $doc['type'];
					}
				}
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'action': $this->fillAction(); break;			
			case 'empty': case 'default': $this->fillView(); break;
			case 'details': $this->fillViewBpoDetails(); break;
			case 'document_list': $this->FillDocumentList(); break;

			default: $this->fillView(); break;
		}
	}


	function FillView() {
		$i=1;
		if (!empty($this->PreparedTemplates['curPage'])) {
			foreach ($this->PreparedTemplates['curPage'] as $k=>$v) {
				$this->TempFillEls['documents'][] = array(
					'id'=>$v['id'],
					'description' => $v['description'],
					'name' => $v['name'],
					'file_name' =>makeLink($this->imagePath.'/documents/'.$v['id'].'_'.$v['file_name'], $v['file_name']),
					'pubdate' => $v['pubdate'],
					'doctype' => $v['doctype'],
					'size' => $v['size'],
					'num' => $i++,
				);
			}
		}
		
		$this->TempFillEls['item_langs1'] = inputHidden('form[name_langs][0][language]',1);
		$this->TempFillEls['item_langs2'] = inputHidden('form[name_langs][1][language]',2);
		$this->TempFillEls['item_langs3'] = inputHidden('form[name_langs][2][language]',3);
		$this->TempFillEls['eng_name'] = inputText('form[name_langs][0][name]',(!empty($this->Request)? $this->getRequestFormField('eng_name') : ''),$this->correctSize('40'));
		$this->TempFillEls['rus_name'] = inputText('form[name_langs][1][name]',(!empty($this->Request)? $this->getRequestFormField('rus_name') : ''),$this->correctSize('40'));
		$this->TempFillEls['ukr_name'] = inputText('form[name_langs][2][name]',(!empty($this->Request)? $this->getRequestFormField('ukr_name') : ''),$this->correctSize('40'));
		$this->TempFillEls['eng_description'] = inputTextArea('form[name_langs][0][description]',(!empty($this->Request)? $this->getRequestFormField('eng_description') : ''),$this->correctSize('40'),$this->correctSize('7'));
		$this->TempFillEls['rus_description'] = inputTextArea('form[name_langs][1][description]',(!empty($this->Request)? $this->getRequestFormField('rus_description') : ''),$this->correctSize('40'),$this->correctSize('7'));
		$this->TempFillEls['ukr_description'] = inputTextArea('form[name_langs][2][description]',(!empty($this->Request)? $this->getRequestFormField('ukr_description') : ''),$this->correctSize('40'),$this->correctSize('7'));
		
		$this->TempFillEls['document'] = inputFile('document');
		$this->TempFillEls['bpoid'] = isset($this->LocalTarget[2])?$this->LocalTarget[2]:'';
	}
	
	
	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = 'The Document is deleted successfully'; break;
			case 'finish_save': $this->TempFillEls['message'] = 'The Document is saved succesfully'; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

	function saveDocument($array) {
		$doc = $this->getRequestField('document');
		if(!empty($doc['tmp_name'])) {
			if(file_exists($this->docPath.$array['id'].'_'.$array['file_name'])) {
				unlink($this->docPath.$array['id'].'_'.$array['file_name']);				
			}
			$size = GetImageSize($doc['tmp_name']);
			copy($doc['tmp_name'],$this->docPath.$array['id'].'_'.$array['file_name']);
			chmod($this->docPath.$array['id'].'_'.$array['file_name'],0664);
			
			
			$thumbnail = new Thumbnail($this->docPath.$array['id'].'_'.$array['file_name']);
			$thumbnail->setMaxSize(137,199,true);
			$thumbnail->setQualityOutput(TRUE);
			ob_start();
			$thumbnail->outputThumbnail('jpg',75);
			$image = ob_get_contents();
			ob_end_clean();
			$file = fopen($this->docPath.$array['id'].'_'.$this->getBriefNameOfFile($array['file_name']).'_prev.'.$this->upload_formats[$size['mime']],'w');
			fputs($file,$image);
			chmod($this->docPath.$array['id'].'_'.$this->getBriefNameOfFile($array['file_name']).'_prew.'.$this->upload_formats[$size['mime']],0664);
		}
	} 
	
	function getBriefNameOfFile($fullname) {
		return substr($fullname, 0, strpos($fullname, '.'));
	}	
	
	function deleteDocument($array) {
		if(!empty($array['file_name'])) {
			if(file_exists($this->docPath.$array['id'].'_'.$array['file_name'])) {
				unlink($this->docPath.$array['id'].'_'.$array['file_name']);				
			}
		}
	}

}
?>