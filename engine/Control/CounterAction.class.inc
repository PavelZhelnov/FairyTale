<?php
class CounterAction extends Action {

	public $Pages = array(
		'7' => array( /*Counter - client view*/
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function CounterAction($name='CounterAction') {
		$this->Action($name);
	}	

}
?>