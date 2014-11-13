<?php

class AdminMemberAction extends Action {

	public $Pages = array(
		'21' => array( /*Member - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminMemberAction($name='AdminMemberAction') {
		$this->Action($name);
	}
}
?>