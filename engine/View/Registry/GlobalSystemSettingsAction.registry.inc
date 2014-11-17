<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'103' => array (
				'list' => array (
					'handlerMethod' => 'selectGlobalSystemSettings',
					'scheme' => 'update',
					'minPerm' => 2,
				),								
				'update' => array (
					'handlerMethod' => 'saveGlobalSystemSettings',
					'scheme' => 'update',
					'minPerm' => 8,
				),
				'open' => array (
					'handlerMethod' => 'openGlobalSystemSettings',
					'scheme' => 'default',
					'minPerm' => 2,
				),				
				'members' => array (
					'minPerm' => 2,
					'handlerMethod' => 'selectMembers',
					'scheme' => 'default',
				),				
			),
		),
	),
);
?>