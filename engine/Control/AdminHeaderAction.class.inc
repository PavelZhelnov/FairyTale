<?php
class AdminHeaderAction extends Action {

	public $Pages = array(
		'11' => array( /*Header image- admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminHeaderAction($name='AdminHeaderAction') {
		$this->Action($name);
	}
}
?>