<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'16' => array (
				'view' => array (
					'handlerMethod' => 'selectNews',
					'scheme' => 'default',
				),
				'edit' => array (
					'handlerMethod' => 'getNews',
					'scheme' => 'edit',
				),
				'save' => array (
					'handlerMethod' => 'saveNews',
					'scheme' => 'default',
				),
				'delete' => array (
					'handlerMethod' => 'deleteNews',
					'scheme' => 'default',
				),
			),
		),
	),
);
?>