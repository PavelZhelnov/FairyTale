<?php

include_once($MODEL_PATH.'/RootEntity.class.inc');
include_once($MODEL_PATH.'/Modules/Common/Module.class.inc'); 
include_once($MODEL_PATH.'/Modules/Common/ModuleSetting.class.inc'); 

class Handler{
	public $DB;
	public $Security;

	function Handler($calledbyson=true){
		global $DatabaseBroker, $Server;
		$this->DB = &$DatabaseBroker;
		if($calledbyson) $this->Security = &$Server->getHandler(2); 
	}

	function parseRequest($request,&$obj) {
		if (!empty($request['gr_id'])) $request['id'] = $request['gr_id'];
		$property_values = get_object_vars($obj);
		$property_names= array_keys($property_values);
		foreach( $request as $key=>$value ){			
			if( in_array($key,$property_names)){
				$this->parseObject( $key,$property_values[$key],$value,$obj);
			}
		}
		return $obj;
	}

	function parseObject($property_name,$property_value,$request_value,&$obj) {
		$type = gettype($property_value);
		switch($type){
			case 'object':
				if(strtolower(get_class($property_value))=='objectslist') $this->parseObjectsList($request_value,$obj->{$property_name});
				else $this->parseRequest($request_value,$obj->{$property_name});
			break;
			default: $obj->{$property_name} = $request_value; break;
		}
	}

	function parseObjectsList($request_value,&$obj) {
		
		foreach($request_value as $index=>$value ) {
			$copy_obj = new $obj->type;
			$obj->data[] = $this->parseRequest($value,$copy_obj);
		}
	}

	function cleanError(&$object) {
		$object->_error = '';
	}
	
	function cleanDialog(&$object) {
		$object->_dialog = 0;
	}

	function getLimit (&$request) {
		$limit='';
		if (empty($request['curPageNumber'])) {
        		$request['curPageNumber']='1';
			$limit=Array('0',$request['pageRecordsQty']);
		}
	    	else {
       			$offset = $request['pageRecordsQty']*($request['curPageNumber']-1);
    			$limit = Array($offset,$request['pageRecordsQty']);
    		}
        	return $limit;
  	}


    	function getOrderBy ($request) {
    		$orderby='';
		if(empty($request['sortColumn'])) $request['sortColumn']='';
		if(empty($request['sortType'])) $request['sortType']='';
    		if (empty($request['sortColumn'])) {
			$orderby='id';
		}
	    	else {
       			$orderby = $request['sortColumn']." ".$request['sortType'];
    		}
        	return $orderby;
  	}


	function countPropertysQty($catergory_id,$propertytable,$categorytable) {
		$catlist[]=$catergory_id;
		$catlist=$this->getSubCategoriesList($catergory_id,$categorytable,$catlist);
		$selected=$this->DB->SelectArray(Array($propertytable),'count(*) as qty',array('category'=>array('in'=>$catlist)),0,0,0,array(),'CND_COMPLEX',array());		
		return $selected[0]['qty'];
	}

	function getSubCategoriesList($catergory_id,$categorytable,$catidarray=array()){
		
		
		$selected=$this->DB->SelectArray(Array($categorytable),'id',Array('parent_category'=>$catergory_id));
		if(!empty($selected)){
			foreach($selected as $k=>$v){
				$catidarray[]=$v['id'];
				$catidarray=array_merge($catidarray,$this->getSubCategoriesList($v['id'],$categorytable));
			}
			
		}
		return $catidarray;
		
	}


	function makeCatTree($ar,$par=0) {
		$tree='';
		foreach($ar as $k=>$v){
			if ($v['parent_category']==$par) {
				$tree[$v['id']]['id']=$v['id'];
				$tree[$v['id']]['name']=$v['name'];
				$tree[$v['id']]['subcat']=$this->makeCatTree($ar,$v['id']);
			}
		}
		return $tree;
	}



	function getGrangParentCategory($catid){
		$gpid=0;
		$catTree=$this->selectCategoriesTree();
	
		foreach ($catTree as $k=>$v){
			if($k==$catid) {
				$gpid=$k;
				break;
			}
			else if ($this->walkForCatTree($catTree[$k],$catid)){
				$gpid=$k;
				break;
			}	
		}
		return $gpid;
		
	}


	function walkForCatTree($catTree,$catid){
		if(is_array($catTree['subcat'])) {
			foreach($catTree['subcat'] as $k=>$v){
				if($k==$catid)	return true;
				else if($this->walkForCatTree($catTree['subcat'][$k],$catid)) return true;
			}
		}
		return false;
	}

	function getSettings($request=array()) {
		if(!empty($request['moduleid'])) {
			$module = new Module();
			$module->settings = new ObjectsList();
			$module->settings->type = new ModuleSetting();
			$module->id = $request['moduleid'];
			$this->DB->initObject($module);
			return $module;
		}
	} 
	
	function justStub($request){
		return $request;
	}
	
	function formatDateToTimeStamp($field) {
		if (empty($field)) return "";
		if (strlen($field)<12) {$field.=" 00:00:00";}
		$hour=substr($field, 11, 2);
		$minute=substr($field, 14, 2);
		$sec=substr($field, 17, 2);
		$day=substr($field, 3, 2);
		$month=substr($field, 0, 2);
		$year=substr($field, 6, 4);
		$am = substr($field, 20, 2);
		if ($am=='PM') $hour = $hour+12;
		//echo "time=".$field."  --".$hour.":".$minute.":".$sec.':'.$am."/".$this->formatTimestampToDate(gmmktime($hour, $minute, $sec, $month, $day, $year))." ts:".gmmktime($hour, $minute, $sec, $month, $day, $year)."       ||||";
		//echo $hour.' '.$minute.' '.$sec.' '.$month.' '.$day.' '.$year;		
		return gmmktime($hour, $minute, $sec, $month, $day, $year);
		
	}
	function formatDateToTimeStampYYYYMMDDhhmmss($field) {
		if (empty($field)) return "";
		$hour=substr($field, 11, 2);
		$minute=substr($field, 14, 2);
		$sec=substr($field, 17, 2);
		$day=substr($field, 8, 2);
		$month=substr($field, 5, 2);
		$year=substr($field, 0, 4);
		$am = substr($field, 20, 2);
		if ($am=='PM') $hour = $hour+12;
		return gmmktime($hour, $minute, $sec, $month, $day, $year);
		
	}
	
	function formatTimestampToDate($field, $format="Y-m-d h:i:s A") {
		if ( ($field!="-1") && ($field!=""))
			return gmdate($format, $field);
		else return '';
			
	}
	
	function getContactIdByLogin($request) {
		$id = $this->DB->SelectSingle(array('contact'),'id',array('login' => $request['login']));
		return $id;
	}

	function replaceHttpSymbols($request) {
		return rawurldecode ($request);
	}
	
	function halt($message) {
		echo "There were some functionality error. Halting with Message:".$message.'. Please, send this message to programmer (willy2005@gmail.com) ';
		die();
	}
	
	function getLogHandler() {
		global $Server; 
		$LogHandler = &$Server->getHandler(104);
		return $LogHandler;
	}
	function getSecurityHandler() {
		global $Server; 
		$sHandler = &$Server->getHandler(2);
		return $sHandler;
	}
	
	function getGlobalSystemSettingsHandler() {
		global $Server;
		$GlobalSystemSettingsHandler = &$Server->getHandler(103);
		return $GlobalSystemSettingsHandler;
	}

	function MakeHash()	{
		return md5(time().rand(0, 10000));
	}	
}
?>