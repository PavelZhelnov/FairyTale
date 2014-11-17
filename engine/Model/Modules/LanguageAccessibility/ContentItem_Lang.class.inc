<?php 
class ContentItem_Lang  extends RootEntity
{
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
    public $value;
   
}
?>