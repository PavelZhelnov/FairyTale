<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'29' => array (
				'new' => array (
					'handlerMethod' => 'createNewDocument',
					'scheme' => 'default',
					'minPerm' => 4,
				),
				'list' => array (
					'minPerm' => 4,
					'handlerMethod' => 'selectDocumentListAdmin',
					'scheme' => 'default',
				), 
				'get' => array (
					'minPerm' => 4,
					'handlerMethod' => 'getDocumentAdmin',
					'scheme' => 'save',
				), 
				'save' => array (
					'minPerm' => 16,
					'handlerMethod' => 'saveDocumentAdmin',
					'scheme' => 'save',
					'viewMethod' => 'saveDocument',
				), 
				'delete' => array (
					'minPerm' => 16,
					'handlerMethod' => 'deleteDocumentAdmin',
					'scheme' => 'default',
					'viewMethod' => 'deleteDocument',
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