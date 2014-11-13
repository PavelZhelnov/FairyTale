<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'19' => array (
				'view' => array (
					'handlerMethod' => 'selectQuotationsAdmin',
					'scheme' => 'default',
				),
				'get' => array (
					'handlerMethod' => 'getQuotation',
					'scheme' => 'edit',
				),
				'save' => array (
					'handlerMethod' => 'saveQuotation',
					'scheme' => 'default',
				),
				'delete' => array (
					'handlerMethod' => 'deleteQuotation',
					'scheme' => 'default',
				),
			),
		),
	),
);
?>