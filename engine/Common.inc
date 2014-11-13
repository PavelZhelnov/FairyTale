<?php
ini_set("register_globals","1");
error_reporting(0);
error_reporting(E_STRICT | E_ALL);
$Debug = false;
//$Debug = true;

$REGISTRY = array();
$REGISTRY['SQLtime'] = '0';

$REGISTRY["Core"] = array (
	'Language' => $HOME_PATH,
	'Path' => $CORE_PATH,
	'ObjectsPath' => $CORE_PATH.'/View/Objects',
	'RegistryPath' => $CORE_PATH.'/View/Registry',
	'ImagePath' => $ROOT_PATH.'/i',
	'ImageWPath' => $WEB_ROOT.'/i',
	"WebRoot" => $WEB_ROOT,
	"WebHome" => $WEB_ROOT.'/'.$HOME_PATH,
	'WXmlPath' => $WEB_ROOT.'/xml',
	'XmlPath' => $ROOT_PATH.'/xml',
	"TemplatesDirDefault" => $CORE_PATH."/Templates",
	"UseCache" => FALSE,
	"TemplateExtension" => ".html",
	"RegistryExtension" => ".registry.inc",
	"RegistryFile" => $CORE_PATH."/Registry.inc",
	"ClassExtension" => ".class.inc",
	"TargetThruQuery" => FALSE,
	"ScriptExt" => ".php",
	"IndexFile" => "/index",
	"SupportLanguages" => TRUE,
	"TitleDelimiter" => " - ",
	"SiteName" => "Fairy Tale",
	"adminemail" => "info@fairytale.com.ua",
	"frommail" => "\"FairyTale\"" . "<"."info@fairytale.com.ua".">",
	'HostName' => 'http://www.fairytale.com.ua',
	"Debug" => TRUE,
);

$REGISTRY["RequestSettings"]["Parameters"] = array (
	"o" => "object"
);
$REGISTRY["Languages"] = array();
$REGISTRY["Messages"] = array (
	"Slot" => array (
		"TemplateNotSet" => "<b>Error:</b> Slot \"%s\": Template \"%s\" is not set.",
		"TemplateFileNotExist" => "<b>Error:</b> Slot \"%s\": Template %s does not exist."
	)
);
$REGISTRY['FileCache'] = array();
$REGISTRY['Objects'] = array();
$REGISTRY['Globals'] = array (
	'static' => array (
		'siteName' => $REGISTRY['Core']['SiteName'],
		'serverPath' => getenv('HTTP_HOST'),
		'picPath' => $WEB_ROOT.'/i',
		'homePath' => $WEB_ROOT.'/'.$HOME_PATH,
		'rootPath' => $WEB_ROOT,
		'lang' => $HOME_PATH,
		'leftS' => '{',
		'rightS' => '}',
		'uni' => md5(uniqid('unique',1)),
		'currentTime' => date("M d, Y H:i"),
		'currentYear' => '2003'.(date("Y") > 2003? ' - '.date("Y") : ''),
	),
	'dynamic' => array()
);
$REGISTRY['Globals']['static']['formEnd'] = '<input type="hidden" name="uni" value="'.$REGISTRY['Globals']['static']['uni'].'"></form>';
$DEBUG = array();
include_once($CORE_PATH."/Registry.inc");

?>
