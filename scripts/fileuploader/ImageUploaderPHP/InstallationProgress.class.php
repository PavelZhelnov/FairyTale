<?php
require_once 'Uploader.class.php';

class InstallationProgress {

  private $_parent;

  public $attributes;

  
	private $_AltInstallerHtml;
	/**
	* @return string
	*/
	public function getAltInstallerHtml() {
		if (isset($this->_AltInstallerHtml))
			return $this->_AltInstallerHtml;
		else
			return null;
	}
	public function setAltInstallerHtml($value) {
		$this->_AltInstallerHtml = $value;
	}
	
	private $_BeforeIE6XPSP2InstructionsHtml;
	/**
	* @return string
	*/
	public function getBeforeIE6XPSP2InstructionsHtml() {
		if (isset($this->_BeforeIE6XPSP2InstructionsHtml))
			return $this->_BeforeIE6XPSP2InstructionsHtml;
		else
			return null;
	}
	public function setBeforeIE6XPSP2InstructionsHtml($value) {
		$this->_BeforeIE6XPSP2InstructionsHtml = $value;
	}
	
	private $_BeforeIE6XPSP2ProgressHtml;
	/**
	* @return string
	*/
	public function getBeforeIE6XPSP2ProgressHtml() {
		if (isset($this->_BeforeIE6XPSP2ProgressHtml))
			return $this->_BeforeIE6XPSP2ProgressHtml;
		else
			return null;
	}
	public function setBeforeIE6XPSP2ProgressHtml($value) {
		$this->_BeforeIE6XPSP2ProgressHtml = $value;
	}
	
	private $_CommonHtml;
	/**
	* @return string
	*/
	public function getCommonHtml() {
		if (isset($this->_CommonHtml))
			return $this->_CommonHtml;
		else
			return null;
	}
	public function setCommonHtml($value) {
		$this->_CommonHtml = $value;
	}
	
	private $_IE6XPSP2InstructionsHtml;
	/**
	* @return string
	*/
	public function getIE6XPSP2InstructionsHtml() {
		if (isset($this->_IE6XPSP2InstructionsHtml))
			return $this->_IE6XPSP2InstructionsHtml;
		else
			return null;
	}
	public function setIE6XPSP2InstructionsHtml($value) {
		$this->_IE6XPSP2InstructionsHtml = $value;
	}
	
	private $_IE6XPSP2ProgressHtml;
	/**
	* @return string
	*/
	public function getIE6XPSP2ProgressHtml() {
		if (isset($this->_IE6XPSP2ProgressHtml))
			return $this->_IE6XPSP2ProgressHtml;
		else
			return null;
	}
	public function setIE6XPSP2ProgressHtml($value) {
		$this->_IE6XPSP2ProgressHtml = $value;
	}
	
	private $_IE7InstructionsHtml;
	/**
	* @return string
	*/
	public function getIE7InstructionsHtml() {
		if (isset($this->_IE7InstructionsHtml))
			return $this->_IE7InstructionsHtml;
		else
			return null;
	}
	public function setIE7InstructionsHtml($value) {
		$this->_IE7InstructionsHtml = $value;
	}
	
	private $_IE7ProgressHtml;
	/**
	* @return string
	*/
	public function getIE7ProgressHtml() {
		if (isset($this->_IE7ProgressHtml))
			return $this->_IE7ProgressHtml;
		else
			return null;
	}
	public function setIE7ProgressHtml($value) {
		$this->_IE7ProgressHtml = $value;
	}
	
	private $_IE8InstructionsHtml;
	/**
	* @return string
	*/
	public function getIE8InstructionsHtml() {
		if (isset($this->_IE8InstructionsHtml))
			return $this->_IE8InstructionsHtml;
		else
			return null;
	}
	public function setIE8InstructionsHtml($value) {
		$this->_IE8InstructionsHtml = $value;
	}
	
	private $_IE8ProgressHtml;
	/**
	* @return string
	*/
	public function getIE8ProgressHtml() {
		if (isset($this->_IE8ProgressHtml))
			return $this->_IE8ProgressHtml;
		else
			return null;
	}
	public function setIE8ProgressHtml($value) {
		$this->_IE8ProgressHtml = $value;
	}
	
	private $_InstructionsCssClass;
	/**
	* @return string
	*/
	public function getInstructionsCssClass() {
		if (isset($this->_InstructionsCssClass))
			return $this->_InstructionsCssClass;
		else
			return null;
	}
	public function setInstructionsCssClass($value) {
		$this->_InstructionsCssClass = $value;
	}
	
	private $_MacInstallJavaHtml;
	/**
	* @return string
	*/
	public function getMacInstallJavaHtml() {
		if (isset($this->_MacInstallJavaHtml))
			return $this->_MacInstallJavaHtml;
		else
			return null;
	}
	public function setMacInstallJavaHtml($value) {
		$this->_MacInstallJavaHtml = $value;
	}
	
	private $_InstallJavaHtml;
	/**
	* @return string
	*/
	public function getInstallJavaHtml() {
		if (isset($this->_InstallJavaHtml))
			return $this->_InstallJavaHtml;
		else
			return null;
	}
	public function setInstallJavaHtml($value) {
		$this->_InstallJavaHtml = $value;
	}
	
	private $_ProgressCssClass;
	/**
	* @return string
	*/
	public function getProgressCssClass() {
		if (isset($this->_ProgressCssClass))
			return $this->_ProgressCssClass;
		else
			return null;
	}
	public function setProgressCssClass($value) {
		$this->_ProgressCssClass = $value;
	}
	
	private $_ProgressHtml;
	/**
	* @return string
	*/
	public function getProgressHtml() {
		if (isset($this->_ProgressHtml))
			return $this->_ProgressHtml;
		else
			return null;
	}
	public function setProgressHtml($value) {
		$this->_ProgressHtml = $value;
	}
	
	private $_ProgressImageUrl;
	/**
	* @return string
	*/
	public function getProgressImageUrl() {
		if (isset($this->_ProgressImageUrl))
			return $this->_ProgressImageUrl;
		else
			return null;
	}
	public function setProgressImageUrl($value) {
		$this->_ProgressImageUrl = $value;
	}
	
	private $_ShowInstallationScreen;
	/**
	* @return undefined
	*/
	public function getShowInstallationScreen() {
		if (isset($this->_ShowInstallationScreen))
			return $this->_ShowInstallationScreen;
		else
			return null;
	}
	public function setShowInstallationScreen($value) {
		$this->_ShowInstallationScreen = $value;
	}
	
	private $_ShowDownloadingScreen;
	/**
	* @return boolean
	*/
	public function getShowDownloadingScreen() {
		if (isset($this->_ShowDownloadingScreen))
			return $this->_ShowDownloadingScreen;
		else
			return null;
	}
	public function setShowDownloadingScreen($value) {
		$this->_ShowDownloadingScreen = $value;
	}
	
	private $_UpdateInstructions;
	/**
	* @return string
	*/
	public function getUpdateInstructions() {
		if (isset($this->_UpdateInstructions))
			return $this->_UpdateInstructions;
		else
			return null;
	}
	public function setUpdateInstructions($value) {
		$this->_UpdateInstructions = $value;
	}
	

  /**
   * 
   * Installation Progress
   * @param $parent Uploader Parent uploader control
   */
  function __construct($parent = NULL){
    $this->_parent = $parent;

    $parent->addPreRenderCallback(array($this, 'preRenderCallback'));

    
		$this->setBeforeIE6XPSP2InstructionsHtml('<p>To install Image Uploader, please reload the page and click 
the <strong>Yes</strong> button when you see the control installation dialog. 
If you don\'t see installation dialog, please check your security settings.</p>');
		$this->setBeforeIE6XPSP2ProgressHtml('<p>To install Image Uploader, please wait until the control will be loaded and click 
the <strong>Yes</strong> button when you see the installation dialog.</p>');
		$this->setCommonHtml('<p>Aurigma Image Uploader control is necessary to upload 
your files quickly and easily. You will be able to select multiple images in user-friendly 
interface instead of clumsy input fields with <strong>Browse</strong> button.</p>');
		$this->setIE6XPSP2InstructionsHtml('<p>To install Image Uploader, please click on the <strong>Information Bar</strong> 
and select <strong>Install ActiveX Control</strong> from the dropdown menu. After page reload click 
<strong>Install</strong> when you see the control installation dialog. If you don\'t see Information Bar, 
please try to reload the page and/or check your security settings.</p>');
		$this->setIE6XPSP2ProgressHtml('<p>Please wait until the control will be loaded.</p>');
		$this->setIE7InstructionsHtml('<p>To install Image Uploader, please click on the <strong>Information Bar</strong> 
and select <strong>Install ActiveX Control</strong> or <strong>Run ActiveX Control</strong> from the dropdown menu.</p>
<p>Then either click <strong>Run</strong> or after the page reload click <strong>Install</strong> when you see the 
control installation dialog. If you don\'t see Information Bar, please try to reload the page and/or check your security 
settings.</p>');
		$this->setIE7ProgressHtml('<p>Please wait until the control will be loaded.</p>');
		$this->setIE8InstructionsHtml('<p>To install Image Uploader, please click on the <strong>Information Bar</strong> 
and select <strong>Install This Add-on</strong> or <strong>Run Add-on</strong> from the dropdown menu.</p>
<p>Then either click <strong>Run</strong> or after the page reload click <strong>Install</strong> when you see the 
control installation dialog. If you don\'t see Information Bar, please try to reload the page and/or check your 
security settings.</p>');
		$this->setIE8ProgressHtml('<p>Please wait until the control will be loaded.</p>');
		$this->setMacInstallJavaHtml('<p>Use the <a href=\"http://support.apple.com/kb/HT1338\">Software Update</a> 
feature (available on the Apple menu) to check that you have the most up-to-date version of Java for your Mac.</p>');
		$this->setInstallJavaHtml('<p>Please <a href=\"http://www.java.com/getjava/\">download</a> and 
install Java.</p>');
		$this->setProgressHtml('<p><img src=\"{0}\" /><br />
Loading Aurigma Image Uploader...</p>');
		$this->setProgressImageUrl('Scripts/InstallationProgress.gif');
		$this->setShowInstallationScreen(true);
		$this->setShowDownloadingScreen(true);
		$this->setUpdateInstructions('You need to update Image Uploader control. Click <strong>Install</strong> 
or <strong>Run</strong> button when you see the control installation dialog. 
If you don\'t see installation dialog, please try to reload the page.');

    $this->attributes = array();
    
		$this->attributes['AltInstallerHtml'] = array('jsName' => 'altInstallerHtml','jsType' => 'String','defaultValue' => '');
		$this->attributes['BeforeIE6XPSP2InstructionsHtml'] = array('jsName' => 'beforeIE6XPSP2InstructionsHtml','jsType' => 'String','defaultValue' => '<p>To install Image Uploader, please reload the page and click 
the <strong>Yes</strong> button when you see the control installation dialog. 
If you don\'t see installation dialog, please check your security settings.</p>');
		$this->attributes['BeforeIE6XPSP2ProgressHtml'] = array('jsName' => 'beforeIE6XPSP2ProgressHtml','jsType' => 'String','defaultValue' => '<p>To install Image Uploader, please wait until the control will be loaded and click 
the <strong>Yes</strong> button when you see the installation dialog.</p>');
		$this->attributes['CommonHtml'] = array('jsName' => 'commonHtml','jsType' => 'String','defaultValue' => '<p>Aurigma Image Uploader control is necessary to upload 
your files quickly and easily. You will be able to select multiple images in user-friendly 
interface instead of clumsy input fields with <strong>Browse</strong> button.</p>');
		$this->attributes['IE6XPSP2InstructionsHtml'] = array('jsName' => 'IE6XPSP2InstructionsHtml','jsType' => 'String','defaultValue' => '<p>To install Image Uploader, please click on the <strong>Information Bar</strong> 
and select <strong>Install ActiveX Control</strong> from the dropdown menu. After page reload click 
<strong>Install</strong> when you see the control installation dialog. If you don\'t see Information Bar, 
please try to reload the page and/or check your security settings.</p>');
		$this->attributes['IE6XPSP2ProgressHtml'] = array('jsName' => 'IE6XPSP2ProgressHtml','jsType' => 'String','defaultValue' => '<p>Please wait until the control will be loaded.</p>');
		$this->attributes['IE7InstructionsHtml'] = array('jsName' => 'IE7InstructionsHtml','jsType' => 'String','defaultValue' => '<p>To install Image Uploader, please click on the <strong>Information Bar</strong> 
and select <strong>Install ActiveX Control</strong> or <strong>Run ActiveX Control</strong> from the dropdown menu.</p>
<p>Then either click <strong>Run</strong> or after the page reload click <strong>Install</strong> when you see the 
control installation dialog. If you don\'t see Information Bar, please try to reload the page and/or check your security 
settings.</p>');
		$this->attributes['IE7ProgressHtml'] = array('jsName' => 'IE7ProgressHtml','jsType' => 'String','defaultValue' => '<p>Please wait until the control will be loaded.</p>');
		$this->attributes['IE8InstructionsHtml'] = array('jsName' => 'IE8InstructionsHtml','jsType' => 'String','defaultValue' => '<p>To install Image Uploader, please click on the <strong>Information Bar</strong> 
and select <strong>Install This Add-on</strong> or <strong>Run Add-on</strong> from the dropdown menu.</p>
<p>Then either click <strong>Run</strong> or after the page reload click <strong>Install</strong> when you see the 
control installation dialog. If you don\'t see Information Bar, please try to reload the page and/or check your 
security settings.</p>');
		$this->attributes['IE8ProgressHtml'] = array('jsName' => 'IE8ProgressHtml','jsType' => 'String','defaultValue' => '<p>Please wait until the control will be loaded.</p>');
		$this->attributes['InstructionsCssClass'] = array('jsName' => 'instructionsCssClass','jsType' => 'String','defaultValue' => '');
		$this->attributes['MacInstallJavaHtml'] = array('jsName' => 'macInstallJavaHtml','jsType' => 'String','defaultValue' => '<p>Use the <a href=\"http://support.apple.com/kb/HT1338\">Software Update</a> 
feature (available on the Apple menu) to check that you have the most up-to-date version of Java for your Mac.</p>');
		$this->attributes['InstallJavaHtml'] = array('jsName' => 'installJavaHtml','jsType' => 'String','defaultValue' => '<p>Please <a href=\"http://www.java.com/getjava/\">download</a> and 
install Java.</p>');
		$this->attributes['ProgressCssClass'] = array('jsName' => 'progressCssClass','jsType' => 'String','defaultValue' => '');
		$this->attributes['ProgressHtml'] = array('jsName' => 'progressHtml','jsType' => 'String','defaultValue' => '<p><img src=\"{0}\" /><br />
Loading Aurigma Image Uploader...</p>');
		$this->attributes['ProgressImageUrl'] = array('jsName' => 'progressImageUrl','jsType' => 'String','defaultValue' => 'Scripts/InstallationProgress.gif');
		$this->attributes['ShowInstallationScreen'] = array('jsName' => 'showInstallationScreen','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['ShowDownloadingScreen'] = array('jsName' => 'showDownloadingScreen','jsType' => 'Boolean','defaultValue' => true);
		$this->attributes['UpdateInstructions'] = array('jsName' => 'updateInstructions','jsType' => 'String','defaultValue' => 'You need to update Image Uploader control. Click <strong>Install</strong> 
or <strong>Run</strong> button when you see the control installation dialog. 
If you don\'t see installation dialog, please try to reload the page.');
  }

  function preRenderCallback() {
    $scripts = array('aurigma.uploader', 'aurigma.uploader.installationprogress');
    foreach ($scripts as $script) {
      $this->_parent->addScriptFileName($script, $this->_parent->getDebugScriptLevel() ?
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
    $sb .= 'var u = this, ip = new $au.installationProgress(u);';

    foreach ($this->attributes as $methodName => $value) {

      $clientMethod = empty($value['jsName']) ? null : $value['jsName'];
      $clientType = empty($value['jsType']) ? null : $value['jsType'];
      $defaultValue = isset($value['defaultValue']) ? $value['defaultValue'] : null;

      if (!empty($clientMethod) && !empty($clientType)) {

        $methodName = 'get' . $methodName;
        $value = $this->$methodName();

        // Do not render properties with default value
        if ($defaultValue === null || $defaultValue != $value . '') {
          switch (strtolower($clientType)) {
            case 'string':
              $value = "'" . $value . "'";
              break;
            case 'boolean':
              $value = $value ? 'true' : 'false';
              break;
          }

          $sb .= "ip.$clientMethod($value);";
        }
      }
    }

    $sb .= '}';
    return $sb;
  }

}