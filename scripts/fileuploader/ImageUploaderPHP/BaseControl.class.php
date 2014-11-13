<?php

abstract class BaseControl {

  public $attributes;

  protected abstract function getClientClassName();

  protected function  getClientNamespace() {
    return '$au';
  }

  private static $_scriptFileNames = array();

  function addScriptFileName($name, $fileName) {
    if (!array_key_exists($name, self::$_scriptFileNames)) {
      self::$_scriptFileNames[$name] = array(
        'fileName' => $fileName,
        'rendered' => FALSE
      );
    }
  }

  function &getScriptFileNames() {
    return self::$_scriptFileNames;
  }

  private $_ID;
  /**
   * @return string
   */
  public function getID() {
    if (isset($this->_ID)) {
      return $this->_ID;
    } else {
      return null;
    }
  }
  public function setID($value) {
    $this->_ID = $value;
  }

  private $_ScriptsDirectory;
  /**
   * @return string
   */
  public function getScriptsDirectory() {
    if (isset($this->_ScriptsDirectory))
    return $this->_ScriptsDirectory;
    else
    return null;
  }
  public function setScriptsDirectory($value) {
    $this->_ScriptsDirectory = $value;
  }

  private $_DebugScriptMode;
  /**
   * @return boolean
   */
  public function getDebugScriptMode() {
    if (isset($this->_DebugScriptMode))
    return $this->_DebugScriptMode;
    else
    return null;
  }
  public function setDebugScriptMode($value) {
    $this->_DebugScriptMode = $value;
  }
  
  private $_DebugScriptLevel = 0;
  /**
   * @return boolean
   */
  public function getDebugScriptLevel() {
    if (isset($this->_DebugScriptLevel))
    return $this->_DebugScriptLevel;
    else
    return null;
  }
  public function setDebugScriptLevel($value) {
    $this->_DebugScriptLevel = $value;
  }
  
  private $_ManualRendering;
  /**
   * @return boolean
   */
  public function getManualRendering() {
    if (isset($this->_ManualRendering))
    return $this->_ManualRendering;
    else
    return null;
  }
  public function setManualRendering($value) {
    $this->_ManualRendering = $value;
  }

  function __construct($id = NULL)
  {
    if (!empty($id)) {
      $this->setID($id);
    }

    $this->setScriptsDirectory($this->getDefaultScriptDirectory());
    $this->attributes = array();
  }

  private static function escapeString($value) {
    $value = str_replace("\\", "\\\\", $value);
    $value = str_replace("\r", "", $value);
    $value = str_replace("\n", "\\n", $value);
    $value = str_replace("'", "\\'", $value);
    return $value;
  }
  
  protected $_preRenderCallbacks;
  
  function addPreRenderCallback($callback) {
    if (!isset($this->_preRenderCallbacks)) {
      $this->_preRenderCallbacks = array();
    }
    
    $this->_preRenderCallbacks[] = $callback;
  }
  
  function removePreRenderCallback($callback) {
    if (!isset($this->_preRenderCallbacks)) {
      return;
    } else {
      foreach ($this->_preRenderCallbacks as $i => $value) {
        if ($callback == $value) {
          array_splice($this->_preRenderCallbacks, $i, 1);
        }
      }
    }
  }

  abstract function render();

  private function getDefaultScriptDirectory() {
    $basePath = dirname($_SERVER['SCRIPT_FILENAME']);
    $basePath = str_replace('\\', '/', $basePath);

    $path = str_replace('\\', '/', dirname( __FILE__ ) . '/Scripts');

    $basePath = explode('/', $basePath);
    $path = explode('/', $path);
    while (count($basePath) > 0 && count($path) > 0 && $basePath[0] == $path[0]) {
      array_shift($basePath);
      array_shift($path);
    }

    while (count($basePath) > 0) {
      array_shift($basePath);
      array_unshift($path, '..');
    }

    $path = implode('/', $path);
    return $path;
  }

  function getJson()
  {
    $html = array ();

    self::getJsonInternal($this, $html);

    return implode("", $html);
  }

  protected function renderClientScripts() {
    if ($this->getDebugScriptLevel() > 0) {
      $this->addScriptFileName('aurigma.uploader', 'aurigma.uploader.js');
    } else {
      $this->addScriptFileName('aurigma.uploader', 'aurigma.uploader.min.js');
    }

    if (method_exists($this, 'getLanguage')) {
      $lang = $this->getLanguage();
      if ($lang) {
        $this->addScriptFileName('aurigma.uploader.' . $lang . '_localization',
          'aurigma.uploader.' . $lang . '_localization.js');
      }
    }

    $scriptsDirectory = $this->getScriptsDirectory();
    if (substr($scriptsDirectory, -1, 1) != '/') {
      $scriptsDirectory .= '/';
    }

    $scriptFileNames = &$this->getScriptFileNames();
    foreach ($scriptFileNames as &$script) {
      if (!$script['rendered']) {
        echo "<script src=\"$scriptsDirectory{$script['fileName']}\" type=\"text/javascript\"></script>";
        $script['rendered'] = TRUE;
      }
    }
  }

  private static function getJsonInternal($obj, &$html)
  {
    if (isset($obj->attributes) && count($obj->attributes) > 0) {
      $html[] = "{";

      $firstLine = true;
      foreach ($obj->attributes as $key=>$value) {
        if (isset($value["jsName"])) {
          $clientMethod = $value["jsName"];
        } else {
          $clientMethod = null;
        }
        if (isset($value["jsType"])){
          $clientType = $value["jsType"];
        } else {
          $clientType = null;
        }
        if (isset($value["defaultValue"])){
          $defaultValue = $value["defaultValue"];
        } else {
          $defaultValue = null;
        }
        $phpMethod = "get" . $key;

        $obj1 = $obj->$phpMethod();
        if (isset($obj1) && $obj1 != $defaultValue) {
          if (!$firstLine) {
            $html[] = ", ";
          }
          if (isset($obj1->attributes)) {
            $html[] = $clientMethod . ": ";
            self::getJsonInternal($obj1, $html);
          } else {
            if (strtolower($clientType) == "string") {
              $html[] = $clientMethod . ": '" . self::escapeString($obj1) . "'";
            } elseif (strtolower($clientType) == 'boolean') {
              $html[] = $clientMethod . ": " . ($obj1 ? 'true' : 'false');
            } elseif (is_array($obj1)) {
              $html[] = $clientMethod . ": ";
              self::getJsonInternal($obj1, $html);
            } else {
              $html[] = $clientMethod . ": " . $obj1;
            }
          }

          $firstLine = false;
        }
      }
      $html[] = "}";
    }
    elseif (is_array($obj)) {
      $html[] = "[";
      $firstElement = true;
      foreach ($obj as $value) {
        if (!$firstElement) {
          $html[] = ", ";
        }
        self::getJsonInternal($value, $html);
        $firstElement = false;
      }
      $html[] = "]";
    } else {
      if ($obj == null || $obj == '') {
        $html[] = '';
      } else {
        $html[] = $obj;
      }
    }
  }
}