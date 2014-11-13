<?php

include_once($MODEL_PATH.'/Handler.class.inc');
include_once($MODEL_PATH.'/Security/Level.class.inc');
include_once($MODEL_PATH.'/Security/MemberModuleRights.class.inc');
include_once($MODEL_PATH.'/Security/Member.class.inc');
include_once($MODEL_PATH.'/ObjectsList.class.inc');
include_once($MODEL_PATH.'/Security/ModuleRights.class.inc');
include_once($MODEL_PATH.'/Modules/Common/Module.class.inc');
include_once($MODEL_PATH.'/Modules/Common/State.class.inc');
include_once($MODEL_PATH.'/Modules/Common/Country.class.inc');

include_once($MODEL_PATH.'/Security/TerminateLog.class.inc');

class SecurityHandler extends Handler {

	public $currentuser;
	public $member;//class Member
	public $level;// class Level
	public $db;
	public $notincludemodule=array();

	function SecurityHandler() {
		$this->Handler(false);
		$this->currentuser = $this->createMember();
		$this->member = $this->createMember();
		$this->level = $this->createLevel();
		$this->openLevel(5);
		$this->currentuser->level=$this->level;
	}

	function getCurrentUser($request = array()){
		return $this->currentuser;
	}

	function openLevel($id) {
		$this->level->id=$id;
		$this->DB->initObject($this->level);
	}

	function isAuthorized() {
		if (empty($this->currentuser->username)) return 0;
		else return 1;
	}

	function getMemberByLoginInfo($request) {
		$member = $this->createMember();
		$this->parseRequest($request,$member);
		$selected=$this->DB->SelectArray("member",array('id','activated'),' where password=\''.$member->password.'\' and login=\''.$member->login.'\'',0, 0, 0, array(),'CND_SIMPLE');
		
		if (!empty($selected)) {
			if($selected[0]['activated']==1) {
				$member->id=$selected[0]['id'];
				$this->DB->initObject($member);
			}
			else {
				$member->_error='2';
			}
		} else {
			$member->_error='1';
		}
		return $member;
	}

	function authorizeMember($request){
		global $Server;
		$this->currentuser=$this->createMember();
		//$this->parseRequest($request,$this->currentuser);
		//$this->cleanError($this->currentuser);
		//if (!isset($this->currentuser->id))
			//$this->currentuser->password=md5($this->currentuser->password);
		$this->currentuser = $this->getMemberByLoginInfo($request);
		if(empty($this->currentuser->keep_loggedin)) $this->currentuser->keep_loggedin=0;
		else $this->currentuser->keep_loggedin=1;
		
		/*$selected=$this->DB->SelectArray("member",array('id','activated'),' where password=\''.$this->currentuser->password.'\' and login=\''.$this->currentuser->login.'\'',0, 0, 0, array(),'CND_SIMPLE');
		if (!empty($selected)) {
			if($selected[0]['activated']==1) {
				$this->currentuser->id=$selected[0]['id'];
				//$this->DB->update('member',Array('keep_loggedin'=>$this->currentuser->keep_loggedin,'date_last_login'=>date('Y-m-d H:i:s',time())),Array('id'=>$this->currentuser->id));
				$this->DB->initObject($this->currentuser);
				//$Server->clearAll();
			}
			else {
				$this->currentuser->_error='2';
			}
		}*/
		if (!empty($this->currentuser->_error)) {
			$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGIN, CommonConstants::LOG_ACTION_SECTION_COMMON, 'Unsuccessful, login used:'.$this->currentuser->login);
		} else {
			$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGIN, CommonConstants::LOG_ACTION_SECTION_COMMON, 'Success');
		}
		return $this->currentuser;
	}

	
	function authorizeMemberSSO($request){
		global $Server;
		$this->currentuser=$this->createMember();

 		try {
            $openid = new LightOpenID;
            if(!$openid->mode) {
                
				$openid->identity = 'https://www.google.com/accounts/o8/id';
				$openid->required = array('namePerson/first', 'namePerson/last', 'contact/email');
				$openid->returnUrl = ($request['url'].'Admin/ssoauthret');
				$openid->version = 2;
				header('Location: ' . $openid->authUrl());
        
            } elseif($openid->mode == 'cancel') {
                echo 'User has canceled authentication!';
                
            } else {
        		if($openid->validate())
        		{			
        			$identity = $openid->identity;
        			$attributes = $openid->getAttributes();
        			$email = $attributes['contact/email'];
        			$first_name = $attributes['namePerson/first'];
        			$last_name = $attributes['namePerson/last'];
        		}
        		else
        		{
        			echo 'User ' . $openid->identity . 'has not logged in.';
        		}
            }
        } catch(ErrorException $e) {
            echo $e->getMessage();
        }
			
		return true;
		
	}
	
    // *** OPENID
    function authorizeMemberSSOReturn() {
        $data = array();
        $this->currentuser = $this->createMember();
        // Added on Dec 2010
		// Try to get current city
		/*$city = $this->uri->segment(1);
		if (!empty($city))
		{
			$this->db->select();
			$this->db->where('permalink', $city);
			$city_res = $this->db->get('cities', 1);
			$city_row = $city_res->row_array();
			
			if (!empty($city_row))
			{
				$this->data['city'] = $city_row;
				$this->city = $city_row;
			} else {
				$this->city = NULL;
				$this->_redirect_default_city();
			}
		}
		$this->db->select();
		$this->data['cities'] = $this->db->get('cities')->result_array();
		$data = $this->data;
		// end added block for city
        
         die();*/
        
        // to retrieve $_GET again
        //parse_str($_SERVER['QUERY_STRING'],$_GET);
        $ru = $_SERVER['REQUEST_URI'];
        parse_str(substr($ru,strpos($ru,'?')+1), $_GET);
        
        $openid = new LightOpenID;

        if($openid->mode == 'cancel') {
            
            return false;//echo 'User has canceled authentication!';
            
        } else {
    		if($openid->validate()) {
    						
    			
    			$identity = $openid->identity;
    			$attributes = $openid->getAttributes();
    			$email = $attributes['contact/email'];
    			$first_name = $attributes['namePerson/first'];
    			$last_name = $attributes['namePerson/last'];
    			
                // do internal logic
                
                $res = $this->DB->SelectAny('select m.id from user_openid uo join member m on m.id=uo.user_id where openid_url = \''.$identity.'\'');
                $granted = FALSE;
                $user_id = null;
                
                if (!empty($res)) { 
                    $user_id = $res[0]['id'];
                    $granted = TRUE;
                    
                } else {
                    
                    $res = $this->DB->SelectAny('select m.id, m.email from member m where m.email=\''.$email.'\'');
                    if (!empty($res ))
                    {
                        $user_id = $res[0]['id'];
                        $this->DB->SelectAny('insert into user_openid (user_id, openid_url, date_created) values ('.$res[0]['id'].', \''.$identity.' \', UNIX_TIMESTAMP())');
                        $granted = TRUE;
                    } else {
                        //echo 'OpenID Ok but cannot bind existing user in database. Please contact administrator.';
                        $this->currentuser->_error='2';
                        return $this->currentuser;
                        $granted = FALSE;
                    }
                }
             
                if ($granted ) {
					$this->currentuser->id=$user_id;
					$this->DB->initObject($this->currentuser);
					if(empty($this->currentuser->keep_loggedin)) $this->currentuser->keep_loggedin=0;
					else $this->currentuser->keep_loggedin=1;
					return $this->currentuser;
                } else {
                    $this->currentuser->_error='1';
                }
    		}
    		else {
    			$this->currentuser->_error='1';
    		}
        }
		if (!empty($this->currentuser->_error)) {
			$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGIN, CommonConstants::LOG_ACTION_SECTION_COMMON, 'Unsuccessful, login used:'.$this->currentuser->login);
		} else {
			$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGIN, CommonConstants::LOG_ACTION_SECTION_COMMON, 'Success');
		}
		return $this->currentuser;
    }
	
    // *** END OPENID
	
	

	//Put new password
	function putNewPswd($request){
	
		$selected=array();
		$id_member = $request['id'];
		
		$selected=$this->DB->SelectArray("member",array('id','login','letter_send'),' where id='.$id_member,0, 0, 0, array(),'CND_SIMPLE');
		
		if(!empty($selected) && (time() - $selected[0]['letter_send'] > 24*60*60 ))//
		{
			$selected['0']['error'] = 'The login/email information was not found!';
		}
		//printArray($selected);
		return $selected;
	}
	
	function isUser($request){
	
		$selected=array();
		if(!empty($request['email']) && !empty($request['login']))
			$selected=$this->DB->SelectArray("member",array('id','first_name','last_name','email'),' where email=\''.$request['email'].'\' and login=\''.$request['login'].'\'',0, 0, 0, array(),'CND_SIMPLE');
		else return 0;
		if(!empty($selected))return 1;
		else return  2;
	}
	//seach user by id
	function checkUser($id){
		$selected=array();
		$selected=$this->DB->SelectArray("member",array('id'),' where id=\''.$id.'\'',0, 0, 0, array(),'CND_SIMPLE');
		if(!empty($selected))return true;
		else return  false;
	}
	
	function UpdatePswd($req){
		
		$new_passw = md5($req['passw']);//get hash
		$this->DB->selectAny('update member set  password = "'.$new_passw.'" where id='.$req['id']);
		$this->DB->selectAny('update contact set  password = "'.$new_passw.'" where member='.$req['id']);
	}
	
	//////////////////////////////////////
	function logoffMember($request){
		global $Server;
		$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGOUT, CommonConstants::LOG_ACTION_SECTION_COMMON);
		if(!empty($this->currentuser) && !empty($this->currentuser->id))
			$this->DB->update('member', array('keep_loggedin_code' => ''), array('id'=>$this->currentuser->id));	
		$this->currentuser=$this->createMember();		
		return $this->currentuser;
	}
	
	function authorizeMemberByCookie($request= array()){
		global $Server;
		if(empty($_COOKIE['skey']) || empty($_COOKIE['dkey']))	// If at least one of the needed cokkies is unset, 
			return false;
		$skey = $_COOKIE['skey'];
		$dkey = $_COOKIE['dkey'];
		$this->currentuser = $this->createMember();
		$selected=$this->DB->SelectArray("member",array('id', 'login', 'activated'),array('keep_loggedin_code'=>$dkey));
		if(	!empty($selected) && ($selected[0]['activated'] == 1) && ($this->getStaticKey($selected[0]) == $skey))
		{
			$this->currentuser->id=$selected[0]['id'];
			$this->DB->initObject($this->currentuser);
		}
		
		if(empty($this->currentuser->keep_loggedin)) $this->currentuser->keep_loggedin=0;
		else $this->currentuser->keep_loggedin=1;
		
		if (!empty($this->currentuser->_error)) {
			$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGIN, CommonConstants::LOG_ACTION_SECTION_COMMON, 'Unsuccessful, login used:'.$this->currentuser->login);
		} else {
			$this->getLogHandler()->addAction(CommonConstants::LOG_ACTION_LOGIN, CommonConstants::LOG_ACTION_SECTION_COMMON, 'Success');
		}
		
		return $this->currentuser;
	}
	function getCookieKeys($request = array()) {
		if(empty($this->currentuser) || empty($this->currentuser->id))
			return '';
		$request['dkey'] = $this->MakeHash();
		$request['skey'] = $this->getStaticKey();
		$this->DB->update('member', array('keep_loggedin_code' => $request['dkey']), array('id' => $this->currentuser->id));
		return $request;
	}
	function getStaticKey($request = array()) {
		$id = '';
		$login = '';
		if(empty($request) || empty($request['id']) || empty($request['login'])){
			if(empty($this->currentuser) || empty($this->currentuser->id) || empty($this->currentuser->login))
				return '';
			else{
				$id = $this->currentuser->id;
				$login = $this->currentuser->login;	
				}
		}
		else{
			$id = $request['id'];
			$login = $request['login'];	
		}
		return md5($id.$login);
	}

	function logoutMember($request){
		global $Server;
		$this->currentuser=$this->createMember();
		$this->level = $this->createLevel();
		$this->openLevel(5);
		$Server->clearAll();
		$this->currentuser->level=$this->level;
		return $this->currentuser;
	}

	function checkPerm($module_id,$minperm) {
		$error = '';
		foreach($this->currentuser->level->moduleRights->data as $k=>$v) {			
			//printObject($v);
			if($v->module==$module_id) {
				if (intval($v->perm) >= intval($minperm)) return $error;
				else return '5';
			}
		}
		return intval($minperm) > 2? '5' : '';
	}

	function activateMember($request){
		global $DatabaseBroker;
		$this->member=$this->createMember();
		$this->parseRequest($request,$this->member);
		$this->cleanError($this->member);
		$selected=$this->DB->SelectArray("member",array('id','activated','activate_code'),array('id'=>$this->member->id));
		if (!empty($selected)) {
			if($selected[0]['activated']==1) {
				//$this->member->_error='3';
			}
			else {
				if ($this->member->activate_code==$selected[0]['activate_code']) {
					$this->member->activated='1';
					$this->DB->processObject($this->member);
					$this->DB->initObject($this->member);
/*
					$forumhandler=new ForumHandler();
					$forumhandler->registerUser($this->member);
					unset($DatabaseBroker);	
					$DatabaseBroker = new DatabaseBroker();	
*/
					$newforumhandler=new NewForumHandler();
					$newforumhandler->registerUser($this->member);
					unset($DatabaseBroker);	
					$DatabaseBroker = new DatabaseBroker();	
				}
				else {
					$this->member->_error='4';
				}
			}
		}
		else {
			$this->member->_error='1';
		}
		$this->member->id='';
		return $this->member;
	}

	function registerAdmin($request){
		$member=$this->createRegMember();
		$this->parseRequest($request,$member);
		if(!$this->checkImages($member)) return $member;
		//$member->passw=md5($member->passw);
		$member->id='';
		$selected=$this->DB->SelectArray("member",'id',array('username'=>$member->username));
		if (!empty($selected)) {
			$member->_error='6';
		}
		else {
			$member->activate_code = md5($member->username.$member->username.$member->passw);
			if (empty($member->level->id)) $member->level->id=4;
			$member->rating=1;
			$member->activated=1;
			$member->date_signed=date('Y-m-d H:i:s',time());
			$this->DB->processObject($member);
			$this->DB->initObject($member);
			$newforumhandler=new NewForumHandler();
			$newforumhandler->registerUser($this->member);
//			$forumhandler=new ForumHandler();
//			$forumhandler->registerUser($member);
		}
		return 	$member;
	}

	function checkDelete(&$member){
		$selected=$this->DB->SelectArray('module','current_object',array('id'=>16));
		if(!empty($selected[0]['current_object'])){
			$selected=$this->DB->SelectArray("image",'member',array('id'=>$selected[0]['current_object']));
			if(!empty($selected) && $selected[0]['member']==$member->id) {
				$member->_error='112';
			} 
		}
		$selected=$this->DB->SelectArray('module','current_object',array('id'=>4));
		if(!empty($selected[0]['current_object'])){
			$selected=$this->DB->SelectArray("aaquestion",'member',array('id'=>$selected[0]['current_object']));
			if(!empty($selected) && $selected[0]['member']==$member->id) {
				$member->_error='113';
			}
		}
		$selected=$this->DB->SelectArray('module','current_object',array('id'=>15));
		if(!empty($selected[0]['current_object'])){
			$selected=$this->DB->SelectArray("humor",'member',array('id'=>$selected[0]['current_object']));
			if(!empty($selected) && $selected[0]['member']==$member->id) {
				$member->_error='114';
			} 
		}
		$selected=$this->DB->SelectArray('zone z, adcampaign a','*',array('z.adcampaign'=>'a.id','z.type'=>1,'a.member'=>$member->id));
		if(!empty($selected)){
			$member->_error='117';
		}
	}

	function logDelete($member){
		$terminatelog=new TerminateLog();
		$terminatelog->username=$member->username;
		$terminatelog->user_level=$member->level->name;
		$terminatelog->first_name=$member->first_name;
		$terminatelog->last_name=$member->last_name;
		$terminatelog->email1=$member->email1;
		$terminatelog->admin_id=$this->currentuser->id;
		$terminatelog->admin_name=$this->currentuser->username;
		$terminatelog->date=date('Y-m-d H:i:s',time());	
		$this->DB->processObject($terminatelog);
	}

	function deleteAdmin($request) {
		$member=$this->createMember();
		$this->parseRequest($request,$member);
		$this->DB->initObject($member);
		if($member->id==$this->currentuser->id){
			$member->_error='118';
			return $member;
		}
		if($member->level->level_type==2){
			$member->_error='116';
			return $member;
		}
		$this->checkDelete($member);
		if(!empty($member->_error)) return $member;
		$this->deleteRelatedUserInfo($member);
		$this->DB->processObject($member,'delete');
		$this->logDelete($member);
		$newforumhandler=new NewForumHandler();
		$newforumhandler->deleteUser($member);
//		$forumhandler=new ForumHandler();
//		$forumhandler->deleteUser($member);
		return $member;
	}

	function deleteMember($request) {
		$member=$this->createMember();
		$this->parseRequest($request,$member);
		$this->DB->initObject($member);
		if($member->level->level_type==1){
			$member->_error='115';
			return $member;
		}
		$this->checkDelete($member);
		if(!empty($member->_error)) return $member;
		$this->deleteRelatedUserInfo($member);
		$this->DB->processObject($member,'delete');
		$this->logDelete($member);
		$newforumhandler=new NewForumHandler();
		$newforumhandler->deleteUser($member);
//		$forumhandler=new ForumHandler();
//		$forumhandler->deleteUser($member);
		return $member;
	}

	function openAdminProfileAdmin($request){
		$admin=$this->createRegMember();
		$this->parseRequest($request,$admin);
		$this->DB->initObject($admin);
		if(empty($admin->level->id)){
			$admin->_error='1';
			return $admin;
		}
		return $admin;
	}

	function openMemberProfileAdmin($request){
		$member=$this->createRegMember();
		$this->parseRequest($request,$member);
		$tmp=$this->createRegMember();
		$tmp->id=$member->id;
		$this->DB->initObject($tmp);
		if(empty($tmp->level->id)){
			$member->_error='1';
			return $member;
		}
		if($tmp->level->level_type==1){
			$member->_error='98';
			return $member;
		}
		$this->DB->initObject($member);
		return $member;
	}

	function getRightsList($request){
		$public =array(
			'0'=>'NA',
			'2'=>'VR',
			'6'=>'VRP',
			'14'=>'VRP,A',
			'22'=>'VRP,M',
			'30'=>'VRP,A,M',
			'62'=>'VRP,A,M,D',
			'126'=>'VRP,A,M,D,CAT',
			'254'=>'VRP,A,M,D,CAT,C',
			'510'=>'VRP,A,M,D,CAT,C,G'
			);
		return $public ;
	}

	function updateAdminProfileAdmin($request){
		$member=$this->createRegMember();
		$this->parseRequest($request,$member);
		$tmp=$this->createRegMember();
		$tmp->id=$member->id;
		$this->DB->initObject($tmp);
		if($tmp->level->id==1 && $this->currentuser->level->id!=1) {
			$member->_error='79';
			return $member;
		}
		if (!$this->checkImages($member)) return $member;
		//if (!empty($member->passw))$member->passw=md5($member->passw);
		$member->status_set_by_id=$this->Security->currentuser->id;
		$selected=$this->DB->SelectArray("member",'id,username',array('id'=>$member->id));
		if (!empty($selected)) {
			if($selected[0]['username']==$member->username) {
				$this->DB->processObject($member);
			}
			else {
				$selected=$this->DB->SelectArray("member",'id',array('username'=>$member->username));
				if (!empty($selected)) $member->_error='6';
				else $this->DB->processObject($member);
			}
			if(empty($member->_error)) {
				$this->DB->initObject($this->currentuser);
				$newforumhandler=new NewForumHandler();
				$newforumhandler->updateUser($member);
//				$forumhandler=new ForumHandler();
//				$forumhandler->updateUser($member);
			}
		}
		else $member->_error='7';
		return 	$member;
	}

	function updateMemberProfileAdmin($request){
		$member=$this->createRegMember();
		$this->parseRequest($request,$member);
		$tmp=$this->createRegMember();
		$tmp->id=$member->id;
		$this->DB->initObject($tmp);
		if($tmp->level->level_type==1) {
			$member->_error='78';
			return $member;
		}
		if(!empty($member->lelvel->id) && $tmp->level->id!=$member->lelvel->id){
			$member->_error='97';
			return $member;
		}
		if (!$this->checkImages($member)) return $member;
		//if (!empty($member->passw))$member->passw=md5($member->passw);
		$member->status_set_by_id=$this->Security->currentuser->id;
		$selected=$this->DB->SelectArray("member",'id,username',array('id'=>$member->id));
		if (!empty($selected)) {
			if($selected[0]['username']==$member->username) {
				$this->DB->processObject($member);
			}
			else {
				$selected=$this->DB->SelectArray("member",'id',array('username'=>$member->username));
				if (!empty($selected)) $member->_error='6';
				else $this->DB->processObject($member);
			}
			if(empty($member->_error)) {
				$this->DB->initObject($this->currentuser);
				$newforumhandler=new NewForumHandler();
				$newforumhandler->updateUser($member);
//				$forumhandler=new ForumHandler();
//				$forumhandler->updateUser($member);
			}
		}
		else $member->_error='7';
		return 	$member;
	}

	function changeMemberLevel($request) {
		$member=$this->createRegMember();
		$this->parseRequest($request,$member);
		$tmp=$this->createMember();
		$tmp->id=$member->id;
		$this->DB->initObject($tmp);
		if($tmp->level->level_type==1) {
			$member->_error='77';
			return $member;
		}
		if($tmp->level->id==7 && $member->level->id!=7){
			$this->DB->delete('ypproperty',array('member'=>$member->id,'propertytype'=>2));
		}
		if($tmp->level->id==8 && $member->level->id!=8){
			$this->DB->delete('ypproperty',array('member'=>$member->id,'propertytype'=>3));
			$this->DB->delete('bdproperty',array('member'=>$member->id,'propertytype'=>3));
		}
		$this->DB->processObject($member);
		$this->DB->update('upgradelevelorder',array('closed'=>1),array('member'=>$member->id,'tolevel'=>$member->level->id));
		$this->DB->initObject($member);
		return $member;
	}

	function selectLevelsAdmin($request){
		$levels=array();
		if(empty($request['fields'])) $request['fields']='id,name,level_type';
		if(empty($request['sortColumn'])) { $request['sortColumn']='id'; $request['sortType']='asc';}
		if (empty($request['conditions']['level_type'])) $request['conditions']['level_type']='2';
		$request['curPage']=$this->DB->SelectArray(Array('level'),$request['fields'],$request['conditions'],$this->getOrderBy($request));
		if (!empty($request['curPage']))foreach($request['curPage'] as $k=>$v) $levels[$v['id']]=$v['name'];
		return $levels;
	}

	function changeAdminLevel($request) {
		$member=$this->createRegMember();
		$this->parseRequest($request,$member);
		$tmp=$this->createMember();
		$tmp->id=$member->id;
		$this->DB->initObject($tmp);
		if($tmp->level->id==1 and $this->currentuser->level->id!=1) {
			$member->_error='80';
			return $member;
		}
		$this->DB->processObject($member);
		return $member;
	}

	function saveModulesRights($request){
		$selected=$this->DB->SelectArray('level','id,name',array(),'id asc');
		foreach($selected as $k=>$v){
			$level=$this->createLevel();
			$level->id=$v['id'];
			$level->moduleRights->data=$this->getModuleRightsForLevel($request,$v['id']);
			$this->DB->processObject($level);
			/*
			print "<li>obj";printObject($level);
			foreach($level->moduleRights->data as $t=>$n){
				print "<li>data";printObject($n);
			}
			*/
		}
		return array();
	}

	function getModuleRightsForLevel($arr,$levelid){
		$modulerightsarr=array();
		foreach ($arr as $k=>$v){
			$moduleright=new ModuleRights();
			$moduleright->module=$k;
			foreach($v['perms'] as $l=>$m){
				if($l==$levelid) $moduleright->perm=$m;
			}
			$modulerightsarr[]=$moduleright;
		}
		return $modulerightsarr;
	}


	function getModulesRightsAdmin($request) {
		$selected=$this->DB->SelectArray('level','id,name',array(),'id asc');
		foreach($selected as $k=>$v){
			$level=$this->createLevel();
			$level->id=$v['id'];
			$this->DB->initObject($level);
			$levels[$v['id']]=$level;
		}
		$selected=$this->DB->SelectArray('module','id,name',array());
		foreach($selected as $k=>$v){
			if (!in_array($v['id'],$this->notincludemodule)) {
				$modulerights[$v['id']]['name']=$v['name'];
				$modulerights[$v['id']]['perms']=$this->getPermsForModule($v['id'],$levels);
			}
		}
		return $modulerights;
	}



	function getPermsForModule($moduleid,$levels){
		$perms=array();
		foreach($levels as $k=>$v){
			foreach($v->moduleRights->data as $l=>$m) {
				if($m->module->id==$moduleid) $perms[$k]=$m->perm;
			}
		}
		return $perms;
	}
	function getPermissionInfoForModule($moduleid,$levelid){
		$perms=array();
		if (!empty($this->currentuser->level->moduleRights)) {
			foreach ($this->currentuser->level->moduleRights->data as $k=>$v) {
				if ($moduleid == $v->module) {
					return $v->perm;
				}
			}
		}
		return 0;
	}
	



	function checkImages(&$member){
		if(!empty($member->_image_width) && !empty($member->_image_height)) {
			$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'3','paramid'=>'1'));
			if (!empty($selected[0]['value']))$maxwidth=$selected[0]['value'];
			else $maxwidth='';
			$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'3','paramid'=>'2'));
			if (!empty($selected[0]['value']))$maxheight=$selected[0]['value'];
			else $maxheight='';
			if((!empty($maxwidth) && $member->_image_width > $maxwidth)) {
				$member->_error='47';
				return false;
			}
			if(!empty($maxheight) && $member->_image_height > $maxheight){
				$member->_error='48';
				return false;
			}
		}
		if(!empty($member->_image_size)) {
			$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'3','paramid'=>'3'));
			if (!empty($selected[0]['value']))$maxsize=$selected[0]['value'];
			else $maxsize='';
			if ((!empty($maxsize) && $member->_image_size > $maxsize)) {
				$member->_error='50';
				return false;
			}
		}
		return true;
	}

	function rememberPassword($request) {
		$this->member=$this->createMember();
		$this->parseRequest($request,$this->member);
		$selected=$this->DB->SelectArray("member",'id,pass_hint,pass_answ,email1,first_name,last_name',array('username'=>$this->member->username));
		if (empty($selected)) {
			$this->member->_error='1';
		}
		else {
			if(empty($this->member->pass_hint)){
				$this->member->pass_hint=$selected[0]['pass_hint'];
			}
			else {
				if ($this->member->pass_answ!=$selected[0]['pass_answ']) $this->member->_error='8';
				else {
					 $this->member->id=$selected[0]['id'];
					 $this->member->email1=$selected[0]['email1'];
					 $this->member->first_name=$selected[0]['first_name'];
					 $this->member->last_name=$selected[0]['last_name'];
					 //$this->member->passw=substr(md5($this->member->id.$this->member->username.$this->member->id),-8);
					 $tmppassw=$this->member->passw;
					 //$this->member->passw=md5($tmppassw);
					 $this->DB->processObject($this->member);
					 $forumhandler=new NewForumHandler();
					 $forumhandler->updateUser($this->member);
					 $this->member->passw=$tmppassw;
					//printObject($this->member);
				}
			}
		}
		return $this->member;
	}

	function getMemberPreview($request=Array('id'=>0)){
		$keys= array_keys($request);
		if (in_array('username',$keys)) {
			$member=new Member();
			$member->id=$request['id'];
			$this->DB->initObject($member);
			$request['username']=$member->username;
			$request['rating']=$member->rating;
		}
		if ($this->isBuddy($request['id'])) $request['isbuddy']=1;
		else $request['isbuddy']=0;
		return $request;
	}

	function isBuddy($id){
		foreach ($this->currentuser->buddyList->data as $k=>$v) {
			if($v->member->id==$id) {
				return true;
			}
		}
		return false;
	}

	function selectAdministratorsListAdmin($request){
		if(empty($request['fields'])) $request['fields']='m.id,m.username,m.first_name,m.last_name,m.email1,m.day_phone,m.image_type,l.id as level_id,l.name as level_name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='username'; $request['sortType']='asc';}
		$request['conditions']['m.level']='l.id';
		$request['conditions']['level_type']='1';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='10';
		$selected=$this->DB->SelectArray(Array('member m','level l'),'count(*) as qty',$request['conditions'],0,0,0);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('member m','level l'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request));
		return $request;
	}
	
	function getSiteOwner() {
		$selected=$this->DB->SelectArray("member",array('id'),' where siteowner=1',0, 0, 0, array(),'CND_SIMPLE');
		if (!empty($selected)) {
			return $selected[0]['id'];
		} else return null;
	}

	function selectMembersListAdmin($request){
		if(empty($request['fields'])) $request['fields']='m.id,m.username,m.rating,m.date_last_login,m.date_last_activity,m.image_type,m.allow_pms,l.id as level_id,l.name as level_name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='ascii(username)'; $request['sortType']='asc';}
		else if($request['sortColumn']=='username') { $request['sortColumn']='ascii(username)'; $request['sortType']='asc';}
		//$request['conditions']['canceled']=array('='=>0);
		$request['conditions']['activated']=array('='=>1);
		$request['conditions']['m.level']=array('='=>'l.id');
		$request['conditions']['l.level_type']=array('!='=>1);
		if(!empty($request['conditions']['username'])) $request['conditions']['username']=array('like'=>'%'.$request['conditions']['username'].'%');
		if(!empty($request['conditions']['keywords'])) $request['conditions']['keywords']=array('like'=>'%'.$request['conditions']['keywords'].'%');
		if(!empty($request['conditions']['level_name'])){
			$request['conditions']['l.name']=array('='=>$request['conditions']['level_name']);
			unset($request['conditions']['level_name']);
		}
		foreach($request['conditions'] as $k=>$v) $rels[]='and';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='10';
		$selected=$this->DB->SelectArray(Array('member m','level l'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$rels);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('member m','level l'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$rels);
		return $request;
	}

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

	function createLevel(){
		$level = new Level();
		$level->moduleRights = new ObjectsList();
		$moduleRights=new ModuleRights();
		$moduleRights->module=new Module();
		$level->moduleRights->type = $moduleRights;
		return $level;
	}
	
	function getLogHandler() {
		global $Server; 
		$LogHandler = &$Server->getHandler(104);
		return $LogHandler;
	}
	
}
?>