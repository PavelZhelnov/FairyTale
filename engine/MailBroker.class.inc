<?php
include_once($CORE_PATH.'/XTemplate.class.inc');
include_once($TOOLS_PATH.'/File.functions.inc');

class MailBroker extends XTemplate {

	const SUBJECT_FIELD = 'subject';
	const TEXT_FIELD = 'text';
	const FROM_FIELD = 'from';
	const FROM_EMAIL_FIELD = 'email';
	const FROM_FIRST_NAME_FIELD = 'first_name';
	const FROM_LAST_NAME_FIELD = 'last_name';
	const DEFAULT_MAIL_FROM = 'info@memphisreo.com';
	
	public $Templates = array();
	public $Properties = array();
	public $frommail;
	public $MSprior = array('1' => 'High','3' => 'Normal','5' => 'Low');

	function MailBroker() {
		global $REGISTRY;
		$Registry = loadObjectRegistry('MailBroker');
		$this->Templates = $Registry['Templates'];
		$this->Properties = $Registry['Properties'];
		$this->frommail = $REGISTRY['Core']['frommail'];
	}

	function sendMail($task = 'default',$arrayMail = array(),$arrayData = array(),$plain = false) {
		$parser = new XTemplate(readCacheFile($this->Templates[$task],templatePath(array('MailBroker/'))));
		$els = &$parser->getElements();
		$body = $parser->parseTemplate($arrayData,templatePath(array('MailBroker/')));
		if (isset($arrayData[MailBroker::TEXT_FIELD])) $body_text = $arrayData[MailBroker::TEXT_FIELD];
		$subj = (isset($arrayData[MailBroker::SUBJECT_FIELD])?$arrayData[MailBroker::SUBJECT_FIELD]:$this->Properties[$task][MailBroker::SUBJECT_FIELD]);
		$fromEmail = isset($arrayData[MailBroker::FROM_FIELD])?$arrayData[MailBroker::FROM_FIELD][MailBroker::FROM_EMAIL_FIELD]:MailBroker::DEFAULT_MAIL_FROM;
		$headers= "Return-Path: <".$fromEmail.">\r\n";
		$headers.= "Reply-To: ".$fromEmail."\r\n";
		$headers.= isset($arrayData[MailBroker::FROM_FIELD])?'From: "'.$arrayData[MailBroker::FROM_FIELD][MailBroker::FROM_FIRST_NAME_FIELD].' '.$arrayData[MailBroker::FROM_FIELD][MailBroker::FROM_LAST_NAME_FIELD]."\" <$fromEmail>\r\n":
			 "From: ".MailBroker::DEFAULT_MAIL_FROM."\r\n";		
		$headers.= "MIME-Version: 1.0\r\n";		
		//$headers.= $plain? "Content-type: text/plain; charset=windows-1251\r\n" : "Content-type: text/html; charset=windows-1251\r\n";		
		//$headers.= $plain? "Content-Transfer-Encoding: 8bit\r\n" : "";
		
		if (is_array($arrayMail )) {
			foreach($arrayMail as $key => $subscriber)
			{
				$email = (isset($subscriber[MailBroker::FROM_EMAIL_FIELD])&&strlen($subscriber[MailBroker::FROM_EMAIL_FIELD])>1)?$subscriber[MailBroker::FROM_EMAIL_FIELD]:$subscriber;
				mail($email,$subj,$body,$headers);
				//echo "EMAIL:".$email."\r\n Subject:".$subj."\r\n body:".$body."\r\n Headers:".$headers;
				//appendFile("email.log", "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
				//appendFile("email.log", "EMAIL:".$email."\r\n Subject:".$subj."\r\n body:".$body."\r\n Headers:".$headers);
			}
		} else {
			mail($arrayMail,$subj,$body,$headers);
			//echo "EMAIL:".$arrayMail."\r\n Subject:".$subj."\r\n body:".$body."\r\n Headers:".$headers;
			//appendFile("email.log", "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
			//appendFile("email.log", "EMAIL:".$arrayMail."\r\n Subject:".$subj."\r\n body:".$body."\r\n Headers:".$headers);
		}		
	}
}
?>