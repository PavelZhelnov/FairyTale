<?php

class LogAction extends Action {

	public $Pages = array(
		'104' => array( /* Log - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function LogAction($name='LogAction') {
		$this->Action($name);
	}

}
?>