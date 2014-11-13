<?php

class RequestBroker extends RootRegistry {

	public $Target = '';
	public $Request = array();
	public $RequestMethod = '';

	function RequestBroker($name = 'RequestBroker') {
		global $REGISTRY,$SiteStructure;
		$this->RootRegistry($name);
		$request = array();
		$this->RequestMethod = $_SERVER['REQUEST_METHOD'];
		$this->Request = ($this->RequestMethod == 'POST' and !allowPosting())? $_GET
			: array_merge($_GET,$_POST,$_FILES);
		$this->Request = $this->deAlias();
		if($REGISTRY['Core']['TargetThruQuery'])
			$rawTarget = $this->Request['target'];
		else
			$rawTarget = (isset($_SERVER['PATH_INFO']) and $_SERVER['PATH_INFO'] != '/')?
						$_SERVER['PATH_INFO'] : '';
		$target = explode('/',preg_replace("/\/$/",'',$rawTarget));
		$this->Target = $this->Path($target);
		$localtarget = array_slice($target,count($this->Target));
		$REGISTRY['Request'] = array(
			'Target' => $target,
			'RawTarget' => implode('/',$target),
			'LocalTarget' => $localtarget,
			'Query' => $this->Request,
			'Method' => $this->RequestMethod,
			'Broker' => $this
		);
		$REGISTRY['Globals']['this_target'] = $REGISTRY['Request']['RawTarget'];
		$REGISTRY['Core']['TemplatesDir'] = $REGISTRY['Core']['TemplatesDirDefault'];
	}

	function getTarget() { return $this->Target; }

	function getPath() {
		$path = implode('/',$this->Target);
		if(empty($path)) $path = "/$path";
		return $path;
	}

	function deAlias() {
		global $REGISTRY;
		$request = array();
		foreach($this->Request as $key => $value)
			$request[isset($REGISTRY["RequestSettings"]["Parameters"][$key])? $REGISTRY["RequestSettings"]["Parameters"][$key] : $key] = $value;
		return $request;
	}

	function getRequestFor($name) {
		if(isset($this->Request["object"]) && $this->Request["object"] == $name) return $this->Request;
		else return array ();
	}

	function Path($path) {
		return $this->validatePath($path,array());
	}

	function validatePath($path,$subtree) {
		$checked = array();
		if(count($path)) {
			$node = array_shift($path);
			if(isset($subtree[$node])) {
				if(is_array($subtree[$node]))
					$checked = $this->validatePath($path,$subtree[$node]);
				array_unshift($checked,$node);
			}
		}
		return $checked;
	}
}
?>