<?php
require_once 'NirvanixException.class.php';
require_once 'Uploader.class.php';

class NirvanixExtender {

  private $_parent;

  private $_sizeBytes = 10485760;
  private $_appKey = '';
  private $_username = '';
  private $_password = '';
  private $_ipRestricted = false;
  private $_destFolderPath = '';
  private $_fileOverwrite = false;
  private $_firstByteExpiration = 600;
  private $_lastByteExpiration = 259200;

  /**
   * NirvanixExtender constructor
   * @param $parent Uploader Parent uploader control
   */
  function NirvanixExtender($parent = NULL) {
    $this->_parent = $parent;

    $parent->addPreRenderCallback(array($this, 'preRenderCallback'));
  }

  function preRenderCallback() {
    $scripts = array('aurigma.uploader', 'aurigma.uploader.nirvanix');
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

  function getSessionToken() {
    $url = "https://services.nirvanix.com/ws/Authentication/Login.ashx?" .
      "appKey=" . urlencode($this->getAppKey()) . 
      "&username=" . urlencode($this->getUsername()) .
      "&password=" . urlencode($this->getPassword());
    $xmlstring = $this->curlGet($url);
    // turn into an object for easier handling.
    $xml = new SimpleXMLElement($xmlstring);

    //throw error if can't get token
    if ($xml->ResponseCode != 0)
    throw new NirvanixException($xml);

    return (string)$xml->SessionToken;
  }

  function getUploadToken($sessionToken, &$uploadHost, &$uploadToken){
    $url = "https://services.nirvanix.com/ws/IMFS/GetStorageNodeExtended.ashx?"
    . "sessionToken=" . urlencode($sessionToken)
    . "&sizeBytes=" . urlencode($this->getSizeBytes());

    if ($this->getIpRestricted()) {
      $url = $url . "&consumerIP=" . urlencode($_SERVER['REMOTE_ADDR']);
    }

    $url = $url . "&ipRestricted=" . urlencode($this->getIpRestricted() ? 'true' : 'false')
    . "&destFolderPath=" . urlencode($this->getDestFolderPath())
    . "&fileOverwrite=" . urlencode($this->getFileOverwrite() ? 'true' : 'false')
    . "&firstByteExpiration=" . urlencode($this->getFirstByteExpiration())
    . "&lastByteExpiration=" . urlencode($this->getLastByteExpiration());

    $xmlstring = $this->curlGet($url);
    // turn into an object for easier handling.
    $xml = new SimpleXMLElement($xmlstring);

    //throw error if can't get token
    if ($xml->ResponseCode != 0)
    throw new NirvanixException($xml);

    $uploadHost = $xml->GetStorageNode->UploadHost;
    $uploadToken = $xml->GetStorageNode->UploadToken;
  }

  function curlGet($url) {
    // Init the CURL library
    $ch = curl_init();
    // Set the URL to request
    curl_setopt($ch, CURLOPT_URL, $url);

    // set the user agent based on the server settings.
    curl_setopt($ch, CURLOPT_USERAGENT, "Image Uploader PHP Library");
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

    //Don't verify remote server SSL certificate
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);

    // execute the curl request and return the xml response.
    $data = curl_exec($ch);

    if (curl_errno($ch) != 0)
    throw new Exception(curl_error($ch));

    if ($data){
      return (string)$data;
    }
    else{
      throw new Exception(curl_error($ch));
    }
    // clean up when finished with the curl library.
    curl_close($ch);
  }

  private function buildScript() {
    $sb = 'function() { ';
    $sb .= 'var u = this, nx = new $au.nirvanixExtender(u);';
    $sb .= "nx.destFolderPath('{$this->getDestFolderPath()}');";

    $sessionToken = $this->getSessionToken();
    $uploadHost = null;
    $uploadToken = null;
    $this->getUploadToken($sessionToken, $uploadHost, $uploadToken);

    $sb .= "nx.uploadHost('$uploadHost');";
    $sb .= "nx.uploadToken('$uploadToken');";

    $sb .= '}';
    return $sb;
  }

  /*********************
   * Public properties *
   *********************/

  //AppKey property
  function getAppKey(){
    return $this->_appKey;
  }
  function setAppKey($value){
    $this->_appKey = $value;
  }

  //DestFolderPath property
  function getDestFolderPath(){
    return $this->_destFolderPath;
  }
  function setDestFolderPath($value){
    $this->_destFolderPath = $value;
  }

  //FileOverwrite property
  function getFileOverwrite(){
    return (bool)$this->_fileOverwrite;
  }
  function setFileOverwrite($value){
    $this->_fileOverwrite=$value;
  }

  //FirstByteExpiration property
  function getFirstByteExpiration(){
    return $this->_firstByteExpiration;
  }
  function setFirstByteExpiration($value){
    $this->_firstByteExpiration=$value;
  }

  //IpRestricted property
  function getIpRestricted(){
    return (bool)$this->_ipRestricted;
  }
  function setIpRestricted($value){
    $this->_ipRestricted=$value;
  }

  //LastByteExpiration property
  function getLastByteExpiration(){
    return $this->_lastByteExpiration;
  }
  function setLastByteExpiration($value){
    $this->_lastByteExpiration=$value;
  }

  //Password property
  function getPassword(){
    return $this->_password;
  }
  function setPassword($value){
    $this->_password=$value;
  }

  //SizeBytes property
  function getSizeBytes(){
    return $this->_sizeBytes;
  }
  function setSizeBytes($value){
    $this->_sizeBytes=$value;
  }

  //Username property
  function getUsername(){
    return $this->_username;
  }
  function setUsername($value){
    $this->_username=$value;
  }
}