<?php

class NewsAction extends Action {

	public $Pages = array(
		'12' => array( /*News - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function NewsAction($name='NewsAction') {
		$this->Action($name);
	}
}
?>