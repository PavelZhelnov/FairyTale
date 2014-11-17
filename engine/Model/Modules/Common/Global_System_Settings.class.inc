<?php
	class Global_System_Settings extends RootEntity {

        /**
         * @required
         * @type:string
         * @maxlength:255
         */
        public $setting_name;
        /**
         * @required
         * @type:string
         * @maxlength:3
         */
        public $email_delimeter;

		public $fake_member; 

	}
?>