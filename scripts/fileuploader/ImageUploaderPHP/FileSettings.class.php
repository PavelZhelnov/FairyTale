<?php

class FileSettings {

  private $_acl = 'private';
  private $_key = '${filename}';
  private $_maxFileSize = 5368709120;
  private $_minFileSize = 0;
  private $_meta;


  function FileSettings() {
  }

  function getAcl() {
    return $this->_acl;
  }

  function setAcl($value) {
    $this->_acl = $value;
  }

  function getKey() {
    return $this->_key;
  }

  function setKey($value) {
    $this->_key = $value;
  }

  function getMaxFileSize() {
    return $this->_maxFileSize;
  }

  function setMaxFileSize($value) {
    $this->_maxFileSize = $value;
  }

  function getMinFileSize() {
    return $this->_minFileSize;
  }

  function setMinFileSize($value) {
    $this->_minFileSize = $value;
  }

  function &getMeta() {
    return $this->_meta;
  }

  function setMeta($value) {
    $this->_meta = $value;
  }
}