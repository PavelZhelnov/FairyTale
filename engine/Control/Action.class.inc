<?php

class Action extends RootRegistry {

	public $ModuleID = 1;
	public $SectionID = 1;
	public $Handler;	/* ссылка на $Server->Model[ModuleID] */
	public $Security;	/* ссылка на SecurityHandler */
	public $Server;

	/* Navigation Bar */
	public $navbar = array(); /* Nav Bar Text*/
	public $pager = array(); /* Nav Bar Pager*/
	public $next = ''; /* Next Page */
	public $prev = ''; /* Previous Page */
	public $first = ''; /* First Page */
	public $last = ''; /* Last Page */

	public $Pages = array(
		'Task' => array(
			'scheme' => 'default',/* имя Scheme текущей страницы */
			'forward_scheme' => 'default'),/* имя Scheme для страницы возврата */
			'forward_url' => '',/* путь для проброса */
			'handler_error' => '', /* ошибка из хендлера для перенаправления страницы */
	);
	public $count = 0;	/* счётчик обращений к финальным страницам */

	public $PreparedTemplates = array();	/* массив препарсеных контентных переменных,
										индексированных по id Handlerов и подзадачам */
	public $Tasks = array();	/* массив соответствий событий задач методам соответствующего
							Handlerа c правами и редиректами */
	public $Errors = array();	/* массив ошибок для текущей задачи */

	public $SubmitControl = array(	 /* массив меток для защиты от множественного сабмита */
		'Task' => array('time' => 0,'uni' => 0),
	);

	function Action($name='Action') {
		global $REGISTRY,$MailBroker;
		$this->RootRegistry($name);
		$this->Tasks = &$this->Properties['Tasks'];
		$this->ImagePath = $REGISTRY['Core']['ImagePath'];
		$this->ImageWPath = $REGISTRY['Core']['ImageWPath'];
		$this->MailBroker = &$MailBroker;
	}

	function Navigator($self,$per_page = '10', $num_rows = '0', $cur_page = '0', $sort = '',&$object) {
		$this->navbar = array();
		$this->pager = array();
		$this->next = '';
		$this->prev = '';
		$this->first = '';
		$this->last = '';
		switch($num_rows > 0) {
			case 'true':
				$page_num = $cur_page + 1;
				$total = ceil($num_rows/$per_page);
				if(validate($total)) {
					$this->navbar = array(
						sprintf($object->globalLangContent['header']['navbar'],$num_rows),
						sprintf($object->globalLangContent['header']['navbar2'],$page_num,$total,$per_page),
					);
					$prevpage = $cur_page-1;
					$nextpage = $cur_page+1;
					if($page_num != 1) $this->prev = makeLink($self.'/'.$prevpage.(validate($sort)? '/'.$sort : ''),makeImage($this->ImagePath.'/arrows/previous.gif',$this->ImageWPath.'/arrows/previous.gif',$object->globalLangContent['header']['prev']));
					if($total > 1) {
						$this->first = makeLink($self.'/0'.(validate($sort)? '/'.$sort : ''),$object->globalLangContent['header']['first'],array(),'','class="pager"');
						$limit = substr($cur_page,-1) == 9? $cur_page + 10 : substr($cur_page,0,(strlen($cur_page)-1)) . 9;
						for($counter = $limit - 10; $counter <= $limit; $counter++)
							if($counter <= $total - 1 && ($counter + 1)>0)
								$this->pager[] = $cur_page==$counter? '<span class="curpage">'.($counter + 1).'</span>' : makeLink($self.'/'.$counter.(validate($sort)? '/'.$sort : ''),($counter + 1),array(),'','class="pager"');
						$this->last = makeLink($self.'/'.($total-1).(validate($sort)? '/'.$sort : ''),$object->globalLangContent['header']['last'],array(),'','class="pager"');
					}
					if($page_num != $total)
						$this->next = makeLink($self.'/'.$nextpage.(validate($sort)? '/'.$sort : ''),makeImage($this->ImagePath.'/arrows/next.gif',$this->ImageWPath.'/arrows/next.gif',$object->globalLangContent['header']['next']),array(),'','class="pager"');
				}
			break;
			case 'false': break;
		}
	}

	function isAuthorize() {
		$perm = getAdminPerm();
		if(empty($perm)) return TRUE;
		$currentuser = $this->Handler->getCurrentUser(array());
		return !empty($currentuser->id)? 1 : 0;
	}

	function setScheme($Task) {
		if($this->Pages[$Task]['scheme']=='finish' || $this->Pages[$Task]['scheme']=='finish_delete' || $this->Pages[$Task]['scheme']=='finish_save')
			switch($this->count) {
				case '1':
					$this->setPage($Task,$this->Pages[$Task]['forward_scheme']);
					$this->count = 0;
				break;
				case '0': $this->count = 1; break;
			}
		return $this->Pages[$Task]['scheme'];
	}

	function setPage($Task,$scheme = false,$forward_scheme = false) {
		if($scheme) $this->Pages[$Task]['scheme'] = $scheme;
		if($forward_scheme) $this->Pages[$Task]['forward_scheme'] = $forward_scheme;
		return TRUE;
	}
	function setError($Task, $err) {
		if($err)
			$this->Pages[$Task]['handler_error'] = $err;
		return true;
	}
	function getError($Task) {
		if(!empty($this->Pages[$Task]['handler_error']))
			return $this->Pages[$Task]['handler_error'];
		return false;
	}
	function clearError($Task) {
		$this->Pages[$Task]['handler_error'] = null;
	}
/*	function authorize($task,$request,&$object) {
		$return = $this->Handler->authorizeMember($request);
		$object->PreparedTemplates = $this->VisualContent($return,$task,'auth');
		return !empty($return->_error)? FALSE : TRUE;
	}*/

	function authorize($task,$request,&$object) {
		$return = $this->Security->authorizeMember($request);
		$object->PreparedTemplates = $this->VisualContent($return,$task,'auth');
		if(!empty($return->_error))
			return false;
		if(isset($request['signedin']) && $request['signedin'] == '1'){
			return $this->set_Cookie($this->Security->getCookieKeys());
		}
		return true;
	}

	function ssoAuthorize($task,$request,&$object) {
		$return = $this->Security->authorizeMemberSSO($request);
		/*$object->PreparedTemplates = $this->VisualContent($return,$task,'auth');
		if(!empty($return->_error))
			return false;
		if(isset($request['signedin']) && $request['signedin'] == '1'){
			return $this->set_Cookie($this->Security->getCookieKeys());
		}
		return true;*/
	}

	function ssoAuthorizeReturn($task,$request,&$object) {
		$return = $this->Security->authorizeMemberSSOReturn($request);
		$object->PreparedTemplates = $this->VisualContent($return,$task,'auth');
		if(!empty($return->_error))
			return false;
		if(isset($request['signedin']) && $request['signedin'] == '1'){
			return $this->set_Cookie($this->Security->getCookieKeys());
		}
		return true;
		
	} 
	
	
	////////////////moe////////////////////
	function put_NewPswd($task,$request,&$object) {
		$return = $this->Security->putNewPswd($request);
		$object->PreparedTemplates = $this->VisualContent($return,$task,'new_pswd');
		return $return;
	} 
	function Update_Pswd($task,$request,&$object) {
		
		$return = $this->Security->UpdatePswd($request);
		$object->PreparedTemplates = $this->VisualContent($request,$task,'new_pswd');
		
		return $object->PreparedTemplates;
	} 
	function is_User($request) {
		
		$return = $this->Security->isUser($request);
		return $return;
	} 
	function check_User($id) {
		
		$return = $this->Security->checkUser($id);
		return $return;
	} 
	////////////////////////////////////////////
	function logoff($task,$request,&$object) {
		$return = $this->Security->logoffMember($request);
		$object->PreparedTemplates = $this->VisualContent($return,$task,'auth');
		setCookie("dkey", '',time()-360000, '/');
		setCookie("skey", '',time()-360000, '/');
		return !empty($return->_error)? FALSE : TRUE;
	} 

	function checkFlood() {
		
	}

	function set_Cookie($request) {
		if(empty($request['dkey']) || empty($request['skey']))
			return false;
		$dkey = $request['dkey'];
		$skey = $request['skey'];
		setcookie("dkey",$dkey,time()+86400*365,"/");
		setcookie("skey",$skey,time()+86400*365,"/");
		return TRUE;
	}
 
	function clearTemplate($task,$event) {
		$this->PreparedTemplates[$task][$event] = array();
		return true;
	}

	function getTemplate($task,$event) {
		return !empty($this->PreparedTemplates[$task][$event])? $this->PreparedTemplates[$task][$event] : array();
	}

	function VisualContent(&$Object,$task,$event) {
		$this->PreparedTemplates[$task][$event] = $this->_parseContent($Object);
		return $this->PreparedTemplates[$task][$event];
	}

	function _parseObject(&$object) {
		if(get_class($object)=='objectslist') return $object->data ;
		else return get_object_vars($object);
	}

	function _parseContent(&$object) {
		isset($TemplatedElements) or $TemplatedElements = array();
		foreach(is_object($object)? $this->_parseObject($object) : $object as $key => $value)
			$TemplatedElements[$key] = is_object($value) || is_array($value)? $this->_parseContent($value) : $value;
		return $TemplatedElements;
	}

	function processEvent($task,$event,$request,&$object) {
		/* Start Check Perm */
		if(!empty($this->Tasks[$task][$event]['minPerm'])) {
			$error = $this->Security->checkPerm($this->ModuleID,$this->Tasks[$task][$event]['minPerm']);
			if(!empty($error)) {
				$this->PreparedTemplates[$task][$event]['_error'] = $error;
				$object->PreparedTemplates['_error'] = $error;
				return FALSE;
			}
		}
		/* End Check Perm */
		/* Start Check Flood */
		/* End Check Flood */
		//print "<li>".get_class($this);
		//print "<li>".get_class($this->Security);
		//print "<li>".$task;
		//print "<li>".$event;
		//printArray($this->Tasks[$task][$event]['handlerMethod']);
		//printArray($this->Tasks[$task]);
		$return = $this->Handler->{$this->Tasks[$task][$event]['handlerMethod']}($request);
		$object->PreparedTemplates = $this->VisualContent($return,$task,$event);
		if(!empty($return->_error)) return FALSE;
		if(!empty($return->_dialog)) return FALSE;
		else {
			if(!empty($this->Tasks[$task][$event]['actionMethod']))
				$this->{$this->Tasks[$task][$event]['actionMethod']}($object->PreparedTemplates);
			if(!empty($this->Tasks[$task][$event]['viewMethod']))
				$object->{$this->Tasks[$task][$event]['viewMethod']}($object->PreparedTemplates);
			return TRUE;
		}
	}
	
	function isAuthorizeUser() {
		$perm = getUserPerm();
		if(empty($perm)) return TRUE;
		$currentuser = $this->Security->getCurrentUser(array());
		return !empty($currentuser->id)? 1 : 0; 
	}

	function isAuthorizeUserForModule($module) {
		$perm = getUserPerm();
		if(empty($perm)) return TRUE;
		$currentuser = $this->Security->getCurrentUser(array());
		if(empty($currentuser->id)) return 0;
		else {
			$right = $this->Security->checkPerm($module,2);
			if(empty($right)) return 1;
			else return 0;
		}
	}

	function isAuthorizeAdmin() {		
		$perm = getAdminPerm();
		if(empty($perm)) return TRUE;
		$currentuser = $this->Security->getCurrentUser();		// Get user information authorized previosly 
		if(empty($currentuser->id)){									// If there isn't authorized user
			$this->Security->authorizeMemberByCookie();					// Try to authorize by cookies
			$currentuser = $this->Security->getCurrentUser();	//
			if(empty($currentuser->id))									// If this user doesn't have valid cookies, return 0
				return 0;
		}
		$right = $this->Security->checkPerm(3,2);
		if(empty($right)) return 1;
		else return 0;
	}
	function isTime($time_letter) {		
		
	}
	function isLostAdmin() {		
		$perm = getAdminPerm();
		if(empty($perm)) return TRUE;
		$currentuser = $this->Security->getCurrentUser(array());
		if(empty($currentuser->id)) return 0;
		else {
			$right = $this->Security->checkPerm(3,2);
			if(empty($right)) return 1;
			else return 0;
		}
	}


}
?>