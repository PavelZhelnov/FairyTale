<?php

class NewsView extends Slot {

	public $ModuleID = 8;
	public $SectionID = 12;
	public $Task = 'view';
	public $orderby = array(
		'Date' => array(
			'sortColumn' => 'pubdate',
			'sortType' => 'desc',
		),
		'Title' => array(
			'sortColumn' => 'title',
			'sortType' => 'asc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	public $imagePath ='';
	public $serviceinfo = array();

	function NewsView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
		$this->serviceinfo = array(
			'hostname' => $REGISTRY['Core']['HostName'].$REGISTRY['Core']['WebHome'],
			'frommail' => $this->fromMail = $REGISTRY['Core']['frommail'],
			'sitename' => $REGISTRY['Core']['SiteName'],
			);
	}
		
	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish' && $this->Scheme != 'finish_save' && $this->Scheme!='finish_delete') {
				$this->curPageNumber = empty($this->LocalTarget[0]) || !validate(intval($this->LocalTarget[0]))? 0 : intval($this->LocalTarget[0]);
				switch(@$this->LocalTarget[0]) {
				case 'View':
					if(!empty($this->LocalTarget[1]) && validate(intval($this->LocalTarget[1]))) {
						$this->Scheme = 'view';
						$this->Task = 'getnews';
						$this->Action->processEvent($this->SectionID,'getnews',array('id' => intval($this->LocalTarget[1]), 'langid' => $this->LM->Langs[$this->language]),$this);
						if(empty($this->PreparedTemplates['curPage'])) 
						{
							header("Location: ".$this->Home.'/News/'.$this->SID);
						}
					}
					//else header("Location: ".$this->Home.'/News/'.$this->SID);
				break;
				default:
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request = array('pageRecordsQty'=>'10','curPageNumber'=>(isset($this->LocalTarget[1])? $this->LocalTarget[1]+1 : 1));
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[1],array_keys($this->orderby))? $this->LocalTarget[1] : 'Date';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$request['imagePath']=$this->imagePath;
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
					 else {$this->getPageControl($this->Home.'/News/'.(!empty($this->LocalTarget[0])?$this->LocalTarget[1]:0),0);}
					//if(empty($this->PreparedTemplates['curPage'])) $this->Scheme = 'empty';
				break; 
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
				}
			}
		}
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('username'),3,32)) $this->errors['username'] = $this->globalLangContent['error_view']['err_admin_email'];
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {			
			case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'default': $this->fillView(); break;
			case 'view': $this->fillViewNews(); break;
		}
	}

	function fillViewNews() {
		$this->TempFillEls = array(
			'newsid' => $this->PreparedTemplates['curPage'][0]['newsid'],
			'newstext' => $this->getWordWrap($this->PreparedTemplates['curPage'][0]['ndescription'], 30, " "),
			'newsheader' => $this->getWordWrap($this->PreparedTemplates['curPage'][0]['nheader'], 20, " "),
			'newsdate' => $this->PreparedTemplates['curPage'][0]['publicatedate'],
		);		
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillView() {
		foreach($this->PreparedTemplates['curPage'] as $key => $value) {			
			$this->TempFillEls['news'][$value['newsid']] = array(
				'newsid' => $value['newsid'],
				'newstext' => $this->getWordWrap($value['ndescription'], 30, " "),
				'newsheader' => $this->getWordWrap($value['nheader'], 20, " "),
				'newsdate' => $value['publicatedate'],
			);
		}
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillMessage() {
		switch($this->Scheme) {			
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['newsubscriber_info']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_info']; break;
			case 'finish': $this->TempFillEls['message'] = $this->globalLangContent['message']['confirm_info']; break;			
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

}
?>