<?php

function loadObjectRegistry($name) {
	global $REGISTRY;
	$Registry = array();
	$file = $REGISTRY['Core']['RegistryPath'].'/'.$name.$REGISTRY['Core']['RegistryExtension'];
	file_exists($file) and include($file);
	return $Registry;
}

function loadObjectClass($name) {
	global $REGISTRY;
	$file = $REGISTRY['Core']['ObjectsPath'].'/'.$name.$REGISTRY['Core']['ClassExtension'];
	file_exists($file) and include_once($file);
}

function &getObject($name,$properties = '') {
	global $REGISTRY, $CORE_PATH;
	if(@!is_object($REGISTRY['Objects'][$name])) {
		include_once($REGISTRY['Core']['ObjectsPath'].'/'.$name.$REGISTRY['Core']['ClassExtension']);
		$REGISTRY['Objects'][$name] = new $name($properties);
	}
	return $REGISTRY['Objects'][$name];
}

function onceObject(&$Obj,$Objname) {
	is_object($Obj) or $Obj = new $Objname();
}


function getClassMethodsAnnotations($class) {
    $result = array();
    $r = new ReflectionClass($class);
    foreach($r->getProperties() as $k=>$v) {
        $result[$v->name] = trim(str_replace(array('/', '*'), '', $v->getDocComment()));
    }
    $doc = $r->getDocComment();
    preg_match_all('#@(.*?)\n#s', $doc, $annotations);
    return $result;
}
?>