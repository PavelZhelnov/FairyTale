<?php
$Registry = array (
	'Properties' => array (
		'Tasks' => array (
			'18' => array (
				'view' => array (
					'handlerMethod' => 'selectSubscriptionCategories',
					'scheme' => 'default',
				),
				//mail
				'viewmail' => array (
					'handlerMethod' => 'selectCategoryMail',
					'scheme' => 'default',
				),
				'editmail' => array (
					'handlerMethod' => 'getMail',
					'scheme' => 'default',
				),
				'deletemail' => array (
					'handlerMethod' => 'deleteMail',
					'scheme' => 'default',
				),
				'sendmail' => array (
					'handlerMethod' => 'addSubscriptionLetter',
					'scheme' => 'default',
					'actionMethod'=>'sendSubscriptionMail',
				),
				//susbcribers
				'viewsubscribers' => array (
					'handlerMethod' => 'selectCategorySubscribers',
					'scheme' => 'default',
				),
				'modifysubscription' => array (
					'handlerMethod' => 'modifySubscription',
					'scheme' => 'default',
				),
				'deletesubscriber' => array (
					'handlerMethod' => 'deleteSubscriber',
					'scheme' => 'default',
				),			
				'authorizesubscriber' => array (
					'handlerMethod' => 'authorizeSubscriber',
					'scheme' => 'default',
					'actionMethod'=>'sendSubscriptionAuth',
				),			
				'checkconfirm' => array (
					'handlerMethod' => 'checkConfirm',
					'scheme' => 'default',
				),
				//category
				'editcategory' => array (
					'handlerMethod' => 'getSubscriptionCategory',
					'scheme' => 'edit',
				),
				'savecategory' => array (
					'handlerMethod' => 'saveSubscriptionCategory',
					'scheme' => 'default',
				),
				'deletecategory' => array (
					'handlerMethod' => 'deleteSubscriptionCategory',
					'scheme' => 'default',
				),
			),
		),
	),
);
?>