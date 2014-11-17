<?php

include_once($MODEL_PATH.'/ObjectsList.class.inc');
include_once($MODEL_PATH.'/Modules/Menu/MenuItem.class.inc');
include_once($MODEL_PATH.'/Modules/Menu/MenuItem_Lang.class.inc');

class MenuHandler extends Handler
{

    public $shortcutmenu;
    public $mainmenu =Array();


    function MenuHandler() {
        $this->Handler(true);
        $this->currentuser = new User();
    }

    function & getMenuItemAdmin($request){
        $menuitem = $this->createMenuItem();
        $this->parseRequest($request,$menuitem);
        $request['curPage']=$this->DB->SelectArray(Array('menuitem'),'id','where id='.$menuitem->id,0,0);
        if (empty($request['curPage'])) {
            $menuitem->_error = '16';
            return $menuitem;
        }
        $this->DB->initObject($menuitem);
        return $menuitem;
    }


    function deleteMenuItemAdmin($request){
        $menuitem = $this->createMenuItem();
        $this->parseRequest($request,$menuitem);
        $this->DB->initObject($menuitem);
        if($menuitem->permanent=='1') {
            $menuitem->_error=11;
            return $menuitem;
        }
        $this->DB->processObject($menuitem,'delete');
        return $menuitem;
    }

    function getMetaInfo($request=array()) {

        $selected=$this->DB->SelectAny('select CASE WHEN m.url!="" THEN m.url WHEN it.name!="" THEN it.name ELSE md.path END as url, ml.meta_info as keywords, ml.name as name, ml.description as description from menuitem m
				LEFT JOIN menuitem_lang ml ON ( m.id = ml.ownerid AND ml.lang ='.$request['langid'].' ) 
				left join infotext as it on m.contentpage=it.id 
				left join module as md on md.id=m.module 
				where (m.id = ml.ownerid and lang = '.$request['langid'].' and (m.url like "%'.$request['url'].'%" or it.name like "%'.$request['url'].'%"))');

        if (!empty($selected)) return $selected[0]; else
            return array();

    }

    function selectMainMenuAdmin($request=Array('langid'=>1)){
        $selected=$this->DB->SelectArray("menuitem m,menuitem_lang ml",'m.id,m.url,m.itorder,ml.description,m.noactive as noactive,m.parent_item,ml.name,m.permanent',array('m.id'=>array('='=>'ml.ownerid'),'lang'=>array('='=>$request['langid'])),0,0,0,array(),'CND_COMPLEX',array('and','and'));
        $mainmenu = array();
        if(!empty($selected)){
            $mainmenu=$this->makeMenu($selected);
        }
        return $mainmenu;
    }

    function saveMenuItemAdmin($request) {
        $mi=$this->createMenuItem();
        $this->parseRequest($request,$mi);

        if ($mi->id<1) {
            $selected=$this->DB->SelectArray("menuitem",'max(itorder) as maxitorder');
            $mi->itorder=$selected[0]['maxitorder']+1;
        }

        foreach ($mi->name_langs as $k=>$v) {
            if (sizeof($v)==1)
                $arobj = ObjToArray($mi->name_langs);
            array_splice($arobj,1);
        }
        $this->DB->processObject($mi);
        return $mi;
    }


    function selectMainMenu($request=Array('langid'=>1)){
        $selected=$this->DB->SelectArray("menuitem m
			    LEFT JOIN menuitem_lang ml ON ( m.id = ml.ownerid AND ml.lang =".$request['langid']." )
			    left join infotext as it on m.contentpage=it.id
			    left join module as md on md.id=m.module",'m.parent_item as pi, m.id,CASE WHEN m.url!="" THEN m.url WHEN it.name!="" THEN it.name ELSE  md.path END as url,ml.description as description,itorder, m.noactive as noactive,m.parent_item,ml.name,m.permanent, m.itorder',array('m.id'=>array('='=>'ml.ownerid'),'lang'=>array('='=>$request['langid']),'noactive'=>array('!='=>'1')),0,0,0,array(),'CND_COMPLEX',array('and','and','and'));
        if(!empty($selected)){
            $mainmenu=$this->makeMenu($selected);
        }
        return $mainmenu;
    }

    function selectModulesForMenu($request=Array('langid'=>1)){
        $selected = $this->DB->SelectGuide(array('module m left join module_lang as ml on ml.ownerid=m.id'),array('m.id','ml.name'),array('language'=>$request['langid'],'contentable'=>'1'));
        return $selected;
    }

    function getContentPages($request) {
        $request['fields']='it.name as name, it.id as id, itl.ownerid as owner, itl.language, itl.value as value, itl.header as header';
        if(empty($request['conditions']['itl.language'])) $request['conditions']['itl.language']=array('='=>$request['langid']);
        $request['pages']=$this->DB->SelectArray(Array('infotext as it left join infotext_lang as itl on it.id=itl.ownerid'),$request['fields'],'where itl.language='.$request['langid'].' order by it.id',0,0,0);
        return $request;
    }


    private function makeMenu($ar,$par=0) {
        $menu='';
        foreach($ar as $k=>$v){
            if ($v['parent_item']==$par) {
                $menu[$v['itorder']]['id']=$v['id'];
                $menu[$v['itorder']]['name']=$v['name'];
                $menu[$v['itorder']]['description']=$v['description'];
                $menu[$v['itorder']]['url']=$v['url'];
                $menu[$v['itorder']]['noactive']=$v['noactive'];
                $menu[$v['itorder']]['permanent']=$v['permanent'];
                $menu[$v['itorder']]['itorder']=$v['itorder'];
                //$menu[$v['itorder']]['pi']=$v['pi'];
                $menu[$v['itorder']]['items']=$this->makeMenu($ar,$v['id']);
                if (is_array($menu[$v['itorder']]['items'])) ksort($menu[$v['itorder']]['items']);
            }
        }
        if (is_array($menu)) ksort($menu);
        return $menu;
    }


    private function makeMenuAdmin($ar,$par=0) {
        $menu='';
        foreach($ar as $k=>$v){
            if ($v['parent_item']==$par) {
                $menu[$v['itorder']]['id']=$v['id'];
                $menu[$v['itorder']]['name']=$v['name'];
                $menu[$v['itorder']]['description']=$v['description'];
                $menu[$v['itorder']]['noactive']=$v['noactive'];
                $menu[$v['itorder']]['features']=$v['features'];
                $menu[$v['itorder']]['permanent']=$v['permanent'];
                $menu[$v['itorder']]['itorder']=$v['itorder'];
                $menu[$v['itorder']]['items']=$this->makeMenuAdmin($ar,$v['id']);
                if (is_array($menu[$v['itorder']]['items'])) ksort($menu[$v['itorder']]['items']);
            }
        }
        if (is_array($menu)) ksort($menu);
        return $menu;
    }

    private function createMenuItem() {
        $menuitem=new MenuItem();
        return $menuitem;
    }

}
?>