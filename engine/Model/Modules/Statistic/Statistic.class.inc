<?php
class Statistic extends RootEntity
{
   public $id; //[obligatory]
   public $module; //what module [obligatory]
   public $st_type; //type of statistic action [obligatory]
   public $ipaddress; //who does it? 
   public $url;
   public $act_date; //current time
   public $value; //some value of action
   public $description; //descrption of action
   public $entity; //id of affected entity
}

?>