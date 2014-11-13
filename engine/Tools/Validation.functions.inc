<?php

	function _is_valid($string,$min_length,$max_length,$regex) {
		if(empty($string) && $string!='0') return false;
		if(!preg_match("/^$regex$/i", $string)) return false;
		$strlen = strlen($string);
		if(($min_length != 0 && $strlen < $min_length) || ($max_length != 0 && $strlen > $max_length))
			return false;
		return true;
	}

	function is_EngText($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[^àáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß]+");
		return $ret;
	}

	function is_Alpha($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[a-zàáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß]+");
		return $ret;
	}

	function is_Num($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[[:digit:]]+");
		return $ret;
	}

	function is_NumDefis($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[[:digit:]\.,-]+");
		return $ret;
	}

	function is_FloatNum($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[[:digit:]\.,]+");
		return $ret;
	}

	function is_AlphaNum($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[a-zàáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß0-9]+");
		return $ret;
	}

	function is_MD5($string) {
		$ret = _is_valid($string,32,32,"[abcdef0-9]+");
		return $ret;
	}

	function is_AlphaNumDefis($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[a-zàáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß0-9_-]+");
		return $ret;
	}

	function is_AlphaNumDefisSpace($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[ a-zàáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß0-9_-]+");
		return $ret;
	}

	/*
	 * Delimeter is ";" - taken from Global System Attributes 
	 * 
	 */
	function is_Email($string) {
		global $Server; 
		$handler = $GlobalSystemSettingsHandler = &$Server->getHandler(103);
		$sgs=$handler->getGlobalSystemSettings();
		$domainString='(biz|com|org|net|mil|edu|info|mobi|travel|a[cdfgilmnoqrstuwxz]|b[abdefghijmnorstwyz]|c[acdfghiklmnoruvxyz]|d[ejkmoz]|e[cegrstu]|f[ijkmor]|g[adefghilmnpqrstuwy]|h[kmnrtu]|i[delmnoqrst]|j[emop]|k[eghimnrwyz]|l[abcikrstuvy]|m[acdghklmnopqrstuvwxyz]|n[acefgilopruz]|om|p[aefghklmnrstwy]|qa|r[eouw]|s[abcdeghiklmnrtvyz]|t[cdfghjklmnortvwz]|u[agksyz]|v[aceginu]|w[fs]|y[etu]|z[amw])';
		$emails = explode($sgs->email_delimeter,$string);
		foreach ($emails as $value) {
			$value = trim($value);
			$ret = preg_match('/^[a-z0-9]+([_\\.-][a-z0-9]+)*@([a-z0-9]+([\.-][a-z0-9]+)*)+\\.'.$domainString.'$/i', $value);
			// '^([a-z0-9_]|\\-|\\.)+'.'@'.'(([a-z0-9_]|\\-)+\\.)+'.$domainString.'$',$value);
			if (!$ret) return $ret; 
		}
		return $ret;
	}

	// äîï. ôóíêöèÿ äëÿ óäàëåíèÿ îïàñíûõ ñèâîëîâ
	function pregtrim($str) {
		return preg_replace("/[^\x20-\xFF]/","",@strval($str));
	}

	function checkURL($url) {
		// ğåæåì ëåâûå ñèìâîëû è êğàéíèå ïğîáåëû
		$url=trim(pregtrim($url));
		// åñëè ïóñòî - âûõîä
		if(strlen($url)==0) return '';
		//ïğîâåğÿåì ÓĞË íà ïğàâèëüíîñòü
		if(!preg_match("~^(?:(?:https?|ftp|telnet)://(?:[a-z0-9_-]{1,32}".
		"(?::[a-z0-9_-]{1,32})?@)?)?(?:(?:[a-z0-9-]{1,128}\.)+(?:com|net|".
		"org|mil|edu|arpa|gov|biz|info|aero|inc|name|[a-z]{2})|(?!0)(?:(?".
		"!0[^.]|255)[0-9]{1,3}\.){3}(?!0|255)[0-9]{1,3})(?:/[a-z0-9.,_@%&".
		"?+=\~/-]*)?(?:#[^ '\"&<>]*)?$~i",$url,$ok))
		return ''; // åñëè íå ïğàâèëüíî - âûõîä
		// åñëè íåò ïğîòîêàëà - äîáàâèòü
		if(!strstr($url,"://")) $url="http://".$url;
		// çàìåíèòü ïğîòîêîë íà íèæíèé ğåãèñòğ: hTtP -> http
		$url=preg_replace("~^[a-z]+~ie","strtolower('\\0')",$url);
		return $url;
	}

	function is_CleanText($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[a-zàáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß[:space:].-]+");
		return $ret;
	}
	
	function is_SupportedFileName($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[a-zA-Z0-9-\xB0-\xEF[:space:]\.,:)(_&]+");
		return $ret;
	}
	
	function is_AdvCleanText($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"[a-zàáâãäå¸æçèéêëìíîïğñòóôõ÷öøùüûúışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜÛÚİŞß0-9[:space:].,;:)(_!?-]+");
		return $ret;
	}

	function is_FullText($string,$min_length = 0,$max_length = 0) {
		$ret = _is_valid($string,$min_length,$max_length,"(.*)+");
		return $ret;
	}

	function chkdate($year,$month,$day) {
		if(empty($year)) return 0;
		if(($month=="01")||($month=="03")||($month=="05")||($month=="08")||($month=="12")||($month=="07")||($month=="10")) {
			if($day<32) return 1;
			else return 0;
		}
		if(($month=="04")||($month=="06")||($month=="09")||($month=="11")) {
			if($day<31) return 1;
			else return 0;
		}
		if($month=="02") {
			$leap = (($year-2000)/4);
			if(gettype($leap)=='integer') $daysin = '29';
			else $daysin = '28';
			if($day<($daysin+1)) return 1;
			else return 0;
		}
	}

	// ????? !!!
	function validate($value = '') {
		$value = is_array($value)? $value : trim($value);
		return !empty($value);
	}

	function equals($name,$value) {
		return isset($name) && $name == $value? true : false;
	}
?>