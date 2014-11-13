<?php

function getAdminPerm() {
	global $REGISTRY;
	$target = $REGISTRY['Request']['Target'];	
	while(count($target)) {
		$path = implode('/', $target);
		if(isset($REGISTRY['RestrictedAreas'][$path])) {
			return $REGISTRY['RestrictedAreas'][$path];
		}
		array_pop($target);
	}
	return FALSE;
}
function getAgentPerm() {
	global $REGISTRY;
	$target = $REGISTRY['Request']['Target'];	
	while(count($target)) {
		$path = implode('/', $target);
		if(isset($REGISTRY['RestrictedAreas'][$path])) {
			return $REGISTRY['RestrictedAreas'][$path];
		}
		array_pop($target);
	}
	return FALSE;
}
function getClientPerm() {
	global $REGISTRY;
	$target = $REGISTRY['Request']['Target'];
	while(count($target)) {
		$path = implode('/', $target);
		if(isset($REGISTRY['RestrictedAreas'][$path])) {
			return $REGISTRY['RestrictedAreas'][$path];
		}
		array_pop($target);
	}
	return FALSE;
}

function getUserPerm() {
	global $REGISTRY;
	$target = $REGISTRY['Request']['Target'];
	while(count($target)) {
		$path = implode('/', $target);
		if(isset($REGISTRY['MemberAreas'][$path]))
			return $REGISTRY['MemberAreas'][$path];
		array_pop($target);
	}
	return FALSE;
}
?>