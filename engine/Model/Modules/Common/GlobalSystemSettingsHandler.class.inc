<?php
include_once($MODEL_PATH.'/Modules/Common/Global_System_Settings.class.inc');

class GlobalSystemSettingsHandler extends Handler {
	
	private $gss;
	
	function GlobalSystemSettingsHandler($calledbyson=true){
		$this->Handler($calledbyson);
	}	
	
	
	
	function selectGlobalSystemSettings($request = array()) {
		$request['fields'] = "s.id, s.setting_name";
		$request['curPage'] = $this->DB->SelectArray(Array('global_system_settings s'),$request['fields'],array(),0,0,0,array(),'CND_COMPLEX',array());
		return $request;
	}
	
	/**
	 * Gets the settings depending on department of logged user
	 * @param $request
	 * @return unknown_type
	 */
	function getGlobalSystemSettings($request=array('id'=>1)) {
    	$selected = $this->DB->SelectArray(Array('global_system_settings s'),"s.id",array('id'=>array('='=>$request['id'])),0,0,0,array(),'CND_COMPLEX',array());
		$this->gss = $this->createGlobalSystemSettings();
		$this->parseRequest(array('id'=>$selected[0]['id']),$this->gss);
		$this->DB->initObject($this->gss);
		return $this->gss;
	}
	
	function openGlobalSystemSettings($request=array('id'=>1)) {
		$this->gss = $this->createGlobalSystemSettings();
		$this->parseRequest($request,$this->gss);
		$this->DB->initObject($this->gss);
		return $this->gss;
	}
	

	function saveGlobalSystemSettings($request) {
		if (isset($request['id']) && validate($request['id'])) {
			$this->gss->id=$request['id'];
			$this->DB->initObject($this->gss);
		}
		$this->parseRequest($request,$this->gss);
		//$this->gss->last_modified_date = date('Y-m-d H:i:s',time()-CommonConstants::TIME_MILLISECONDS_OFFSET);
		//$this->gss->last_modified_member= clone($this->Security->currentuser);
		$this->DB->processObject($this->gss);
		
		return $this->gss;
	}
	
	function createGlobalSystemSettings() {
		$gss = new Global_System_Settings();
		return $gss;
	}
	function createMember(){
		$member =  new Member();
		return $member;
	}
	function selectMembers($request=array()) {
		$pr = $this->DB->SelectGuide(array('member c'),array('c.id, CONCAT(c.last_name," - ",c.first_name) as name'),array());
		return $pr;
	}
	
}
?>