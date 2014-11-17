<?php

class AdminContentItemView extends Slot {

    public $ModuleID = 3;
    public $SectionID = 20;
    public $Task = 'view';

    private $item;

    private $orderby = array(
        'contenttype_name' => array(
            'sortColumn' => 'contenttype_name',
            'sortType' => 'desc',
        ),
        'var' => array(
            'sortColumn' => 'var',
            'sortType' => 'desc',
        ),

    );
    private $sort_array = array();
    private $sortby = '';
    private $imagePath;

    private $contenttypes = array();
    private $modules = array();

    const HOME_URL = '/Admin/AdminContentItems/';

    function AdminContentItemView($pquery) {
        global $REGISTRY;
        $this->Slot($pquery);
        $this->imagePath = $REGISTRY['Core']['ImagePath'];
        $this->handleModel = 'ContentItem';
        $this->DEFAULT_ELEMENT_SIZE = '40';
        $request['langid']=$this->LM->Langs[$this->language];
        $this->modules = mergeArrays(array('0' => ' --- Choose Module --- '), $this->Action->Server->getGuide('module'));
        $this->contenttypes = mergeArrays(array('0' => ' --- Choose Content Type --- '), $this->Action->Server->getGuide('contenttype'));
    }

    function init() {
        global $PHP_SELF;

        $this->Scheme = $this->Action->setScheme($this->SectionID);
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
                    if(empty($this->PreparedTemplates)) header("Location: ".$this->Home.self::HOME_URL);
                break;
            case 'DeleteItem':
                if(!empty($this->LocalTarget[2]) && validate(intval($this->LocalTarget[2]))) {
                    $this->Scheme = 'action';
                    $this->Task="edit";
                    $this->Action->processEvent($this->SectionID,'edit',array('id' => $this->LocalTarget[2]),$this);
                    $this->item = $this->PreparedTemplates;
                    if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
                }
                else header("Location: ".$this->Home.self::HOME_URL);
                break;
            default:
                $this->Scheme = 'default';
                $this->Task = 'view';
                $request['langid']=$this->LM->Langs[$this->language];
                $this->Action->processEvent($this->SectionID,'view',$request,$this);

                if(empty($this->PreparedTemplates['curPage'])) {$this->Scheme = 'empty';}
                    else {$this->getPageControl($this->Home.self::HOME_URL,$this->sortby);}

                break;
        }
        if(!empty($this->Request)) {
            switch($this->getRequestField('step')) {
                case 'edit': case "add":
                $this->validateForm() and $this->Action->processEvent($this->SectionID,'update',$this->correctWords($this->getRequestField('form')),$this)
                and header("Location: ".$this->Home.self::HOME_URL.'//saved');
                if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
                break;
                case 'delete':
                    $this->Scheme="delete";
                    $this->validateForm() and $this->Action->processEvent($this->SectionID,'delete',$this->getRequestField('form'),$this)
                    and header("Location: ".$this->Home.self::HOME_URL.'//deleted');
                    if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
                    break;
            }
        }
        if(!empty($this->PreparedTemplates['_error'])) $this->Scheme = 'message';
        $this->setSchemeTemplate($this->Scheme);

    }

    function validateForm() {
        switch($this->getRequestField('step')) {
            case 'add': case 'edit':
                $this->errors = $this->validateByModel($this->handleModel, $this->Request['form'], array());
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
        if (!empty($this->PreparedTemplates['curPage'])) {
            foreach($this->PreparedTemplates['curPage'] as $k => $v) {
                $this->TempFillEls['Items'][$k] = array (
                    'urledit' => makeLink($this->Home.self::HOME_URL.'EditItem/'.$v['id'],$this->globalLangContent['button']['admin_bt_edit'],array(),'',"class='menuitem'"),
                    'urldelete' => (makeLink($this->Home.self::HOME_URL.'DeleteItem/'.$v['id'],$this->globalLangContent['button']['admin_bt_delete'], array(),'',"class='menuitem'")),
                    'module' => $this->modules[$v['module']],
                    'contenttype' => $this->contenttypes[$v['contenttype']],
                    'var' => $v['var'],
                    'id' => $v['id'],
                    'contenttype_name' => $v['contenttype_name'],
                    'module_name' => $v['module_name'],
                );
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
        $tempFillEls = $this->fillModel($this->handleModel,
            $this->item,
            $action,
            $selectArrays = array(
                'module' => $this->modules,
                'contenttype' => $this->contenttypes
            )
        );

        $this->TempFillEls['Edit'][] = $tempFillEls;

    }

    function getModules() {
        $request['langid']=$this->LM->Langs[$this->language];
        $this->Action->processEvent($this->SectionID,'getmodules',$request,$this);
        $this->modules = mergeArrays(array('0' => ' --- Choose Module --- '),$this->Action->getTemplate($this->SectionID,'getmodules'));
        return $this->modules;
    }

}
?>