<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'11' => array (
				'save' => array (
					'minPerm' => 16,
					'handlerMethod' => 'saveHeaderAdmin',
					'scheme' => 'save',
					'viewMethod' => 'saveHeader',
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