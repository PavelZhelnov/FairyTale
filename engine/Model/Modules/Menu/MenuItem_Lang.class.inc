<?php

class MenuItem_Lang extends RootEntity {

    /**
     * @type:integer
     */
    public $ownerid;
    /**
     * @type:hidden
     */
    public $lang;
    /**
     * @type:string
     * @maxlength:255
     * @required
     */
    public $name;
    /**
     * @type:string
     * @maxlength:255
     * @required
     */
    public $description;
    /**
     * @type:text
     */
	public $meta_info;

}



?>