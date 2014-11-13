<?php

include_once($MODEL_PATH.'/Modules/Common/News.class.inc');
include_once($MODEL_PATH.'/Modules/Common/News_Lang.class.inc');

class NewsHandler extends Handler {
	
	public $currentuser;
	public $categorylist;
	public $categorylistid;

	
	function NewsHandler($calledbyson=true){
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
		if(empty($request['fields'])) $request['fields']='nw.name as newsname, nw.id as newsid, DATE_FORMAT(nw.pubdate,\'%d/%m/%Y\') as publicatedate, nw.pubdate, nwl.ownerid as newsowner, nwl.language, nwl.description as ndescription, nwl.header as nheader';
		if(empty($request['conditions']['nwl.language'])) $request['conditions']['nwl.language']=$request['langid'];
		if(empty($request['conditions']['nw.id'])) $request['conditions']['nw.id']=$request['id'];
		$request['curPage']=$this->DB->SelectArray(Array('news as nw left join news_lang as nwl on nw.id=nwl.ownerid'),$request['fields'],$request['conditions']);
		if(empty($request['curPage'])) {
			$request->_error='4'; //no such news
			return $request;
		}
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

	function createNews() {
		$news = new News();
		$news->name_langs=new ObjectsList();
		$news->name_langs->type=new News_Lang();
		return $news;
	}
}
?>