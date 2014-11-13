<?php
$Registry = array(
	'Templates' => array(
		'default' => 'default.mail.html',
		'onlinerequest' => 'onlinerequest.mail.html',	
		'vacancy' => 'vacancy.mail.html',	
	),
	'Properties' => array(//задача - сабж, важность
		//Registration
		'default' => array(
			'subj' => 'Default',
			'prior' => '1',
		),
		'onlinerequest' => array(
			'subj' => 'Online Request',
			'prior' => '3',
		),
		'vacancy' => array(
			'subj' => 'Application form',
			'prior' => '3',
		),

	),
);
?>