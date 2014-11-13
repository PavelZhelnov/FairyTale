<?php

class AdminStatisticAction extends Action {

	public $Pages = array(
		'28' => array( /* AdminStatistic - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function AdminStatisticAction($name='AdminStatisticAction') {
		$this->Action($name);
	}

}
?>