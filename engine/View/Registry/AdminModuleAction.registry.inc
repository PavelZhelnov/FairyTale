<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'24' => array (
				'select' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectModuleItems',
					'scheme' => 'select',
				),
				'open' => array (
					'minPerm' => 2,
					'handlerMethod' => 'openModuleItem',
					'scheme' => 'open',
				),
				'save' => array (
					'minPerm' => 2,
					'handlerMethod' => 'saveModuleItem',
					'scheme' => 'save',
				),
				'getmodules' => array(
					'minPerm' => 2,
					'handlerMethod' => 'selectModules',
					'scheme' => 'default',
				),
				'modules' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectModules2',
					'scheme' => 'types',
				),
				'set_search' => array (
					'minPerm' => 2,
					'handlerMethod' => 'setSearch',
					'scheme' => 'default',
				),
				'get_search' => array (
					'minPerm' => 2,
					'handlerMethod' => 'getSearch',
					'scheme' => 'default',
				), 
			),
		),
	),
);
?>