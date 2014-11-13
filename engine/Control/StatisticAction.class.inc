<?php

class StatisticAction extends Action {

	public $Pages = array(
		'26' => array( /* Statistic - show all entities */
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
	        ),
	);

	function StatisticAction($name='StatisticAction') {
		$this->Action($name);
	}

}
?>