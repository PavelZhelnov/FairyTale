<?php

include_once($MODEL_PATH.'/Modules/LanguageAccessibility/ContentItem.class.inc');	
include_once($MODEL_PATH.'/Modules/LanguageAccessibility/ContentItem_Lang.class.inc');	
include_once($MODEL_PATH.'/Modules/LanguageAccessibility/ContentType.class.inc');	
include_once($MODEL_PATH.'/ObjectsList.class.inc');

class LangHandler extends Handler {

	function LangHandler(){
		$this->Handler(true);
	}
	
	
	function setSearch($request = array()) {
		global $Server;
		$Server->settings['LanguageAdminSearch'] = array();
		foreach($request as $key => $value) $Server->settings['LanguageAdminSearch'][$key] = $value;
		return array();
	}

	function getSearch($request = array()) {
		global $Server;
		return $Server->settings['LanguageAdminSearch'];
	}

	function getConditions($request = array(), $search = array()) {
		if (isset($search['var']) && validate($search['var']))
			$request['conditions']['ci.var'] = $search['var'];

		if (!empty($search['type'])) {
			foreach ($search['type'] as $k=>$v) {
				if (validate($v))
					$request['conditions']['ci.contenttype'] = $v;
			}
		}
		if (!empty($search['module'])) {
			foreach ($search['module'] as $k=>$v) {
				if (validate($v))
					$request['conditions']['ci.module'] = $v;
			}
		}

		return $request;
	}
	
	function saveContentItemAdmin($request){
		$contentitem=$this->createContentItem();
		$this->parseRequest($request,$contentitem);
		$this->DB->processObject($contentitem);
		return $contentitem;
	}


	function openContentItemAdmin($request){
		$contentitem=$this->createContentItem();
		$this->parseRequest($request,$contentitem);
		$this->DB->initObject($contentitem);
		return $contentitem;
	}

	function selectContentItemsAdmin($request){
		
		$search = $this->getSearch();
		$request = $this->getConditions($request,$search);
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 100;

		if(empty($request['fields'])) $request['fields']='ci.id,ci.module,ci.contenttype,ci.var,cit.name as contenttype_name,m.name as module_name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='module asc, contenttype_name asc';}
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(!empty($request['curModule']) && $request['curModule']!='') $request['conditions']['m.id'] = $request['curModule'];
		$request['conditions']['m.id']='ci.module';
		$request['conditions']['cit.id']='ci.contenttype';
		$selected=$this->DB->SelectArray('contentitem ci,contenttype cit, module m','count(*) as qty',$request['conditions']);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('contentitem ci,contenttype cit, module m'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request));		
		return $request;
	}
	


	function selectContentType($request){
		$contenttypes=array();
		if(empty($request['fields'])) $request['fields']='id,name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='id'; $request['sortType']='asc';}
		$request['curPage']=$this->DB->SelectArray(Array('contenttype'),$request['fields']);
		if (!empty($request['curPage']))foreach($request['curPage'] as $k=>$v) $contenttypes[$v['id']]=$v['name'];
		return $contenttypes;
	}

	function selectContentModules($request){
		$modules=array();
		if(empty($request['fields'])) $request['fields']='id,name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='id'; $request['sortType']='asc';}
		$request['curPage']=$this->DB->SelectArray(Array('module'),$request['fields']);
		if (!empty($request['curPage']))foreach($request['curPage'] as $k=>$v) $modules[$v['id']]=$v['name'];
		return $modules;
	}


	function createContentItem(){
		$contentitem=new ContentItem();
		return $contentitem;
		
	}

}
?>