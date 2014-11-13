<?php

function readRegistry() {
	global $REGISTRY;
	$result = FALSE;
	$reg = readWholeFile($REGISTRY["Core"]["RegistryFile"]);
	if($reg and preg_match_all('/\/\/\s+REGISTRY\/([^\s]+)(.*)\/\/\s+~REGISTRY\/\1/sm', $reg, $m)) 
		foreach($m[1] as $k => $v) 
			$result[$v] = $m[2][$k];
	return $result;
}

function saveRegistry($pos) {
	global $REGISTRY;
	$reg = readRegistry();
	if(isset($reg[$pos])) {
		$reg[$pos] = PHPformatArray($REGISTRY, "REGISTRY", array($pos));
		$out = "<?php\n\n";
		foreach($reg as $key => $value)
			$out.= "\n// REGISTRY/$key$value// ~REGISTRY/$key\n";
		$out.= "\n?>";
		return saveFile($REGISTRY["Core"]["RegistryFile"],$out);
	}
	return FALSE;
}
?>