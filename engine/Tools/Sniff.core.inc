<?php

class SniffCore {

	public $_browser_info = array(
		'ua'		 => '',
		'browser'	 => 'Unknown',
		'version'	 => 0,
		'maj_ver'	 => 0,
		'min_ver'	 => 0,
		'letter_ver' => '',
		'javascript' => '0.0',
		'platform'	 => 'Unknown',
		'os'		 => 'Unknown',
		'ip'		 => 'Unknown',
		'cookies'	 => 'Unknown',
		'ss_cookies' => 'Unknown',
		'st_cookies' => 'Unknown',
		'language'	 => '',
		'long_name'	 => '',
		'gecko'		 => '',
		'gecko_ver'	 => ''
	);

	public $_feature_set = array(
		'html'		 =>	true,
		'images'	 =>	true,
		'frames' 	 =>	true,
		'tables'	 =>	true,
		'java'		 =>	true,
		'plugins'	 => true,
		'iframes'	 => false,
		'css2'		 =>	false,
		'css1'		 =>	false,
		'xml'		 =>	false,
		'dom'		 =>	false,
		'wml'		 =>	false,
		'hdml'		 =>	false
	);

	public $_quirks = array(
		'must_cache_forms'			=>	false,
		'avoid_popup_windows'		=>	false,
		'cache_ssl_downloads'		=>	false,
		'break_disposition_header'	=>	false,
		'empty_file_input_value'	=>	false,
		'scrollbar_in_way'			=>	false
	);

	public $_get_languages_ran_once = false;
	public $_browser_search_regex = '([a-z]+)([0-9]*)([0-9.]*)(up|dn|\+|\-)?';
	public $_language_search_regex = '([a-z-]{2,})';

	function init() {
		$this->_get_ip();
		$this->_test_cookies();
		$this->_get_browser_info();
		$this->_get_languages();
		$this->_get_os_info();
		$this->_get_javascript();
		$this->_get_features();
		$this->_get_quirks();
		$this->_get_gecko();
	}

	function property($p = null) {
		if($p == null) return $this->_browser_info;
		else return $this->_browser_info[strtolower($p)];
	}

	function get_property($p) {
		return $this->property($p);
	}

	function is($s) {
		if(preg_match('/l:'.$this->_language_search_regex.'/i',$s,$match)) {
			if($match) return $this->_perform_language_search($match);
		}
		elseif(preg_match('/b:'.$this->_browser_search_regex.'/i',$s,$match)) {
			if($match) return $this->_perform_browser_search($match);
		}
		return false;
	}

	function browser_is($s) {
		preg_match('/'.$this->_browser_search_regex.'/i',$s,$match);
		if($match) return $this->_perform_browser_search($match);
	}

	function language_is($s) {
		preg_match('/'.$this->_language_search_regex.'/i',$s,$match);
		if($match) return $this->_perform_language_search($match);
	}

	function has_feature($s) {
		return $this->_feature_set[$s];
	}

	function has_quirk($s) {
		return $this->_quirks[$s];
	}

	function _perform_browser_search($data) {
		$search = array();
		$search['phrase'] 		= isset($data[0]) ? $data[0] : '';
		$search['name']   		= isset($data[1]) ? strtolower($data[1]) : '';
		$search['maj_ver']   	= isset($data[2]) ? $data[2] : '';
		$search['min_ver']   	= isset($data[3]) ? $data[3] : '';
		$search['direction']	= isset($data[4]) ? strtolower($data[4]) : '';
		$looking_for = $search['maj_ver'].$search['min_ver'];
		if($search['name'] == 'aol' || $search['name'] == 'webtv')
			return stristr($this->_browser_info['ua'],$search['name']);
		elseif($this->_browser_info['browser'] == $search['name']) {
			$majv = $search['maj_ver'] ? $this->_browser_info['maj_ver'] : '';
			$minv = $search['min_ver'] ? $this->_browser_info['min_ver'] : '';
			$what_we_are = $majv.$minv;
			if(($search['direction'] == 'up' || $search['direction'] == '+') && ($what_we_are >= $looking_for))
				return true;
			elseif(($search['direction'] == 'dn' || $search['direction'] == '-') && ($what_we_are <= $looking_for))
				return true;
			elseif($what_we_are == $looking_for) return true;
		}
		return false;
	}

	function _perform_language_search($data) {
		$this->_get_languages();
		return stristr($this->_browser_info['language'],$data[1]);
	}

	function _get_languages() {
		if(!$this->_get_languages_ran_once) {
			if($languages = getenv('HTTP_ACCEPT_LANGUAGE'))
				$languages = preg_replace('/(;q=[0-9]+.[0-9]+)/i','',$languages);
			else $languages = $this->_default_language;
			$this->_set_browser('language',$languages);
			$this->_get_languages_ran_once = true;
		}
	}

	function _get_os_info() {
		$regex_windows = '/([^dar]win[dows]*)[\s]?([0-9a-z]*)[\w\s]?([a-z0-9.]*)/i';
		$regex_mac     = '/(68[k0]{1,3})|(ppc mac os x)|([p\S]{1,5}pc)|(darwin)/i';
		$regex_os2     = '/os\/2|ibm-webexplorer/i';
		$regex_sunos   = '/(sun|i86)[os\s]*([0-9]*)/i';
		$regex_irix    = '/(irix)[\s]*([0-9]*)/i';
		$regex_hpux    = '/(hp-ux)[\s]*([0-9]*)/i';
		$regex_aix     = '/aix([0-9]*)/i';
		$regex_dec     = '/dec|osfl|alphaserver|ultrix|alphastation/i';
		$regex_vms     = '/vax|openvms/i';
		$regex_sco     = '/sco|unix_sv/i';
		$regex_linux   = '/x11|inux/i';
		$regex_bsd     = '/(free)?(bsd)/i';

		// look for Windows Box
		if(preg_match_all($regex_windows,$this->_browser_info['ua'],$match)) {
			$v  = $match[2][count($match[0])-1];
			$v2 = $match[3][count($match[0])-1];
			if(stristr($v,'NT') && $v2 == 5.1) $v = 'xp';
			elseif($v == '2000') $v = '2000';
			elseif(stristr($v,'NT') && $v2 == 5.0) $v = '2000';
			elseif(stristr($v,'9x') && $v2 == 4.9) $v = '98';
			elseif($v.$v2 == '16bit') $v = '3_1';
			else $v .= $v2;
			if(empty($v)) $v = 'win';
			$this->_set_browser('os',strtolower($v));
			$this->_set_browser('platform','win');
		}
		// look for OS2
		elseif( preg_match($regex_os2,$this->_browser_info['ua'])) {
			$this->_set_browser('os','os2');
			$this->_set_browser('platform','os2');
		}
		// look for Mac
		elseif( preg_match($regex_mac,$this->_browser_info['ua'],$match) ) {
			$this->_set_browser('platform','mac');
			$os = !empty($match[1]) ? '68k' : '';
			$os = !empty($match[2]) ? 'osx' : $os;
			$os = !empty($match[3]) ? 'ppc' : $os;
			$os = !empty($match[4]) ? 'osx' : $os;
			$this->_set_browser('os',$os);
		}
		// look for *nix boxes
		// sunos sets: platform = *nix ; os = sun|sun4|sun5|suni86
		elseif(preg_match($regex_sunos,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			if(!stristr('sun',$match[1])) $match[1] = 'sun'.$match[1];
			$this->_set_browser('os',$match[1].$match[2]);
		}
		// irix sets: platform = *nix ; os = irix|irix5|irix6|...
		elseif(preg_match($regex_irix,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os',$match[1].$match[2]);
		}
		// hp-ux sets: platform = *nix ; os = hpux9|hpux10|...
		elseif(preg_match($regex_hpux,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$match[1] = str_replace('-','',$match[1]);
			$match[2] = (int) $match[2];
			$this->_set_browser('os',$match[1].$match[2]);
		}
		// aix sets: platform = *nix ; os = aix|aix1|aix2|aix3|...
		elseif(preg_match($regex_aix,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','aix'.$match[1]);
		}
		// dec sets: platform = *nix ; os = dec
		elseif(preg_match($regex_dec,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','dec');
		}
		// vms sets: platform = *nix ; os = vms
		elseif(preg_match($regex_vms,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','vms');
		}
		// sco sets: platform = *nix ; os = sco
		elseif(preg_match($regex_sco,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','sco');
		}
		// unixware sets: platform = *nix ; os = unixware
		elseif(stristr('unix_system_v',$this->_browser_info['ua'])) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','unixware');
		}
		// mpras sets: platform = *nix ; os = mpras
		elseif(stristr('ncr',$this->_browser_info['ua'])) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','mpras');
		}
		// reliant sets: platform = *nix ; os = reliant
		elseif(stristr('reliantunix',$this->_browser_info['ua'])) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','reliant');
		}
		// sinix sets: platform = *nix ; os = sinix
		elseif(stristr('sinix',$this->_browser_info['ua'])) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','sinix');
		}
		// bsd sets: platform = *nix ; os = bsd|freebsd
		elseif(preg_match($regex_bsd,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os',$match[1].$match[2]);
		}
		// last one to look for
		// linux sets: platform = *nix ; os = linux
		elseif(preg_match($regex_linux,$this->_browser_info['ua'],$match)) {
			$this->_set_browser('platform','*nix');
			$this->_set_browser('os','linux');
		}
	}

	function _get_browser_info() {
		$this->_build_regex();
		if(preg_match_all($this->_browser_regex,$this->_browser_info['ua'],$results)) {
			$count = count($results[0])-1;
			if($this->_allow_masquerading && $count > 0) $count--;
			$this->_set_browser('browser',$this->_get_short_name($results[1][$count]));
			$this->_set_browser('long_name',$results[1][$count]);
			$this->_set_browser('maj_ver',$results[2][$count]);
			preg_match('/([.\0-9]+)?([\.a-z0-9]+)?/i',$results[3][$count],$match);
			if(isset($match[1])) $this->_set_browser('min_ver',$match[1]);
			else $this->_set_browser('min_ver','.0');
			if(isset($match[2])) $this->_set_browser('letter_ver',$match[2]);
			$this->_set_browser('version',$this->_browser_info['maj_ver'].$this->property('min_ver'));
		}
	}

	function _get_ip() {
		$this->_set_browser('ip',$this->IP());
	}

	function checkPrivIP($ip) {
		if(ereg('^(127\.)',$ip)) return true;
		if(ereg('^(10\.)',$ip)) return true;
		if(ereg('^(192\.168\.)',$ip)) return true;
		if(ereg('^(172\.)'.'([0-9]{1,3})',$ip,$part)) {
			if(($part[2] > 15) and ($part[2] < 32)) return true;
		}
		return false;
	}

	function IP() { 
		if(getenv('HTTP_CLIENT_IP')) return getenv('HTTP_CLIENT_IP');
		elseif(getenv('HTTP_X_FORWARDED_FOR')) {
			$ips = explode(',',getenv('HTTP_X_FORWARDED_FOR'));
			foreach($ips as $key => $value)
				if(!$this->checkPrivIP($value)) return $value;
			return getenv('REMOTE_ADDR');
		}
		else return getenv('REMOTE_ADDR'); 
	}

	function _build_regex() {
		$browsers = '';
		foreach($this->_browsers as $k => $v) {
			if(!empty($browsers)) $browsers .= "|";
			$browsers .= $k;
		}
		$version_string = "[\/\sa-z(]*([0-9]+)([\.0-9a-z]+)?";
		$this->_browser_regex = "/($browsers)$version_string/i";
	}

	function _get_short_name($long_name) {
		return $this->_browsers[strtolower($long_name)];
	}

	function _test_cookies() {
		global $phpSniff_session,$phpSniff_stored;
		if($this->_check_cookies) {
			$fp = @fopen($this->_temp_file_path.$this->property('ip'),'r');
			if(!$fp) {
				$fp = @fopen($this->_temp_file_path.$this->property('ip'),'a');
				fclose($fp);
				setcookie('phpSniff_session','ss');
				setcookie('phpSniff_stored','st',time()+3600*24*365);
				$QS=getenv('QUERY_STRING');
				$script_path=getenv('PATH_INFO')?getenv('PATH_INFO'):getenv('SCRIPT_NAME');
				if(is_integer($pos=strpos(strrev($script_path),"php.xedni/"))&&!$pos)
					$script_path=strrev(substr(strrev($script_path),9));
				$location='http://'.getenv('SERVER_NAME').$script_path.($QS==''?'':'?'.$QS);
				header("Location: $location");
				exit;
			}
			else {
				unlink($this->_temp_file_path.$this->property('ip'));
				fclose($fp);
				$this->_set_browser('cookies',$phpSniff_session=='ss'?'true':'false');
				$this->_set_browser('ss_cookies',$phpSniff_session=='ss'?'true':'false');
				$this->_set_browser('st_cookies',$phpSniff_stored=='st'?'true':'false');
				setcookie('phpSniff_stored','');
			}
		}
	}

	function _get_javascript() {
		$set=false;
		foreach($this->_javascript_versions as $version => $browser) {
			$browser = explode(',',$browser);
			foreach($browser as $key => $search) {
				if($this->is('b:'.$search)) {
					$this->_set_browser('javascript',$version);
					$set = true;
					break;
				}
			}
			if($set) break;
		}
	}

	function _get_features() {
		foreach($this->_browser_features as $feature => $browser) {
			$browser = explode(',',$browser);
			foreach($browser as $key => $search) {
				if($this->browser_is($search)) {
					$this->_set_feature($feature);
					break;
				}
			}
		}
	}

	function _get_quirks() {
		foreach($this->_browser_quirks as $quirk => $browser) {
			$browser = explode(',',$browser);
			foreach($browser as $key => $search) {
				if($this->browser_is($search)) {
					$this->_set_quirk($quirk);
					break;
				}
			}
		}
	}

	function _get_gecko() {
		if(preg_match('/gecko\/([0-9]+)/i',$this->property('ua'),$match)) {
			$this->_set_browser('gecko',$match[1]);
			if(preg_match('/rv:([0-9a-z.+]+)/i',$this->property('ua'),$mozv))
				$this->_set_browser('gecko_ver',$mozv[1]);
			elseif (preg_match('/(m[0-9]+)/i',$this->property('ua'),$mozv))
				$this->_set_browser('gecko_ver',$mozv[1]);
			if(preg_match('/([0-9]+)([\.0-9]+)([a-z0-9+]+)/i',$mozv[1],$match)) {
				$this->_set_browser('version',$mozv[1]);
				$this->_set_browser('maj_ver',$match[1]);
				$this->_set_browser('min_ver',$match[2]);
				$this->_set_browser('letter_ver',$match[3]);
			}
		}
		elseif($this->is('b:'.$this->_get_short_name('mozilla'))) {
			$this->_set_browser('long_name','netscape');
			$this->_set_browser('browser',$this->_get_short_name('netscape'));
		}
	}

	function _set_browser($k,$v) {
		$this->_browser_info[strtolower($k)] = strtolower($v);
	}

	function _set_feature($k) {
		$this->_feature_set[strtolower($k)] = !$this->_feature_set[strtolower($k)];
	}

	function _set_quirk($k) {
		$this->_quirks[strtolower($k)] = true;
	}
}
?>