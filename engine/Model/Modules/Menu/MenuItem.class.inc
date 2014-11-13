<?php

/**
 * Class MenuItem
 */
class MenuItem extends RootEntity {

    /**
     * @type:string
     * @maxlength:40
     */
    public $name;

    /**
     * @type:string
     * @maxlength:40
     */
    public $url;

    /**
     * @type:integer
     */
    public $module;
    public $features;

    /**
     * @type:boolean
     */
    public $noactive;

    /**
     * @type:integer
     */
    public $contentpage;
    public $parent_item;

    /**
     * @type:object
     * @object:MenuItem_Lang
     */
    public $name_langs;//ObjectsList
    /**
     * @type:text
     */
    public $infotext; //link to page content for this link

    /**
     * @type:boolean
     */
    public $permanent; //1 - can't delete

    function MenuItem() {
        $this->name_langs=new ObjectsList();
        $this->name_langs->type=new MenuItem_Lang();
    }

}
?>