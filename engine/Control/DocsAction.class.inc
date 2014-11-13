<?php
class DocsAction extends Action {

	public $Pages = array(
		'30' => array( /*Docs - client view*/
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function DocsAction($name='DocsAction') {
		$this->Action($name);
	}	

}
?>