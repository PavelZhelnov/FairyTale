<?php

class AdminMemberView extends Slot {

	public $ModuleID = 3;
	public $SectionID = 21;
	public $Task = 'view';
	public $level;
	public $amount = array('5' => '5', '10' => '10', '15' => '15','30' => '30','50'=>'50','100'=>'100');
	public $orderby = array(
		'Date' => array(
			'sortColumn' => 'date',
			'sortType' => 'desc',
		),
		'Status' => array(
			'sortColumn' => 'level',
			'sortType' => 'asc',
		),
		'Name' => array(
			'sortColumn' => 'last_name',
			'sortType' => 'asc',
		),
	);
	public $sort_array = array();
	public $sortby = '';
	public $search_params;
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


	function AdminMemberView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
	}

	function init() {
		global $PHP_SELF;
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Action->processEvent($this->SectionID,'get_search',$this->getRequestField('form'),$this);
		$this->search_params = $this->PreparedTemplates;

		$this->Action->processEvent($this->SectionID,'selectLevels',array('langid' => $this->LM->Langs[$this->language]),$this);
		$this->level = $this->PreparedTemplates;
		
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				$this->curPageNumber = empty($this->LocalTarget[1]) || !validate(intval($this->LocalTarget[1]))? 0 : intval($this->LocalTarget[1]);
				switch(@$this->LocalTarget[1]) {
				case 'AddMember':
					$this->Scheme = 'action';
					$this->Action->processEvent($this->SectionID,'new',$this->getRequestField('form'),$this);
				break; 
				case 'ViewMember':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'viewmember';
						$this->Task = 'viewmember';
						$this->Action->processEvent($this->SectionID,'viewmember',array('id' => intval($this->LocalTarget[2]), 'langid' => $this->LM->Langs[$this->language]),$this);
						if(empty($this->PreparedTemplates)) 
						{
							header("Location: ".$this->Home.'/Admin/AdminMember'.$this->SID);
						}
					}
					else header("Location: ".$this->Home.'/Admin/AdminMember'.$this->SID);
				break;
				case 'EditMember':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$request['id'] = $this->LocalTarget[2];						
						$this->Scheme = 'action';
						$this->Task = 'view';
						if (isset($this->Request['form']))
							$request = $this->Request['form'];
						if (isset($request['id'])) {
							$request['langid'] = $this->LM->Langs[$this->language];
							$this->Action->processEvent($this->SectionID,'getmember',$request,$this);
						}
						else $this->Action->processEvent($this->SectionID,'view',$request,$this);
					}
					else header("Location: ".$this->Home.'/Admin/AdminMember'.$this->SID);
				break;
				case 'DeleteMember':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$request['id'] = $this->LocalTarget[2];						
						$this->Scheme = 'action';
						$this->Task = 'delete';
						if (isset($this->Request['form']))
							$request = $this->Request['form'];
						if (isset($request['id'])) {
							$request['langid'] = $this->LM->Langs[$this->language];
							$this->Action->processEvent($this->SectionID,'getmember',$request,$this);
						}
						else $this->Action->processEvent($this->SectionID,'view',$request,$this);
					}
					else header("Location: ".$this->Home.'/Admin/AdminMember'.$this->SID);
				break;
				case 'ViewByStatus':
					if (validate($this->LocalTarget[2]))
					$this->Request['form']['level'] = $this->LocalTarget[2]
					and $this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
					and header("Location: ".$this->Home.'/Admin/AdminMember/');
				break; 
				case 'ViewAll':
					$this->Request['form']['level'] = 0;
					$this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
					and header("Location: ".$this->Home.'/Admin/AdminMember'.$this->SID);
				break; 
				default:
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request = array('pageRecordsQty'=>'10','curPageNumber'=>(isset($this->LocalTarget[1])? $this->LocalTarget[1]+1 : 1));
					$this->sortby = !empty($this->LocalTarget[2]) && in_array($this->LocalTarget[2],array_keys($this->orderby))? $this->LocalTarget[2] : 'Status';
					$request['sortColumn'] = $this->orderby[$this->sortby]['sortColumn'];
					$request['sortType'] = $this->orderby[$this->sortby]['sortType'];
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
					 //else {$this->getPageControl($this->Home.'/Admin/AdminMember/'.(!empty($this->LocalTarget[1])?$this->LocalTarget[1]:0),0);}
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'delete':
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'delete',$this->getRequestField('form'),$this)
						and $this->Action->setPage($this->SectionID,'finish_delete') and header("Location: ".$this->Home.'/Admin/AdminMember/'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) {$this->Scheme = 'message'; }
					break;
					case 'search':
						$this->validateForm()
						and $this->Action->processEvent($this->SectionID,'set_search',$this->getRequestField('form'),$this)
						and header("Location: ".$this->Home.'/Admin/AdminMember'.$this->SID);
					break;				
					case 'edit': case 'add':
						$this->Task = 'update';
						$request = $this->Request['form'];
						$request['langid'] = $this->LM->Langs[$this->language];
						$image = $this->getRequestField('image');
						if($image['size']) {
							$size = GetImageSize($image['tmp_name']);
							$request['image_type'] = $this->upload_formats[$image['type']];
						}
						//$list = (!empty($this->PreparedTemplates['curPage'])?$this->PreparedTemplates['curPage']:array());
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'update',$request,$this)
						and $this->Action->setPage($this->SectionID,'finish_save') and header("Location: ".$this->Home.'/Admin/AdminMember/'.$this->SID);
						if(!empty($this->PreparedTemplates['_error'])) {$this->PreparedTemplates['curPage'] = $list; }
					break;
					case 'send_confirm':
						$request = $this->Request['form'];
						$request['langid']=$this->LM->Langs[$this->language];						
						$this->Action->processEvent($this->SectionID,'sendconfirmregistration',$request,$this);
						if(!empty($this->PreparedTemplates['_error'])) {$this->Scheme = 'message'; }
						$this->Scheme = 'end';
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
			case 'edit':
				if(!is_AlphaNumDefisSpace($this->getRequestFormField('first_name'),1,32)) $this->errors['first_name'] = $this->globalLangContent['error_view']['err_firstname'];
				if(!is_AlphaNumDefisSpace($this->getRequestFormField('last_name'),3,32)) $this->errors['last_name'] = $this->globalLangContent['error_view']['err_lastname'];
				if(!is_AlphaNumDefis($this->getRequestFormField('login'),3,32)) $this->errors['login'] = $this->globalLangContent['error_view']['err_login'];
				if(!is_Email($this->getRequestFormField('email'),5,32)) $this->errors['email'] = $this->globalLangContent['error_view']['err_email'];
			break;
			case 'add':
				if(!is_AlphaNumDefisSpace($this->getRequestFormField('first_name'),1,32)) $this->errors['first_name'] = $this->globalLangContent['error_view']['err_firstname'];
				if(!is_AlphaNumDefisSpace($this->getRequestFormField('last_name'),3,32)) $this->errors['last_name'] = $this->globalLangContent['error_view']['err_lastname'];
				if(!is_AlphaNumDefis($this->getRequestFormField('login'),3,32)) $this->errors['login'] = $this->globalLangContent['error_view']['err_login'];
				if(!is_Email($this->getRequestFormField('email'),5,32)) $this->errors['email'] = $this->globalLangContent['error_view']['err_email'];
				if(!is_AlphaNumDefisSpace($this->getRequestFormField('password'),5,20)) $this->errors['password'] = $this->globalLangContent['error_view']['err_password'];
				if($this->getRequestFormField('password')!=$this->getRequestFormField('conf_password') ) $this->errors['conf_password'] = $this->globalLangContent['error_view']['confirmpassw'];
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
			case 'viewmember': $this->fillViewMember(); break;
		}
	}

	
	function fillView() {
		if (isset($this->Request['form'])) $member=$this->Request['form'];
		$this->TempFillEls = array(
			'id' => inputHidden('form[id]',''),
			'first_name' => inputText('form[first_name]',(isset($member['first_name'])?$member['first_name']:'')),
			'last_name' => inputText('form[last_name]',(isset($member['last_name'])?$member['last_name']:'')),
			'company' => inputText('form[company]',(isset($member['company'])?$member['company']:'NycApts4Rent')),
			'address' => inputText('form[address]',(isset($member['address'])?$member['address']:'')),
			'phone' => inputText('form[phone]',(isset($member['phone'])?$member['phone']:'')),
			'fax' => inputText('form[fax]',(isset($member['fax'])?$member['cell']:'')),
			'cell' => inputText('form[cell]',(isset($member['cell'])?$member['cell']:'')),
			'login' => inputText('form[login]', (isset($member['login'])?$member['login']:'')),			
			'password' => inputPassword('form[password]',''),
			'conf_password' => inputPassword('form[conf_password]',''),
			'email' => inputText('form[email]',(isset($member['email'])?$member['email']:'')),
			'level' => inputSelect('form[level][id]',$this->level,(!empty($this->Request['form']['level']['id'])? $this->Request['form']['level']['id'] : '0')),
			'image' => inputFile('image')
		);

		$i=1;
		foreach($this->PreparedTemplates['curPage'] as $key => $value) {
			$this->TempFillEls['member'][$value['id']] = array(
				'id' => $value['id'],
				'email' =>  $value['email'],
				'first_name' =>$value['first_name'],
				'last_name' => $value['last_name'],
				'company' => $value['company'],
				//'address' => $value['address'],
				//'phone' => $value['phone'],
				//'fax' => $value['fax'],
				//'cell' => $value['cell'],				
				'login' => $value['login'],
				'date' => $value['date'],
				'activated' => $value['activated']=='0'?'No':'Yes',
				'level' => $value['level'],
				'number' =>$i,
				'objectprew' => (isset($value['image_type'])?
						makeImage($this->ImagePath.'/members/'.$value['id'].'prew.'.$value['image_type'],$this->ImageWPath.'/members/'.$value['id'].'prew.'.$value['image_type'],'','center',array(),0):
						makeImage($this->ImagePath.'/elements/membernotavail.jpg',$this->ImageWPath.'/elements/membernotavail.jpg','','center',array(),0)), 
			);
			$i++;
		}
		
		$this->sort_array = array(
			'date' => $this->sortby=='Date'? '<span class=first>Date</span>' : makeLink($this->Home.'Admin/AdminMember/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/Date',' Date '),
			'status' => $this->sortby=='Status'? '<span class=first>Status</span>' : makeLink($this->Home.'Admin/AdminMember/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/Status',' Status '),
			'name' => $this->sortby=='Name'? '<span class=first>Name</span>' : makeLink($this->Home.'Admin/AdminMember/'.(validate(intval(@$this->LocalTarget[1]))? $this->LocalTarget[1] : 0).'/Name',' Name '),
		);
		$this->TempFillEls['sort'][] = $this->sort_array;
		
		$this->TempFillEls['first_name'] = inputText('form[first_name]',(!empty($this->search_params['first_name'])? $this->search_params['first_name'] : ''),$this->correctSize('20'));
		$this->TempFillEls['last_name'] = inputText('form[last_name]',(!empty($this->search_params['last_name'])? $this->search_params['last_name'] : ''),$this->correctSize('20'));
		$this->TempFillEls['company'] = inputText('form[company]',(!empty($this->search_params['company'])? $this->search_params['company'] : ''),$this->correctSize('20'));
		//$this->TempFillEls['email'] = inputText('form[email]',(!empty($this->search_params['email'])? $this->search_params['email'] : ''),$this->correctSize('20'));
		$this->TempFillEls['amount'] = inputSelect('form[amount]',$this->amount,(!empty($this->search_params['amount'])? $this->search_params['amount'] : 10), ' onchange="document.forms.search.submit();" ');
		$this->TempFillEls['email'] = inputText('form[email]',(!empty($this->search_params['email'])? $this->search_params['email'] : ''),$this->correctSize('20'));		
		$this->getPageControl($this->Home.'Admin/AdminMember',$this->sortby);		
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);		
	}
 	
	function fillMemberStatistic() {
		$props=0; $bpos = 0; $tasks = 0;
		foreach ($this->PreparedTemplates['_statistic']['properties'] as $k=>$v) {
			$this->TempFillEls['statuses'][] = array(
				'name' => makeLink($this->Home.'/Admin/AdminListing/ViewByBoth/'.$this->PreparedTemplates['id'].'/'.$v['status'], $v['name'].' Listing',array()),
				'qty' => makeLink($this->Home.'/Admin/AdminListing/ViewByBoth/'.$this->PreparedTemplates['id'].'/'.$v['status'], ' '.$v['qty'].' ',array()),
				//'name' => $v['name'].' Listing',
				//'qty' => $v['qty'].' ',

			);
			if (!empty($v['qty'])) $props = $props + $v['qty'];	
		}
		foreach ($this->PreparedTemplates['_statistic']['mlss'] as $k=>$v) {
			$this->TempFillEls['bpos'][] = array(
				'name' => makeLink($this->Home.'/Admin/AdminListing/ViewByBoth/'.$this->PreparedTemplates['id'].'/'.$v['status'], $v['name'].' Listing',array()),
				'qty' => makeLink($this->Home.'/Admin/AdminListing/ViewByBoth/'.$this->PreparedTemplates['id'].'/'.$v['status'], ' '.$v['qty'].' ',array()),
				//'name' => $v['name'].' Listing',
				//'qty' => ' '.$v['qty'].' ',

			);
			if (!empty($v['qty'])) $bpos = $bpos + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['_statistic']['duetasks'] as $k=>$v) {
			$this->TempFillEls['duetasks'][] = array(
				//'name' => makeLink($this->Home.'/Admin/AdminListing//ViewTasks/', $v['name'],array()),
				//'qty' => makeLink($this->Home.'/Admin/AdminListing//ViewTasks/', ' '.$v['qty'].' ',array()),
				'name' => $v['name'],
				'qty' => ' '.$v['qty'].' ',

			);
			if (!empty($v['qty'])) $tasks = $tasks + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['_statistic']['overduetasks'] as $k=>$v) {
			$this->TempFillEls['overduetasks'][] = array(
				//'name' => makeLink($this->Home.'/Admin/AdminListing//ViewTasks/', $v['name'],array()),
				//'qty' => makeLink($this->Home.'/Admin/AdminListing//ViewTasks/', ' '.$v['qty'].' ',array()),
				'name' => $v['name'],
				'qty' => $v['qty'].' ',

			);
			if (!empty($v['qty'])) $tasks = $tasks + $v['qty'];	
		}

		foreach ($this->PreparedTemplates['_statistic']['notes'] as $k=>$v) {
			$this->TempFillEls['notes'][] = array(
				//'name' => makeLink($this->Home.'/Admin/AdminListing//ViewNotes/', $v['name'],array()),
				//'qty' => makeLink($this->Home.'/Admin/AdminListing//ViewNotes/', $v['qty'].' ',array()),
				'name' => $v['name'],
				'qty' => $v['qty'].' ',

			);
			if (!empty($v['qty'])) $tasks = $tasks + $v['qty'];
		}
		$this->TempFillEls['properties'] = $props.' ';
		$this->TempFillEls['bpo'] = $bpos.' ';
		$this->TempFillEls['tasks'] = $tasks.' ';
	}

	function fillViewMember() {
		$this->state = $this->Action->Server->getGuide('state');
        $member=$this->PreparedTemplates;
		$this->TempFillEls = array(
			'id' => $member['id'],
			'email' =>  $member['email'],
			'first_name' =>$member['first_name'],
			'last_name' =>$member['last_name'],
			'company' => $member['company'],
			'address' => $member['address'],
			'phone' => $member['phone'],
			'fax' => $member['fax'],
			'cell' => $member['cell'],			
			'login' => $member['login'],
			'level' => $this->level[$member['level']['id']],
			'objectprew' => (isset($member['image_type'])?
					makeImage($this->ImagePath.'/members/'.$member['id'].'prew.'.$member['image_type'],$this->ImageWPath.'/members/'.$member['id'].'prew.'.$member['image_type'],'','center',array(),0):
					makeImage($this->ImagePath.'/elements/membernotavail.jpg',$this->ImageWPath.'/elements/membernotavail.jpg','','left',array(),0)), 

		);
		$this->fillMemberStatistic();
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'viewnews');
	}

	function fillAction() {
		global $PHP_SELF;
		$action = (isset($this->LocalTarget[1])?($this->LocalTarget[1]=='EditMember'?'edit':($this->LocalTarget[1]=='DeleteMember'?'delete':'add')):'add');
        $member=$this->PreparedTemplates;
        $memberlevel = ( (!empty($this->Request['form']['level'])? $this->Request['form']['level'] : (isset($member['level'])?$member['level']:0)) );
        //$membermanager = ( (!empty($this->Request['form']['ownerid'])? $this->Request['form']['ownerid'] : (isset($member['ownerid'])?$member['ownerid']:0)) );
 		//$this->Action->processEvent($this->SectionID,'managers',array(),$this);
		//$this->manager = mergeArrays(array('0' => ' --- Choose Manager --- '),$this->Action->getTemplate($this->SectionID,'managers'));
		$this->TempFillEls = array(
			'id' => $member['id'],
			'first_name' => ($action=='delete')? $member['first_name']: inputText('form[first_name]',(!empty($this->Request)? $this->getRequestFormField('first_name') : $member['first_name']),$this->correctSize('38')),
			'last_name' => ($action=='delete')? $member['last_name']: inputText('form[last_name]',(!empty($this->Request)? $this->getRequestFormField('last_name') : $member['last_name']),$this->correctSize('38')),
			'address' => ($action=='delete')? $member['address']: inputText('form[address]',(!empty($this->Request)? $this->getRequestFormField('address') : $member['address']),$this->correctSize('38')),
			'phone' => ($action=='delete')? $member['phone']: inputText('form[phone]',(!empty($this->Request)? $this->getRequestFormField('phone') : $member['phone']),$this->correctSize('38')),
			'fax' => ($action=='delete')? $member['fax']: inputText('form[fax]',(!empty($this->Request)? $this->getRequestFormField('fax') : $member['fax']),$this->correctSize('38')),
			'cell' => ($action=='delete')? $member['cell']: inputText('form[cell]',(!empty($this->Request)? $this->getRequestFormField('cell') : $member['cell']),$this->correctSize('38')),
			
			
			'email' => ($action=='delete')? $member['email']: inputText('form[email]',(!empty($this->Request)? $this->getRequestFormField('email') : $member['email']),$this->correctSize('38')),
			'company' => ($action=='delete')? $member['company']: inputText('form[company]',(!empty($this->Request)? $this->getRequestFormField('company') : $member['company']),$this->correctSize('38')),
			'login' => ($action=='delete')? $member['login']: inputText('form[login]',(!empty($this->Request)? $this->getRequestFormField('login') : $member['login']),$this->correctSize('38')),
			'password' => ($action=='delete')? '**********': inputPassword('form[password]',(!empty($this->Request)? $this->getRequestFormField('password') : $member['password']),$this->correctSize('38')),
			'conf_password' => ($action=='delete')? '***********': inputPassword('form[conf_password]',(!empty($this->Request)? $this->getRequestFormField('conf_password') : $member['password']),$this->correctSize('38')),
			
			'activated' => ($action=='delete'? ($member['activated']=='1'?'Yes':'No'): inputCheckBox('form[activated]',$member['activated'],'','1')),
			'level' => ($action=='delete'?$this->level[$member['level']]: inputSelect('form[level]',$this->level,$memberlevel,' style=\'width:200px\';')),
			'action' =>$action,
			'actiontext' => ( (($action=='delete') ? 'Delete member' : (($action=='edit')?'Update member':'Add new member'))),
			'image' => ($action=='delete'?'--':inputFile('image')),
			'objectprew' => (isset($member['image_type'])?
					makeImage($this->ImagePath.'/members/'.$member['id'].'prew.'.$member['image_type'],$this->ImageWPath.'/members/'.$member['id'].'prew.'.$member['image_type'],'','center',array(),0):
					makeImage($this->ImagePath.'/elements/membernotavail.jpg',$this->ImageWPath.'/elements/membernotavail.jpg','','left',array(),0)), 

		);
		$this->PreparedTemplates = $this->Action->getTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save'));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,($action == 'Delete'? 'delete' : 'save')); 
	}
		
	function fillMessage() {
		switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_broker']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_user']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->globalLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); 
				 break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}
	}


	function fillEnd() {
		$this->TempFillEls = array();
	}
	
	function deleteImages($array) {		
		if (!empty($array['id'])) {
			foreach($this->upload_formats as $key => $value)
				if(file_exists($this->ImagePath.'/members/'.$array['id'].'.'.$value)) {
					@unlink($this->ImagePath.'/members/'.$array['id'].'.'.$value);
					@unlink($this->ImagePath.'/members/'.$array['id'].'prew.'.$value);
				}
        }
	}
 
	function saveImage($array) {
		$photo = $this->getRequestField('image');
		if(!empty($photo['tmp_name'])) {
			foreach($this->upload_formats as $key => $value)
				if(file_exists($this->ImagePath.'/members/'.$array['id'].'.'.$value)) {
					unlink($this->ImagePath.'/members/'.$array['id'].'.'.$value);
					@unlink($this->ImagePath.'/members/'.$array['id'].'prew.'.$value);
				}
			$size = GetImageSize($photo['tmp_name']);
			$size = GetImageSize($photo['tmp_name']);
			copy($photo['tmp_name'],$this->ImagePath.'/members/'.$array['id'].'.'.$this->upload_formats[$size['mime']]);
			chmod($this->ImagePath.'/members/'.$array['id'].'.'.$this->upload_formats[$size['mime']],0664);			
			$thumbnail = new Thumbnail($this->ImagePath.'/members/'.$array['id'].'.'.$this->upload_formats[$size['mime']]);
			$thumbnail->setMaxSize(160,120,true);
			$thumbnail->setQualityOutput(TRUE);
			ob_start();
			$thumbnail->outputThumbnail('jpg',75);
			$image = ob_get_contents();
			ob_end_clean();
			$file = fopen($this->ImagePath.'/members/'.$array['id'].'prew.'.$this->upload_formats[$size['mime']],'w');
			fputs($file,$image);
			chmod($this->ImagePath.'/members/'.$array['id'].'prew.'.$this->upload_formats[$size['mime']],0664);
		}
	}

}
?>