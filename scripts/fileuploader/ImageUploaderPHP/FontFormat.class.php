<?php
class FontFormat {


  function FontFormat() {

  }


  private $_name = null;

  /**
   * @return string
   */
  function getName() {
    return $this->_name;

  }

  /**
   * @param string $value
   */
  function setName($value) {
    $this->_name = $value;
  }


  private $_size = null;

  /**
   * @return int
   */
  function getSize() {
    return $this->_size;
  }

  /**
   * @param int $value
   */
  function setSize($value) {
    $this->_size = $value;
  }


  private $_bold = null;

  /**
   * @return boolean
   */
  function getBold() {
    return $this->_bold;
  }

  /**
   * @param boolean $value
   */
  function setBold($value) {
    $this->_bold = $value;
  }


  private $_italic = null;

  /**
   * @return boolean
   */
  function getItalic() {
    return $this->_italic;
  }

  /**
   * @param boolean $value
   */
  function setItalic($value) {
    $this->_italic = $value;
  }


  /**
   * @return string
   */
  function __toString() {
    $sb = '';

    if (!empty($this->_name)) {
      $sb .= "Name={$this->_name};";
    }

    if (!empty($this->_size)) {
      $sb .= "Size={$this->_size};";
    }

    $style = '';
    if (!empty($this->_bold)) {
      $style .= 'Bold';
    }

    if (!empty($this->_italic)) {
      if (!empty($style)) {
        $style .= ',';
      }

      $style .= 'Italic';
    }

    if (!empty($style)) {
      $sb .= "Style=$style;";
    }

    return $sb;
  }
}
