<?php
include_once($CORE_PATH.'/Tools/Slot.functions.inc');
include_once($CORE_PATH.'/XTemplate.class.inc');
include_once($CORE_PATH.'/Tools/recaptchalib.php');

class Slot extends XTemplate {

	//protected $error = array();
	public $TempFillEls = array();
	public $isRelocate = false;
	
	public $ModuleID = 1;
	public $SectionID = 1;
	public $Task;
	public $ID;
	public $Action;
	public $PreparedTemplates = array();
	public $UA = array();
	public $Rewards = array();
	public $Home;
	public $XmlPath;
	public $WXmlPath;
	
	public $TemplateContents = '';
	public $TemplateElements = array();
	public $TemplateFilledElements = array();
	public $TemplateFile = '';
	public $TemplatePath = array();
	public $Templates = array();

	public $Name = '';
	public $VName = '';
	public $Type = '';
	public $TemplateName = '';
	public $Properties = array();
	public $LoadFunction = 'templateFile';
	public $Reset = TRUE;
	public $Scheme = '';

	public $Ready = FALSE;
	public $Result = FALSE;
	public $Locate = TRUE;

	public $Target = array();
	public $LocalTarget = array();
	public $SID;

	public $language;
	public $LM;
	public $globalLangContent = array();
	public $localLangContent = array();
	
	public $debugID = 0;

	public $Request = array();

	public $DB;

	public $errors = array();

	public $month = array('--Month--');
	public $day = array('--Day--');
	public $year = array('--Year--');
	public $hour = array('--Hour--');
	public $min = array('--Min--');

    public $DEFAULT_ELEMENT_SIZE = '40';

    function Relocate($path) {
		header("Location: ".$path);
		$this->isRelocate = true;
	}
	
	function Slot($pquery) {
		global $REGISTRY,$RequestBroker,$Server,$HOME_PATH,$PHP_SELF;		
		if (isset($_SERVER["REDIRECT_URL"])) $PHP_SELF=$_SERVER["REDIRECT_URL"];

		$this->language = $HOME_PATH;
		$this->Home = $REGISTRY['Core']['WebHome'];
		$this->XmlPath = $REGISTRY['Core']['XmlPath'];
		$this->WXmlPath = $REGISTRY['Core']['WXmlPath'];
		$this->Action = &$Server->getAction($this->SectionID);
		$this->Action->ModuleID = &$this->ModuleID;
		$this->LM = &$Server->getLM();
		$this->UA = &$Server->getUserAgent();
		$this->SID = $this->getSID();
		$this->Name = $pquery['Name'];
		$this->Request = $RequestBroker->getRequestFor($this->Name);
		isset($pquery['Locate']) and $this->Locate = $pquery['Locate'];
		$this->globalLangContent = &$this->LM->globalContent;
		$this->Locate and $this->ModuleID!=1 and $this->localLangContent = $this->LM->moduleContent($this->ModuleID);
		$this->VName = isset($pquery['VName'])? $pquery['VName'] : $this->Name;
		debug('Slot ('.$this->Name.')',"VName = '".$this->VName."'<br>");
		$this->Type = $pquery['Type'];
		if($this->TemplateName != $pquery['Template']) {
			$this->TemplateName = $pquery['Template'];
			$reset = TRUE;
		}
		!empty($pquery['Templates']) and $this->Templates = $pquery['Templates'];
		$this->Properties = $pquery['Properties'];
		$this->ID = !empty($this->Properties['id'])? $this->Properties['id'] : 0;
		$this->_ModuleID = !empty($this->Properties['moduleid'])? $this->Properties['moduleid'] : 0;
		$this->setSchemeTemplate(!empty($this->Properties['scheme'])? $this->Properties['scheme'] : 'default');
		$this->setTemplatePath();
		$this->Target = $pquery['Target'];
		$this->LocalTarget = empty($pquery['LocalTarget'])? array() : $pquery['LocalTarget'];
		$this->Ready = FALSE;
		$this->Result = FALSE;
		$this->TemplateFilledElements = array();
		$this->Reset = TRUE;
		$this->TempFillEls = &$this->TemplateFilledElements;
		for($i = 1; $i < 32; $i++) $this->day[$i] = date2pg($i);
		for($i = 1; $i < 13; $i++) $this->month[$i] = date2pg($i);
		for($i = date('Y',time())-10; $i>date('Y',time())-100; $i--) $this->year[$i] = $i;
		for($i = 18; $i < 100; $i++) $this->age[$i] = $i;
		$this->ImagePath = $REGISTRY['Core']['ImagePath'];
		$this->ImageWPath = $REGISTRY['Core']['ImageWPath'];
	}

	function correctWords($array = array(),$HTML = false) {
		is_array($array) or $array = array();
		foreach($array as $key => $value)
			$array[$key] = is_array($value)? $this->correctWords($value) : $this->_replaceHTML($value,$HTML);
		return $array;
	}
	
	function _replaceHTML($value = '',$HTML = false) {
		if($HTML) {
			$value = preg_replace("/\<p\>/i","{p}",$value);
			$value = preg_replace("/\<br\>/i","{br}",$value);
		}
		$value = trim(strip_tags($value));
		if($HTML) {
			$value = preg_replace("/\{p\}/i","<p>",$value);
			$value = preg_replace("/\{br\}/i","<br>",$value);
		}
		return $value;
	}

	function getWordWrap($text,$cut,$break,$flag = false,$len = 0) {
		if(!$flag) {
			$text = preg_replace("/-| - /"," - ",$text);
			$text = preg_replace("/,|, /",", ",$text);
		}
		$words = preg_split("/ /",$text);
		foreach($words as $key => $value) {
			if(strlen($value)>$len) $len = strlen($value);
			$words[$key] = $len > $cut? wordwrap($words[$key],$cut,"$break",1) : $words[$key];
		}
		$text = implode(" ",$words);
		$text = preg_replace("/\\n/i","<br>",$text);
		return $text;
	}

	function getPageControl($self,$sort = '') {
		$per_page = isset($this->PreparedTemplates['pageRecordsQty'])? $this->PreparedTemplates['pageRecordsQty'] : 10;
		$num_rows = isset($this->PreparedTemplates['recordsTotal'])? $this->PreparedTemplates['recordsTotal'] : 0;
		$cur_page = isset($this->PreparedTemplates['curPageNumber'])? $this->PreparedTemplates['curPageNumber'] -1 : 0;
		$pages_total = isset($this->PreparedTemplates['pagesTotal'])? $this->PreparedTemplates['pagesTotal'] : 0;
		if($this->PreparedTemplates['curPageNumber'] > $this->PreparedTemplates['pagesTotal'] && count($this->PreparedTemplates['curPage'])) header("Location: ".$self.$this->SID);
		$this->Action->Navigator($self,$per_page,$num_rows,$cur_page,$sort,$this);
		$this->TempFillEls['navbar'] = implode('<br>',$this->Action->navbar);
		$this->TempFillEls['pagecontrol'][] = array(
			'prev' => $this->Action->prev,
			'first' => $this->Action->first,
			'pager' => implode(' | ',$this->Action->pager),
			'last' => $this->Action->last,
			'next' => $this->Action->next,
			'total' => $num_rows,
			'pages' => $pages_total,
			'gotopage' => inputText('form[goToPage]', '', $this->correctSize(8)),			
		);
		if(count($this->PreparedTemplates['curPage'])== 0) {
			if(!empty($this->PreparedTemplates['pagesTotal'])) header("Location: ".$self.$this->SID);
			else {
				$this->TempFillEls['navbar'] = $this->globalLangContent['message']['empty_page'];
				$this->TempFillEls['pagecontrol'] = array();
			}
		}
		else {
			if(empty($this->Action->pager)) $this->TempFillEls['pagecontrol'] = array();
			$this->TempFillEls['pagecontrol2'] = $this->TempFillEls['pagecontrol'];
		}
	}

	function getSID() {
		$SID = SID? SID : '';
		$SID = $this->UA['browser']=='ns'? (!empty($SID)? $SID.'&'.time() : time()) : $SID;
		$SID = !empty($_GET)? (!empty($SID)? '&'.$SID : '') : (!empty($SID)? '?'.$SID : '');
		return $SID;
	}

	function getRealValue($name) {
		return !empty($this->Request['form'])? $this->getRequestFormField($name) : $this->PreparedTemplates[$name];
	}

	function getRealValueMy($name) {
		return !$this->getRequestFormField($name)? $this->getRequestFormField($name) : $this->PreparedTemplates[$name];
	}

	function getRequestField($name) {
		return isset($this->Request[$name])? $this->Request[$name] : '';
	}

	function getRequestFormField($name,$id = false) {
		if($id) return isset($this->Request['form'][$name]['id'])? stripslashes($this->Request['form'][$name]['id']) : '';
		else return isset($this->Request['form'][$name])? stripslashes($this->Request['form'][$name]) : '';
	}

	function printError($error) {
		return isset($error)? '<span class=error>'.$error.' !</span>' : '';
	}

	function setSelected($name,$id = false) {
		return !empty($this->Request)? $this->getRequestFormField($name,$id) : (!empty($this->PreparedTemplates[$name])? ($id? $this->PreparedTemplates[$name]['id'] : $this->PreparedTemplates[$name]) : '');
	}

	function getSelect($name,$ext = false,$event = false) {
		return inputSelect('form['.$name.']'.($ext? $ext : ''),$this->{$name},
			$this->setSelected($name,$ext),$event? $event : '');
	}

	function getRadioSet($name,$array = array()) {
		foreach(radioButtons($this->{$name},'form['.$name.']',$this->setSelected($name)) as $value) $array[]['value'] = $value;
		return $array;
	}

	function correctSize($size) {
		return $this->UA['browser']=='ns'? ((int)$size <= 15? $size - 5 : $size - 10) : $size;
	}

	function getCheckbox($name) {
		return inputCheckbox('form['.$name.']',$this->setSelected($name));
	}

	function setBoxes($name,$guide = '') {
		foreach(checkBoxes($this->{($guide? $guide : $name)},'form['.$name.']',$this->setSelected($name)) as $key => $value) 
			$column[$key % 2][]['value'] = $value.'<br>';
		$this->TempFillEls['first_'.$name] = $column[0];
		$this->TempFillEls['second_'.$name] = $column[1];
	}

	function setSchemeTemplate($scheme = 'default') {
		global $REGISTRY;
		$this->Scheme = $scheme;
		@$tFile = !empty($this->Templates[$this->Scheme])? $this->Templates[$this->Scheme] : (!empty($REGISTRY['Templates'][$this->TemplateName])?$REGISTRY['Templates'][$this->TemplateName]:null);
		//toDA('tempFile',  array('$tFile' => $tFile, 'scheme' => $this->Scheme, 'err' => $this->TempFillEls['passive_message']));
		$this->setTemplateFile('/'.$tFile);
	}

	function init() {}

	function resetTemplate(&$content) { 
		$this->Ready = FALSE;
		$this->TemplateContents = $content;
		!empty($content) and $this->setTemplateID();
		$this->retrieveTemplate();
		$this->setTemplate($this->TemplateContents);
		$this->TemplateElements = &$this->getElements();
	}
	
	function render(&$reparse) {
		$this->isRelocate = false;
		$this->init();
		if($this->Reset or !empty($reparse)) { 
			!empty($reparse) and debug("Slot(".$this->Name.").render","reparsing<br>");
			$this->resetTemplate($reparse);
			$this->Reset = FALSE;
		}
		$this->fillElements();
		
		//error notification
		$err = $this->Action->getError($this->Task);
		if ($err !== false) {
			$this->TempFillEls['action_message_error'] = $this->globalLangContent['error_model'][$err];
		}
		
		if(!$this->isRelocate) {
			$this->Action->clearError($this->Task);
		}
		
		if (empty($this->Ready)) {
			$result = $this->parseTemplate($this->TempFillEls);
			unset ($this->TempFillEls);
			return $this->setResult($result);
		} else {
			return $this->setResult($this->Result);
		}
	}
	
	function fillElements() {}


	function fillAuth() {
		global $PHP_SELF;
		$this->TempFillEls = array(
			'formaction' => $PHP_SELF,
			'hidden' => inputHidden('o',$this->Name),
			'login' => inputText('form[login]',$this->getRequestFormField('login'),$this->correctSize('25'),' id="form[login]" required minlength=3 '),
			'passw' => inputPassword('form[password]',$this->getRequestFormField('password'),$this->correctSize('25'),' id="form[passw]" required minlength=3 '),
			'signedin' => inputCheckbox('form[signedin]', false, 'id="signedin"'),
			'action_message' => (empty($this->PreparedTemplates['action_message'])?'':$this->PreparedTemplates['action_message']),
		);
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<b>'.$v.'</b><p>' : $this->printError($v);
	}

	function message($message,$info) {
		global $REGISTRY;
		$this->setResult(sprintf($REGISTRY['Messages']['Slot'][$message],$this->Name,$info));
	}

	function setTemplatePath($path = array()) {
		$this->TemplatePath = array_merge($path,templatePath(array($this->Name)));
	}

	function setTemplateFile($name) {
		debug("setTemplateFile","$name<br>");
		if ($this->TemplateFile != $name) {
			$this->Reset = TRUE;
			$this->TemplateFile = $name;
		}
		$this->setTemplateID($this->TemplateFile);
	}

	function retrieveTemplate() {
		if(!empty($this->TemplateContents) or !$this->{$this->LoadFunction}()) return;
		if($this->Type == 'npblock') $this->setResult($this->TemplateContents);
	}

	function setResult($result) {
		$this->Result = $result;
		$this->Ready = TRUE;
		return $result;
	}

	function templateFile() {
		global $REGISTRY;
		if(!empty($this->TemplateContents)) return TRUE;
		debug ("Slot (".$this->Name.")","Loading Template: ".$this->TemplateFile."<br>");
		if(!empty($this->TemplateFile)) {
			$this->TemplateContents = readCacheFile($this->TemplateFile,$this->TemplatePath);
			if($this->TemplateContents) return TRUE;
			$this->message('TemplateFileNotExist',$this->TemplateFile);
			return FALSE;
		}
		else debug("<br>");
		$this->message('TemplateNotSet',$this->TemplateName);
		return FALSE;
	}

	function _debugDummyContent() {
		if(is_array($this->TemplateElements)) {
			foreach($this->TemplateElements as $key => $value)
				if(is_array($value)) $this->_debugDummyContentRecursive($value,$this->TempFillEls[$key]);
				else $this->TempFillEls[$key] = $key.'_Content';
		}
	}

	function _debugDummyContentRecursive($from,&$to) {
		foreach($from as $key => $value) {
			for($i = 0; $i < 5; $i++) {
				if(is_array($value)) $this->_debugDummyContentRecursive($value,$to[$key]);
				elseif($value == "slot") $to[$key] = array('id' => $this->debugID++);
				else $to[$key] = $key."_Content$i-".rand(0,100);
				$filled[$i][$key] = $to[$key];
			}
		}
		$to = $filled;
	}
	
	function authorizeMemberByCookie() {
		if($this->Name == 'Layout' and empty($this->Action->Security->currentuser->id)) {
			if(!empty($_COOKIE['bbuserid']) && !empty($_COOKIE['bbpassword'])) {
				$_user = $this->Action->Security->authorizeMemberByCookie(array('id' => $_COOKIE['bbuserid'],'passw' => $_COOKIE['bbpassword']));
				$user = $this->Action->VisualContent($_user,'0','cookie');
				if(!empty($user['_error'])) $this->Action->clearCookie();
				else $this->Action->set_Cookie($user);
			}
		}
	}

    function getPrepObjByLangId($prepObj, $languageId) {
        foreach($prepObj as $k=>$v) {
            if ($v['lang'] == $languageId) {
                return $v;
            }
        }
        return '';
    }

    function fillLanguageModel($className, $template=array(), $action="default") {
        $classMeta = getClassMethodsAnnotations($className);
        $menuArray = array();
        foreach($this->LM->Langs as $languagekey=>$languagevalue) {
            $prepObj = !empty($template['name_langs'])?
                $this->getPrepObjByLangId($template['name_langs']['data'], $languagevalue):'';

            foreach($classMeta as $itemMetaKey => $itemMetaValue) {
                $modelAnn = new ModelAnnotation( $itemMetaValue );
                $index = $languagevalue - 1;
                $menuArray[$languagevalue.'-l']['language_label'] = $this->globalLangContent['label']['language_'.$languagekey];
                $prepData = !empty($prepObj)?$prepObj[$itemMetaKey]:'';
                $fieldName = 'form[name_langs]['.$index.']['.$itemMetaKey.']';
                $addParameters = ' id="'.$fieldName.'" '.($modelAnn->required?' required ':'');
                switch ($modelAnn->type) {
                    case 'hidden':
                        $menuArray[$languagevalue.'-l'][$itemMetaKey] =
                            inputHidden($fieldName,$languagevalue);
                        break;
                    case 'string':
                        $menuArray[$languagevalue.'-l'][$itemMetaKey] =
                            ($action=='delete'?
                                $prepData:
                                inputText(
                                    $fieldName,
                                    (!empty($this->Request)? $this->Request['form']['name_langs'][$index][$itemMetaKey] :$prepData ),
                                    $this->correctSize($this->DEFAULT_ELEMENT_SIZE), $addParameters)
                            );
                        break;
                    case 'text':
                        $menuArray[$languagevalue.'-l'][$itemMetaKey] =
                            ($action=='delete'?
                                $prepData:
                                inputTextArea(
                                    $fieldName,
                                    (!empty($this->Request)? $this->Request['form']['name_langs'][$index][$itemMetaKey] : $prepData),
                                    $this->correctSize($this->DEFAULT_ELEMENT_SIZE),$this->correctSize('5'), $addParameters)
                            );
                        break;
                    default:
                        break;
                }
            }

        }
        return $menuArray;
    }


    function fillModel($className, $template=array(), $action="default", $selectArrays = array()) {
        //printArray($selectArrays);
        $classMeta = getClassMethodsAnnotations($className);
        $result = array();
        $result['langid']=$this->LM->Langs[$this->language];
        $result['action'] = $action;
        $result['actionbutton'] = ($action=='delete'?$this->globalLangContent['button']['admin_bt_delete']:$this->globalLangContent['button']['admin_bt_update']);

        $prepObj = (!empty($template)&&$action!="default")?$template:array();
        $tabIndex = 1;
        foreach($classMeta as $itemMetaKey => $itemMetaValue) {
            $modelAnn = new ModelAnnotation( $itemMetaValue );
            $prepData = !empty($prepObj)?$prepObj[$itemMetaKey]:'';

            $fieldName = 'form['.$itemMetaKey.']';
            $addParameters = ' id="'.$fieldName.'" '.($modelAnn->required?' required ':'');
            switch ($modelAnn->type) {
                case 'boolean':
                    $result[$itemMetaKey.'_stub'] = inputHidden($fieldName,0);
                    $result[$itemMetaKey] = ($action=='delete'?($prepData?"Y":"N"):
                        inputCheckbox($fieldName,
                        (!empty($this->Request['form'][$itemMetaKey])? $this->Request['form'][$itemMetaKey] :$prepData ), $prepData?TRUE:FALSE, $tabIndex++));
                    break;
                case 'hidden':
                    $result[$itemMetaKey] = inputHidden($fieldName,$prepData);
                    break;
                case 'string':
                    $result[$itemMetaKey] =
                            ($action=='delete'?
                                $prepData:
                                inputText(
                                    $fieldName,
                                    (!empty($this->Request['form'][$itemMetaKey])? $this->Request['form'][$itemMetaKey] :$prepData ),
                                    $this->correctSize($this->DEFAULT_ELEMENT_SIZE), $addParameters)
                            );
                    break;
                case 'text':
                    $result[$itemMetaKey] =
                            ($action=='delete'?
                                $prepData:
                                inputTextArea(
                                    $fieldName,
                                    (!empty($this->Request['form'][$itemMetaKey])? $this->Request['form'][$itemMetaKey] : $prepData),
                                    $this->correctSize($this->DEFAULT_ELEMENT_SIZE),$this->correctSize('5'), $addParameters)
                            );
                    break;
                case 'object':
                    $result['Language'] = $this->fillLanguageModel($modelAnn->object, $template, $action);
                    break;
                case 'select':
                    $result[$itemMetaKey] =
                            ($action=='delete'?
                                $selectArrays[$itemMetaKey][$prepData]:
                                inputSelect(
                                    $fieldName, $selectArrays[$itemMetaKey], $prepData, (!empty($modelAnn->onchange)?$modelAnn->onchange:''))
                            );
                    break;
                 default:
                    break;
            }
        }
        //merge
        $result = array_merge_recursive($result, $this->errors);
        return $result;
    }

    function validateByModel($className, $template=array(), $prefix = array()) {
        $classMeta = getClassMethodsAnnotations($className);
        $prepObj = (!empty($template)) ? $template : array();
        foreach ($classMeta as $itemMetaKey => $itemMetaValue) {
            $modelAnn = new ModelAnnotation($itemMetaValue);
            $prepData = !empty($prepObj[$itemMetaKey]) ? $prepObj[$itemMetaKey] : '';
            if ($modelAnn->uiignore) continue;
            if ($modelAnn->required && empty($prepData)) {
                $prefix[$itemMetaKey.'_error'] = $this->globalLangContent['error_view']['err_name'];//TODO
                continue;
            }
            switch ($modelAnn->type) {
                case 'string':
                    if(!empty($prepData) && !is_FullText($prepData,1,$modelAnn->maxlength)) {
                        $prefix[$itemMetaKey.'_error'] = $this->globalLangContent['error_view']['err_name'];//TODO
                    }
                    break;
                case 'object':
                    if (strpos($modelAnn->object, "_Lang")>0) {
                        foreach($template[$itemMetaKey] as $k=>$v) {
                            $langValidatetionError = $this->validateByModel($modelAnn->object, $v, array());
                            if (!empty($langValidatetionError)) {
                                $prefix['Language'][$v['lang'] . '-l'] = $langValidatetionError;
                            }

                        }
                    } else {
                        $this->validateByModel($modelAnn->object, $template[$itemMetaKey]);
                    }
                    break;
                default:
                    break;
            }
        }
        return $prefix;
    }


}
?>