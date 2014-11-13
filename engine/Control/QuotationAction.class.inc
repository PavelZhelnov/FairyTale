<?php

class QuotationAction extends Action {

	public $Pages = array(
		'13' => array( /*Quotation - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	    ),
	);

	function QuotationAction($name='QuotationAction') {
		$this->Action($name);
	}
}
?>