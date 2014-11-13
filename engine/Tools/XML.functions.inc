<?php

function getXMLChildren($vals,&$i) {
	$children = array();
	if(isset($vals[$i]['value'])) array_push($children, $vals[$i]['value']);
	$prevtag = '';
	while(++$i < count($vals)) {
		switch($vals[$i]['type']) {
			case 'cdata': array_push($children,$vals[$i]['value']); break;
			case 'complete': $children[$vals[$i]['tag']] = $vals[$i]['value']; break;
			case 'open':
				@$j++;
				if($prevtag <> $vals[$i]['tag']) {
					// Restart Index j on Unique Tag
					$j = 0;
					$prevtag = $vals[$i]['tag'];
				}
				$children[$vals[$i]['tag']][$j] = getXMLChildren($vals,$i);
			break;
			case 'close': return($children);
		}
	}
}

function getXMLTree($file) {
	// If it is a local xml file, just open it
	if(file_exists($file)) $data = implode('',file($file));
	/*else {
		// If URI, we must check remote server is active
		$urldata = parse_url($file);
		$filepointer = fsockopen($urldata['host'],80,$errno,$errstr,1);
		if(!$filepointer) return(0);
		else $data = implode('', file($file));
	}*/
	$xml_parser = xml_parser_create();
	xml_parser_set_option($xml_parser, XML_OPTION_SKIP_WHITE, 1);
	xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
	xml_parse_into_struct($xml_parser, $data, $vals, $index);
	xml_parser_free($xml_parser);
	$tree = array();
	$i = 0;
	$tree = getXMLChildren($vals,$i);
	return($tree);
}

function getXMLTreeFromData($data) {
	$xml_parser = xml_parser_create();
	xml_parser_set_option($xml_parser, XML_OPTION_SKIP_WHITE, 1);
	xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
	xml_parse_into_struct($xml_parser, $data, $vals, $index);
	xml_parser_free($xml_parser);
	$tree = array();
	$i = 0;
	$tree = getXMLChildren($vals,$i);
	return($tree);
}

function getXMLFullTree($file) {
	if(file_exists($file)) $data = implode('',file($file));
	$xml_parser = xml_parser_create();
	xml_parser_set_option($xml_parser, XML_OPTION_SKIP_WHITE, 1);
	xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
	xml_parse_into_struct($xml_parser, $data, $vals, $index);
	xml_parser_free($xml_parser);
	$tree = array();
	$i = 0;
	$tree = getXMLFullChild($vals,$i);
	return($tree);
}

function getXMLFullChild($vals,&$i) {
	$children = array();
	if(isset($vals[$i]['value'])) array_push($children, $vals[$i]['value']);
	$prevtag = '';
	while(++$i < count($vals)) {
		switch($vals[$i]['type']) {
			case 'cdata': array_push($children,$vals[$i]['value']); break;
			case 'complete': $children[$vals[$i]['tag']] = iconv('UTF-8','CP1251',$vals[$i]['value']); break;
			case 'open':
				@$j++;
				if($prevtag <> $vals[$i]['tag']) {
					// Restart Index j on Unique Tag
					$j = 0;
					$prevtag = $vals[$i]['tag'];
				}
				if(!empty($vals[$i]['attributes'])) {
					foreach($vals[$i]['attributes'] as $key => $value) $vals[$i]['attributes'][$key] = iconv('UTF-8','CP1251',$value);
					$children[$vals[$i]['tag']][$j]['attributes'] = $vals[$i]['attributes'];
				}
				$children[$vals[$i]['tag']][$j]['record'] = getXMLFullChild($vals,$i);
			break;
			case 'close': return($children);
		}
	}
}
?>