<?php

function parseQuery ($query) {
	$query = explode ('?', $query);
	$target = explode (':', array_shift ($query));
	$properties = array_shift ($query);
	$name = array_shift ($target);
	$type = array_shift ($target);
	$template = array_shift ($target);
	$template or $template = $name;
	$result = array ('Name' => $name, 'Type' => $type, 'Template' => $template, 'Properties' => array ());
	if ($properties)
		foreach (explode ('&', $properties) as $pair) {
			$pair = explode ('=', $pair);
			$result["Properties"][array_shift ($pair)] = array_shift ($pair);
		}
	return $result;
}
  
function unparseQuery ($pquery, $extra = "") {
	is_array ($extra) or $extra = array ();
	$properties = array_merge ($pquery["Properties"], $extra);
	foreach ($properties as $key => $value) $prop[] = $key . '=' . $value;
	return $pquery["Name"] . ':' . $pquery["Type"] . ':' . $pquery["Template"]
		. (empty ($prop) ? '' : '?' . implode ('&', $prop));
}
  
function substVS($name) {
	global $REGISTRY;
	$locate = TRUE;
	$target = $theTarget = $REGISTRY['Request']['Target'];
	$self = TRUE;
	$VS = &$REGISTRY['VirtualSlotTarget'][$name];
	while(count($target) and empty($slot)) {
		$key = implode('/', $target);
		$node = isset($VS[$key])? $VS[$key] : '';
		if(is_array($node)) {
			$slot = (!$self or empty($node['self']))? $node['inherit'] : $node['self'];
			$locate = $node['Locate'];
		}
		else $slot = $node;
		$self = FALSE;
		$entry = array_pop($target);
	}
	array_push ($target, $entry);
	$pquery = parseQuery ($slot);
	$pquery['Target'] = $target;
	$pquery['VName'] = $name;
	$pquery['Locate'] = $locate;
	$pquery['LocalTarget'] = array_slice($theTarget,count($target));
	return $pquery;
}

class Variable {

	public $Type = 'variable';
	public $Name = '';
	public $Result = '';
	
	function Variable($pquery) {
		global $REGISTRY;
		$this->Name = $pquery["Name"];
		$this->Result = isset($REGISTRY["Globals"][$pquery["Type"]][$this->Name]) ?
			$REGISTRY["Globals"][$pquery["Type"]][$this->Name] : '';
	}
	
	function render() { return $this->Result; }
} 


function createSlot($query, $extra = '') {
	global $REGISTRY;
	$pquery = is_array($query)? $query : parseQuery($query);
	isset ($pquery["Target"]) or $pquery["Target"] = $REGISTRY["Request"]["Target"];
	is_array($extra) or $extra = array();
	switch ($pquery["Type"]) {
		case 'static': return new Variable($pquery);
		case 'dynamic': return new Variable($pquery);
		case 'virtual': return createSlot(substVS($pquery["Name"]), array_merge($pquery["Properties"], $extra));
		case 'object': return createObject($pquery, $extra);
		default: 
			$pquery["Properties"] = array_merge($pquery["Properties"], $extra);
			return new Slot($pquery);
	}
}

function createObject($pquery, $extra = '') {
	global $REGISTRY;
	is_array($extra) or $extra = array();
	$reg = loadObjectRegistry($pquery['Name']);
	$class = !empty($reg["Class"])? $reg["Class"] : $pquery["Name"];
	loadObjectClass($class);
	empty($reg["Properties"]) and $reg["Properties"] = array();
	$pquery["Properties"] = array_merge(array_merge($reg["Properties"], $pquery["Properties"]), $extra);
	!empty($reg["Templates"]) and $pquery["Templates"] = $reg["Templates"];
	return new $class ($pquery);
}

function renderSlot($query,$extra = '',$root = FALSE) {
	global $REGISTRY;
	$content = '';	
	$target = $REGISTRY['Request']['Target'];
	$slot = createSlot($query, $extra);
	$slot->Type == 'variable';
	debug ("renderSlot", "Rendering...<ul>");
	$rendered = $slot->render($content);
	debug ("</ul>");	
	return $rendered;
}

/**
* Make URL and file name safe
* Enter description here ...
* @param $string
* @param $force_lowercase
* @param $anal
*/
function sanitizeFileName($string, $force_lowercase = true, $anal = false) {
  	$strip = array("~", "`", "!", "@", "#", "$", "%", "^", "&", "*", "=", "+", "{", 
               	"(", ")", ",", "}", "\\", "|", ";", ":", "\"", "'", "&#8216;", "&#8217;", "&#8220;", "&#8221;", "&#8211;", "&#8212;",
               	"<", ".", ">", "/", "?");
   	$clean = trim(str_replace($strip, "", strip_tags($string)));
   	$clean = preg_replace('/\s+/', "_", $clean);
   	$clean = ($anal) ? preg_replace("/[^a-zA-Z0-9]/", "", $clean) : $clean ;
   	return ($force_lowercase) ?
        (function_exists('mb_strtolower')) ?
           	mb_strtolower($clean, 'UTF-8') :
           	strtolower($clean) :
       	$clean;
}

?>