<?php

class AdminContentItemAction extends Action {

    public $Pages = array(
        '20' => array( /*Content item- admin menu items */
            'scheme' => 'default',
            'forward_scheme' => 'default',
            'forward_url' => '',
        ),
    );

    function AdminContentItemAction($name='AdminContentItemAction') {
        $this->Action($name);
    }
}
?>