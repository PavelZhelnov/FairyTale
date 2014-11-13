<?php

include_once($MODEL_PATH.'/Modules/Common/ModelAnnotation.class.inc');
include_once($MODEL_PATH.'/Modules/Common/User.class.inc');
include_once($MODEL_PATH.'/Modules/Common/Subscribers.class.inc');

include_once($MODEL_PATH.'/Modules/Admin/InfoText.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/InfoText_Lang.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/Message.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/Message_Lang.class.inc');
include_once($MODEL_PATH.'/Modules/Common/News.class.inc');
include_once($MODEL_PATH.'/Modules/Common/News_Lang.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/SubscriptionCategory.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/SubscriptionCategory_Lang.class.inc');
include_once($MODEL_PATH.'/Modules/Admin/SubscriptionLetter.class.inc');
include_once($MODEL_PATH.'/Security/Member.class.inc');
include_once($MODEL_PATH.'/Security/Level.class.inc');


class AdminHandler extends Handler {
	
	public $currentuser;
	public $categorylist;
	public $categorylistid;

	
	function AdminHandler($calledbyson=true){
		$this->Handler($calledbyson);
		$this->currentuser = new User();
	}

	function getCurrentUser($request){
		return $this->currentuser;
	}

	function authorizeMember($request){
		global $Server;
		$this->currentuser = new User();
		$this->parseRequest($request,$this->currentuser);
		//$this->currentuser->password = md5($this->currentuser->password);
		$selected=$this->DB->SelectArray("user",array('id'),array('username'=>$this->currentuser->username,'password'=>$this->currentuser->password));
		if (!empty($selected)) {
			$this->currentuser->id=$selected[0]['id'];
			$this->DB->initObject($this->currentuser);
		}
		else $this->currentuser->_error='1';
		return $this->currentuser;
	}


	//Email content ******************************************// Admin
	function updateEmail($request)
	{
		$selected=$this->DB->update('modulesetting',array('value'=>$request['email']),array('ownerid'=>'1','paramid'=>'1'));
		return $request;
	}

	function getAdminEmail($request){
		$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'1','paramid'=>'1'));	
		if(!empty($selected)) $request['adminemail']=$selected[0]['value'];
		return $request;
	}

	
	//Pages content ********************************************** //Admin
	function selectPagesToEdit($request) {		
		if(empty($request['fields'])) $request['fields']='it.name as textname, it.id as textid, itl.ownerid as textowner, itl.language, itl.value as tvalue, itl.header as theader';
		//if(empty($request['conditions']['itl.language'])) $request['conditions']['itl.language']=array('='=>$request['langid']);
		$request['curPage']=$this->DB->SelectArray(Array('infotext as it left join infotext_lang as itl on it.id=itl.ownerid'),$request['fields'],'where itl.language='.$request['langid'].' order by it.id',0,0,0);
		return $request;
	}

	function getPage($request) {
		if (!isset($request['id'])) {$request['id']=0;}
		if(empty($request['fields'])) $request['fields']='it.name as textname, it.id as textid, itl.ownerid as textowner, itl.language, itl.value as tvalue, itl.header as theader';
		$request['curPage']=$this->DB->SelectArray(Array('infotext as it left join infotext_lang as itl on it.id=itl.ownerid'),$request['fields'],' where it.id='.$request['id'].' order by itl.language' ,0,0);
		if(empty($request['curPage'])) {
			$request["_error"]='3'; //no such page
			return $request;
		}
		return $request;
	}

	function updatePage($request)
	{
		$itl=$this->createInfoText();
		$this->parseRequest($request,$itl);		
		$selected=$this->DB->SelectArray('infotext',array('name'),array('name'=>$itl->name));
		if ((!empty($selected)) && ($itl->id<1)){
			$itl->_error='14';
			return $itl;
		}
		$this->DB->processObject($itl);
		return $itl;
	}

	function deletePage($request){
		$page = $this->createInfoText();
		$this->parseRequest($request,$page);
		$this->DB->initObject($menuitem);
		$selected=$this->DB->SelectArray('menuitem',array('contentpage'),array('contentpage'=>$page->id));
		if(!empty($selected)) {
			$page->_error=12;
			return $page;
		}
		$this->DB->processObject($page,'delete');
		return $page;	
	}

	//Message text **********************************************
	
	function getAdminMessage($request) {
		//if (!isset($request['id'])) {$request['id']=0;}
		if(empty($request['fields'])) $request['fields']='m.name, m.id as id, ml.ownerid, ml.language, ml.text';
		//if(empty($request['conditions']['ml.language'])) $request['conditions']['ml.language']=array('='=>$request['langid']);
		$request['curPage']=$this->DB->SelectArray(Array('message as m left join message_lang as ml on m.id=ml.ownerid'),$request['fields']);
		return $request;
	}

	function saveMessage($request) {
		$m=$this->createMessage();
		$this->parseRequest($request,$m);
		$this->DB->processObject($m);
		return $nwl;
		
	}
	
	function saveHeaderAdmin($request) {
		$selected = $this->DB->SelectAny('update modulesetting set value = \''.$request['image_type'].'\' where ownerid=1 and paramid = 3');
		return $request;
	}	

	//News content **********************************************
	function selectNews($request) {		
		if(empty($request['fields'])) $request['fields']='nw.name as newsname, nw.id as newsid, DATE_FORMAT(nw.pubdate,\'%m/%d/%y\') as publicatedate, nw.pubdate, nwl.ownerid as newsowner, nwl.language, nwl.description as ndescription, nwl.header as nheader';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='5';
		if(empty($request['conditions']['nwl.language'])) $request['conditions']['nwl.language']=array('='=>$request['langid']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('news as nw left join news_lang as nwl on nw.id=nwl.ownerid'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);

		$request['curPage']=$this->DB->SelectArray(Array('news as nw left join news_lang as nwl on nw.id=nwl.ownerid'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		return $request;
	}

	function getNews($request) {
		if (!isset($request['id'])) {$request['id']=0;}
		if(empty($request['fields'])) $request['fields']='nw.name as newsname, nw.id as newsid, DATE_FORMAT(nw.pubdate,\'%m/%d/%y\') as publicatedate, nw.pubdate, nwl.ownerid as newsowner, nwl.language, nwl.description as ndescription, nwl.header as nheader';
		if(empty($request['conditions']['nwl.language'])) $request['conditions']['nwl.language']=array('='=>$request['langid']);
		$request['curPage']=$this->DB->SelectArray(Array('news as nw left join news_lang as nwl on nw.id=nwl.ownerid'),$request['fields'],'where nw.id='.$request['id'].' order by nwl.language asc',0,0);
		if(empty($request['curPage'])) {
			$request->_error='4'; //no such news
			return $request;
		}
		return $request;
	}

	function saveNews($request) {
		$nwl=$this->createNews();
		$this->parseRequest($request,$nwl);
		$this->DB->processObject($nwl);
		return $nwl;
		
	}

	function deleteNews($request) {
		$nwl=$this->createNews();
		$this->parseRequest($request,$nwl);
		$selected=$this->DB->SelectArray(Array('news'),'*',array('id'=>$nwl->id),0,0);
		if(empty($selected)) {
			$nws->_error='4'; //no such news
			return $nwl;	
		}
		$this->DB->processObject($nwl, 'delete');
		return $nwl;
	}

	
	//Subscription content ********************************************** //Admin

	//mail section
	function selectCategoryMail($request) {
		if(empty($request['fields'])) $request['fields']='scl.name as categoryname, scl.id as categoryid, sl.id as mailid, FROM_UNIXTIME(sl.pubdate,"%d/%m/%Y") as publicatedate, sl.pubdate, sl.description as subscriptiontext, sl.last_sent as lastsent';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='5';
		if(empty($request['conditions']['scl.language'])) $request['conditions']['scl.language']=array('='=>$request['langid']);
		if(empty($request['conditions']['sl.category'])) $request['conditions']['sl.category'] = array('='=>$request['id']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('subscriptionletter as sl left join subscriptioncategory_lang as scl on sl.category=scl.ownerid'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('subscriptionletter as sl left join subscriptioncategory_lang as scl on sl.category=scl.ownerid'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		return $request;
	}

	function addSubscriptionLetter($request) {
		//this add to db records - message for history
		//returns list of users' emails - subscribers
		$list=array();
		$users=array();
		$let = $this->createSubscriptionLetter();
		foreach ($request['sendcategory'] as $k=>$v) {
			$let->id=0; $let->category = $v; $let->description=$request['description'];
			$let->pubdate=time(); $let->last_sent=time();
			$this->DB->processObject($let);			
			$selected=$this->DB->SelectArray(Array('subscriptionusers as s left join subscribers on subscribers.id=s.subscriber'),'subscribers.email as email,subscribers.subscription_format as format, subscriber as userid, category',array('category'=>$v,'subscribers.subscription_confirmed'=>'1'));
			if (!empty($selected)) {$list=array_merge($list, $selected);}
		}		
		//get emails from array of subscribers to unique them
		if (!empty($list)) 
		{
			foreach ($list as $k=>$v) 
			{
				$users=array_merge($users,$v['email']);
			}
		}
		$request['subscribers']=$list;
		return $request;
	}
	
	function getMail($request) {
		$request['id'] = (isset($request['id'])?$request['id']:0);
		if(empty($request['fields'])) $request['fields']='sl.id as id, sl.pubdate, sl.description as mailtext, sl.category as categoryid';
		$request['curPage']=$this->DB->SelectArray(Array('subscriptionletter as sl'),$request['fields'],'where sl.id='.$request['id'].' order by sl.pubdate desc',0,0);
		if(empty($request['curPage'])) {
			$request->_error='8'; //no such mail subscription
			return $request;
		}		
		$array=$this->selectCategoriesTree($request,0,1);
		//$request['categoryPath']=$array;
		$request['categoryTree']=$array;
		return $request;
	}

	function deleteMail($request) {
		$sl=$this->createSubscriptionLetter();
		$this->parseRequest($request,$sl);
		$selected=$this->DB->SelectArray(Array('subscriptionletter'),'*',array('id'=>$sl->id),0,0);
		if(empty($selected)) {
			$sl->_error='8'; //no such subscription
			return $sl;	
		}
		$this->DB->processObject($sl, 'delete');
		return $sl;
	}

	
	//subscribers section

	function selectCategorySubscribers($request) {
		if ($request['id']=='0') {//select all subscribers
			if(empty($request['fields'])) $request['fields']='"" as categoryname, 0 as categoryid, s.id as subscriptionid, s.email as subscriberemail, FROM_UNIXTIME(s.subscription_date,"%d/%m/%Y") as subscribedate, s.subscription_confirmed as confirmed, s.id as subscriberid, s.subscription_authcode as subscriberauthcode';
			if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
			if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='20';						
			$selected=$this->DB->SelectArray(Array('subscribers as s'),'count(*) as qty');
			$request['recordsTotal']=$selected[0]['qty'];
			$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
			$request['curPage']=$this->DB->SelectArray(Array('subscribers as s'),$request['fields']);
		} else {//select subscribers from subscription-table
			if(empty($request['fields'])) $request['fields']='scl.name as categoryname, scl.id as categoryid, su.id as subscriptionid, s.email as subscriberemail, FROM_UNIXTIME(s.subscription_date,"%d/%m/%Y") as subscribedate, s.subscription_confirmed as confirmed, s.id as subscriberid, s.subscription_authcode as subscriberauthcode';
			if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
			if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='20';
			if(empty($request['conditions']['scl.language'])) $request['conditions']['scl.language']=array('='=>$request['langid']);
			if( empty($request['conditions']['sl.category']) && $request['id']>0) $request['conditions']['su.category'] = array('='=>$request['id']);
			foreach($request['conditions'] as $k=>$v) $relarr[]='and';
			$selected=$this->DB->SelectArray(Array('subscriptionusers as su left join subscriptioncategory_lang as scl on su.category=scl.ownerid left join subscribers as s on s.id=su.subscriber'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
			$request['recordsTotal']=$selected[0]['qty'];
			$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
			$request['curPage']=$this->DB->SelectArray(Array('subscriptionusers as su left join subscriptioncategory_lang as scl on su.category=scl.ownerid left join subscribers as s on s.id=su.subscriber'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		}
		return $request;
	}

	function modifySubscription($request) {
		//this is for add/delete subscription categories to the table subscription_user
		$subscriber = $this->createSubscriber();
		$subscriber->id = $request['id'];
		if (isset($request['EmailFormat'])) $subscriber->subscription_format=$request['EmailFormat'];
		$this->DB->processObject($subscriber);
		if (!empty($request['Subscribe']))
		{
			$selected=$this->DB->delete('subscriptionusers',array('subscriber' => $request['id']), 'CND_HOMOGENIC', array('relation' => '=', 'operation' => 'and'));
			foreach ($request['Subscribe'] as $k=>$v)
			{
				$this->DB->insert('subscriptionusers',array('subscriber'=>$request['id'],'category'=>$v));
			}
		}
		return $request;
	}
	
	function selectSubscriptionCategories($request) {
		//this for view all categories and check for the current usver'
		$this->categorylistid=0;
		$this->categorylist=array();
		$request['id'] = (isset($request['id'])?$request['id']:0);
		$array=$this->selectCategoriesTree($request,0,1);
		$request['categoryPath']=$array;
		$request['categoryTree']=$array;
		$request['emailFormat']='0';
		$selected=$this->DB->SelectArray(array('subscribers'),'id,subscription_authcode,subscription_format,email',array('id' => $request['id']));
		if (!empty($selected)) 
		{
			$request['emailFormat']=$selected[0]['subscription_format'];
			$request['email']=$selected[0]['email'];
			$request['id']=$selected[0]['id'];
			$request['authcode']=$selected[0]['subscription_authcode'];
		}
		return $request;		
	}

	function getSubscriptionCategory($request){
		$ct= $this->createSubscriptionCategory();
		$this->parseRequest($request,$ct);
		$request['sortColumn'] = 'scl.language';
		$request['sortType'] = 'asc';
		$request['curPage']=$this->DB->SelectArray(Array('subscriptioncategory as sc, subscriptioncategory_lang as scl'),'scl.id as idl, sc.id as id, scl.ownerid as ownerid, scl.language, scl.name as name, sc.parent_category as parent',array('sc.id'=>$ct->id, 'ownerid'=>'sc.id'),$this->getOrderBy($request),0);
		if(empty($request['curPage'])) {
			$ct->_error='2'; //no such category
			return $ct;	
		}
		if((!empty($request['browseCategory'])) && ($request['browseCategory']>0))
		{
			$array=$this->selectCategoriesTree($request, $request['browseCategory'],1);
		} else 
		{
			$array=$this->selectCategoriesTree($request,0,1);
		}
		$request['categoryTree']=$array;
		return $request;
	}

	function saveSubscriptionCategory($request)
	{
		$ctl=$this->createSubscriptionCategory();
		$this->parseRequest($request,$ctl);
		$this->DB->processObject($ctl);
		return $ctl;
	}

	function deleteSubscriptionCategory($request) {
		$ctl=$this->createSubscriptionCategory();
		$this->parseRequest($request,$ctl);
		$selected=$this->DB->SelectArray(Array('subscriptioncategory'),'*',array('id'=>$ctl->id),0,0);
		if(empty($selected)) {
			$cts->_error='2'; //no such category
			return $ctl;	
		}
		$selected=$this->DB->SelectArray(Array('subscriptioncategory'),'*',array('parent_category'=>$ctl->id),0,0);
		if(!empty($selected)) {
			$ctl->_error='5'; //cant delete cause contains some subcategories
			return $ctl;	
		}
		$selected=$this->DB->SelectArray(Array('subscriptionletter'),'*',array('category'=>$ctl->id),0,0);
		if(!empty($selected)) {
			$ctl->_error='10'; //cant delete cause contains some letters in this category
			return $ctl;	
		}
		//delete users' subscription information for this category (ask if it's correct?)
		$selected=$this->DB->delete('subscriptionusers',array('category' => $ctl->id), 'CND_HOMOGENIC', array('relation' => '=', 'operation' => 'and'));
		$this->DB->processObject($ctl, 'delete');
		return $ctl;
	}

	function setTargetCatArray($array=array(), $category)
	{
		foreach ($array as $k => $v)
		{
			if ($v['id']==$category) 
			{
				$this->categorylist[0]=$v;				
			}
			if (!empty($v['subcat'])) 
			{
				$this->setTargetCatArray($v['subcat'], $category);
			}
		}
		return $this->categorylist;
	}
	
	function selectCategoriesTree($request, $category=0, $writecount=0){
		$catArray=Array();		
		$selected=$this->DB->SelectArray('subscriptioncategory c,subscriptioncategory_lang cl left join subscriptionusers as su ON (su.category=c.id and su.subscriber='.$request['id'].')','c.id,c.parent_category,cl.name, IFNULL(su.category,0) as signed',array('c.id'=>'cl.ownerid','language'=>$request['langid']));
		if(!empty($selected)){
			$catArray=$this->makeCatTreeMy($selected);
		}
		if ($category>0) 
		{
			$this->categorylist=array();
			$this->parentCategory=0;
			$catArray=$this->setTargetCatArray($catArray, $category);	
		}
		return $catArray;
	}	

	function makeCatTreeMy($ar,$par=0) {
		$tree='';
		foreach($ar as $k=>$v){
			if ($v['parent_category']==$par) {
				$tree[$v['id']]['id']=$v['id'];
				$tree[$v['id']]['name']=$v['name'];
				$tree[$v['id']]['signed']=$v['signed'];
				$tree[$v['id']]['subcat']=$this->makeCatTreeMy($ar,$v['id']);
			}
		}
		return $tree;
	}

	function deleteSubscriber($request) {
		$subscriber = $this->createSubscriber();
		$subscriber->id = (isset($request['id'])?$request['id']:0);
		$subscriber->subscription_authcode = (isset($request['authcode'])?$request['authcode']:'');
		$selected=$this->DB->SelectArray('subscribers u','u.id,u.email as email,u.subscription_confirmed as confirm'," where u.id='".$subscriber->id."' and u.subscription_authcode='".$subscriber->subscription_authcode."'");
		if(empty($selected)){
			$subscriber->_error='6'; //authcode error
			return $subscriber;
		}
		$selected=$this->DB->delete('subscriptionusers',array('subscriber' => $subscriber->id), 'CND_HOMOGENIC', array('relation' => '=', 'operation' => 'and'));
		$this->DB->processObject($subscriber, 'delete');
		return $subscriber;
	}

	//**********************************************SUBSCRIBER SECTION
	function authorizeSubscriber($request) {
		//this checking whether subscriber exists in the data base, authorize him
		//if not - put into db and send the confirmational letter. Let him have some spam ;)
		$subscriber=$this->createSubscriber();
		$this->parseRequest($request,$subscriber);

		//Select if subscriber already exists.
		//Send him the second letter if exists.

		$selected=$this->DB->selectAny('select * from subscribers where email = '."'".$subscriber->email."'");
		if (!empty($selected))
		{			
			$subscribehref=$request['serviceinfo']['hostname'].'/Things/Subscription/Confirm/'.$selected[0]['id'].'/'.$selected[0]['subscription_authcode'];
			$unsubscribehref=$request['serviceinfo']['hostname'].'/Things/Subscription/Unsubscribe/'.$selected[0]['id'].'/'.$selected[0]['subscription_authcode'];
			$selected=$this->DB->SelectArray('contentitem c left join contentitem_lang cl on cl.ownerid=c.id','c.id,cl.value,c.var',array('c.var'=>'subscription_confirmation_text','language'=>$request['langid']));
			$text = sprintf($selected[0]['value'], $subscribehref, $unsubscribehref);
			//$request->_error='7'; //subscriber already exists
			$request['_error']='7';
			$request['text'] = $text;
			return $request;
		}
		//Subscriber doesn't exist.
		//Assigning new subscriber and sending him confirmation message
		$subscriber->id=0;
		$subscriber->subscription_authcode=$this->MakeHash();
		$subscriber->subscription_date = time();
		$this->DB->processObject($subscriber);
		$selected=$this->DB->SelectArray('contentitem c left join contentitem_lang cl on cl.ownerid=c.id','c.id,cl.value,c.var',array('c.var'=>'subscription_confirmation_text','language'=>$request['langid']));
		$subscribehref=$request['serviceinfo']['hostname'].'/Things/Subscription/Confirm/'.$subscriber->id.'/'.$subscriber->subscription_authcode;
		$unsubscribehref=$request['serviceinfo']['hostname'].'/Things/Subscription/Unsubscribe/'.$subscriber->id.'/'.$subscriber->subscription_authcode;		
		$text = sprintf($selected[0]['value'], $subscribehref, $unsubscribehref);
		$selected[0]['id']=$subscriber->id; $selected[0]['authcode'] = $subscriber->subscription_authcode; $selected[0]['new']='1';
		$selected[0]['text']=$text;
		$selected[0]['email'] = $request['email'];
		return $selected[0];
	}

	function checkConfirm($request) {
		//the link from confirmational letter checking here.
		//if all ok - subscriber is subscribed to letters
		//if subscriber didn't confirm the subscription during 2 days, the record will be deleted.

		//deleting section - if subscriber do the knob for two days ;)
		//deletes the subscriber all information.
		$subscriber=$this->createSubscriber();
/*		$selected=$this->DB->SelectAny('select subscribers.id, subscribers.subscription_confirmed from subscribers where UNIX_TIMESTAMP(NOW())-subscription_date > "86400" and subscription_confirmed = "0"');
		if (!empty($selected))
		{
			foreach ($selected as $k=>$v)
			{
				$selected=$this->DB->delete('subscriptionusers',array('subscriber' => $v['id']), 'CND_HOMOGENIC', array('relation' => '=', 'operation' => 'and'));
			}
		}
		$selected=$this->DB->delete('subscribers',array('UNIX_TIMESTAMP(NOW())-subscription_date' => '86400'), 'CND_HOMOGENIC', array('relation' => '>', 'operation' => 'and'));*/
		
		//confirmation checking

		$selected=$this->DB->SelectArray('subscribers u','u.id,u.email as email,u.subscription_confirmed as confirm'," where u.id='".$request['id']."' and u.subscription_authcode='".$request['authcode']."'");
		if(empty($selected)){
			$subscriber->_error='6'; //authcode error
			return $subscriber;
		}
		if (isset($request['confirm'])) {$selected=$this->DB->update('subscribers',array('subscription_confirmed'=>'1'), array('id' => $request['id']));}
		return $request;
	}


	
	//member
	
	function newMember($request) {
		$member= $this->createMember();
		$member->activated = 1;
		$member->level = 3;
		$member->company = 'Nycapts4Rent';
		return $member;
	}
	
	function deleteMember($request) {
		//$member= $this->createMember();		
		$member = $this->getMember($request);
		$selected=$this->DB->SelectArray(Array('member'),'*',array('id'=>$member->id),0,0);
		if(empty($selected)) {
			$member->_error='1';
			return $member;
		}		
		$selected=$this->DB->SelectArray(Array('listing'),'publisher',array('publisher'=>$member->id),0,0);
		if(!empty($selected)) {
			$member->_error='20';
			return $member;
		}
		if ($member->level['id'] == 6 || $member->level->id == 6) {
			$selected=$this->DB->SelectArray('proprietor',array('id, login')," where login='$member->login'");
			$proprietor = $this->createProprietor();
			if (!empty($selected)) {
				$proprietor->id = $selected[0]['id'];
				$this->DB->processObject($proprietor, 'delete');
			}
		}
		$this->DB->processObject($member, 'delete');
		return $member;
	}

	function getMember($request){
		$member= $this->createMember();		
		$this->parseRequest($request,$member);
		$selected=$this->DB->SelectArray(Array('member'),'*',array('id'=>$member->id),0,0);
		if(empty($selected)) {
			$member->_error='1';
			return $member;
		}
		$this->DB->initObject($member);
		//get Statistic Handler and get all statistic for this member
		global $Server; 
		$this->Statistic = &$Server->getHandler(28);
		$member->_statistic = $this->Statistic->getStatus(array('member'=>$member->id));
		return $member;
	} 
	
	function getProprietor($request){
		$proprietor= $this->createProprietor();		
		$this->parseRequest($request,$proprietor);
		$selected=$this->DB->SelectArray(Array('proprietor'),'*',array('id'=>$proprietor->id),0,0);
		if(empty($selected)) {
			$proprietor->_error='1';
			return $proprietor;
		}
		$this->DB->initObject($proprietor);
		//get Statistic Handler and get all statistic for this member
		return $proprietor;
	} 

	function setSearch($request = array()) {
		global $Server;
		//$Server->settings['ListingSearch'] = array();
		foreach($request as $key => $value) $Server->settings['AdminMemberSearch'][$key] = $value;
		return array();
	}

	function getSearch($request = array()) {
		global $Server;
		return $Server->settings['AdminMemberSearch'];
	}

	function getConditions($request = array(), $search = array()) {
		$request['conditions'] = array();
		if (isset($search['first_name']) && validate($search['first_name']))
			$request['conditions']['b.first_name'] = array('like'=>'%'.$search['first_name'].'%');
		if (isset($search['last_name']) && validate($search['last_name']))
			$request['conditions']['b.last_name'] = array('like'=>'%'.$search['last_name'].'%');
		if (isset($search['email']) && validate($search['email']))
			$request['conditions']['b.email'] = array('='=>'"'.$search['email'].'"');
		if (isset($search['level']) && validate($search['level']))
			$request['conditions']['b.level'] = array('='=>$search['level']);

		return $request;
	}

	function selectMembers($request) {
		$search = $this->getSearch();
		$request = $this->getConditions($request,$search);

		if(empty($request['fields'])) $request['fields']='b.first_name, lv.name as level, b.image_type, b.company, b.address, b.phone, b.fax, b.cell, b.last_name, b.id, FROM_UNIXTIME(b.date_registered,\'%m/%d/%y\') as date, b.email, b.login, b.activated';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 10;
		if (!empty($request['conditions']))
			foreach($request['conditions'] as $k=>$v) $relarr[]='and'; 
			else $relarr=array();
		$selected=$this->DB->SelectArray(Array('member as b left join level as lv on lv.id=b.level '),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('member as b left join level as lv on lv.id=b.level '),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		return $request;
	}
	
	function selectLevels($request=array()) {
		$lv = $this->DB->SelectGuide(array('level l'),array('l.id','l.name'),array());
		return $lv;
	} 

	function saveMember($request) {
		$member = $this->createMember();
		$proprietor = $this->createProprietor();
		$this->parseRequest($request,$member);
		$this->parseRequest($request,$proprietor);
		if ($member->id<=0) {
			$member->date_registered = time();
			$member->hashcode = $this->MakeHash();
			$member->activated='1';			
			
		}
		$selected=$this->DB->SelectArray('member',array('login')," where login='$member->login'");
		if (!empty($selected) && empty($member->id)){
			$member->_error='18';
			return $member;
		}
		if ($member->level['id'] == 6 || $member->level->id == 6) {
			$selected=$this->DB->SelectArray('proprietor',array('id, login')," where login='$proprietor->login'");
			if (!empty($selected) && !empty($proprietor->id)){
				$proprietor->id = $selected[0]['id'];
			}
			$this->DB->processObject($proprietor);
		}
		$this->DB->processObject($member);

		return $member;
	}
	
	//********************************
	function createInfoText() {
		$infotext=new InfoText();		
		$infotext->name_langs=new ObjectsList();
		$infotext->name_langs->type=new InfoText_Lang();
		return $infotext;
	} 
	
	function createNews() {
		$news = new News();
		$news->name_langs=new ObjectsList();
		$news->name_langs->type=new News_Lang();
		return $news;
	}

	function createMessage() {
		$mes = new Message();
		$mes->name_langs=new ObjectsList();
		$mes->name_langs->type=new Message_Lang();
		return $mes;
	}

	function createSubscriptionCategory() {
		$scategory= new SubscriptionCategory();
		$scategory->parent_category=new SubscriptionCategory();
		$scategory->name_langs=new ObjectsList();
		$scategory->name_langs->type=new SubscriptionCategory_Lang();
		return $scategory;
	}
	
	function createSubscriber() {
		$subscr = new Subscribers();
		return $subscr;
	}

	function createSubscriptionLetter() {
		$let = new SubscriptionLetter();
		return $let;
	}
	function createMember() {
		$member = new Member();
		//$member->level = new Level();
		return $member;
	}
	function createProprietor() {
		$pr = new Proprietor();
		//$pr->ownerid = $this->createMember();
		return $pr;
	} 
	function MakeHash()	{
		return md5(time());
	}
}
?>