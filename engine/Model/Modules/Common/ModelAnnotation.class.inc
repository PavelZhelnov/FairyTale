<?php
class ModelAnnotation {

    public $uiignore;
    public $type;
    public $maxlength;
    public $minlength;
    public $object;
    public $required;
    public $onchange;


    function __construct($doc) {
        $this->parse($doc);
    }

    function parse($doc) {
        $temp = explode("@", $doc);
        foreach($temp as $k => $v) {
            if ($v) {
                $element = explode(":", $v);
                $this->{trim($element[0])} = !empty($element[1])?trim($element[1]):true;
            }
        }
    }


} 