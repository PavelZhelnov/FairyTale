<?php

class AdminSubscriptionAction extends Action {

	public $Pages = array(
		'18' => array( /*Subscription - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminSubscriptionAction($name='AdminSubscriptionAction') {
		$this->Action($name);
	}
	
	function sendSubscriptionMail($array) {
		$this->MailBroker->sendMail('subscriptionmail',$array['subscribers'],$array);
	}

	function sendSubscriptionAuth($array) {
		$this->MailBroker->sendMail('subscriptionauth',array($array['email']),$array);
		//$this->MailBroker->sendMail('feedbackconfirm',array($array['email']),$array);
	}

}
?>