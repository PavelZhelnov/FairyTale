<?php
include_once($MODEL_PATH.'/Modules/Common/Action_Log.class.inc');
include_once($MODEL_PATH.'/CommonConstants.class.inc');

class LogHandler extends Handler {

	function setSearch($request = array()) {
		global $Server;
		foreach($request as $key => $value) $Server->settings['LogSearch'][$key] = $value;
		return array();
	}

	function getSearch($request = array()) {
		global $Server;
		return $Server->settings['LogSearch'];
	}
	function clearSearch($request = array()) {
		global $Server;
		$Server->settings['LogSearch'] = array();
		return $Server->settings['LogSearch'];
	}
	
	function getConditions($request = array(), $search = array()) {
		if (isset($search['action_type']) && validate($search['action_type']))
			$request['conditions']['a.action_type'] = array('='=>$search['action_type']);
		if (isset($search['section']) && validate($search['section']))
			$request['conditions']['a.section'] = array('='=>$search['section']);
		if (isset($search['last_name']) && validate($search['last_name']))
			$request['conditions']['m.last_name'] = array('='=>$search['last_name']);
		if (isset($search['first_name']) && validate($search['first_name']))
			$request['conditions']['m.first_name'] = array('='=>$search['first_name']);
		if (isset($this->Security->currentuser->id))
			$request['conditions']['a.ownerid'] = array('='=>$this->Security->currentuser->id);
		if (isset($search['date_from']) && (validate($search['date_from']))) {
			$request['conditions']['a.action_time'] = array('>='=>$search['date_from']);
		}
		if (isset($search['date_to']) && (validate($search['date_to']))) {
			$request['conditions']['(a.action_time)'] = array('<='=>$search['date_to']);
		}
		return $request;
	}
	
	function selectLogs($request) {		
		$search = $this->getSearch();
		$request = $this->getConditions($request,$search);
		if ($this->Security->currentuser->level->level_type==1) unset($request['conditions']['a.ownerid']);
		if ($this->Security->currentuser->level->level_type>1 ) $request['conditions']['a.ownerid'] = array('='=>$this->Security->currentuser->id);
		$relarr = array();
		if(empty($request['fields'])) $request['fields']='a.id, a.action_time,  a.description, asecl.name as section_name, lal.name as action_name,concat(m.last_name, " ", m.first_name) as owner,
			(CASE lal.name WHEN "save" THEN concat(asec.url,a.description) WHEN "delete" THEN description ELSE 0 END) as url,
			(CASE lal.name WHEN "log in" THEN a.description WHEN "delete" THEN a.description ELSE "" END) as description ';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 50;
		if(empty($request['sortColumn'])) { $request['sortColumn']='pubdate'; $request['sortType']='desc';}
		//if(empty($request['conditions']['ll.language'])) $request['conditions']['ll.language']=array('='=>$request['langid']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$request['tables'] = Array('action_log a
			left join log_action la on la.id = a.action_type
			left join log_action_lang lal on lal.ownerid=la.id
			left join action_log_section asec on asec.id = a.section
			left join action_log_section_lang asecl on asecl.ownerid = asec.id
			left join member m on m.id = a.ownerid');
		$selected=$this->DB->SelectArray($request['tables'],'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray($request['tables'],$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),array(),array(),'CND_COMPLEX',$relarr);
		return $request;
	}
	
	function add($request) {
		$al = new Action_Log();
		$this->parseRequest($request,$al);
		if ($al->action_type == CommonConstants::LOG_ACTION_VIEW) return; //TODO
		$sgs = $this->getGlobalSystemSettingsHandler()->getGlobalSystemSettings();
		$al->ownerid = (isset($this->Security->currentuser->id)?$this->Security->currentuser->id:$sgs->fake_member);
		$al->action_time = date('Y-m-d H:i:s',time() - CommonConstants::TIME_MILLISECONDS_OFFSET);
		if (empty($al->section)) $al->section = CommonConstants::LOG_ACTION_SECTION_COMMON;
		$this->DB->processObject($al);
		return $al;
	}
	
	function addAction($action_type, $section, $description="") {
		return $this->add(array('action_type'=>$action_type, 'section'=>$section, 'description'=>$description));
	}
	
	/**
	 * Security purpose; Check if some action has been processed often for the period
	 *
	 * @param unknown_type $request
	 * @return unknown
	 */
	function checkLastActionTimeDiff($request) {
		$selected = $this->DB->SelectAny('select * from action_log where action_type='.$request['action_type'].' order by action_time desc limit 1');
		if (!empty($selected)) {
			$diff_ts = $this->formatDateToTimeStampYYYYMMDDhhmmss($selected[0]['action_time']);
			$time = time();
			return ($time - $diff_ts);			
		} else return 0;
	}
	
}

?>