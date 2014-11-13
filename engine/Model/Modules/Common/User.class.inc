<?php

class User extends RootEntity {
	
	public $username;
	public $password;
	public $first_name;
	public $last_name;
	public $email;
	public $subscription_confirmed;
	public $subscription_authcode;
	public $subscription_date;
	public $subscription_format;
}
?>