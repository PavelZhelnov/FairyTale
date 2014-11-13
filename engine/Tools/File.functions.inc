<?php

function get_filesize($dsize) { 
	if (strlen($dsize)>=10) return number_format($dsize/1073741824,2).' Gb';
	elseif (strlen($dsize)<=9 and strlen($dsize)>=7) return number_format($dsize/1048576,2).' Mb';
	else return number_format($dsize/1024,2).' Kb';
}

function filesize_format($size, $sizes = array('Bytes', 'KB', 'MB', 'GB', 'TB', 'PB', 'EB', 'ZB', 'YB'))
{
    if ($size == 0) return('n/a');
    return (round($size/pow(1024, ($i = floor(log($size, 1024)))), 2) . ' ' . $sizes[$i]);
}

function getServer($servers=array('name'=>'','url'=>'')) {
	foreach($servers as $key => $value) {
		$urldata = parse_url($value['url']);
		$serverpointer = fsockopen($urldata['host'], 80, $errno, $errstr, 30);
		if($serverpointer) return $value;
		else return 0;
	}
}

function getRemoteFile($file){
	$urldata = parse_url($file);
	$filepointer = fsockopen($urldata['host'],80,$errno,$errstr, 30);
	if(!$filepointer) return 0;
	else return $data = implode('', file($file));
}

function saveRemoteFile($filename,$file){
	if(!$fp = fopen($filename, 'w')) { 
		//print "Cannot open file ($filename)";
		return false;
	}
	if(!fwrite($fp, $file)) { 
		//print "Cannot write to file ($filename)";
		return false;
	}
	fclose($fp); 
	return true;
}

function appendFile($filename, $data) {
	$fh = fopen($filename, 'a') or die("can't open file");
	fwrite($fh, $data);
	fclose($fh);
}

function removedir_recursive($dir) { 
    if (!is_dir($dir) || is_link($dir)) return unlink($dir); 
    foreach (scandir($dir) as $file) { 
        if ($file == '.' || $file == '..') continue; 
        if (!removedir_recursive($dir.'/'.$file)) { 
            chmod($dir.'/'.$file, 0777); 
            if (!removedir_recursive($dir.'/'.$file)) return false; 
        }; 
    } 
    return rmdir($dir); 
}

function convertBytesToKb($size,$precision=2) {
 	$base = log($size) / log(1024);
    $suffixes = array('', 'k', 'M', 'G', 'T');   

    return round(pow(1024, $base - floor($base)), $precision) . $suffixes[floor($base)];
}
?>