<?php

class Module extends RootEntity {

	public $sys_name;
	public $path;
	public $name_langs;	// ObjectsList - Module_Lang
	public $contents;		// ObjectsList - Content
	public $settings;		// ObjectsList - ModuleSetting
	public $type;		//1 - user, 2 - admin, 3 - partner
}
?>