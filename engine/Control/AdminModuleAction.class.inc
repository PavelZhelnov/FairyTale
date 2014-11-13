<?php
class AdminModuleAction extends Action {

	public $Pages = array(
		'24' => array( /*module - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminModuleAction($name='AdminModuleAction') {
		$this->Action($name);
	}
}
?>