<?php

class AdminMenuItemsView extends Slot {

	public $ModuleID = 53;
    public $SectionID = 17;
    public $Task = 'view';

    private $item;

    private $orderby = array(
		'Date' => array(
			'sortColumn' => 'date',
			'sortType' => 'desc',
		),
	);
    private $sort_array = array();
    private $sortby = '';
    private $imagePath;
    private $menuitems = array();
    private $contentpages = array();

    const URL_ADMIN_MENU_ITEMS = '/Admin/AdminMenuItems/';

    function AdminMenuItemsView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImagePath'];
	}

	function init() {
		global $PHP_SELF;
        $this->Scheme = $this->Action->setScheme($this->SectionID);
		if($this->Scheme != 'finish_delete' && $this->Scheme != 'finish_save' && $this->Scheme!='finish') {
				switch(@$this->LocalTarget[1]) {
				case 'EditItem':
					if (isset($this->LocalTarget[2])) {
						$this->Scheme = 'action';
						$this->Task = 'view';
						$request['langid']=$this->LM->Langs[$this->language];
						$request['id']=@$this->LocalTarget[2];
						$this->Action->processEvent($this->SectionID,'edit',$request,$this);
                        $this->item = $this->PreparedTemplates;
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					} else
					if(empty($this->PreparedTemplates)) header("Location: ".$this->Home.self::URL_ADMIN_MENU_ITEMS);
				break;
				case 'DeleteItem':
					if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
						$this->Scheme = 'action';
						$this->Task="edit";
						$this->Action->processEvent($this->SectionID,'edit',array('id' => $this->LocalTarget[2]),$this);
                        $this->item = $this->PreparedTemplates;
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					}
					else header("Location: ".$this->Home.self::URL_ADMIN_MENU_ITEMS);
				break;
				case 'Up':
					if (isset($this->LocalTarget[2])) {
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'up',array('id'=>$this->LocalTarget[2]),$this)
						and header("Location: ".$this->Home. self::URL_ADMIN_MENU_ITEMS);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					} else header("Location: ".$this->Home. self::URL_ADMIN_MENU_ITEMS);
				break;
				case 'Down':
					if (isset($this->LocalTarget[2])) {
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'down',array('id'=>$this->LocalTarget[2]),$this)
						and header("Location: ".$this->Home. self::URL_ADMIN_MENU_ITEMS);
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					} else header("Location: ".$this->Home. self::URL_ADMIN_MENU_ITEMS);
				break;					
				
				default:
					$this->Scheme = 'default';
					$this->Task = 'view';
					$request['langid']=$this->LM->Langs[$this->language];
					$this->Action->processEvent($this->SectionID,'view',$request,$this);
					//if(empty($this->PreparedTemplates)) $this->Scheme = 'empty';
					break;
				}
			if(!empty($this->Request)) {
				switch($this->getRequestField('step')) {
					case 'auth':
						$this->validateForm() and $this->Action->authorize($this->SectionID,$this->getRequestField('form'),$this) and
						header("Location: ".$PHP_SELF.$this->SID);
					break;
					case 'edit': case "add":
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'update',$this->correctWords($this->getRequestField('form')),$this)
                        and header("Location: ".$this->Home.self::URL_ADMIN_MENU_ITEMS.'//saved');
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
					case 'delete':
						$this->Scheme="delete";
						$this->validateForm() and $this->Action->processEvent($this->SectionID,'delete',$this->getRequestField('form'),$this)
						and header("Location: ".$this->Home.self::URL_ADMIN_MENU_ITEMS.'//deleted');
						if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
					break;
				}
			}
		}
		if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
		$this->setSchemeTemplate($this->Scheme);

	}

	function validateForm() {
		switch($this->getRequestField('step')) {
			case 'auth':
				if(!is_AlphaNumDefis($this->getRequestFormField('username'),3,32)) $this->errors['username'] = $this->globalLangContent['error_view']['username'];
				if(!is_AlphaNumDefis($this->getRequestFormField('passw'),3,32)) $this->errors['passw'] = $this->globalLangContent['error_view']['passw'];
			break;
			case 'add': case 'edit':
                //TODO
                foreach($this->LM->Langs as $k=>$v) {
                    if(!is_FullText($this->Request['form']['name_langs'][$v-1]['name'],1,512)) $this->errors['name'] = $this->globalLangContent['error_view']['err_name'];
                    if(!is_FullText($this->Request['form']['name_langs'][$v-1]['description'],1,512)) $this->errors['description'] = $this->globalLangContent['error_view']['err_title'];
                }
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {	
		switch($this->Scheme) {
            case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'action': $this->fillActionItem(); break;
			case 'default': case 'view': $this->fillView(); break;
		}
	}

	function fillMessage() {
        /*switch($this->Scheme) {
			case 'finish_delete': $this->TempFillEls['message'] = $this->globalLangContent['message']['delete_info']; break;
			case 'finish_save': $this->TempFillEls['message'] = $this->globalLangContent['message']['save_info']; break;
			case 'finish': $this->TempFillEls['message'] = $this->Scheme == 'finish'? $this->localLangContent['message'][$this->Action->Tasks[$this->SectionID][$this->Task]['scheme']]: $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
			default: $this->TempFillEls['message'] = $this->printError($this->globalLangContent['error_model'][$this->PreparedTemplates['_error']]); break;
		}*/
        if (!empty($this->LocalTarget[1])) {
            switch ($this->LocalTarget[1]) {
                case 'saved': $this->TempFillEls['action_message'] = 'The Item has been saved successfully';break;
                case 'deleted': $this->TempFillEls['action_message'] = 'The Item has been deleted successfully';break;
            }
        }

    }

	function fillView() {
		if (!empty($this->PreparedTemplates)) {
			foreach($this->PreparedTemplates as $k => $v) {
				$this->TempFillEls['Menu'][$k] = array (
				    'urledit' => makeLink($this->Home.self::URL_ADMIN_MENU_ITEMS.'EditItem/'.$v['id'],$this->globalLangContent['button']['admin_bt_edit'],array(),'',"class='menuitem'"),
				    'urldelete' => ($v['permanent']==1 ? '': ' / '.makeLink($this->Home.self::URL_ADMIN_MENU_ITEMS.'DeleteItem/'.$v['id'],$this->globalLangContent['button']['admin_bt_delete'], array(),'',"class='menuitem'")),
					'url' => $v['url'],					
					'id' => $v['id'],
					'class' => ($v['noactive']=='1'?'nonactive':'menuitem'),
					'name' => $v['name'],
					'navibullet' => ($k % 5) +1,
				);
				if(!empty($v['items'])) $this->setTargetArray($v['items'],$k,1,array(),array(),$v['noactive']);
			}
            $this->fillMessage();
        }

        $this->TempFillEls['Edit'] = $this->fillLanguageModel("MenuItem_Lang");

		$this->TempFillEls['url'] = inputText('form[url]',(!empty($this->Request)? $this->getRequestFormField('url') : 'Things/'),$this->correctSize('40'));
		$this->TempFillEls['active'] = inputCheckbox('form[noactive]', (!empty($this->Request)? $this->getRequestFormField('noactive') : ''), '', '1');
		$this->menuitems[0]=$this->globalLangContent['label']['root'];
		$this->setTargetArray2($this->PreparedTemplates);
		$this->TempFillEls['menuitems'] = inputSelect('form[parent_item]', $this->menuitems, $this->PreparedTemplates, '', ' disabled=\'true\'');
		//getting modules available
		$request['langid']=$this->LM->Langs[$this->language];
		$this->Action->processEvent($this->SectionID,'getmodules',$request,$this);
		$this->modules = mergeArrays(array('0' => ' --- Choose Module --- '),$this->Action->getTemplate($this->SectionID,'getmodules'));
		$this->TempFillEls['modules'] = inputSelect('form[module]', $this->modules, '', ' onchange=\'toggleModule();\'');
		
		$request['langid']=$this->LM->Langs[$this->language];
		$this->Action->processEvent($this->SectionID,'getpages',$request,$this);		
		$this->contentpages[0]='--- Choose content page ---';
		$this->setTargetArrayPages($this->PreparedTemplates['pages']);
		$this->TempFillEls['contentpage'] = inputSelect('form[contentpage]', $this->contentpages, $this->PreparedTemplates, ' onchange=\'toggleContent();\'');
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);
		$this->PreparedTemplates = $this->Action->clearTemplate($this->SectionID,'view');
	}

	function fillActionItem() {
		global $PHP_SELF;
		$action = ($this->LocalTarget[1]=="DeleteItem"?'delete':'edit');
        $this->TempFillEls = array(
			'action' => $action,
			'id' => $this->PreparedTemplates['id'],
            'version' =>  $this->item['version'],
			'idhidden' => inputHidden('form[id]',(!empty($this->Request)? $this->getRequestFormField('id') : $this->PreparedTemplates['id'])),
			'active' => inputCheckbox('form[noactive]', ($this->PreparedTemplates['noactive']=='1'?TRUE:FALSE), '', '1'),
			'actionbutton' => ($action=='delete'?$this->globalLangContent['button']['admin_bt_delete']:$this->globalLangContent['button']['admin_bt_update']),
		);

        $this->TempFillEls['Edit'] = $this->fillLanguageModel("MenuItem_Lang", $action);

        //getting items tree options select
		$item = $this->PreparedTemplates;
		$request['langid']=$this->LM->Langs[$this->language];
		$this->Action->processEvent($this->SectionID,'view',$request,$this);
		$this->menuitems[0]=$this->globalLangContent['label']['root'];
		$this->setTargetArray2($this->PreparedTemplates);
		$this->TempFillEls['menuitems'] = ($action=='delete'?'':inputSelect('form[parent_item]', $this->menuitems, $item['parent_item'], '', ' disabled=\'true\''));
		
		//getting modules available
		$request['langid']=$this->LM->Langs[$this->language];
		$this->Action->processEvent($this->SectionID,'getmodules',$request,$this);
		$this->modules = mergeArrays(array('0' => ' --- Choose Module --- '),$this->Action->getTemplate($this->SectionID,'getmodules'));
		$this->TempFillEls['modules'] = (($item['permanent']==1||$action=='delete') ? ($item['module']>0? $this->PreparedTemplates['modules'][$item['module']]['path']:'' ): inputSelect('form[module]', $this->modules , $item['module'], ' onchange=\'toggleModule();\''));
		
		//getting infotexts to link options select
		$this->Action->processEvent($this->SectionID,'getpages',$request,$this);
		$this->contentpages[0]='--- Choose content page ---';
		$this->setTargetArrayPages($this->PreparedTemplates['pages']);

		$this->TempFillEls['contentpage'] = (($item['permanent']==1||$action=='delete') ? ($item['infotext']>0? $this->PreparedTemplates['pages'][$item['infotext']]['name']:'' ): inputSelect('form[contentpage]', $this->contentpages , $item['contentpage'], ' onchange=\'toggleContent();\''));
		!empty($this->PreparedTemplates['_error']) and $this->errors['model'] = $this->globalLangContent['error_model'][$this->PreparedTemplates['_error']];
		if(count($this->errors) > 0) $this->errors['header'] = $this->globalLangContent['error_view']['header_error'];
		foreach($this->errors as $k => $v) $this->TempFillEls[$k.'_error'] = $k=='header'? '<br><b>'.$v.'</b><p>' : $this->printError($v);
	}

	function setTargetArray($array = array(),$k, $level = 1,$subitems = array(), $subitems=array(),$noactive=0) {
		foreach($array as $key => $value) {
			$this->TempFillEls['Menu'][$k]['Items'][$value['id']] = array(
				'url' => $value['url'],
				'id' => $value['id'],
				'class' => ($value['noactive']=='1'?'nonactive': $noactive=='1'?'nonactive':'menuitem'),
				'name' => str_repeat("&nbsp;&nbsp;&nbsp;&nbsp;",$level).$value['name'],
			    'urledit' => makeLink($this->Home.self::URL_ADMIN_MENU_ITEMS.'EditItem/'.$value['id'],$this->globalLangContent['button']['admin_bt_edit'],array(),'',"class='menuitem'"),
			    'urldelete' => ($value['permanent']==1 ? '': ' / '.makeLink($this->Home. self::URL_ADMIN_MENU_ITEMS . 'DeleteItem/' .$value['id'],$this->globalLangContent['button']['admin_bt_delete'], array(),'',"class='menuitem'")),

			);
			if(!empty($value['items'])) {$this->setTargetArray($value['items'],$k,$level+1, array(), array(), $noactive);}
		}
		return $subitems;
	}


	function setTargetArray2($array = array(),$level = 0) {
		foreach($array as $key => $value) {
			$this->menuitems[$value['id']] = str_repeat("-",$level).$value['name'];
			if(!empty($value['items'])) $this->setTargetArray2($value['items'],$level+2);
		}
	}

	function setTargetArrayPages($array = array(),$level = 0) {
		foreach($array as $key => $value) {
			$this->contentpages[$value['id']] = $value['header'];
		}
	}

}
?>