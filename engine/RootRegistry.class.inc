<?php

class RootRegistry {

	public $Name = '';
	public $Templates = array();
	public $Properties = array();

	function RootRegistry($name) { 
		$this->setName($name);
		$this->loadRegistry();
	}

	function getName() {
		return $this->Name;
	}

	function setName($name) {
		$this->Name = $name;
	}

	function loadRegistry() {
		$Registry = loadObjectRegistry($this->Name);
		$this->Templates = isset($Registry['Templates'])? $Registry['Templates'] : '';
		$this->Properties = isset($Registry['Properties'])? $Registry['Properties'] : '';
	}
}
?>