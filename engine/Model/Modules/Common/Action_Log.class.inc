<?php
	class Action_Log extends RootEntity {
		public $action_type; //log action 
		public $ownerid; //member
		public $action_time;
		public $section; //workflow table 
		public $description;
	}
?>