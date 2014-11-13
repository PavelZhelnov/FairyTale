<?php
class BackgroundImageFormat {

  /**
   * This is method BackgroundImageFormat
   */
  function BackgroundImageFormat() {

  }

  var $_width = null;

  /**
   * @return int
   */
  function getWidth() {
    return $this->_width;

  }

  /**
   * @param int $value
   */
  function setWidth($value) {
    $this->_width = $value;
  }


  var $_height = null;

  /**
   * @return int
   */
  function getHeight() {
    return $this->_height;
  }

  /**
   * @param int $value
   */
  function setHeight($value) {
    $this->_height = $value;
  }


  var $_url = '';

  /**
   * @return string
   */
  function getUrl() {
    return $this->_url;
  }

  /**
   * @param string value
   */
  function setUrl($value) {
    $this->_url = $value;
  }


  var $_position = 'Center';

  /**
   * @return string
   */
  function getPosition() {
    return $this->_position;
  }

  /**
   * @param string $value
   */
  function setPosition($value) {
    $this->_position = $value;
  }



  /**
   * This is method toString
   *
   * @return string This is the return value description
   */
  function __toString() {
    if ($this->_url == '') {
      return '';
    }
    else {
      $sb = '';

      if (!empty($this->_position) && strcasecmp($this->_position, 'Center') != 0) {
        $sb .= 'Position=';
        $sb .= $this->_position;
        $sb .= ';';
      }
      
      if (!empty($this->_width)) {
        $sb .= 'Width=';
        $sb .= $this->_width;
        $sb .= ';';
      }

      if (!empty($this->_height)) {
        $sb.= 'Height=';
        $sb .= $this->_height;
        $sb .= ';';
      }

      $sb .= 'Url=';
      $sb .= $this->_url;
      $sb .= ';';

      return $sb;
    }
  }
}