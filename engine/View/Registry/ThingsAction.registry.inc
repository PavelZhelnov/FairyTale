<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'5' => array (
				'view' => array (
					'handlerMethod' => 'selectInformation',
					'scheme' => 'default',
				),
				'photos' => array (
					'handlerMethod' => 'selectPhotos',
					'scheme' => 'photos',
				),
				'newssubscribe' => array (
					'handlerMethod' => 'getEmail',
					'scheme' => 'photos',
					'actionMethod' => 'sendNewsSubscription',
				),
				'settings' => array (
					//'minPerm' => 2,
					'handlerMethod' => 'getSettings',
					'scheme' => 'default',
				),
				'sendonlinerequest' => array (
					'handlerMethod' => 'getEmail',
					'scheme' => 'photos',
					'actionMethod' => 'sendOnlineRequest',
					'minPerm' => 2,
				),
				'sendvacancy' => array (
					'handlerMethod' => 'getEmailForVacancy',
					'scheme' => 'photos',
					'actionMethod' => 'sendVacancy',
					'minPerm' => 2,
				),
				
			),
		),
	),
);
?>