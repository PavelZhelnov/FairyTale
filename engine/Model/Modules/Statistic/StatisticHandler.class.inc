<?php

include_once($MODEL_PATH.'/Modules/Statistic/Statistic.class.inc');

include_once($MODEL_PATH.'/Security/Member.class.inc');

class StatisticHandler extends Handler {
	

	function StatisticHandler($calledbyson=true){
		$this->Handler($calledbyson);
	}

	function getStatusAdmin($request) {
		
		$request['conditions'] = array('0'=>array('='=>'0'));$relarr=array();
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected['docs']=$this->DB->SelectArray(Array('document as d'),' "Documents" as colname, count(d.id) as qty ',$request['conditions'],0,0,' colname ',array(),'CND_COMPLEX',$relarr);

		$request['conditions'] = array('0'=>array('='=>'0'));$relarr=array();
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected['pages']=$this->DB->SelectArray(Array('infotext as d'),' "Pages" as colname, count(d.id) as qty ',$request['conditions'],0,0,' colname ',array(),'CND_COMPLEX',$relarr);

		$request['conditions'] = array('0'=>array('='=>'0'));$relarr=array();
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected['menus']=$this->DB->SelectArray(Array('menuitem as d'),' "Menus" as colname, count(d.id) as qty ',$request['conditions'],0,0,' colname ',array(),'CND_COMPLEX',$relarr);
		
		return $selected;
	}
	
	function addEvent($request = array()) {
		$statistic = $this->createStatistic();
		$this->parseRequest($request,$statistic);
		$statistic->ipaddress = ip2long($statistic->ipaddress);
		$this->DB->processObject($statistic);
		return $statistic;
	}
	
	function getEventsBrief($request = array()) {
		$relarr = array();
		$group=0;
		$request['conditions']['s.module'] = array('='=>isset($request['module'])?$request['module']:0);
		if (isset($request['entity'])) {$request['conditions']['s.entity'] = array('='=>$request['entity']);}
		if (isset($request['st_type'])) $request['conditions']['s.st_type'] = array('='=>$request['st_type']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$request['curPage']=$this->DB->SelectArray(Array('statistic as s'),' 1 as st_type, count(*) as qty ',$request['conditions'],0,0,$group,array(),'CND_COMPLEX',$relarr);
		return $request['curPage'];
	}
	
	function getEventsByDate($request = array()) {
		$relarr = array();
		$group=0;
		$request['conditions']['s.module'] = array('='=>isset($request['module'])?$request['module']:0);
		if (isset($request['entity'])) {$request['conditions']['s.entity'] = array('='=>$request['entity']); $group = 'entity';}
		if (isset($request['st_type'])) $request['conditions']['s.st_type'] = array('='=>$request['st_type']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$request['curPage']=$this->DB->SelectArray(Array('statistic as s'),' 1 as st_type, count(*) as qty ',$request['conditions'],0,0,$group,array(),'CND_COMPLEX',$relarr);
		return $request['curPage'];
	}
	
	function getEventsWhole($request = array()) {
		$relarr = array();
		$group=0;
		$request['conditions']['s.module'] = array('='=>isset($request['module'])?$request['module']:0);
		if (isset($request['entity'])) {$request['conditions']['s.entity'] = array('='=>$request['entity']); $order = 'act_date';}
		if (isset($request['st_type'])) $request['conditions']['s.st_type'] = array('='=>$request['st_type']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$request['curPage']=$this->DB->SelectArray(Array('statistic as s'),'st_type, ipaddress, FROM_UNIXTIME(act_date,\'%m/%d/%y %h:%m:%s\') as act_date ',$request['conditions'],$order,0,$group,array(),'CND_COMPLEX',$relarr);
		return $request['curPage'];
	}	
	
	function createStatistic() {
		$statistic = new Statistic();
		return $statistic;
	}
	
	// ******************************************************
	
}
?>