<?php
class MetaInfoAction extends Action {

	public $Pages = array(
		'8' => array( /*MetaInfo - client view*/
			'scheme' => 'default',
			'forward_scheme' => 'default',
			'forward_url' => '',
		),
	);

	function MetaInfoAction($name='MetaInfoAction') {
		$this->Action($name);
	}	

}
?>