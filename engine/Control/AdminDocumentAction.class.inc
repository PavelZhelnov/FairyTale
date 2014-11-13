<?php
class AdminDocumentAction extends Action {

	public $Pages = array(
		'29' => array( /*Documents - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminDocumentAction($name='AdminDocumentAction') {
		$this->Action($name);
	}	

}
?>