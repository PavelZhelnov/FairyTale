<?php

class NirvanixException extends Exception {
	
	function NirvanixException($exceptionObject) {
		parent::__construct($exceptionObject->ResponseCode . ": " . $exceptionObject->ErrorMessage);
	}
}

?>