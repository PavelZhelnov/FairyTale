<?php

class AdminMenuItemsAction extends Action {

	public $Pages = array(
		'17' => array( /*Pages - admin menu items */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminMenuItemsAction($name='AdminMenuItemsAction') {
		$this->Action($name);
	}
}
?>