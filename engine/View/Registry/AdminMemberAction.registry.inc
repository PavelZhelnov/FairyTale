<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'21' => array (
				'view' => array (
					'handlerMethod' => 'selectMembers',
					'scheme' => 'default',
				),
				'new' => array (
					'handlerMethod' => 'newMember',
					'scheme' => 'default',
				), 
				'viewmember' => array (
					'handlerMethod' => 'getMember',
					'scheme' => 'viewmember',
				),
				'update' => array (
					'handlerMethod' => 'saveMember',
					'scheme' => 'second',
					'viewMethod' => 'saveImage',
				),
				'getmember' => array (
					'handlerMethod' => 'getMember',
					'scheme' => 'default',
				),
				'delete' => array (
					'handlerMethod' => 'deleteMember',
					'scheme' => 'default',
					'viewMethod' => 'deleteImages', 
				),
				'selectLevels' => array (
					'handlerMethod' => 'selectLevels',
					'scheme' => 'default',
				),
				'set_search' => array (
					//'minPerm' => 2,
					'handlerMethod' => 'setSearch',
					'scheme' => 'default',
				),
				'get_search' => array (
					//'minPerm' => 2,
					'handlerMethod' => 'getSearch',
					'scheme' => 'default',
				),
			),
		),
	),
);
?>