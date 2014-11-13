<?php

class GlobalSystemSettingsAction extends Action {

	public $Pages = array(
		'103' => array( /* GlobalSystemSettings - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function GlobalSystemSettingsAction($name='GlobalSystemSettingsAction') {
		$this->Action($name);
	}

}
?>