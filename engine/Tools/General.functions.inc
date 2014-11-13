<?php

function allowPosting() { return TRUE; }

function templatePath($sub = array()) {
	global $REGISTRY;
	array_unshift($sub, '');
	foreach($sub as $subpath) {
		$slash = empty($subpath)? '' : '/';
		$path[] = $REGISTRY['Core']['TemplatesDirDefault'].$slash.$subpath;
		$path[] = $REGISTRY['Core']['TemplatesDir'].$slash.$subpath;
	}
	return array_unique($path);
}

function arrayPath($path) {
	return $path == '/'? array('') : explode('/', $path);
}

function stringPath($path) {
	return implode('/', $path);
}

function readCacheFile($file,$path = '') {
	global $REGISTRY;
	is_array($path) or $path = array($path);
	foreach($path as $eachPath)
		if(!empty($REGISTRY['FileCache'][$eachPath.$file])) 
			return $REGISTRY['FileCache'][$eachPath.$file];
		elseif(file_exists($eachPath.$file)) {
			//print $eachPath.$file.'<br>';
			$result = implode('', file($eachPath.$file));
			$REGISTRY['FileCache'][$eachPath.$file] = $result;
			return $REGISTRY['FileCache'][$eachPath.$file];
		}
	return FALSE;
}

function makeLink ($link, $linkname = '', $extra = array(), $anchor = '', $class = '') {
	foreach($extra as $key => $value) $pairs[] = $key.'='.$value;
	if(isset($pairs)) {count($pairs) and $query = implode('&', $pairs);}
	if(!empty($query)) $link.= '?'.$query;
	if($anchor) $link.= '#'.$anchor;
	if(empty($linkname)) $linkname = $link;
	return "<a href=\"".$link."\" ".$class.">".$linkname."</a>";
}

function targetLink ($target, $linkname = '', $extra = array(), $anchor = '', $class = '') {
	global $REGISTRY;
	return makeLink($REGISTRY['Core']['WebHome'].implode('/', $target), $linkname, $extra, $anchor, $class);
}

function makeImage($file,$src,$alt = '',$align ='',$spaces = array(),$border = 0, $extra='') {
	if(file_exists($file)) {
		$s = getimagesize($file);
		return "<img src=\"" . $src . "\" " .  " bordercolor=\"#000000\" border=\"".$border."\" alt=\"".$alt."\" ".(!empty($align)? " align=\"$align\" " : "").(!empty($spaces)? " hspace=\"$spaces[0]\" vspace=\"$spaces[1]\" " : "")." ".$extra.">";
	}
	else return ' ';
}

function makeSWF($file,$src,$width=120,$height=120,$standby='') {
	if(file_exists($file)) {
		$s = getimagesize($file);
		return "<OBJECT classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"
			codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0\"
			".$s[3]." border=0 TYPE=\"application/x-shockwave-flash\">
			<PARAM NAME=movie VALUE=\"$src\">
			<PARAM NAME=menu VALUE=true>
			<PARAM NAME=quality VALUE=high>
			<PARAM NAME=bgcolor VALUE=\"#ffffff\">
			<EMBED src=\"$src\" menu=true quality=best 
			bgcolor=\"#ffffff\" ".$s[3]." border=0 TYPE=\"application/x-shockwave-flash\"
			PLUGINSPAGE=\"http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash\">
			</EMBED>
			</OBJECT>";
	}
	else return ' ';
}

function makeGame($file,$src,$get = '',$background = '') {
	if(file_exists($file)) {
		$s = getimagesize($file);
		return "<OBJECT classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"
			codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0\"
			".$s[3]." border=1 TYPE=\"application/x-shockwave-flash\" standby=\"\">
			<PARAM NAME=movie VALUE=\"".$src.(!empty($get)? '?'.$get : '')."\">
			<PARAM NAME=menu VALUE=true>
			<PARAM NAME=quality VALUE=high>
			<PARAM NAME=bgcolor VALUE=\"#".(!empty($background)? $background : 'c9d2ff')."\">
			<EMBED src=\"$src\" menu=true quality=best 
			bgcolor=\"#".(!empty($background)? $background : 'c9d2ff')."\" ".$s[3]." border=1 TYPE=\"application/x-shockwave-flash\"
			PLUGINSPAGE=\"http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash\">
			</EMBED>
			</OBJECT>";
	}
	else return ' ';
}

function setGlobal ($name, $value) {
	global $REGISTRY;
	$REGISTRY['Globals'][$name] = $value;
}

function getGlobal ($name) {
	global $REGISTRY;
	return isset($REGISTRY['Globals'][$name])?  $REGISTRY['Globals'][$name] : false;
}

function appendGlobal($name, $value) {
	global $REGISTRY;
	$REGISTRY['Globals'][$name] .= $value;
}

function debug($name, $message = "") {
	global $DEBUG, $REGISTRY;
	if(empty($REGISTRY['Core']['Debug'])) return;
	$DEBUG[] = empty($message)? $name : '<b>'.$name.'</b>: '.$message;
}

function debugArray(&$array, $ksorted = FALSE) {
	global $REGISTRY;
	if(empty($REGISTRY['Core']['Debug'])) return;
	debug(HTMLformatArray($array, 4, $ksorted, TRUE));
}

function debugContent() {
	global $DEBUG, $REGISTRY;
	if(empty($REGISTRY['Core']['Debug'])) return;
	return '<h3>Debug info:</h3>'.implode("\n", $DEBUG);
}
function getAge($year,$month,$day) {
	$age = date("Y") - $year;
	if($month > date("m")) $age--;
	else if($month == date("m") && $day > date("d")) $age--;
	return $age;
}

function astr(&$str,$add,$delim=" ") {
    if($add) { 
	if($str) $str.=$delim;
	$str.=$add;
	}
}
?>