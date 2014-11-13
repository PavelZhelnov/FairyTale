<?php

class LangAction extends Action {

	public $Pages = array(
		'67' => array( /* Lang */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function LangAction($name='LangAction') {
		$this->Action($name);
	}
}
?>