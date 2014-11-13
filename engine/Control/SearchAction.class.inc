<?php
class SearchAction extends Action {

	public $Pages = array(
		'200' => array( /*Search enging - client view*/
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function SearchAction($name='SearchAction') {
		$this->Action($name);
	}	

}
?>