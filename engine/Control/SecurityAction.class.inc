<?php

class SecurityAction extends Action {

	public $Pages = array(
		'2' => array(
			'scheme' => 'default',
			'forward_scheme' => 'default',
		),
	);

	function SecurityAction($name='SecurityAction') {
		$this->Action($name);
	}

	function sendRegisterMail($array) {
		$this->MailBroker->sendMail('plain',array($array['email1']),$array,true);
		$this->MailBroker->sendMail('register',array($array['email1']),$array);
		$this->MailBroker->sendMail('reg_notice',array('info@russiannj.com'),$array);
	}

	function sendRememberMail($array) {
		$this->MailBroker->sendMail('remember',array($array['email1']),$array);
	}
}
?>