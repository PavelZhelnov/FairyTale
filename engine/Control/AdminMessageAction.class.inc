<?php
class AdminMessageAction extends Action {

	public $Pages = array(
		'14' => array( /*Message - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminMessageAction($name='AdminMessageAction') {
		$this->Action($name);
	}
}
?>