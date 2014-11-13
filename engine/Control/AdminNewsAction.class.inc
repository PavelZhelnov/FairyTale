<?php

class AdminNewsAction extends Action {

	public $Pages = array(
		'16' => array( /*News - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminNewsAction($name='AdminNewsAction') {
		$this->Action($name);
	}
}
?>