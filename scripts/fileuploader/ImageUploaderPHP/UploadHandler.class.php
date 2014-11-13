<?php

require_once 'UploadSession.class.php';

// sys_get_temp_dir function exists in PHP 5 >= 5.2.1
if ( !function_exists('sys_get_temp_dir')) {
  function sys_get_temp_dir() {
    if ($temp = ini_get('upload_tmp_dir')) {
      return $temp;
    }
    if ($temp = getenv('TMP')) {
      return $temp;
    }
    if ($temp = getenv('TEMP')) {
      return $temp;
    }
    if ($temp = getenv('TMPDIR')){
      return $temp;
    }
    $temp = tempnam(dirname(__FILE__), '');
    if (file_exists($temp)) {
      unlink($temp);
      return dirname($temp);
    }
    return null;
  }
}

/**
 * Handle upload requests from uploader.
 */
class UploadHandler {

  private static $_processed = false;

  protected $_uploadSession;
  private $_fileUploadedCallback;
  private $_allFilesUploadedCallback;

  private $_destination;
  private $_cacheAliveTimeout = 1800; // 30 minutes

  function __construct() {
    $this->_uploadSession = new UploadSession($_POST, $_FILES, $_SERVER);

    // set default cache directory
    $tempDir = rtrim(sys_get_temp_dir(), '/\\');
    $this->_uploadSession->getUploadCache()->setCacheRoot($tempDir . DIRECTORY_SEPARATOR .
      'uploader_c2215afa418f4cc2bc2c0f92746882f0');
  }

  /**
   * Add file uploaded callback function. Function will be called for every uploaded file.
   * @param callback $callback
   */
  public function setFileUploadedCallback($callback) {
    $this->_uploadSession->setFileUploadedCallback($callback);
  }

  public function setAllFilesUploadedCallback($callback) {
    $this->_uploadSession->setAllFilesUploadedCallback($callback);
  }

  public function getFileUploadedCallback() {
    return $this->_uploadSession->getFileUploadedCallback();
  }

  public function getAllFilesUploadedCallback() {
    return $this->_uploadSession->getAllFilesUploadedCallback();
  }

  public function getCacheAliveTimeout() {
    return $this->_cacheAliveTimeout;
  }

  /**
   * Set upload cache expire timeout.
   * After timeout expires all files for this upload session will be removed.
   * @param int $value Timeout in seconds
   */
  public function setCacheAliveTimeout($value) {
    $this->_cacheAliveTimeout = $value;
  }

  /**
   * Get temp directory for uploaded files
   */
  public function getUploadCacheDirectory() {
    return $this->_uploadSession->getUploadCache()->getCacheRoot();
  }

  /**
   * Set temp directory for uploaded files
   * @param string $value
   */
  public function setUploadCacheDirectory($value) {
    $this->_uploadSession->getUploadCache()->setCacheRoot($value);
  }

  public function processRequest() {
    if (UploadHandler::$_processed) {
      return;
    }

    UploadHandler::$_processed = true;
    $this->_uploadSession->processRequest();

    $this->removeExpiredSessions();
  }

  /**
   * Remove expired upload sessions
   */
  private function removeExpiredSessions() {
    $uploadCache = $this->_uploadSession->getUploadCache();
    $cacheRoot = $uploadCache->getCacheRoot();
    if (empty($cacheRoot) || !is_dir($cacheRoot)) {
      return;
    }
     
    $lastFullScan = $uploadCache->getLastFullScanTimestamp();
    $currentTimestamp = time();
     
    // Do not scan all cache too often
    if ($lastFullScan + $this->_cacheAliveTimeout / 2 > $currentTimestamp) {
      return;
    }
     
    $dirs = scandir($cacheRoot);
    foreach ($dirs as $dir) {
      if ($dir != '.' && $dir != '..') {
        $uploadCache = new UploadCache($dir);
        $uploadCache->setCacheRoot($cacheRoot);
        if ($uploadCache->getWriteTimestamp() + $this->_cacheAliveTimeout < $currentTimestamp) {
          $uploadCache->cleanUploadSessionCache();
        }
      }
    }

    $uploadCache->setLastFullScanTimestamp($currentTimestamp);
  }

  public function saveFiles($destination) {
    if (empty($destination)) {
      return;
    }
    rtrim($destination, '/\\');
    $this->_destination = $destination;

    $this->setFileUploadedCallback(array($this, 'saveUploadedFileCallback'));
    $this->processRequest();
  }

  /**
   * Save uploaded file callback
   * @param UploadedFile $uploadedFile
   */
  public function saveUploadedFileCallback($uploadedFile) {
    if (empty($this->_destination)) {
      return;
    }
    /* @var $uploadedFile UploadedFile */
    $relativePath = $uploadedFile->getRelativePath();
    if (empty($relativePath)) {
      $basePath = $this->_destination;
    } else {
      $relativePath = trim($relativePath, '/\\');
      $relativePath = preg_replace('#\\/#', DIRECTORY_SEPARATOR, $relativePath);
      $basePath = $this->_destination . DIRECTORY_SEPARATOR . $relativePath;
    }
    if (!is_dir($basePath)) {
      mkdir($basePath, 0777, true);
    }
    $basePath .= DIRECTORY_SEPARATOR;
    foreach ($uploadedFile->getConvertedFiles() as $convertedFile) {
      /* @var $convertedFile ConvertedFile */
      $name = $convertedFile->getName();
      $path_info = pathinfo($name);
      $i = 2;
      $fullFilePath = $basePath . $name;
      while (file_exists($fullFilePath)) {
        $fullFilePath = $basePath . $path_info['filename'] . '_' . $i . '.' . $path_info['extension'];
        $i++;
      }
      $convertedFile->moveTo($fullFilePath);
    }
  }
}