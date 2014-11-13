<?php

class AdminSubscriptionView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 18;
	public $Task = 'view';
	public $orderby = array(
		'Date' => array(
			'sortColumn' => 'pubdate',
			'sortType' => 'desc',
		),
		'Subscriber' => array(
			'sortColumn' => 'su.id',
			'sortType' => 'asc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	public $category = array();
	public $serviceinfo = array();

	function AdminSubscriptionView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->serviceinfo = array(
			'hostname' => $REGISTRY['Core']['HostName'].$REGISTRY['Core']['WebHome'],
			'frommail' => $this->fromMail = $REGISTRY['Core']['frommail'],
			'sitename' => $REGISTRY['Core']['SiteName'],
			);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				case 'EditCategory': case 'DeleteCategory':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'actioncategory';
						$this->Task = 'editcategory';
						$this->Action->processEvent($this->SectionID,'editcategory',array('id' => intval($this->LocalTarget[2]), 'langid' => $this->LM->Langs[$this->language]),$this);
						if(!empty($this->PreparedTemplates['_error'])) header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
					}
					else header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
				break;
				case 'BrowseCategory':
					$this->Scheme = 'viewmail';
					$this->Task = 'viewcategorymail';
					$request = array('pageRecordsQty'=>'5','curPageNumber'=>(isset($this->LocalTarget[4])? $this->LocalTarget[4]+1 : 1));
					$this->sortby = !empty($this->LocalTarget[5]) && in_array($this->LocalTarget[5],array_keys($this->orderby))? $this->LocalTarget[5] : 'Date';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$request['id'] = !empty($this->LocalTarget[2]) ? $this->LocalTarget[2] : 0;
					$this->Action->processEvent($this->SectionID,'viewmail',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'emptymail';}
					 else {$this->getPageControl($this->Home.'/Admin/AdminSubscription/BrowseCategory/'.$request['id'].'/'.(!empty($this->LocalTarget[4])?$this->LocalTarget[4]:0));}
					if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
				break;
				case 'ViewSubscribers':
					$this->Scheme = 'viewsubscribers';
					$this->Task = 'viewcategorysubscribers';
					$request = array('pageRecordsQty'=>'5','curPageNumber'=>(isset($this->LocalTarget[4])? $this->LocalTarget[4]+1 : 1));
					$this->sortby = !empty($this->LocalTarget[5]) && in_array($this->LocalTarget[5],array_keys($this->orderby))? $this->LocalTarget[5] : 'Subscriber';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$request['id'] = !empty($this->LocalTarget[2]) ? $this->LocalTarget[2] : 0;
					$this->Action->processEvent($this->SectionID,'viewsubscribers',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'emptysubscribers';}
					 else {$this->getPageControl($this->Home.'/Admin/AdminSubscription/ViewSubscribers/'.$request['id'].'/'.(!empty($this->LocalTarget[4])?$this->LocalTarget[4]:0));}
					if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
				break;
				case 'EditMail': case 'DeleteMail':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'actionmail';
						$this->Task = 'editmail';
						$this->Action->processEvent($this->SectionID,'editmail',array('id' => intval($this->LocalTarget[2]), 'langid' => $this->LM->Langs[$this->language]),$this);
						if(empty($this->PreparedTemplates['curPage'])) 
						{
							header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
						}
					}
					else header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
				break;
				case 'EditSubscriber': case 'DeleteSubscriber':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'actionsubscriber';
						$this->Task = 'editsubscriber';
						$this->Action->processEvent($this->SectionID,'view',array('id' => intval($this->LocalTarget[2]), 'langid' => $this->LM->Langs[$this->language]),$this);
					}
					else header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
				break;
				case 'ConfirmSubscriber':
					$this->validateForm() and $this->Action->processEvent($this->SectionID,'checkconfirm',array('id'=>(isset($this->LocalTarget[2])?$this->LocalTarget[2]:0), 'authcode'=>(isset($this->LocalTarget[3])?$this->LocalTarget[3]:''), 'confirm'=>'1'),$this)
					and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'/Admin/AdminSubscription/');
					if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
				break;
				default:
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request = array('pageRecordsQty'=>'5','curPageNumber'=>(isset($this->LocalTarget[2])? $this->LocalTarget[2]+1 : 1));
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'Date';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];					
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'addcategory':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'savecategory',$this->correctWords($this->getRequestField('form')),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;

					case 'add':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'savecategory',$this->correctWords($this->getRequestField('form')),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'EditCategory':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'savecategory',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'DeleteCategory':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'deletecategory',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$this->Home.'/Admin/AdminSubscription'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'EditMail': case 'sendmail':
						if (!empty($this->Request['form']['sendcategory']))
						{
							 foreach ($this->Request['form']['sendcategory'] as $k=>$v) {
								$request['Category'][$k] = $v;
							}
						}
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'sendmail',$this->correctWords($this->getRequestField('form')),$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'DeleteMail':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'deletemail',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'EditSubscriber':
						$request['id']=(!empty($this->LocalTarget[2])?$this->LocalTarget[2]:0);
						foreach ($this->Request['form']['subscr'] as $k=>$v) {
							$request['Subscribe'][$k] = $v;
						}
						$request['EmailFormat']=$this->Request['form']['emailformat'];
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'modifysubscription',$request,$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'/Admin/AdminSubscription/');
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'DeleteSubscriber':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'deletesubscriber',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$this->Home.'/Admin/AdminSubscription/');
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message'; break;
					break;
					case 'AddSubscriber':
						if ($this->validateForm())
						{
							$request=$this->Request['form'];
							$request['langid']=$this->LM->Langs[$this->language];
							$request['serviceinfo']=$this->serviceinfo;
							$this->Action->processEvent($this->SectionID,'authorizesubscriber',$request,$this);
							$request=$this->PreparedTemplates;$request['langid']=$this->LM->Langs[$this->language];
							if(!empty($this->PreparedTemplates['_error'])) {$this->Scheme = 'message'; break;}
							foreach ($this->Request['form']['subscr'] as $k=>$v) {
								$request['Subscribe'][$k] = $v;	}
							$this->Action->processEvent($this->SectionID,'modifysubscription',$request,$this);
							if (isset($request['new'])) //new subscriber
							{
								$this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$PHP_SELF);
							} else {
								$this->Action->processEvent($this->SectionID,'viewsubscription',$request,$this);
								header("Location: ".$PHP_SELF);
							}
						}						
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
			case 'addcategory': case 'EditCategory':
				if(!is_FullText($this->Request['form']['name_langs']['0']['name'],1,255)) $this->errors['name1'] = $this->globalLangContent['error_view']['err_name'];
				if(!is_FullText($this->Request['form']['name_langs']['1']['name'],1,255)) $this->errors['name2'] = $this->globalLangContent['error_view']['err_name'];
			break;
			case 'sendmail':
				if(empty($this->Request['form']['sendcategory'])) {$this->errors['category'] = $this->globalLangContent['error_view']['err_emptycategorylist'];}
				if(!is_FullText($this->getRequestFormField('description'),0,65535)) $this->errors['message'] = $this->globalLangContent['error_view']['err_message'];
			break;
			case 'AddSubscriber':
				if(!is_Email($this->getRequestFormField('email'))) $this->errors['email'] = $this->globalLangContent['error_view']['err_admin_email'];
				if(empty($this->Request['form']['subscr'])) $this->errors['category'] = $this->globalLangContent['error_view']['err_emptycategorylist'];
				//if(!is_AlphaNumDefis($this->getRequestFormField('password'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['err_admin_password'];
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
		switch($this->Scheme) {
			case 'save': case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			//case 'edit': $this->fillEditPage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'viewmail': $this->fillViewMail(); break;
			case 'viewsubscribers': $this->fillViewSubscribers(); break;
			case 'emptymail': $this->fillViewEmptyMail(); break;
			case 'emptycategory': $this->fillViewEmptyCategoryMail(); break;
			case 'emptysubscribers': $this->fillViewEmptySubscribers(); break;
			case 'actioncategory': $this->fillActionCategory(); break;
			case 'actionmail': $this->fillActionMail(); break;
			case 'actionsubscriber': $this->fillActionSubscriber(); break;
			case 'empty': case 'default': case 'view': $this->fillView(); break;
		}
	}

	function fillViewEmptyMail() {
		$this->TempFillEls['empty_message']= $this->globalLangContent['label']['empty_mail'];
		$this->TempFillEls['categoryid'] = $this->LocalTarget['2'];
		$this->TempFillEls['description'] = inputTextArea('form[description]',(!empty($this->Request['form']['description'])? $this->Request['form']['description'] : ''),$this->correctSize('50'), $this->correctSize('10'));
		$this->TempFillEls['email_format1'] = $this->globalLangContent['label']['subscription_format_html'].inputRadio('form[emailformat]',0,(isset($this->PreparedTemplates['emailFormat']) && $this->PreparedTemplates['emailFormat']==0)?TRUE:FALSE);
		$this->TempFillEls['email_format2'] = $this->globalLangContent['label']['subscription_format_text'].inputRadio('form[emailformat]',1,(isset($this->PreparedTemplates['emailFormat']) && $this->PreparedTemplates['emailFormat']==1)?TRUE:FALSE);
		$this->TempFillEls['email']= inputText('form[email]',(!empty($this->Request)? $this->Request['form']['email'] : ''),$this->correctSize('40'));
		$this->TempFillEls['categoryidsub'] = inputHidden('form[subscr]['.(isset($this->LocalTarget['2'])?$this->LocalTarget['2']:0).']', (isset($this->LocalTarget['2'])?$this->LocalTarget['2']:0));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
	}

	function fillViewEmptySubscribers() {
		$this->TempFillEls['empty_message']= $this->globalLangContent['label']['empty_subscriber'];
		$this->TempFillEls['categoryid'] = !empty($this->LocalTarget[2]) ? $this->LocalTarget[2] : 0;
		$this->TempFillEls['categoryidsub'] = inputHidden('form[subscr]['.(isset($this->LocalTarget['2'])?$this->LocalTarget['2']:0).']', (isset($this->LocalTarget['2'])?$this->LocalTarget['2']:0));
		$this->TempFillEls['description'] = inputTextArea('form[description]',(!empty($this->Request['form']['description'])? $this->Request['form']['description'] : ''),$this->correctSize('50'), $this->correctSize('10'));
		$this->TempFillEls['email_format1'] = $this->globalLangContent['label']['subscription_format_html'].inputRadio('form[emailformat]',0,(isset($this->PreparedTemplates['emailFormat']) && $this->PreparedTemplates['emailFormat']==0)?TRUE:FALSE);
		$this->TempFillEls['email_format2'] = $this->globalLangContent['label']['subscription_format_text'].inputRadio('form[emailformat]',1,(isset($this->PreparedTemplates['emailFormat']) && $this->PreparedTemplates['emailFormat']==1)?TRUE:FALSE);
		$this->TempFillEls['email']= inputText('form[email]',(!empty($this->Request)? $this->Request['form']['email'] : ''),$this->correctSize('40'));

		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
	}

	function fillView() {
		if (!empty($this->PreparedTemplates['categoryTree']))
		{
			foreach($this->PreparedTemplates['categoryTree'] as $k => $v) {
				$this->TempFillEls['menu'][$k]['header'][$k] = array (
				'catname' => makeLink($this->Home.'/Admin/AdminSubscription/BrowseCategory/'.$v['id'],ucwords($v['name']),array(),'','class="menuitem"'),
				'catid' =>$v['id'],
				'catchecks' => inputCheckbox('form[sendcategory]['.$v['id'].']', FALSE, '', $v['id']),
			);
				if(!empty($v['subcat'])) $this->setTargetArray2($v['subcat'],$k,1);
			}
		}
		$this->category[0]='***'.$this->globalLangContent['label']['root'].'***';
		if (!empty($this->PreparedTemplates['categoryPath'])) $this->setTargetArray($this->PreparedTemplates['categoryPath']);
		$this->TempFillEls['mailtext'] = inputTextArea('form[description]',(!empty($this->Request['form']['description'])? $this->Request['form']['description'] : ''),$this->correctSize('50'), $this->correctSize('10'));
		$this->TempFillEls['categorysel'] = inputSelect('form[category][id]', $this->category, (!empty($this->LocalTarget[2])?$this->LocalTarget[2]:0));
		$this->TempFillEls['formaction'] =$this->Home."/Admin/AdminSubscription/".(!empty($this->LocalTarget[0])?$this->LocalTarget[0]:'').(!empty($this->LocalTarget[1])?"/".$this->LocalTarget[1]:'');

		$this->TempFillEls['item_langs1'] = inputHidden('form[name_langs][0][language]',1);
		$this->TempFillEls['item_langs2'] = inputHidden('form[name_langs][1][language]',2);
		$this->TempFillEls['categoryadd'] = inputSelect('form[parent_category][id]', $this->category, (!empty($this->LocalTarget[2])?$this->LocalTarget[2]:0));
		$this->TempFillEls['eng_name'] = inputText('form[name_langs][0][name]',(!empty($this->Request['form']['name_langs'])? $this->Request['form']['name_langs']['0']['name'] : ''),$this->correctSize('40'));
		$this->TempFillEls['rus_name'] = inputText('form[name_langs][1][name]',(!empty($this->Request['form']['name_langs'])? $this->Request['form']['name_langs']['1']['name'] : ''),$this->correctSize('40'));

		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);

		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillViewMail() {
		if (!empty($this->PreparedTemplates['curPage']))
		{
			foreach($this->PreparedTemplates['curPage'] as $k => $v) {
				$this->TempFillEls['mail'][$k] = array (
				'mailheader' => $v['publicatedate'],
				'maillink' => makeLink($this->Home.'/Admin/AdminSubscription/EditMail/'.$v['mailid'],ucwords($v['publicatedate']),array(),'','class="menuitem"'),
				'mailtext' => substr($this->getWordWrap($v['subscriptiontext'],40,' '),0, 200).'...',
				'mailcategoryid' => $v['categoryid'],
				'mailcategoryname' => $v['categoryname'],
				'maillastsent' => $v['lastsent'],
				'mailid' => $v['mailid'],				
				);
				$this->TempFillEls['categoryid'] = $v['categoryid'];
				$this->TempFillEls['categoryname'] = $v['categoryname'];
			}
			$this->TempFillEls['description'] = inputTextArea('form[description]',(!empty($this->Request['form']['description'])? $this->Request['form']['description'] : ''),$this->correctSize('50'), $this->correctSize('10'));
		}
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);

		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'viewmail');
	}
	
	function fillViewSubscribers() {
		if (!empty($this->PreparedTemplates['curPage']))
		{
			foreach($this->PreparedTemplates['curPage'] as $k => $v) {
				$this->TempFillEls['subscriber'][$k] = array (
				'subscriberemail' => $v['subscriberemail'],
				'subscriberlink' => makeLink($this->Home.'/Admin/AdminSubscription/EditSubscriber/'.$v['subscriberid'],ucwords($v['subscriberemail']),array(),'','class="menuitem"'),
				'subscribedate' => $v['subscribedate'],
				'confirmed' => ($v['confirmed']=='1'? $this->globalLangContent['label']['yes']: makeLink($this->Home.'/Admin/AdminSubscription/ConfirmSubscriber/'.$v['subscriberid'].'/'.$v['subscriberauthcode'],$this->globalLangContent['label']['no'],array(),'','class="menuitem"')),
//					$this->globalLangContent['label']['no']),
				//'mailtext' => substr($this->getWordWrap($v['subscriptiontext'],40,' '),0, 200).'...',
				'categoryid' => $v['categoryid'],
				'categoryname' => $v['categoryname'],
				//'maillastsent' => $v['lastsent'],
				'subscriberid' => $v['subscriberid'],
				);
				$this->TempFillEls['categoryid'] = $v['categoryid'];
				$this->TempFillEls['categoryname'] = $v['categoryname'];
			}
		}
		$this->TempFillEls['email_format1'] = $this->globalLangContent['label']['subscription_format_html'].inputRadio('form[emailformat]',0,TRUE);
		$this->TempFillEls['email_format2'] = $this->globalLangContent['label']['subscription_format_text'].inputRadio('form[emailformat]',1,TRUE);
		$this->TempFillEls['email']= inputText('form[email]',(!empty($this->Request)? $this->Request['form']['email'] : ''),$this->correctSize('40'));
		$this->TempFillEls['categoryidsub'] = inputHidden('form[subscr]['.(isset($this->LocalTarget['2'])?$this->LocalTarget['2']:0).']', (isset($this->LocalTarget['2'])?$this->LocalTarget['2']:0));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'viewsubscribers');
	}
	
	function fillActionCategory() {
		global $PHP_SELF;
		$action = $this->LocalTarget[1];
		$this->category[0]='***'.$this->globalLangContent['label']['root'].'***';
		if (!empty($this->PreparedTemplates['categoryTree']))
		{
			$this->setTargetArray($this->PreparedTemplates['categoryTree']);
		}		
		$this->TempFillEls = array(
			'item_langs1' => inputHidden('form[name_langs][0][language]',1),
			'item_langs2' => inputHidden('form[name_langs][1][language]',2),
			'id' => $action=='Add'? '' : $this->PreparedTemplates['curPage'][0]['id'],
			'action' => $action,
			'actionbutton' => ($action == 'DeleteCategory'? $this->globalLangContent['button']['admin_bt_delete'] : $this->globalLangContent['button']['admin_bt_update']),
			'eng_name' => $action == 'DeleteCategory'? $this->PreparedTemplates['curPage'][0]['name'] : inputText('form[name_langs][0][name]',(!empty($this->Request)? $this->Request['form']['name_langs']['0']['name'] : $this->PreparedTemplates['curPage'][0]['name']),$this->correctSize('40')),
			'rus_name' => $action == 'DeleteCategory'? $this->PreparedTemplates['curPage'][1]['name'] : inputText('form[name_langs][1][name]',(!empty($this->Request)? $this->Request['form']['name_langs']['1']['name'] : $this->PreparedTemplates['curPage'][1]['name']),$this->correctSize('40')),
			'formaction' => "",
		);
		$selectedIndex=(!empty($this->LocalTarget[2])?$this->LocalTarget[2]:0);		
		$this->TempFillEls['categorysel'] = ($action == 'DeleteCategory'? $this->category[$selectedIndex] : inputSelect('form[parent_category][id]', $this->category, $this->PreparedTemplates['curPage'][0]['parent']));
		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
	}

	function fillActionMail() {
		global $PHP_SELF;
		$action = $this->LocalTarget[1];
		if (!empty($this->PreparedTemplates['categoryTree']))
		{
			$this->setTargetArray($this->PreparedTemplates['categoryTree']);
		}		
		$this->TempFillEls = array(
			'id' => $action=='Add'? '' : $this->PreparedTemplates['curPage'][0]['id'],
			'action' => $action,
			'actionbutton' => ($action == 'DeleteMail'? $this->globalLangContent['button']['admin_bt_delete'] : $this->globalLangContent['button']['admin_bt_send']),
			'description' => $action == 'DeleteMail'? $this->PreparedTemplates['curPage'][0]['mailtext'] : inputTextArea('form[description]',(!empty($this->Request)? $this->Request['form']['description'] : $this->PreparedTemplates['curPage'][0]['mailtext']),$this->correctSize('50'),$this->correctSize('10')),
			'formaction' => "../",
			'categoryid' => $this->PreparedTemplates['curPage'][0]['categoryid'],
		);
		$selectedIndex=$this->PreparedTemplates['curPage'][0]['categoryid'];
		$this->TempFillEls['categorysel'] = ($action == 'DeleteMail'? $this->category[$selectedIndex] : inputSelect('form[sendcategory]['.$this->PreparedTemplates['curPage'][0]['categoryid'].']', $this->category, $this->PreparedTemplates['curPage'][0]['categoryid']));
		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
	}

	function fillActionSubscriber() {
		$action = $this->LocalTarget[1];
		if (!empty($this->PreparedTemplates['categoryTree']))
		{
			foreach($this->PreparedTemplates['categoryTree'] as $k => $v) {
				$this->TempFillEls['menu'][$k]['header'][$k] = array (
				'catname' => ($action == 'DeleteSubscriber'? '': makeLink($this->Home.'/Admin/AdminSubscription/BrowseCategory/'.$v['id'],ucwords($v['name']),array(),'','class="menuitem"')),
				'catchecksubscr' => ($action == 'DeleteSubscriber'? '': inputCheckbox('form[subscr]['.$v['id'].']', ($v['signed']>0?TRUE:FALSE), '', $v['id'])),
				'catid' =>$v['id'],
				);
				if((!empty($v['subcat'])) && ($action != 'DeleteSubscriber')) $this->setTargetArray2($v['subcat'],$k,1);
			}
			if ($action != 'DeleteSubscriber')
			{
				$this->TempFillEls['email_format1'] = $this->globalLangContent['label']['subscription_format_html'].inputRadio('form[emailformat]',0,($this->PreparedTemplates['emailFormat']==0?TRUE:FALSE));
				$this->TempFillEls['email_format2'] = $this->globalLangContent['label']['subscription_format_text'].inputRadio('form[emailformat]',1,($this->PreparedTemplates['emailFormat']==1?TRUE:FALSE));
			}
		}
		$this->TempFillEls['action'] = $action;
		$this->TempFillEls['email']= ($action == 'DeleteSubscriber'? $this->PreparedTemplates['email'] : inputText('form[email]',(!empty($this->Request)? $this->Request['form']['email'] : $this->PreparedTemplates['email']),$this->correctSize('40')));
		$this->TempFillEls['authcode']= inputHidden('form[id]',(!empty($this->Request)? $this->Request['form']['id'] : $this->PreparedTemplates['id']),$this->correctSize('40'));
		$this->TempFillEls['id']= inputHidden('form[authcode]',(!empty($this->Request)? $this->Request['form']['authcode'] : $this->PreparedTemplates['authcode']),$this->correctSize('40'));
		$this->TempFillEls['actionbutton'] = ($action == 'DeleteSubscriber'? $this->globalLangContent['button']['admin_bt_delete'] : $this->globalLangContent['button']['admin_bt_subscribe']);

		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'viewsubscription');
	}

	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_info']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_info']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->globalLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); 
				 break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}

	
	function setTargetArray($array = array(),$level = 0) {
		foreach($array as $key => $value) {
			$this->category[$value['id']] = str_repeat("-",$level).$value['name'];
			if(!empty($value['subcat'])) $this->setTargetArray($value['subcat'],$level+2);
		}
	}

	function setTargetArray2($array = array(),$k, $level = 1,$subitems = array(), $subitems=array()) {		
		$color='#F8F8F8';
		foreach($array as $key => $value) {
			$this->TempFillEls['menu'][$k]['category'][$value['id']] = array(
				'catname' => makeLink($this->Home.'/Admin/AdminSubscription/BrowseCategory/'.$value['id'],ucwords($value['name']),array(),'','class="menuitem"'),
				'catid' => $value['id'],
				'catchecks' => inputCheckbox('form[sendcategory]['.$value['id'].']', FALSE, '', $value['id']),
				'catchecksubscr' => inputCheckbox('form[subscr]['.$value['id'].']', ($value['signed']>0?TRUE:FALSE), '', $value['id']),
				'catwidth' => intval($level*50),
				'catwidth2' => 600 - intval($level*50),
				'catclass' => 'b',
				'catbgcolor' => $color,
			);
			if(!empty($value['subcat'])) {$this->setTargetArray2($value['subcat'],$k,$level+1);}
		}		
		return $subitems;
	}
}
?>