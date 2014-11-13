<?php

class MessageAction extends Action {

	public $Pages = array(
		'13' => array( /* Message */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function MessageAction($name='MessageAction') {
		$this->Action($name);
	}
}
?>