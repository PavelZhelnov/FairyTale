<?php

class UploadCache {

  private $_uploadSession;
  private $_cacheSessionDirectory;
  // TODO; What default value should be?
  private $_cacheRoot;

  /**
   * UploadCache constructor
   * @param UploadSession $uploadSession
   */
  function __construct($uploadSessionId) {
    if (empty($uploadSessionId)) {
      throw new Exception('Upload session id can not be null.');
    }
    $this->_uploadSessionId = $uploadSessionId;
  }

  /**
   * Get default root upload cache directory.
   */
  public function getCacheRoot() {
    return $this->_cacheRoot;
  }

  public static function moveFile($source, $destination) {
    $result = @rename($source, $destination);
    if (!$result) {
      // copy-remove otherwise
      $result = copy($source, $destination);
      unlink($source);
    }
    return $result;
  }

  public function getLastFullScanTimestamp() {
    $file = $this->getCacheRoot().DIRECTORY_SEPARATOR.'timestamp';
    $timestamp = file_get_contents($file);
    if ($timestamp) {
      $timestamp = intval($timestamp, 10);
    } else {
      $timestamp = 0;
    }
    return $timestamp;
  }

  public function setLastFullScanTimestamp($value = NULL) {
    $file = $this->getCacheRoot().DIRECTORY_SEPARATOR.'timestamp';
    if ($value === NULL) {
      $value = time();
    }
    file_put_contents($file, $value);
  }

  /**
   * Set root upload cache directory
   * @param string $value
   */
  public function setCacheRoot($value) {
    if (!empty($value)) {
      rtrim($value, '/\\');
    }
    $this->_cacheRoot = $value;
  }

  /**
   * Check if package exists in the cache
   * @param $package
   */
  public function isPackageCached($packageIndex) {
    return file_exists($this->getPackageCacheDirectory($packageIndex));
  }

  private function getPackageCacheDirectory($packageIndex) {
    return $this->getSessionCacheDirectory() . DIRECTORY_SEPARATOR . $packageIndex;
  }

  public function loadSavedFields($packageIndex) {
    $filePath = $this->getPackageCacheDirectory($packageIndex) . DIRECTORY_SEPARATOR . 'post';
    return unserialize(file_get_contents($filePath));
  }

  public function loadSavedFiles($packageIndex) {
    $path = $this->getPackageCacheDirectory($packageIndex);
    $paths = glob($path . DIRECTORY_SEPARATOR . 'File*_*');
    $files = array();
    foreach ($paths as $file) {
      $files[basename($file)] = array(
  		  'cached' => true,
  		  'tmp_name' => $file,
  		  'type' => 'application/octet-stream',
  		  'error' => UPLOAD_ERR_OK,
  		  'size' => filesize($file)
      );
    }
    return $files;
  }

  /**
   * Save package fields and files into upload temp cache
   * @param Package $package
   */
  public function saveRequestData($packageIndex, $fields, $files) {
    $path = $this->getPackageCacheDirectory($packageIndex);

    if (!file_exists($path)) {
      mkdir($path, 0777, true);
    }

    $this->saveFields($path, $fields);
    $this->saveFiles($path, $files);

    $sessionDir = $this->getSessionCacheDirectory();
    $filename = 'timestamp';
    file_put_contents($sessionDir.DIRECTORY_SEPARATOR.$filename, time());
  }

  private function saveFields($path, $fields) {
    $filePath = $path . DIRECTORY_SEPARATOR . 'post';
    if (file_exists($filePath)) {
      $data = file_get_contents($filePath);
      $data = unserialize($data);
    }
    if (isset($data)) {
      $fields = array_merge($data, $fields);
    }
    file_put_contents($path . DIRECTORY_SEPARATOR . 'post', serialize($fields));
  }

  private function saveFiles($path, $files) {
    foreach ($files as $key => $file) {
      $filePath = $path . DIRECTORY_SEPARATOR . $key;
      if (is_uploaded_file($file['tmp_name']) && !file_exists($filePath)) {
        move_uploaded_file($file['tmp_name'], $filePath);
      } else {
        $this->appendToFile($file['tmp_name'], $filePath);
      }
    }
  }

  private function appendToFile($source, $destination) {
    $buff = 4096;
    $fsrc = fopen($source, 'r');
    $fdst = fopen($destination, 'a');
    while (($data = fread($fsrc, $buff)) !== '') {
      fwrite($fdst, $data);
    }
    fclose($fsrc);
    fclose($fdst);
  }

  public function getSessionCacheDirectory() {
    if (empty($this->_cacheRoot)) {
      throw new Exception('Cache directory is not specified.');
    }

    if (empty($this->_cacheSessionDirectory)) {
      $this->_cacheSessionDirectory = $this->getCacheRoot() . DIRECTORY_SEPARATOR . $this->_uploadSessionId;
    }
    return $this->_cacheSessionDirectory;
  }

  public function getWriteTimestamp() {
    $timestampFile = $this->getSessionCacheDirectory().DIRECTORY_SEPARATOR.'timestamp';
    $timestamp = file_get_contents($timestampFile);
    $timestamp = @intval($timestamp, 10);
    if (!$timestamp > 0) {
      // If no timestamp file then set current time
      $timestamp = time();
    }
    return $timestamp;
  }

  public function cleanUploadSessionCache() {
    $dir = $this->getSessionCacheDirectory();
    if (!empty($dir) && file_exists($dir)) {
      if (!function_exists('rmdir_recursive')) {
        function rmdir_recursive($dir) {
          if (is_dir($dir)) {
            $objects = scandir($dir);
            foreach ($objects as $object) {
              if ($object != '.' && $object != '..') {
                if (is_dir($dir.DIRECTORY_SEPARATOR.$object)) {
                  rmdir_recursive($dir.DIRECTORY_SEPARATOR.$object);
                } else {
                  unlink($dir.DIRECTORY_SEPARATOR.$object);
                }
              }
            }
            reset($objects);
            rmdir($dir);
          }
        }
      }
      rmdir_recursive($dir);
    }
  }

}