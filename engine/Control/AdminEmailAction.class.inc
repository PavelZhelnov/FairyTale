<?php
class AdminEmailAction extends Action {

	public $Pages = array(
		'19' => array( /*Email - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminEmailAction($name='AdminEmailAction') {
		$this->Action($name);
	}
}
?>