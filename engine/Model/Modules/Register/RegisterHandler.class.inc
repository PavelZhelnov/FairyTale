<?php

include_once($MODEL_PATH.'/Modules/Common/User.class.inc');
include_once($MODEL_PATH.'/Security/Member.class.inc');
include_once($MODEL_PATH.'/Security/Level.class.inc');
include_once($MODEL_PATH.'/Security/MemberModuleRights.class.inc');
include_once($MODEL_PATH.'/Security/Member.class.inc');
include_once($MODEL_PATH.'/Modules/Listing/Proprietor.class.inc');

class RegisterHandler extends Handler {

	public $currentuser;
	public $categorylist;
	public $categorylistid;


	function RegisterHandler($calledbyson=true){
		$this->Handler($calledbyson);
		$this->currentuser = new User();
	}

	function getCurrentUser($request){
		return $this->currentuser;
	}

	function viewInfo($request) {
		$member = $this->createMember();
		return $member;
	}

	function saveProprietor($request) {
		$proprietor = $this->createProprietor();
		$member = $this->createMember();
		$this->parseRequest($request,$proprietor);
		$this->parseRequest($request,$member);
		if (!isset($proprietor->id) || $proprietor->id<1) {
			$selected=$this->DB->SelectArray('member',array('login')," where login='$proprietor->login'");
			if (!empty($selected) && empty($proprietor->id)){
				$proprietor->_error='18';
				return $proprietor;
			}
			$member->date_registered = time();
			$member->hashcode = $this->MakeHash();
			$member->activated='1';
			$member->level->id=6;
			$this->DB->processObject($member);
		}
		$proprietor->ownerid = $this->Security->currentuser->id;
		$this->DB->processObject($proprietor);
		$this->DB->initObject($proprietor);
		return $proprietor;
	}
	
	function deleteProprietor($request) {
		$proprietor=$this->createProprietor();
		$this->parseRequest($request,$proprietor);
		$selected=$this->DB->SelectArray('listing',array('id')," where proprietor='$proprietor->id'");
		if (!empty($selected)){
			$proprietor->_error='21';
			return $proprietor;
		}

		$selected=$this->DB->delete('proprietor',array('id' => $proprietor->id), 'CND_HOMOGENIC', array('relation' => '='));
		return $this->proprietor;
	}
	
	function selectProprietors($request) {
		if(empty($request['fields'])) $request['fields']='p.id, p.first_name, p.last_name, p.login, p.password, p.email';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 100;
		if(empty($request['sortColumn'])) { $request['sortColumn']='last_name'; $request['sortType']='desc';}
		$request['conditions']['p.ownerid']=array('='=>$this->Security->currentuser->id);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('proprietor as p'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('proprietor as p'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		return $request;
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
		return $proprietor;
	} 

	function saveMember($request) {
		$member = $this->createMember();
		$this->parseRequest($request,$member);
		//when changing password - confirm old password
		if (isset($request['oldpassword'])) {
			$selected=$this->DB->SelectArray('member',array('password')," where id='$member->id' and password='".$request['oldpassword']."'");
			if (empty($selected)){
				$member->_error='1';
				return $member;
			}
		}
		//init new user
		if ($member->id<=0) {
			$member->date_registered = time();
			$member->hashcode = $this->MakeHash();
			$member->level->id=3;
		}
		//if (isset($member->password)) $member->password=md5($member->password);
		$selected=$this->DB->SelectArray('member',array('email')," where email='$member->email'");
		if (!empty($selected) && empty($member->id)){
			$member->_error='14';
			return $member;
		}
		$selected=$this->DB->SelectArray('member',array('login')," where login='$member->login'");
		if (!empty($selected) && empty($member->id)){
			$member->_error='18';
			return $member;
		}
		$this->DB->processObject($member);
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
		return $member;
	} 
	
	function sendConfirmation($request) {
		$member = $this->createMember();
		$member = $this->getMember($request);
		$selected=$this->DB->SelectArray('contentitem c left join contentitem_lang cl on cl.ownerid=c.id','c.id,cl.value,c.var',array('c.var'=>'confirmation_text','language'=>$request['langid']));
		$request['email'] = $member->email;
		$subscribehref=$request['serviceinfo']['hostname'].'/'.$request['lgroup'].'/Register/Confirm/'.$member->id.'/'.$member->hashcode;
		$modifyhref=$request['serviceinfo']['hostname'].'/'.$request['lgroup'].'/Register/Modify/'.$member->id.'/'.$member->hashcode;
		$text = sprintf($selected[0]['value'], $member->first_name, $member->login, $subscribehref, $modifyhref);
		$request['text'] = $text;

		return $request;
	}
	
	function checkConfirm($request) {
		$member=$this->createMember();
		$this->parseRequest($request,$member);
		$selected=$this->DB->SelectArray('member b','b.id,b.email as email,b.activated as activated'," where b.id='".$member->id."' and b.hashcode='".$member->hashcode."'");
		if(empty($selected)){
			$member->_error='6'; //authcode error
			return $member;
		}
		if (isset($request['confirm'])) {
			$member->activated = '1';
			unset($member->password);
			$this->DB->processObject($member);
			$this->DB->initObject($member);			
		}
		return $member;
	}

	function saveImageUser($request) {
		$user = $this->createImageUser();
		$this->parseRequest($request,$user);
		$user->member = $request['id'];
		$user->id = '';
		$this->DB->processObject($user);
		return $user;
	}

	function updateProduct($request) {
	    $member = $this->createMember();
        $this->parseRequest($request,$member);
        if (!empty($request['product_del'])) {
			foreach ($request['product_del'] as $k=>$v)
			{
				$selected=$this->DB->delete('product_selection',array('member' => $member->id,'product'=>$k), 'CND_HOMOGENIC', array('relation' => '=', 'operation' => 'and'));
			}        	
        }
   		if (!empty($request['product'])) {
			foreach ($request['product'] as $k=>$v)
			{
				$this->DB->insert('product_selection',array('member'=>$member->id,'product'=>$k,'prom_code'=>$v));
			}
		}
		return $member;
	}

	function updateContact($request) {
	    $contact = $this->createContact();
        $this->parseRequest($request,$contact);
        $contact->id = $request['contactid'];
        $contact->member = $request['id'];
        $contact->contact_group = $request['groupid'];
        $this->DB->processObject($contact);
		return $contact;
	}

	// ******************************************************

	function createMember(){
		$member =  new Member();
		//$member->country = new Country();
		//$member->state = new State();
		$member->level =$this->createLevel();
   		$member->memberModuleRights = new ObjectsList();
   		$memberModuleRights=new MemberModuleRights();
   		$memberModuleRights->module=new Module();
   		$member->memberModuleRights->type =$memberModuleRights;
		return $member;
	}
	
	function createProprietor() {
		$pr = new Proprietor();
		//$pr->ownerid = $this->createMember();
		return $pr;
	}

	function createLevel(){
		$level = new Level();
		$level->moduleRights = new ObjectsList();
		$moduleRights=new ModuleRights();
		$moduleRights->module=new Module();
		$level->moduleRights->type = $moduleRights;
		return $level;
	}

	function MakeHash()	{
		return md5(time());
	}

}
?>