<?php

class InvoicesAction extends Action {

	public $Pages = array(
		'22' => array( /* Invoices - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function InvoicesAction($name='InvoicesAction') {
		$this->Action($name);
	}
}
?>