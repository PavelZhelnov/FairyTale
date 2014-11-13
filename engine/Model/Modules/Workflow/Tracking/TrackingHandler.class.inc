<?php

include_once($MODEL_PATH.'/Modules/Workflow/Tracking/Snoopy.class.inc');

include_once($MODEL_PATH.'/Security/Member.class.inc');

class TrackingHandler extends Handler {
	
	public $currentuser;
	
	function TrackingHandler($calledbyson=true){		
		$this->Handler($calledbyson);
		if ($calledbyson==true) {
			$this->currentuser = new User();
		}
	}

	function getInfo($request) {
		$this->cleanError($this->document);
		if(!empty($request['id'])) {
			$info = $this->DB->SelectAny('select * from tracking where id='.$request['id']);
			$info = $info[0];
			$buf='';
			
			switch ($request['id']) {
				case '1':$buf = $this->processMSC($info, $request); break; //OK
				case '2':$buf = $this->processSimpleGet($info, $request); break; //OK
				case '3':$buf = $this->processSimpleGet($info, $request); break; //OK cenwwwsvcbus@maersk.com
				case '4':$buf = $this->processNYK($info, $request); break; //OK
				case '5':$buf = $this->processCMACGM($info, $request); break; //OK
				case '6':$buf = $this->processNORASIA($info, $request); break; //OK
				case '8':$buf = $this->processSimpleGet($info, $request); break; //OK
				case '9':$buf = $this->processSenator($info, $request); break; //OK ? stefan.schlack@bre.senatorlines.com (customer service)
				case '10':$buf = $this->processKLine($info, $request); break; //OK
				case '11':$buf = $this->processHapagLloyd($info, $request); break; //X http://www.hapag-lloyd.com/en/contact_form_.htm, info.de@hlag.com
				case '12':$buf = $this->processEvergreen($info, $request); break; //OK
				case '13':$buf = $this->processAPL($info, $request); break; //X webmaster@apl.com
				case '14':$buf = $this->processSimpleGet($info, $request); break; //OK
				
				case '15':$buf = $this->processSimpleGet($info, $request); break;
				default:
					$data = ereg_replace("\{1\}", $request['presence'], $info['data']);
					$buf = $this->sendToHost($info['webaddress'], $info['method'], $info['path'], $data);
				break;
				
			}
			
			//PROCESSING
			$buf = $this->cutString($buf, $info['strfrom'], $info['strto'], $info['includefrom'], $info['includeto']);
			$siteurl = $this->DB->SelectAny('select * from tracking where id = '.$request['id']);
			$request['siteurl'] = $siteurl[0]['siteurl'];

			//$buf = str_replace("a href=\"", "a href=\"".$request['siteurl'], $buf);
			if ($request['id']!='15') {
				$request['info'] = $buf;
			} else {
				$request['pres'] = $this->postProcessPresence($buf);
			}
			return $request;
		}
		
		return $request;
	}
	
	function postProcessPresence($buf) {
		if (preg_match("/is present/i", $buf)) {
			$buf='container_exists';
		} else {
			$buf='container_absent';
		}
		return $buf;
	}
	
	
	function processSimpleGet($info, $request) {
			$snoopy = new Snoopy;
			$data = ereg_replace("\{1\}", $request['trackingnum'], $info['data']);
			
			$snoopy->referer = $info['webaddress'].'/';
			$submit_url = $info['webaddress'].$info['path'].'?'.$data;
			
			$snoopy->fetch($submit_url);
			
			$buf = $snoopy->results;
			return $buf;
	}


	function processMSC($info, $request) {
			$snoopy = new Snoopy;
			
			$submit_url = $info['webaddress'].$info['path'];
			$submit_vars['edBL'] = 'MSCU';
			$submit_vars['btSearchCtr'] = 'Search';
			$submit_vars['edCtr'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;
	}

	function processSenator($info, $request) {
			$snoopy = new Snoopy;
			
			$submit_url = $info['webaddress'].$info['path'];
			$submit_vars['numberType'] = 'C';
			$submit_vars['numberTypeNo'] = $request['trackingnum'];
			$submit_vars['cntrNo'] = $request['trackingnum'];

			$snoopy->referer = $info['webaddress'].'/';
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;
	}
	
	function processKLine($info, $request) {
			$snoopy = new Snoopy;
			$snoopy->fetch($info['webaddress'].'/');
			$buf = $snoopy->results;
			$sesspos = strpos($buf, 'jsessionid=');
			$endsesspos = strpos($buf, '" METHOD="POST"');
			//echo $sesspos.'-'.$endsesspos;
			$formaction = substr($buf, $sesspos+strlen('jsessionid='), $endsesspos-($sesspos+strlen('jsessionid=')) );
			
			$submit_url = $info['webaddress'].$info['path'];
			$submit_vars['SearchType'] = 'CN';
			$submit_vars['No2'] = '';
			$submit_vars['No3'] = '';
			$submit_vars['No4'] = '';
			$submit_vars['No5'] = '';
			$submit_vars['No6'] = '';
			$submit_vars['No7'] = '';
			$submit_vars['No8'] = '';
			$submit_vars['Action'] = 'Search';
			$submit_vars['SearchNo'] = '';
			$submit_vars['No1'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;
		
	}
	
	//TODO
	function processSearates($info, $request) {

			$snoopy = new Snoopy;
			$snoopy->fetch($info['webaddress'].'/');
			$buf = $snoopy->results;
			$sesspos = strpos($buf, 'jsessionid=');
			$endsesspos = strpos($buf, '" METHOD="POST"');
			//echo $sesspos.'-'.$endsesspos;
			//$formaction = substr($buf, $sesspos+strlen('jsessionid='), $endsesspos-($sesspos+strlen('jsessionid=')) );
			
			$submit_url = $info['webaddress'].$info['path'];
			$submit_vars['state'] = '';
			$submit_vars['sealine'] = '7';
			$submit_vars['searchtype'] = 'Container';
			$submit_vars['numb'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			//$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;

	}
	
	function processEvergreen($info, $request) {

			$snoopy = new Snoopy;
			$snoopy->fetch($info['webaddress'].'/');
			$buf = $snoopy->results;
			$sesspos = strpos($buf, 'jsessionid=');
			$endsesspos = strpos($buf, '" METHOD="POST"');
			//echo $sesspos.'-'.$endsesspos;
			//$formaction = substr($buf, $sesspos+strlen('jsessionid='), $endsesspos-($sesspos+strlen('jsessionid=')) );
			
			$submit_url = $info['webaddress'].$info['path'];
			
			
			$submit_vars['Area_vessel'] = 'Area';
			$submit_vars['email'] = 'Email+address';
			$submit_vars['view'] = '2';
			$submit_vars['CNTR'] = $request['trackingnum'];
			$submit_vars['TYPE'] = 'CNTR';
			$submit_vars['BL'] = '';
			$submit_vars['chgSearch'] = 'Cargo';
			$submit_vars['CargoNO'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			//$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;

	}
	
	function processCMACGM2($info, $request) {
			$snoopy = new Snoopy;
			$snoopy->fetch($info['webaddress'].'/');
			$buf = $snoopy->results;
			$sesspos = strpos($buf, 'jsessionid=');
			$endsesspos = strpos($buf, '" METHOD="POST"');
			//echo $sesspos.'-'.$endsesspos;
			//$formaction = substr($buf, $sesspos+strlen('jsessionid='), $endsesspos-($sesspos+strlen('jsessionid=')) );
			
			$submit_url = $info['webaddress'].$info['path'];
			
			$submit_vars['__WPPS'] = 's';
			$submit_vars['__LASTFOCUS'] = '02007132403';
			$submit_vars['ctl00_MainLeftMenu_LMenu_ExpandState'] = 'eunnunnnnn';
			$submit_vars['ctl00_MainLeftMenu_LMenu_SelectedNode'] = 'ctl00_MainLeftMenu_LMenun3';
			$submit_vars['__EVENTTARGET'] = '';
			$submit_vars['__EVENTARGUMENT'] = '';
			$submit_vars['ctl00_MainLeftMenu_LMenu_PopulateLog'] = '';
			$submit_vars['__VSTATE'] = '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';
			$submit_vars['ctl00_ContentPlaceBody_DListSearch'] = '';
			$submit_vars['ctl00_ContentPlaceBody_TextSearch'] = $request['trackingnum'];
			$submit_vars['ctl00_ContentPlaceBody_TextFormat'] = 'AAAA9999999';
			$submit_vars['ctl00_MainTopMenu_EnglishButton'] = '';
			$submit_vars['ctl00_MainTopMenu_FrenchButton'] = '';			
			$submit_vars['T'] = '02007132403';
			$submit_vars['ContNum'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			//$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;

	}


	function processCMACGM($info, $request) {
			$buf="<script language=\"javascript\">window.open('http://www.cma-cgm.com/eBusiness/Tracking/Default.aspx?ContNum=".$request['trackingnum']."','_blank','scrollbars=yes,resizable=no,status=yes,width=850,height=590');</script>";
			return $buf;

/*			$snoopy = new Snoopy;
			//$snoopy->fetch($info['webaddress'].'/');
			//$buf = $snoopy->results;
			//$sesspos = strpos($buf, 'jsessionid=');
			//$endsesspos = strpos($buf, '" METHOD="POST"');
			//echo $sesspos.'-'.$endsesspos;
			//$formaction = substr($buf, $sesspos+strlen('jsessionid='), $endsesspos-($sesspos+strlen('jsessionid=')) );
			
			$submit_url = $info['webaddress'].$info['path'];
			
			$submit_vars['__WPPS'] = 's';
			$submit_vars['__LASTFOCUS'] = '';
			$submit_vars['ctl00_MainLeftMenu_LMenu_ExpandState'] = 'eunnunnnnn';
			$submit_vars['ctl00_MainLeftMenu_LMenu_SelectedNode'] = 'ctl00_MainLeftMenu_LMenun3';
			$submit_vars['__EVENTTARGET'] = '';
			$submit_vars['__EVENTARGUMENT'] = '';
			$submit_vars['ctl00_MainLeftMenu_LMenu_PopulateLog'] = '';
			$submit_vars['__VSTATE'] = $sessionId;
			$submit_vars['__VIEWSTATE']= '';
			$submit_vars['ctl00_ContentPlaceBody_DListSearch'] = '';
			$submit_vars['ctl00_ContentPlaceBody_TextSearch'] = $request['trackingnum'];
			$submit_vars['ctl00_ContentPlaceBody_TextFormat'] = 'AAAA9999999';
			$submit_vars['ctl00_MainTopMenu_EnglishButton'] = '';
			$submit_vars['ctl00_MainTopMenu_FrenchButton'] = '';			
			//$submit_vars['T'] = '02007132403';
			$submit_vars['ContNum'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			//$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			echo $buf;
			die();
			return $buf;*/

	}
	
	function processAPL($info, $request) {

			return "";
			/*$snoopy = new Snoopy;
			$data = ereg_replace("\{1\}", $request['trackingnum'], $info['data']);
			$first_url = 'http://homeport.apl.com/gentrack/trackingMain.do?trckSingleInput='.$request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			$submit_url = $first_url;
			$snoopy->maxframes=5;
		
			//$snoopy->fetch($submit_url);
			//$buf = $snoopy->results[4];
			//$buf = str_replace("FRAME", "..", $buf);
			//second			

			$snoopy = new Snoopy;
			$submit_url = $info['webaddress'].$info['path'];
			$snoopy->lastredirectaddr = $first_url;
			$snoopy->referer = $info['webaddress'].'/';
			//$submit_vars['popupFlag'] = 'false';
			//$submit_vars['blNbr'] = '';
			//$submit_vars['trackInput01'] = $request['trackingnum'];
			//$submit_vars['TRACOBJ0'] = $request['trackingnum'];

			//$submit_vars['cntrNbr'] = $request['trackingnum'];
			$submit_vars['REQTYPE'] = 'blcntr';
			$submit_vars['TRACE'] = $request['trackingnum'];
			//$submit_vars['cntrNbr'] = '';

			$snoopy->fetch($submit_url);
			
			$buf = $snoopy->results;
			
			echo $buf;
			die();
			return $buf;

			/*$snoopy = new Snoopy;
			
			$submit_url = $info['webaddress'].$info['path'];
			
			
			$submit_vars['TRACOBJ0'] = $request['trackingnum'];
			$submit_vars['TRACOBJ1'] = '';
			$submit_vars['TRACOBJ2'] = '';			
			$submit_vars['TRACOBJ3'] = '';
			$submit_vars['TRACOBJ4'] = '';
			$submit_vars['TRACOBJ5'] = '';
			$submit_vars['TRACOBJ6'] = '';
			$submit_vars['TRACOBJ7'] = '';
			$submit_vars['TRACOBJ8'] = '';
			$snoopy->referer = $info['webaddress'].'/';
			//$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;
*/
	}	
	
	function processNORASIA($info, $request) {
		
			$snoopy = new Snoopy;
			$snoopy->referer = $info['webaddress'].'/';
			$submit_url = 'http://www.csavnorasia.com/rastreo/rastreo.nsf/yourtrace?openagent&'.$request['trackingnum'];
			$snoopy->fetch($submit_url);
			
			$buf = $snoopy->results;
			
			$sessionId = $this->cutString($buf, '<FORM onSubmit="return false;" METHOD=post ACTION="/rastreo/rastreo.nsf/viewTrace/', '?EditDocument&Seq=1" NAME="_YourTrace"', 0,0);
			return $buf;
			
			/*
			$snoopy = new Snoopy;
			$snoopy->fetch($info['webaddress'].'/');
			$buf = $snoopy->results;
			//echo $sesspos.'-'.$endsesspos;
			//$formaction = substr($buf, $sesspos+strlen('jsessionid='), $endsesspos-($sesspos+strlen('jsessionid=')) );
			
			$submit_url = $info['webaddress'].$info['path'].$sessionId;
			
			$submit_vars['__Click'] = '0';
			//$submit_vars['%%ModDate'] = '842572BB00443392';
			$submit_vars['YourTrace'] = $request['trackingnum'];
			
			$submit_vars['MULTICSS'] = '<link href="/norasia.css" rel="stylesheet" type="text/css">';
			$submit_vars['MULTIJS'] = '<SCRIPT type="Text/Javascript" SRC="/norasia.js"></SCRIPT>';
			$submit_vars['HTTP_Cookie'] = 'MULTICSS=norasia.css; MULTIJS=norasia.js; MULTIFolder=/; MULTICarrier=NCLL';
			$submit_vars['MULTIFolder'] = '/';
			$submit_vars['MULTILenguaje'] = 'EN-US';
			$submit_vars['Tracking'] = '';
			$submit_vars['TrackingAux'] = 'Tracking';
			$submit_vars['Search'] = '';
			$submit_vars['SearchAux'] = 'Search';
			$submit_vars['Profile'] = '';
			$submit_vars['MULTIFolderMenu'] = '/';
			$submit_vars['profile1024'] = '';
			$submit_vars['profile800'] = '';
			$submit_vars['DSPCarrier'] = 'NORASIA';
			$submit_vars['maximum_number_to_track'] = '75';
			$submit_vars['lblInstructions'] = '<ul><li>Type your container, booking or B/L number into the box provided and hit the "Tracking" button.<li>Want to track multiple containers, bookings or multiple B/L\'s at the same time ?<ol><li>Type your B/L, booking or container numbers into the box, hitting "enter" between each one. </li><li>You can even cut and paste up to 75 different numbers into the tracking box.</li></ol><li>Pls. do not include \'spaces\', \'-\', \' \' or \'/ \' in the numbers.</li>';
			$submit_vars['IMG'] = '[<img border=0 name="imgSub" src="/imagenes/botones_interior/tracking_off.gif">]';
			//$submit_vars['Reporte'] = '<br><br><br><div class=titulo2>&nbsp; No data available for Container <b>TTNU3740842</b></div><br><br><br><table class="etiqueta2"><tr><td><br><br></td></tr></table>';
			$submit_vars['remote_addr'] = '195.114.129.166';
			$submit_vars['remote_host'] = '';
			$submit_vars['remote_user'] = '';
			$submit_vars['server_name'] = 'www.csavnorasia.com';
			$submit_vars['database_name'] = 'rastreo\rastreo.nsf';
			$submit_vars['ID'] = '';
			$submit_vars['web_agent_timeout'] = '60';
			$submit_vars['lblAdvisory'] = 'Advisory: To protect the privacy of your information and the security of your cargo\'s tracking module only supplies operational information in the public domain. For this reason, no direct links exist between your BL and container numbers (or vice versa) on this module.';
			$submit_vars['lblObsPublic'] = "Should you have any problems, please <a href='/web/newcsav.nsf/contactus?openform'>contact us</a>.<br>Please note that an input lag period does sometimes exist between the movement of a container and the updating of that movement on the web.";
			
			$snoopy->referer = $info['webaddress'].'/';
			//$snoopy->cookies["SessionID"] = $formaction;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			echo $buf;
			die();


			$buf = '/rastreo/rastreo.nsf/a75dbc4271575c4704256a880056dc78/9ef2f98bd429de7a04257158001737ef?OpenDocument';
			
			$snoopy = new Snoopy;
			$snoopy->referer = $info['webaddress'].'/';
			$submit_url = $info['webaddress'].$buf;
			
			$snoopy->fetch($submit_url);
			
			$buf = $snoopy->results;
			
			return $buf; */
	}		
	
	
	function processNYK($info, $request) {
		//http://www2.nykline.com/ct/containerSearchForm.nyk
			$snoopy = new Snoopy;
			$snoopy->referer = $info['webaddress'].'/';
			$submit_url = 'http://www2.nykline.com/ct/containerSearchForm.nyk';
			$snoopy->fetch($submit_url);
			
			$buf = $snoopy->results;
			
			$sessionStr = $this->cutString($buf, 'jsessionid=', '<!-- END TOP NAV; START CONTENT AREA -->', 0,0);
  		$sessionStr = preg_replace("[\"\>]","",$sessionStr);
			$sessionId = substr($sessionStr, 0, strpos($sessionStr, "?"));
						
			$snoopy = new Snoopy;
			
			$submit_url = $info['webaddress'].$info['path'];//.$sessionId;
			$submit_vars['I1l'] = substr($sessionStr, strpos($sessionStr, 'I1l=')+4);			
			$submit_vars['searchBy'] = 'Container';
			$submit_vars['searchNumbers[0].number'] = $request['trackingnum'];
			$submit_vars['butFilter'] = 'Retrieve Movement Information';
			
			$snoopy->referer = $info['webaddress'].'/';
			$snoopy->cookies["SessionID"] = $sessionId;
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;
	
	}
	
	function processHapagLloyd($info, $request) {
			return "";
			/*$snoopy = new Snoopy;
			$snoopy->referer = $info['webaddress'].'/';
			$submit_url = 'http://www.hapag-lloyd.com/inet/DispatchServlet?id_tc=UPPER_MENU_Tracing&language=';
			//$requestId = $this->cutString($buf, "requestId=", "" NAME="OLB_CONTENT"",0,0);
			//$submit_vars['language'] = 'I';
			//$submit_vars['javascript'] = 'Y';
			//$submit_vars['dyn'] = '';
			//$submit_vars['MU:EContainer_ContainerNumber'] = $request['trackingnum'];

			$snoopy->fetch($submit_url);
			
			$buf = $snoopy->results;
			echo $buf;
			die();

			$snoopy = new Snoopy;
			
			$submit_url = $info['webaddress'].$info['path'];
			$submit_vars['language'] = 'I';
			$submit_vars['javascript'] = 'Y';
			$submit_vars['dyn'] = '';
			$submit_vars['MU:EContainer_ContainerNumber'] = $request['trackingnum'];
			
			$snoopy->referer = $info['webaddress'].'/';
			$snoopy->rawheaders["Pragma"] = "no-cache";
			$snoopy->maxredirs = 2;
			$snoopy->offsiteok = false;
			$snoopy->expandlinks = false;

			$snoopy->submit($submit_url, $submit_vars);
			
			$buf = $snoopy->results;
			return $buf;*/
	}
	
	
	
	
	function cutString($buf, $strfrom, $strto, $inclfrom, $inclto) {
			$from = $inclfrom=='1'?strpos($buf, $strfrom):strpos($buf, $strfrom)+strlen($strfrom);
			$to = $inclto=='0'?strpos($buf, $strto):strpos($buf, $strto)+strlen($strto);
			if ($strfrom=='') $from = 0;
			if ($strto=='') $to=strlen($buf);
			//TODO 
			$buf = substr($buf, 
				$from,
				$to-$from
			    );
			return $buf;
	}
	
	
	
	function sendToHost($host,$method,$path,$data,$useragent=0)
	{
	    // Supply a default method of GET if the one passed was empty
	    if (empty($method)) {
	        $method = 'GET';
	    }
	    $method = strtoupper($method);
	    $fp = fsockopen($host,80);
	    if ($method == 'GET' and $data!='') {
	        $path .= '?' . $data;
	    }
	    fputs($fp, "$method $path HTTP/1.1\r\n");
	    fputs($fp, "Host: $host\r\n\r\n");
	    fputs($fp,"Content-type: application/x-www-form- urlencoded\r\n");
	    fputs($fp, "Content-length: " . strlen($data) . "\r\n");
	    if ($useragent) {
	        fputs($fp, "User-Agent: MSIE\r\n");
	    }
	    fputs($fp, "Connection: close\r\n\r\n");
	    if ($method == 'POST' and $data!='') {
	        fputs($fp, $data);
	    }
		$buf='';
	    while (!feof($fp)) {
	        $buf .= fgets($fp,128);
	    }
	    fclose($fp);
	    return $buf;
	}	
	
	function getServices($request) {
		$selected = $this->DB->SelectAny('select id, trackingname, siteurl, showurl from tracking where showinlist=1 order by id ');
		return $selected;
	}

	
	function createUser() {
		$user = new User();
		return $user;
	}

	function MakeHash()	{
		return md5(time());
	}
	
}
?>