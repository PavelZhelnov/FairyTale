<?php

class AdminAction extends Action {

	public $Pages = array(
		'3' => array( /*Admin Action */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminAction($name='AdminAction') {
		$this->Action($name);
	}
}
?>