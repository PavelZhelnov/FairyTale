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
				'edit' => array (
					'handlerMethod' => 'getMenuItemAdmin',
					'scheme' => 'edit',
				),
				'update' => array (
					'handlerMethod' => 'saveMenuItemAdmin',
					'scheme' => 'default',
				),
				'delete' => array (
					'handlerMethod' => 'deleteMenuItemAdmin',
					'scheme' => 'default',
				),
				'getpages' => array (
					'handlerMethod' => 'getContentPages',
					'sheme' => 'default',
				),
				'getmodules' => array (
					'handlerMethod' => 'selectModules',
					'sheme' => 'default',
				),				
			),
		),
	),
);
?>