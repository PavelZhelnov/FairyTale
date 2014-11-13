<?php

require_once 'BaseControl.class.php';
require_once 'ActiveXControl.class.php';
require_once 'ThumbnailClientEvents.class.php';
require_once 'JavaControl.class.php';
require_once 'Utils.class.php';

final class Thumbnail extends BaseControl {

  public $attributes;

  
	private $_ActiveXControl;
	/**
	* @return ActiveXControl
	*/
	public function getActiveXControl() {
		if (isset($this->_ActiveXControl))
			return $this->_ActiveXControl;
		else
			return null;
	}
	public function setActiveXControl($value) {
		$this->_ActiveXControl = $value;
	}
	
	private $_BackgroundColor;
	/**
	* @return string
	*/
	public function getBackgroundColor() {
		if (isset($this->_BackgroundColor))
			return $this->_BackgroundColor;
		else
			return null;
	}
	public function setBackgroundColor($value) {
		$this->_BackgroundColor = $value;
	}
	
	private $_ClientEvents;
	/**
	* @return ThumbnailClientEvents
	*/
	public function getClientEvents() {
		if (isset($this->_ClientEvents))
			return $this->_ClientEvents;
		else
			return null;
	}
	public function setClientEvents($value) {
		$this->_ClientEvents = $value;
	}
	
	private $_Guid;
	/**
	* @return string
	*/
	public function getGuid() {
		if (isset($this->_Guid))
			return $this->_Guid;
		else
			return null;
	}
	public function setGuid($value) {
		$this->_Guid = $value;
	}
	
	private $_Height;
	/**
	* @return string
	*/
	public function getHeight() {
		if (isset($this->_Height))
			return $this->_Height;
		else
			return null;
	}
	public function setHeight($value) {
		$this->_Height = $value;
	}
	
	private $_JavaControl;
	/**
	* @return JavaControl
	*/
	public function getJavaControl() {
		if (isset($this->_JavaControl))
			return $this->_JavaControl;
		else
			return null;
	}
	public function setJavaControl($value) {
		$this->_JavaControl = $value;
	}
	
	private $_ParentControlName;
	/**
	* @return string
	*/
	public function getParentControlName() {
		if (isset($this->_ParentControlName))
			return $this->_ParentControlName;
		else
			return null;
	}
	public function setParentControlName($value) {
		$this->_ParentControlName = $value;
	}
	
	private $_Width;
	/**
	* @return string
	*/
	public function getWidth() {
		if (isset($this->_Width))
			return $this->_Width;
		else
			return null;
	}
	public function setWidth($value) {
		$this->_Width = $value;
	}
	

  function __construct($id = NULL) {
    parent::__construct($id);

    
		$this->setActiveXControl(new ActiveXControl());
		$this->setBackgroundColor('#ffffff');
		$this->setClientEvents(new ThumbnailClientEvents());
		$this->setHeight('100px');
		$this->setJavaControl(new JavaControl());
		$this->setWidth('100px');

    
		$this->attributes['ActiveXControl'] = array('jsName' => 'activeXControl','jsType' => 'activeXControl','defaultValue' => '[new]');
		$this->attributes['BackgroundColor'] = array('jsName' => 'backgroundColor','jsType' => 'String','defaultValue' => '#ffffff');
		$this->attributes['ClientEvents'] = array('jsName' => 'events','jsType' => 'thumbnailEvents','defaultValue' => '[new]');
		$this->attributes['Guid'] = array('jsName' => 'guid','jsType' => 'String','defaultValue' => '');
		$this->attributes['Height'] = array('jsName' => 'height','jsType' => 'String','defaultValue' => '100px');
		$this->attributes['ID'] = array('jsName' => 'id','jsType' => 'String','defaultValue' => '');
		$this->attributes['JavaControl'] = array('jsName' => 'javaControl','jsType' => 'javaControl','defaultValue' => '[new]');
		$this->attributes['ParentControlName'] = array('jsName' => 'parentControlName','jsType' => 'String','defaultValue' => '');
		$this->attributes['Width'] = array('jsName' => 'width','jsType' => 'String','defaultValue' => '100px');
  }

  protected function getClientClassName() {
    return 'thumbnail';
  }

  function render()
  {
    $this->renderClientScripts();

    $html = array ();
    $html[] = "<script type=\"text/javascript\">";
    $html[] = "//<![CDATA[";

    //keep global namespace clean. wrap all script in anonymous function.
    $html[] = '(function() {';

    if ($this->getDebugScriptLevel() > 0) {
      $html[] = '$au.debug().level(' . $this->getDebugScriptLevel() . ');';
    }

    if ($this->getDebugScriptMode()) {
      $mode = $this->getDebugScriptMode();
      $values = explode(',', strtolower($mode));
      if (count($values) > 1) {
        $rg = '#console|popup|alert#';
        for ($i = 0, $imax = count($values); $i < $imax; $i++) {
          $m = NULL;
          if (preg_match($rg, $values[$i], $m)) {
            $values[$i] = "'" . $m[0] . "'";
          }
        }
        $mode = '[' . implode(',', $values) . ']';
      } else {
        $mode = "'$mode'";
      }
      $html[] = '$au.debug().mode(' . $mode . ');';
    }

    $html[] = "var u = {$this->getClientNamespace()}.{$this->getClientClassName()}({id: '{$this->getID()}' });";

    // add properties script
    $html[] = 'u.set(' . $this->getJson() . ');';

    // add write markup script
    if (!$this->getManualRendering()) {
      $html[] = 'u.writeHtml();';
    }

    $html[] = '})();';

    $html[] = "//]]>";
    $html[] = "</script>";

    echo implode("\n", $html);
  }
}