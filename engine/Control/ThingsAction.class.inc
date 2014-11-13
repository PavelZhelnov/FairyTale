<?php

class ThingsAction extends Action {

	public $Pages = array(
		'5' => array( /*Things - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function ThingsAction($name='ThingsAction') {
		$this->Action($name);
	}
	
	function sendOnlineRequest($array) {
		if (isset($array['email'])) 
			$this->MailBroker->sendMail('onlinerequest',$array['emailto'],$array);
	}	
	function sendVacancy($array) {
		if (isset($array['email'])) 
			$this->MailBroker->sendMail('vacancy',$array['emailto'],$array);
	}	

}
?>