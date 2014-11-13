<?php

class Member extends RootEntity {
	
	public $id;
	public $first_name;
	public $last_name;
	public $address;
	public $phone;
	public $fax;
	public $cell;
	public $company;
	public $login;
	public $email;
	public $password;
	public $activated;
	public $date_registered;
	public $hashcode;
    public $level;// class Level
    public $image_type;
    public $memberModuleRights;// class ObjectsList
    public $agent;
    public $ownerid; //agent (Class Contact)
    public $department; //fk to organization
    public $email_sent;
    public $keep_loggedin_code;
}
?>