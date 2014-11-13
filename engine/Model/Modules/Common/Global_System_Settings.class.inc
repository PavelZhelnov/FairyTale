<?php
	class Global_System_Settings extends RootEntity {
		
		public $department; //fk to organization
		
		public $email_delimeter;
		public $fake_member; 
		public $default_city;
		//
		public $default_urgency_period;
		//
		public $default_state;
		public $last_modified_date;
		public $last_modified_member;
		public $feedback_email;
		public $support_email;
		public $subscription_email;
		public $offer_confirmation_email;
		/**
		 * Used when creating new offer by public agent; 
		 */
		public $default_offer_agent;
		/* will be used when 
		* 1) creating new Property by Office Staff;
		* 2) show a list of showing appointment, default filtering by listing agent;
		*/
		public $default_listing_agent; 
		public $showing_app_listing_agent_first;
		public $autoclose_overdue_tasks_period;
		
		public $autoclose_old_properties_period; //period in days
		public $autoclose_old_properties_status; // get into defauls property status
		//
		public $license_expiration_warn_period;
		public $license_expiration_notification_method;
		/*
		1 - Notify via email(once)
		2 - Notify via email (every day)
		3 - Notify via message at Home page(once)
		4 - Notify via message at Home page(every time on login)
		13 - Notify via email(once) and Notify via message at Home page (once)
		23 - Notify via email (every day) and Notify via message at Home page (once)
		14 - Notify via email(once) and Notify via message at Home page (every time on login)
		24 - Notify via email (every day) and Notify via message at Home page (every time on login)
		*/
		//
		
		//Earnest Money steps, done from Offer and Closing
		public $em_office_steps_email;
		public $em_step3_default_body; //3 - send for closing
	}
?>