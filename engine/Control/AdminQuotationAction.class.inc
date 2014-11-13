<?php

class AdminQuotationAction extends Action {

	public $Pages = array(
		'19' => array( /*Quotation - admin edit */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function AdminQuotationAction($name='AdminQuotationAction') {
		$this->Action($name);
	}
}
?>