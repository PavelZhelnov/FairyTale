<?php
$Registry = array (
    'Properties' => array (
        'Tasks' => array (
            '20' => array (
                'view' => array (
                    //'minPerm' => 2,
                    'handlerMethod' => 'selectContentItemsAdmin',
                    'scheme' => 'default',
                ),
                'edit' => array (
                    'handlerMethod' => 'getContentItemAdmin',
                    'scheme' => 'edit',
                ),
                'update' => array (
                    'handlerMethod' => 'saveContentItemAdmin',
                    'scheme' => 'default',
                ),
                'delete' => array (
                    'handlerMethod' => 'deleteContentItemAdmin',
                    'scheme' => 'default',
                ),
            ),
        ),
    ),
);
?>