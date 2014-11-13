<?php

include_once($MODEL_PATH.'/Modules/Common/User.class.inc');
include_once($MODEL_PATH.'/Modules/Common/Subscribers.class.inc');

class ThingsHandler extends Handler {
	
	public $currentuser;
	public $categorylist;
	public $categorylistid;

	
	function ThingsHandler($calledbyson=true){
		$this->Handler($calledbyson);
		$this->currentuser = new User();
	}

	function getAdminEmail($request){
		$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'1','paramid'=>'1'));	
		if(!empty($selected)) $request['adminemail']=$selected[0]['value'];
		return $request;
	}
	
	function getEmailForVacancy($request) {
		$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'1','paramid'=>'1'));	
		if(!empty($selected)) $request['emailto']=array($selected[0]['value']);
		return $request;
	}

	function getEmail($request){
		$selected=$this->DB->SelectArray('modulesetting',array('value'),array('ownerid'=>'1','paramid'=>'2'));	
		if(!empty($selected)) $request['emailto']=array($selected[0]['value']);
		return $request;
	}

	function sendContact($request) {
		//$this->addSubscriber($request);
		$request = $this->getAdminEmail($request);
		return $request;
	}
	
	function selectNewsCategories($request) {
		//this for view all categories and check for the current usver'
		$this->categorylistid=0;
		$this->categorylist=array();
		$request['id'] = (isset($request['id'])?$request['id']:0);
		$array=$this->selectCategoriesTree($request,0,1);
		$request['categoryTree']=$array;
		return $request;		
	}

	
	function selectInformation($request)
	{		
		if (isset($request['browsePage']))	{
			$browsePage=$request['browsePage'];
			$selected=$this->DB->SelectArray('infotext as it','it.name',array('it.name'=>$request['browsePage']));
		}
		if (!isset($request['browsePage']) || (empty($selected))) {
			$browsePage="Home";
		}
		if(empty($request['fields'])) $request['fields']='it.name as textname, it.id as textid, itl.ownerid as textowner, itl.language, itl.value as tvalue';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='9';
		if(empty($request['conditions']['ih.id'])) 
		$request['conditions']['it.name']=array('='=>$browsePage);
		if(empty($request['conditions']['itl.language'])) $request['conditions']['itl.language']=array('='=>$request['langid']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$request['curPage']=$this->DB->SelectArray(Array('infotext as it left join infotext_lang as itl on it.id=itl.ownerid'),$request['fields'],$request['conditions'],0,$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		$patt = array ("/(\{picPath:static\})/","/(\{homePath:static\})/");
		$repl = array ($request['imagePath'], $request['homePath']);
		$request['curPage'][0]['tvalue']=preg_replace($patt, $repl, $request['curPage'][0]['tvalue']);	    
		return $request;
	}

	function selectAgents($request) {
		if(empty($request['fields'])) $request['fields']='b.first_name, lv.name as level, b.image_type, b.company, b.address, b.phone, b.fax, b.cell, b.last_name, b.id, FROM_UNIXTIME(b.date_registered,\'%m/%d/%y\') as date, b.email, b.login, b.activated';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		$request['conditions']['b.level'] = array ('='=>'3');
		$request['pageRecordsQty'] = 10;
		if (!empty($request['conditions']))
			foreach($request['conditions'] as $k=>$v) $relarr[]='and'; 
			else $relarr=array();
		$selected=$this->DB->SelectArray(Array('member as b left join level as lv on lv.id=b.level '),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('member as b left join level as lv on lv.id=b.level '),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),0,array(),'CND_COMPLEX',$relarr);
		return $request;
	}

	// ******************MESSAGE HEADER TEXT*****************	
	
	function selectMessageText($request) {
		if (!isset($request['id'])) {$request['id']=0;}
		if(empty($request['fields'])) $request['fields']='m.id, ml.ownerid, ml.language, ml.text as text';
		if(empty($request['conditions']['ml.language'])) $request['conditions']['ml.language']=$request['langid'];
		$request['curPage']=$this->DB->SelectArray(Array('message as m left join message_lang as ml on m.id=ml.ownerid'),$request['fields'],$request['conditions']);
		return $request;
	}
	
	// ******************************************************
	
	function createUser() {
		$user = new User();
		return $user;
	}

	function MakeHash()	{
		return md5(time());
	}

	function createSubscriber() {
		$subscr = new Subscribers();
		return $subscr;
	}

}
?>