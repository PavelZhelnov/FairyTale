<?php

include_once($MODEL_PATH.'/Modules/Common/ModuleSetting.class.inc');	
include_once($MODEL_PATH.'/ObjectsList.class.inc');

class AdminModuleHandler extends Handler {

	function AdminModuleHandler(){
		$this->Handler(true);
	}
	
	
	function setSearch($request = array()) {
		global $Server;
		$Server->settings['ModuleAdminSearch'] = array();
		foreach($request as $key => $value) $Server->settings['ModuleAdminSearch'][$key] = $value;
		return array();
	}

	function getSearch($request = array()) {
		global $Server;
		return $Server->settings['ModuleAdminSearch'];
	}

	function getConditions($request = array(), $search = array()) {
		if (isset($search['var']) && validate($search['var']))
			$request['conditions']['ci.var'] = $search['var'];

		if (!empty($search['module'])) {
			foreach ($search['module'] as $k=>$v) {
				if (validate($v))
					$request['conditions']['ci.ownerid'] = $v;
			}
		}

		return $request;
	}
	
	function selectModules($request) {
		if(empty($request['fields'])) $request['fields']='m.id, m.name, m.path, m.preview_name, ml.name as modulename,count(ms.id) as msid';
		if(empty($request['sortColumn'])) { $request['sortColumn']='m.id asc';}
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='100';
		$request['conditions']['ml.language']=$request['lang'];
		$selected=$this->DB->SelectArray('module as m left join module_lang as ml on m.id=ml.ownerid left join modulesetting as ms on ms.ownerid = m.id','count(*) as qty',$request['conditions'],'','',' m.id having count(ms.id)>0 ');
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('module as m left join module_lang as ml on m.id=ml.ownerid left join modulesetting as ms on ms.ownerid = m.id'),$request['fields'],$request['conditions'],'',$this->getLimit($request),' m.id having count(ms.id)>0 ');
		return $request;

	}
	
	function saveModuleItem($request){
		$item=$this->createModuleSetting();
		$this->parseRequest($request,$item);
		$this->DB->processObject($item);
		return $item;
	}


	function openModuleItem($request){
		$item=$this->createModuleSetting();
		$this->parseRequest($request,$item);
		$this->DB->initObject($item);
		return $item;
	}

	function selectModuleItems($request){
		$search = $this->getSearch();
		$request = $this->getConditions($request,$search);
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 100;
		if(empty($request['fields'])) $request['fields']='ci.id,ci.ownerid,ci.name, ci.value,m.name as module_name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='value asc';}
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		if(!empty($request['curModule']) && $request['curModule']!='') $request['conditions']['m.id'] = $request['curModule'];
		$request['conditions']['m.id']='ci.ownerid';
		$selected=$this->DB->SelectArray('modulesetting ci, module m','count(*) as qty',$request['conditions']);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('modulesetting ci, module m'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request));
		return $request;
	}
	
	function selectModules2($request){
		$modules=array();
		if(empty($request['fields'])) $request['fields']='id,name';
		if(empty($request['sortColumn'])) { $request['sortColumn']='id'; $request['sortType']='asc';}
		$request['curPage']=$this->DB->SelectArray(Array('module'),$request['fields']);
		if (!empty($request['curPage']))foreach($request['curPage'] as $k=>$v) $modules[$v['id']]=$v['name'];
		return $modules;
	}


	function createModuleSetting(){
		$item=new ModuleSetting();
		return $item;		
	}




	
}



?>