<?php

class MenuAction extends Action {

	public $Pages = array(
		'10' => array( /* Menu */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function MenuAction($name='MenuAction') {
		$this->Action($name);
	}
}
?>