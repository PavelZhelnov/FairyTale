<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'15' => array (
				'view' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectPagesToEdit',
					'scheme' => 'default',
				),
				'edit' => array (
					'handlerMethod' => 'getPage',
					'scheme' => 'edit',
					'minPerm' => 2,
				),
				'update' => array (
					'handlerMethod' => 'updatePage',
					'scheme' => 'default',
					'actionMethod' => 'sendPageChangedConfirm',
					'minPerm' => 8,
				),
				'delete' => array (
					'handlerMethod' => 'deletePage',
					'scheme' => 'default',
					'minPerm' => 16,
				),
			),
		),
	),
);
?>