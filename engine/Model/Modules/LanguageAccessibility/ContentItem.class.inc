<?php

/**
 * Class ContentItem
 */
class ContentItem extends RootEntity {

    /**
     * @type:select
     */
    public $module;

    /**
     * @type:select
     */
    public $contenttype;

    /**
     * @type:string
     * @maxlength:255
     */
    public $var;

    /**
     * @type:object
     * @object:ContentItem_Lang
     */
    public $name_langs;//ObjectsList

    function ContentItem() {
        $this->name_langs=new ObjectsList();
        $this->name_langs->type=new ContentItem_Lang();
    }

}
?>