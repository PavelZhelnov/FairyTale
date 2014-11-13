<?php

class TrackingAction extends Action {

	public $Pages = array(
		'31' => array( /*Tracking - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	    ),
	);

	function TrackingAction($name='TrackingAction') {
		$this->Action($name);
	}
}
?>