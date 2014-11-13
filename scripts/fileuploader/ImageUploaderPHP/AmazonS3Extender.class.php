<?php
require_once 'FileSettings.class.php';
require_once 'Uploader.class.php';

class AmazonS3Extender {

  private $_parent;

  /**
   * AmazonS3Extender constructor
   * @param $parent Uploader Parent uploader control
   */
  function AmazonS3Extender($parent = NULL) {
    $this->_parent = $parent;

    $parent->addPreRenderCallback(array($this, 'preRenderCallback'));

    $this->_policyExpiration = 86400; // 24 hours
  }

  function preRenderCallback() {

    // Add scripts to render
    $scripts = array('aurigma.uploader', 'aurigma.uploader.amazons3');
    foreach ($scripts as $script) {
      $this->_parent->addScriptFileName($script, $this->_parent->getDebugScriptLevel() > 0 ?
      $script . '.js' : $script . '.min.js');
    }

    $clientPreRender = $this->_parent->getClientEvents()->getPreRender();
    if (!isset($clientPreRender)) {
      $clientPreRender = array();
    }
    $clientPreRender[] = $this->buildScript();
    $this->_parent->getClientEvents()->setPreRender($clientPreRender);
  }

  private function buildScript() {
    $sb = 'function() { ';
    $sb .= 'var u = this, as3 = new $au.amazonS3Extender(u);';
    $sb .= "as3.bucket('{$this->_bucket}');";
    $sb .= "as3.accessKeyId('{$this->_AWSAccessKeyId}');";

    if (!empty($this->_bucketHostName)) {
      $sb .= "as3.bucketHostName('{$this->_bucketHostName}');";
    }

    $files = $this->getFiles();
    if (!empty($files)) {
      $sb .= 'as3.converters([';
      $first = true;
      foreach ($files as $file) {
        /* @var $file FileSettings */
        if (!$first) {
          $sb .= ',';
        } else {
          $first = false;
        }

        $sb .= '{';
        $sb .= "acl: '{$file->getAcl()}'";
        $sb .= ", key: '{$file->getKey()}'";

        $policy = $this->constructPolicy($file);
        $sb .= ", policy: '$policy'";

        $signature = $this->signPolicy($policy);
        $sb .= ", signature: '$signature'";

        $this->buildMetaProperties($file, $sb);

        $sb .= '}';

      }
      $sb .= ']);';
    }

    //remove session cookie
    $session_name = SESSION_PARAM_NAME;
    $sb .= "u.metadata().removeCustomField('$session_name')";

    $sb .= '}';
    return $sb;
  }

  function buildMetaProperties($fs, &$sb) {
    $meta = $fs->getMeta();
    if (empty($meta)) {
      return;
    }

    $sb .= ', meta: [';
    $first = true;
    foreach ($meta as $mp) {
      if (!$first) {
        $sb .= ', ';
      } else {
        $first = false;
      }

      if (isset($mp['name'])) {
        $name = $mp['name'];

        if (isset($mp['value'])) {
          $sb .= "{ name: '$name', value: '{$mp['value']}' }";
        } elseif (isset($mp['field'])) {
          $sb .= "{ name: '$name', field: '{$mp['field']}' }";
        }
      }
    }
    $sb .= ']';
  }

  /**
   *
   * Construct policy string
   * @param $settings FileSettings
   */
  function constructPolicy($settings) {
    $policy = '';
    $expDate =gmdate("Y-m-d\TH:i:s.000\Z", gmmktime() + $this->_policyExpiration);

    $policy .= "{ \"expiration\": \"" . $expDate . "\"";
    $policy .= ", \"conditions\": [";
    $policy .= "  {\"acl\": \"" . $settings->getAcl() . "\" }";
    $policy .= "  , {\"bucket\": \"" . $this->getBucket() . "\" }";
    $policy .= "  , {\"success_action_status\": \"200\"}";

    if ($settings->getMinFileSize() > 0 || $settings->getMaxFileSize() < 5368709120) {
      $policy .= ", [\"content-length-range\", {$settings->getMinFileSize()}, {$settings->getMaxFileSize()}]";
    }

    $key = $settings->getKey();
    $i = strpos($key, '${filename}');
    if ($i !== false) {
      $key = substr($key, 0, -11);
    }
    $policy .= "  , [\"starts-with\", \"\$key\", \"" . $key . "\"]";

    $meta = $settings->getMeta();
    if (!empty($meta)) {
      foreach ($meta as $mp) {
        $policy .= "  , [\"starts-with\", \"\$x-amz-meta-" . strtolower($mp['name']) . "\", \"\"]";
      }
    }

    $policy .= "]";
    $policy .= "}";

    return base64_encode($policy);;
  }

  function  signPolicy($policy) {
    // helper function binsha1 for amazon_hmac (returns binary value of sha1 hash)
    if (!function_exists('binsha1'))
    {
      if (version_compare(phpversion(), "5.0.0", ">=")) {
        function binsha1($d) { return sha1($d, true); }
      } else {
        function binsha1($d) { return pack('H*', sha1($d)); }
      }
    }

    $aws_secret = $this->_secretAccessKey;

    if (strlen($aws_secret) == 40)
    $aws_secret = $aws_secret.str_repeat(chr(0), 24);

    $ipad = str_repeat(chr(0x36), 64);
    $opad = str_repeat(chr(0x5c), 64);

    $hmac = binsha1(($aws_secret^$opad).binsha1(($aws_secret^$ipad).$policy));
    return base64_encode($hmac);
  }

  function getParentControl() {
    return $this->_parent;
  }

  function setParentControl($parent) {
    $this->_parent = $parent;
  }

  private $_AWSAccessKeyId;

  function getAWSAcceccKeyId() {
    return $this->_AWSAccessKeyId;
  }

  function setAWSAcceccKeyId($value) {
    $this->_AWSAccessKeyId = $value;
  }

  private $_secretAccessKey;

  function getSecretAccessKey() {
    return $this->_secretAccessKey;
  }

  function setSecretAccessKey($value) {
    $this->_secretAccessKey = $value;
  }

  private $_bucket;

  function getBucket() {
    return $this->_bucket;
  }

  function setBucket($value) {
    $this->_bucket = $value;
  }

  private $_bucketHostName;

  function getBucketHostName() {
    return $this->_bucketHostName;
  }

  function setBucketHostName($value) {
    $this->_bucketHostName = $value;
  }

  private $_policyExpiration;

  function getPolicyExpiration() {
    return $this->_policyExpiration;
  }

  function setPolicyExpiration($value) {
    $this->_policyExpiration = $value;
  }

  private $_files;

  function &getFiles() {
    return $this->_files;
  }

  function setFiles($value) {
    $this->_files = $value;
  }


}