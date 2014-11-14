<?php

	//ini_set("zlib.output_compression","On");
	//ini_set("zlib.output_compression_level","9");
	//ob_start(array('ob_gzhandler','3'));
	ini_set('session.gc_maxlifetime', '3600');
	ini_set('date.timezone', 'America/Chicago');
	register_shutdown_function('handleShutdown');
	
	 
	function currentTime() {
		$time = gettimeofday();
		return $time['sec'] + $time['usec']/1000000;
	}
	$time0 = currentTime();
	//echo $SERVER_NA;
	$ROOT_PATH = ereg_replace('/eng$|/rus$|/ukr$','',$SCRIPT_FILENAME);
	$CORE_PATH = $ROOT_PATH.'/engine';	
	$HOME_PATH = ereg_replace('/fairytale/','',$SCRIPT_NAME);
		
	$WEB_ROOT = '/fairytale';
	$TOOLS_PATH = $CORE_PATH.'/Tools';
	$MODEL_PATH = $CORE_PATH.'/Model';
	$CONTROL_PATH = $CORE_PATH.'/Control';
	$DB_PATH = $CORE_PATH.'/DB';
	//$ROOT_PATH = ereg_replace('/eng$|/rus$','',$SCRIPT_FILENAME);	
	//$CORE_PATH = $ROOT_PATH.'/engine';
	//$HOME_PATH = ereg_replace('/','',$SCRIPT_NAME);
	//$WEB_ROOT = substr($REQUEST_URI,0,- strlen(stristr($REQUEST_URI,'/'.$HOME_PATH)));

	include_once($CORE_PATH.'/Common.inc');
	include_once($TOOLS_PATH.'/General.functions.inc');
	include_once($TOOLS_PATH.'/Thumbnail.class.inc');
	include_once($TOOLS_PATH.'/ThumbnailBMP.class.inc');
	include_once($TOOLS_PATH.'/WrappedText.class.inc');
	include_once($TOOLS_PATH.'/Object.functions.inc');
	include_once($TOOLS_PATH.'/Permission.functions.inc');
	include_once($TOOLS_PATH.'/Array.functions.inc');
	include_once($TOOLS_PATH.'/Validation.functions.inc');
	include_once($TOOLS_PATH.'/Form.functions.inc');
	include_once($TOOLS_PATH.'/Text.functions.inc');
	include_once($CORE_PATH.'/RootRegistry.class.inc');
	include_once($DB_PATH.'/DatabaseBroker.class.inc');
	include_once($CORE_PATH.'/RequestBroker.class.inc');
	include_once($CORE_PATH.'/MailBroker.class.inc');
	include_once($CORE_PATH.'/Slot.class.inc');
	include_once($CORE_PATH.'/Server.class.inc');

	$time1 = currentTime();
	$dt1 = $time1 - $time0;

	header("Expires: Mon, 26 Jul 1997 05:00:00 GMT",true);
	header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT",true);
	header("Cache-Control: no-store, no-cache, must-revalidate, proxy-revalidate",true);
	header("Cache-Control: post-check=0, pre-check=0", true);
	header("Cache-Control: max-age=0",true);
	header("Pragma: no-cache",true);

	$RequestBroker = new RequestBroker();
	$DatabaseBroker = new DatabaseBroker();
	$MailBroker = new MailBroker();

	session_register('Server');
	onceObject($Server,'Server');
	if($Server->LM->language != $HOME_PATH) $Server->setLM($Server->LM->Langs);

	//echo "ROOT_PATH - ".$ROOT_PATH."<br>";
	//echo "CORE_PATH - ".$CORE_PATH."<br>";
	//echo "HOME_PATH - ".$HOME_PATH."<br>";
	//echo "WEB_ROOT - ".$WEB_ROOT;

	$time2 = currentTime();
	$dt2 = $time2 - $time1;

	$render = renderSlot(':virtual','',TRUE);
	print $render;
	$time3 = currentTime();
	$dt3 = $time3 - $time2;
	if(empty($REGISTRY['Core']['Debug'])) return;
	$dt4 = $REGISTRY['SQLtime'];
	//phpinfo();
	$time4 = currentTime();
	$dt5 = $time4 - $time3;
	//print "<!-- " . round($dt1 + $dt2 + $dt3,6) . " -->";
/*	print "\n<br>\n<table border=\"1\" cellpadding=\"2\" cellspacing=\"0\"><tr><td colspan=\"2\"><b>Time spent</b></td></tr>"
		. "<tr><td>include</td><td>".round($dt1, 6)." sec</td></tr>"
		. "<tr><td>init</td><td>".round($dt2, 6)." sec</td></tr>"
		. "<tr><td>sql</td><td>".round($dt4, 6)." sec</td></tr>"
		. "<tr><td>render</td><td>".round(abs($dt3 - $dt4), 6)." sec</td></tr>"
		. "<tr><td><b>total</b></td><td>".round($dt1 + $dt2 + $dt3, 6)." sec</td></tr>"
		. "</table>";
		*/
	//printArray(get_declared_classes());
	//debugArray($REGISTRY["PreparedTemplates"]);
	//print debugContent();
	//printArray($REGISTRY['Request']['Target']);
	//printArray($DEBUG);
	//print '<li>'.count($Server->Control,1);
	//print '<li>'.count($Server->Model,1);
	//phpinfo();
	//ob_end_flush();
	 function handleShutdown() {
            $error = error_get_last(); //printArray($error );
            if ($error !== NULL && !empty($error)) {
            	mail("willy2005@gmail.com","Adminmls:error",implode(";", $error));
            }
            if($error !== NULL &&  ($error['type'] == 1)){
                $info = "[SHUTDOWN] file:".$error['file']." | ln:".$error['line']." | msg:".$error['message'] .PHP_EOL;
                echo "<h3>Opps! The error happened on the server. </h3><br>
                        Please restart your browser and try to process previous steps. If the message appears again, consult with web developer ( <a href='mailto:info@adminmls.com'>info@adminmls.com</a>) <br><br>";
                mail("willy2005@gmail.com","Adminmls:error",$info);
            }
            else{
                //echo "SHUTDOWN";
            }
     }	
?>