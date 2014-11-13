<?php

global $TOOLS_PATH;
include_once($TOOLS_PATH.'/Sniff.core.inc');

class Sniff extends SniffCore {

	public $_temp_file_path	 = '/tmp/';
	public $_check_cookies		 = NULL;
	public $_default_language	 = 'en-us';
	public $_allow_masquerading = NULL;
	public $_php_version		 = '';

	public $_browsers = array(
		'microsoft internet explorer' => 'IE',
		'msie'						  => 'IE',
		'netscape6'					  => 'NS',
		'netscape'					  => 'NS',
		'mozilla'					  => 'MZ',
		'opera'						  => 'OP',
		'konqueror'					  => 'KQ',
		'icab'						  => 'IC',
		'lynx'						  => 'LX',
		'links'						  => 'LI',
		'ncsa mosaic'				  => 'MO',
		'amaya'						  => 'AM',
		'omniweb'					  => 'OW',
		'hotjava'					  => 'HJ',
		'browsex'					  => 'BX',
	);

	public $_javascript_versions = array(
		'1.5' => 'IE5.5UP,NS5UP,MZ5UP',
		'1.4' => '',
		'1.3' => 'NS4.05UP,OP5UP,IE5UP',
		'1.2' => 'NS4UP,IE4UP',
		'1.1' => 'NS3UP,OP,KQ',
		'1.0' => 'NS2UP,IE3UP',
		'0'   => 'LI,LX,HJ'	
	);

	public $_browser_features = array(
		'html'		=>	'',
		'images'	=>	'LI,LX',
		'frames' 	=>	'LI,LX',
		'tables'	=>	'',
		'java'		=>	'OP3,LI,LX,NS1,MO,IE1,IE2',
		'plugins'	=>	'IE1,IE2,LI,LX',
		'css2'		=>	'NS5UP,IE5UP',
		'css1'		=>	'NS4UP,IE4UP',
		'iframes'	=>	'IE3UP,NS5UP',
		'xml'		=>	'IE5UP,NS5UP',
		'dom'		=>	'IE5UP,NS5UP',
		'hdml'		=>	'',
		'wml'		=>	''
	);

	public $_browser_quirks = array(
		'must_cache_forms'			=>	'NS',
		'avoid_popup_windows'		=>	'IE3,LI,LX',
		'cache_ssl_downloads'		=>	'IE',
		'break_disposition_header'	=>	'IE5.5',
		'empty_file_input_value'	=>	'KQ',
		'scrollbar_in_way'			=>	'IE6'
	);

	function Sniff($UA='',$settings = true) {
		if(is_array($settings)) {
			$run = true;
			extract($settings);
			$this->_check_cookies = $check_cookies;
			$this->_default_language = $default_language;
			$this->_allow_masquerading = $allow_masquerading;
		}
		else $run = $settings;
		if(empty($UA)) $UA = getenv('HTTP_USER_AGENT');
		if(empty($UA)) {
			$pv = explode(".", PHP_VERSION);
			$UA = ($pv[0] > 3 && $pv[1] > 0 )? $_SERVER['HTTP_USER_AGENT'] : $HTTP_SERVER_VARS['HTTP_USER_AGENT'];
		}
		if(empty($UA)) return false;
		$this->_set_browser('ua',$UA);
		if($run) $this->init();
	}
}
?>