<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'30' => array (
				'listdocuments' => array (
					'handlerMethod' => 'selectDocumentList',
					'scheme' => 'default',
				), 
				'set_search' => array (
					'handlerMethod' => 'setSearch',
					'scheme' => 'default',
				),
				'get_search' => array (
					'handlerMethod' => 'getSearch',
					'scheme' => 'default',
				),
				'settings' => array (
					'handlerMethod' => 'getSettings',
					'scheme' => 'default',
				),
			),
		),
	),
);
?>