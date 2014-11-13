<?php
class HeaderAction extends Action {

	public $Pages = array(
		'6' => array( /*Header - client view*/
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function HeaderAction($name='HeaderAction') {
		$this->Action($name);
	}	

}
?>