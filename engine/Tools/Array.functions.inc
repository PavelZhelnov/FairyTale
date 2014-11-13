<?php
function phpArray2js($js_name, &$array) {
	$res = "var " . $js_name . " = {";
	if(is_array($array) and (count($array) > 0))
	{
		reset($array);
		$c = each($array);
		$res .= '"'.$c['key'] . '":"'.$c['value'].'"';
		while($c = each($array))
		{
			$res .= ',"'.$c['key'] . '":"'.$c['value'].'"';
		}
	}
	return $res.'};';
}
function joinDictionary($innerDelim, $outerDelim, &$array) {
	if(!is_array($array) or (count($array) < 1))
	return '';
	reset($array);
		$c = each($array);
		$res = $c['key'] . $innerDelim . $c['value'];
		while($c = each($array))
		{
			$res .= $outerDelim.$c['key'] . $innerDelim.$c['value'];
		}
		return $res;
}
function replaceArray($string,&$array) {
	$new_array = explode(',',$string);
	foreach($new_array as $key => $value) $new_array[$key] = $array[$value];
	$new_string = implode(', ',$new_array);
	return $new_string;
}

function compactArray(&$array,$new_array = array()) {
	foreach($array as $k => $v) $new_array[] = $array[$k];
	$array = $new_array;
}

function mergeArrays($a, $b) {
	if(!is_array($b)) return $a;
	foreach(array_keys($a) as $k)
		if(isset($b[$k])) {
			$c[$k] = is_array($a[$k])? mergeArrays($a[$k], $b[$k]) : $b[$k];
			unset($b[$k]);
			unset($a[$k]);
		}
		else $c[$k] = $a[$k];
	foreach($b as $k => $v) $c[$k] = $v;
	return $c;
}

function getValuesToKeys(&$array,$array2=array()) {
	foreach($array as $key => $value) $array2[$value] = $key;
	return $array2;
}

function formatArray(&$array, $params = array("break" => "\n","ident" => "\t","function" => "addslashes"), $depth = 0) {
	$break = $params["break"];
	$ident = str_repeat($params["ident"], $depth);
	$pairs = array();
	if(is_array($array)) {
		if(!empty($params["ksorted"])) ksort ($array);
		$newident = str_repeat($params["ident"], $depth + 1);
		foreach(array_keys($array) as $key) {
			$emKey = !empty ($params["emkeys"]) ? "<b>" . $key . "</b>" : $key;
			$pairs[] = "$newident" . (is_int ($key) ? $emKey : "\"" . $emKey . "\"") . " => "
				. formatArray ($array[$key], $params, $depth + 1);
		}
		$result = count ($pairs) ? "$break" . implode (",$break", $pairs) . "$break$ident" : "";
		return "array ($result)";
	}
	elseif (is_object ($array)) return "object";
	else return $array;
}

function HTMLformatArray (&$array, $ident = 4, $ksorted = FALSE, $emKeys = FALSE) {
	return formatArray (
		$array, 
		array (
			"break" => "<br>\n", 
			"ident" => str_repeat ("&nbsp;", $ident), 
			"function" => "htmlentities",
			"ksorted" => $ksorted,
			"emkeys" => $emKeys
		)
	);
}

function PHPformatArray(&$array,$arrayName,$path = array()) {
	while(count($path) and isset($array[$path[0]])) {
		$key = array_shift($path);
		$arrayName .= '['.(is_int($key)? $key : "\"$key\"").']';
		$array = &$array[$key];
	}
	return "\$$arrayName = ".formatArray($array).';';
}

function beforeValue(&$value,$key,$suffix) {
	$value = $value.'_'.$suffix;
}

function beforeArray(&$array, $suffix) {
	array_walk($array,'beforeValue',$suffix);
}

function listArrayValues($array,$separator=',',$prepared=0) {
	$list = '';
	foreach($array as $key => $value) {
		if ($value == null) {$value='null';} else {
			$value = $prepared? "'".$value."'" : $value;
		}
		$list .= $value.$separator;
	}
	$list = substr($list,0,-strlen($separator));
	return $list;
}

function listArrayValuesLower($array,$separator=',',$prepared=0) {
	$list = '';
	foreach($array as $key => $value) {
		$value = $prepared? "'".strtolower($value)."'" : strtolower($value);
		$list .= $value.$separator;
	}
	$list = substr($list,0,-strlen($separator));
	return $list;
}
function listArrayKeys($array,$separator=',') {
	$list = '';
	foreach($array as $key => $value) $list .= $key.$separator;
	$list = substr($list,0,-strlen($separator));
	return $list;
}

function listArrayKeysAndValues($array,$relation='=',$separator=',',$prepared=0) {
	$list = '';
	foreach($array as $key => $value) {
		if ($value == null) {$value='null';} else {
			$value = $prepared? "'".$value."'" : $value;
		}
		$list .= $key.$relation.$value.$separator;
	}
	$list = substr($list,0,-strlen($separator));
	return $list;
}

function printArray (&$array, $ksorted = FALSE) {	print HTMLformatArray ($array, 4, $ksorted) . "<br>"; }

function _ObjToArray($object) {
	return is_object($object)? get_object_vars($object) : $object;
}

function ObjToArray($object) {
	$clon = $object;
	$array = _ObjToArray($clon);
	foreach($array as $key => $value) {
		if(is_object($value)) $array[$key] = ObjToArray($value);
	}
	return $array;
}

function printObject($object) {
	$objar = ObjToArray($object);
	printArray($objar);
}

function array_max($data) {
	$first = true;
	foreach($data as $key => $val) {
		if($first) {
			$max = intval($val);
			$first = false;
		}
		elseif($max < intval($val)) $max = intval($val);
	}
	return $max;
}

function removeIntegerValuesFromArray(&$array) {
	is_array($array) or $array = array();
	foreach($array as $k => $v)
		if(is_numeric($v)) unset($array[$k]);
	return $array;
}

function removeNotIntegerValuesFromArray(&$array) {
	is_array($array) or $array = array();
	foreach($array as $k => $v)
		if(!is_numeric($v)) unset($array[$k]);
	return $array;
}

function removeIntegerKeysFromArray(&$array) {
	foreach($array as $k => $v)
		if(is_integer($k)) unset($array[$k]);
	return $array;
}

function removePrivateKeysFromArray(&$array) {
	foreach($array as $k => $v)
		if(preg_match('/^_/i',$k)) unset($array[$k]);
	return $array;
}

function removeNullValuesFromArray(&$array) {
	foreach($array as $k => $v) {
		if(is_array($v) && (is_integer($k) || preg_match("/(pop)[0-9]+/", $k) )) $array[$k]=removeNullValuesFromArray($v);
		if (empty($v)) {unset($array[$k]);}
	}
	return $array;
}

function prepareValueOrExpression(&$value) {
	if(is_string($value) && (strtoupper($value) != "NULL"))
		if((is_integer(strpos($value,'EXPRESSION='))) && (strpos($value,'EXPRESSION=') == 0))
			$value = substr($value,strlen('EXPRESSION='));
		else			
			if(!get_magic_quotes_gpc()) $value = "\"".addslashes($value)."\"";
			else $value = "\"".$value."\"";
			if(preg_match('/\./i',$value) && (!preg_match('/%/i',$value) && (!preg_match('/@/i',$value) && (!preg_match('/http/i',$value))))) $value = preg_replace("/\"/i",'',$value);
}

function prepareValuesOrExpressions(&$values) {
	array_walk($values,'prepareValueOrExpression');
}

function formatArrayXML(&$array, $params = array("break" => "\n","ident" => "\t","function" => "addslashes"), $depth = 1) {
	$break = $params["break"];
	$ident = str_repeat($params["ident"], $depth);
	$pairs = array();
	if(is_array($array)) {
		if(!empty($params["ksorted"])) ksort ($array);
		$newident = str_repeat($params["ident"], $depth + 1);
		foreach(array_keys($array) as $key) {
			$emKey = !empty ($params["emkeys"]) ? $key : $key;
			$pairs[] = "$newident" . (is_int ($key) ? $emKey : "<" . $emKey . ">") . 
				formatArrayXML ($array[$key], $params, $depth + 1).
				(is_int ($key) ? $emKey : "</" . $emKey . ">\n");
		}
		$result = count ($pairs) ? "$break" . implode ("$break", $pairs) . "$break$ident" : "";
		return "$result";
	}
	elseif (is_object ($array)) return "object";
	else return $array;
}

function printArrayToXML (&$array, $ksorted = FALSE) {
	print formatArrayXML ($array, 4, $ksorted) . "\n"; 
}
function objToXml($obj){
	print("<?xml version=\"1.0\"?\>\n");
	print "<".get_class($obj).">\n";	
	$objarr = ObjToArray($obj);
	printArrayToXML($objarr);
	print "\n</".get_class($obj).">";
	
}
function arrayToXml($arr){
	print("<?xml version=\"1.0\"?\>\n");
	print "<Array>\n";	
	printArrayToXML($arr);
	print "</Array>\n";
}


function flatArrayToGridXml($array, $params=array('appendhead'=>0), $columnProps) {
	if (empty($array)) return null;
	$buf = "<?xml version=\"1.0\" encoding=\"windows-1251\"?>\n";
	$buf = $buf. ($params['appendhead']?'<!DOCTYPE rows SYSTEM "dhtmlxgrid.dtd">':'');

	$id = 1;
	$buf=$buf."\n<rows>\n";
	//head	
	if ($params['appendhead']) {
		$keys = array_keys($array);
		$key = $keys[0];
		$buf = $buf. "\t<head>\n"; 
		foreach(array_keys($array[$key]) as $k) {
			if ($k=='id') continue;
			$options = '';
			$columnp = ' width="'.(!empty($columnProps[$k]['width'])?$columnProps[$k]['width']:'100').'"'.
				' id="'.$k.'"'.
				' type="'.(!empty($columnProps[$k]['type'])?$columnProps[$k]['type']:'ro').'"'.
				' align="'.(!empty($columnProps[$k]['align'])?$columnProps[$k]['align']:'left').'"'.
				' sort="'.(!empty($columnProps[$k]['sort'])?$columnProps[$k]['sort']:'str').'"';
			if (!empty($columnProps[$k]['options'])) {
				foreach($columnProps[$k]['options'] as $ko=>$v) {
					$options = $options."\n\t\t\t".'<option value="'.$ko.'">'.$v.'</option>'."\n";
				}
			}
			$buf = $buf. "\t\t<column $columnp>". (!empty($columnProps[$k]['name'])?$columnProps[$k]['name']:$k). $options. "</column>\n";
		}
		$buf = $buf. "\t</head>\n";
	}

	
	
	foreach(array_keys($array) as $key) {
			//$buf = $buf. "<" . $key . ">". $array[$key]. "</" . $key . ">\n";
			foreach(array_keys($array[$key]) as $k) {
				if ($k=='id') {
					$buf = $buf. "\t<row id=\"".$array[$key][$k]."\">\n"; 
				} else {
					$buf = $buf. "\t\t<cell>". $array[$key][$k]. "</cell>\n";
				}
			}
			$buf = $buf. "\t</row>\n";
	}
	$buf=$buf."</rows>";
	return $buf;
}

?>