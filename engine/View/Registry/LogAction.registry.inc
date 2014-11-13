<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'104' => array (
				'view' => array (
					'handlerMethod' => 'selectLogs',
					'scheme' => 'default',
					'minPerm' => 2,
				),
				'set_search' => array (
					'minPerm' => 2,
					'handlerMethod' => 'setSearch',
					'scheme' => 'default',
				),
				'clear_search' => array (
					'minPerm' => 2,
					'handlerMethod' => 'clearSearch',
					'scheme' => 'default',
				),				
				'get_search' => array (
					'minPerm' => 2,
					'handlerMethod' => 'getSearch',
					'scheme' => 'default',
				),
				'settings' => array (
					'minPerm' => 2,
					'handlerMethod' => 'getSettings',
					'scheme' => 'default',
				),
			),
		),
	),
);
?>