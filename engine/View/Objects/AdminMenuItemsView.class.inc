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
    private $modules = array();

    const URL_ADMIN_MENU_ITEMS = '/Admin/AdminMenuItems/';

    function AdminMenuItemsView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImagePath'];
	}

	function init() {
		global $PHP_SELF;
        $this->DEFAULT_ELEMENT_SIZE = '40';

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
			case 'add': case 'edit':
                $this->errors = $this->validateByModel("MenuItem",$this->Request['form'], array());
			break;
		}
		if(count($this->errors) > 0) return FALSE;
		return TRUE;
	}

	function fillElements() {
        $this->fillMessage();
        switch($this->Scheme) {
            //case 'message': case 'finish': case 'finish_save': case 'finish_delete': $this->fillMessage(); break;
			case 'auth': $this->fillAuth(); break;
			case 'action': $this->fillActionItem(); break;
			case 'default': case 'view': $this->fillView(); break;
		}
	}

	function fillMessage() {
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
        }

        $this->prepareEditForm("default");
	}

	function fillActionItem() {
		global $PHP_SELF;
		$action = ($this->LocalTarget[1]=="DeleteItem"?'delete':'edit');
        $this->prepareEditForm($action);
	}

    function prepareEditForm($action) {
        $tempFillEls = $this->fillModel("MenuItem",
            $this->item,
            $action,
            $selectArrays = array(
                'parent_item' => $this->getParentItems(),
                'module' => $this->getModules(),
                'contentpage' => $this->getPages()
            )
        );

        $this->TempFillEls['Edit'][] = $tempFillEls;

    }

    function getPages() {
        $request['langid']=$this->LM->Langs[$this->language];
        $this->Action->processEvent($this->SectionID,'getpages',$request,$this);
        $this->contentpages[0]='--- Choose content page ---';
        $this->setTargetArrayPages($this->PreparedTemplates['pages']);
        return $this->contentpages;
    }

    function getParentItems() {
        $request['langid']=$this->LM->Langs[$this->language];
        $this->Action->processEvent($this->SectionID,'view',$request,$this);
        $this->menuitems[0]=$this->globalLangContent['label']['root'];
        $this->setTargetArrayForMenuItems($this->PreparedTemplates);
        return $this->menuitems;
    }

    function getModules() {
        $request['langid']=$this->LM->Langs[$this->language];
        $this->Action->processEvent($this->SectionID,'getmodules',$request,$this);
        $this->modules = mergeArrays(array('0' => ' --- Choose Module --- '),$this->Action->getTemplate($this->SectionID,'getmodules'));
        return $this->modules;
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


	function setTargetArrayForMenuItems($array = array(),$level = 0) {
		foreach($array as $key => $value) {
			$this->menuitems[$value['id']] = str_repeat("-",$level).$value['name'];
			if(!empty($value['items'])) $this->setTargetArrayForMenuItems($value['items'],$level+2);
		}
	}

	function setTargetArrayPages($array = array(),$level = 0) {
		foreach($array as $key => $value) {
			$this->contentpages[$value['id']] = $value['header'];
		}
	}

}
?>