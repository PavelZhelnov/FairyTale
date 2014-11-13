<?php

class DocsView extends Slot {

	public $ModuleID = 7;
	public $SectionID = 30;
	public $Task = 'view';
	public $document;
	public $amount = array('3' => '3', '5' => '5', '10' => '10', '20' => '20','30' => '30','40'=>'40','50'=>'50','60'=>'60','70'=>'70','80'=>'80','90'=>'90','100'=>'100');
	public $imagePath ='';
	public $docPath = '';

	public $orderby = array(
		'name' => array(
			'sortColumn' => 'name',
			'sortType' => 'asc',
		),
	);

	public $sortby = '';
	public $search_params = array();

	function DocsView($pquery) {
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


		if($this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete') {
		$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
			switch(@$this->LocalTarget[0]) {
				case 'View':
					$this->Scheme = 'viewdoc';
				break;
				default:
					$request = array('pageRecordsQty'=>'5','curPageNumber'=>(isset($this->LocalTarget[1])? $this->LocalTarget[1]+1 : 1));
					$this->Scheme = 'default';
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'name';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'listdocuments',$request,$this);

					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
						else {$this->getPageControl($this->Home.'/Docs',$this->sortby);}
				break; 
			}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;

					case 'search':
						if (isset($this->Request['form']['goToPage']) && (!empty($this->Request['form']['goToPage'])) && is_Num($this->Request['form']['goToPage'])) {
							$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'name';
							header("Location: ".$this->Home.'/Admin/AdminDocument/'.($this->Request['form']['goToPage']-1).'/'.$this->sortby);
						} else {
							$this->validateForm()
							and $this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
							and header("Location: ".$this->Home.'/Docs/'.$this->SID);
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
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'viewdoc': $this->fillViewDoc(); break;
			case 'empty': case 'default': $this->fillView(); break;
			default: $this->fillView(); break;
		}
	}


  function fillViewDoc() {
  	if (isset($this->LocalTarget[1])) {
  		$this->TempFillEls = array (
  			'img' => '<img src="'.$this->imagePath.'/documents/'.$this->LocalTarget[1].'" border=0>'
  		);
  	}
  }
  
	function FillView() {
		$i=1;$size=0;
		
		foreach($this->PreparedTemplates['curPage'] as $k => $v) {
//			echo $this->imagePath.'/documents/'.$v['id'].'_'.$v['file_name'];
			$data[$i% 3 == 0? 2 : (($i+1) % 3 == 0? 1 : 0)][] = array(
				'key' => $k,
				'id'=>$v['id'],
				'description' => $v['description'],
				'name' => makeLink($this->imagePath.'/documents/'.$v['id'].'_'.$v['file_name'], $v['name'], array(), '', 'class="sub_mainheader_bold"'),
				'title' => $v['name'],
				'file_name' =>makeLink($this->imagePath.'/documents/'.$v['id'].'_'.$v['file_name'], $v['file_name']),
				'pubdate' => $v['pubdate'],
				'doctype' => $v['doctype'],
				'size' => floor($v['size']/1000),
				'num' => $i++,
				'image' => makeLink($this->Home.'/Docs/View/'.$v['id'].'_'.$v['file_name'],'<img src="'.$this->imagePath.'/documents/'.$v['id'].'_'.$this->getNameOfFile($v['file_name']).'_prev.jpg" border=0>', array(), '', 'target="_blank"'),
			);
			$i++;
		}
		foreach($data[0] as $key => $value)
			$this->TempFillEls['Images'][$key] = array(
				'first_image' => array($data[0][$key]),
				'second_image' => isset($data[1][$key])? array($data[1][$key]) : array(),
				'third_image' => isset($data[2][$key])? array($data[2][$key]) : array(),
			);
		
	}

	function getNameOfFile($fullname) {
		return substr($fullname, 0, strpos($fullname, '.'));
	}	
	
	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = 'The Document is deleted successfully'; break;
			case 'finish_save': $this->TempFillEls['message'] = 'The Document is saved succesfully'; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}


}
?>