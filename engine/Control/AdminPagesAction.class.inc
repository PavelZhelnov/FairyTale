<?php

class AdminPagesAction extends Action {

	public $Pages = array(
		'15' => array( /*Pages - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminPagesAction($name='AdminPagesAction') {
		$this->Action($name);
	}
}
?>