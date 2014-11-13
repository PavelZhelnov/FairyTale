<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'17' => array (
				'view' => array (
					//'minPerm' => 2,
					'handlerMethod' => 'selectMainMenuAdmin',
					'scheme' => 'default',
				),
				'up' => array (
					//'minPerm' => 2,
					'handlerMethod' => 'shiftMenuItemUp',
					'scheme' => 'default',
				),
				'down' => array (
					//'minPerm' => 2,
					'handlerMethod' => 'shiftMenuItemDown',
					'scheme' => 'default',
				),				
				'edit' => array (
					'handlerMethod' => 'getMenuItem',
					'scheme' => 'edit',
				),
				'update' => array (
					'handlerMethod' => 'saveMenuItem',
					'scheme' => 'default',
				),
				'delete' => array (
					'handlerMethod' => 'deleteMenuItem',
					'scheme' => 'default',
				),
				'getpages' => array (
					'handlerMethod' => 'getContentPages',
					'sheme' => 'default',
				),
				'getmodules' => array (
					'handlerMethod' => 'selectModulesForMenu',
					'sheme' => 'default',
				),				
			),
		),
	),
);
?>