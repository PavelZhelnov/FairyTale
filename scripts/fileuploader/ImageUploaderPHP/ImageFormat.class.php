<?php
class ImageFormat {
  
  
  function ImageFormat() {

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


  var $_backgroundColor = '';

  /**
   * @return string
   */
  function getBackgroundColor() {
    return $this->_backgroundColor;
  }

  /**
   * @param string $value
   */
  function setBackgroundColor($value) {
    $this->_backgroundColor = $value;
  }


  var $_urlNormal = '';

  /**
   * @return string
   */
  function getUrlNormal() {
    return $this->_urlNormal;
  }

  /**
   * @param string $value
   */
  function setUrlNormal($value) {
    $this->_urlNormal = $value;
  }


  var $_urlNormalFocused = '';

  /**
   * @return string
   */
  function getUrlNormalFocused() {
    return $this->_urlNormalFocused;
  }

  /**
   * @param string $value
   */
  function setUrlNormalFocused($value) {
    $this->_urlNormalFocused = $value;
  }


  var $_urlHover = '';

  /**
   * @return string
   */
  function getUrlHover() {
    return $this->_urlHover;
  }

  /**
   * @param string $value
   */
  function setUrlHover($value) {
    $this->_urlHover = $value;
  }


  var $_urlHoverFocused = '';

  /**
   * @return string
   */
  function getUrlHoverFocused() {
    return $this->_urlHoverFocused;
  }

  /**
   * @param string value
   */
  function setUrlHoverFocused($value) {
    $this->_urlHoverFocused = $value;
  }


  var $_urlPressed = '';

  /**
   * @return string
   */
  function getUrlPressed() {
    return $this->_urlPressed;
  }

  /**
   * @param string $value
   */
  function setUrlPressed($value) {
    $this->_urlPressed = $value;
  }


  var $_urlDisabled = '';

  /**
   * @return string
   */
  function getUrlDisabled() {
    return $this->_urlDisabled;
  }

  /**
   * @param string $value
   */
  function setUrlDisabled($value) {
    $this->_urlDisabled = $value;
  }


  /**
   * @return string
   */
  function __toString() {
    if (empty($this->_urlNormal)) {
      return '';
    }
    else {
      $sb = '';

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

      if (!empty($this->_backgroundColor)) {
        $sb .= 'BackgroundColor=';
        $sb .= $this->_backgroundColor;
        $sb .= ';';
      }

      if (!empty($this->_urlNormalFocused)) {
        $sb .= 'UrlNormalFocused=';
        $sb .= $this->_urlNormalFocused;
        $sb .= ';';
      }

      if (!empty($this->_urlHover)) {
        $sb .= 'UrlHover=';
        $sb .= $this->_urlHover;
        $sb .= ';';
      }

      if (!empty($this->_urlHoverFocused)) {
        $sb .= 'UrlHoverFocused=';
        $sb .= $this->_urlHoverFocused;
        $sb .= ';';
      }

      if (!empty($this->_urlPressed)) {
        $sb .= 'UrlPressed=';
        $sb .= $this->_urlPressed;
        $sb .= ';';
      }

      if (!empty($this->_urlDisabled)) {
        $sb .= 'UrlDisabled=';
        $sb .= $this->_urlDisabled;
        $sb .= ';';
      }
      
      $sb .= 'UrlNormal=';
      $sb .= $this->_urlNormal;
      $sb .= ';';

      return $sb;
    }
  }
}