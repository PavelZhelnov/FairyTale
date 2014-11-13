<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'4' => array (
				'select' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectContentItems',
					'scheme' => 'select',
				),
				'open' => array (
					'minPerm' => 2,
					'handlerMethod' => 'openContentItem',
					'scheme' => 'open',
				),
				'save' => array (
					'minPerm' => 2,
					'handlerMethod' => 'saveContentItem',
					'scheme' => 'save',
				),
				'types' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectContentType',
					'scheme' => 'types',
				),
				'getmodules' => array(
					'minPerm' => 2,
					'handlerMethod' => 'selectModules',
					'scheme' => 'default',
				),
				'modules' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectContentModules',
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