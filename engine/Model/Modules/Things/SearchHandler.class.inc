<?php

class SearchHandler extends Handler {
	
	public $categorylist;
	public $categorylistid;

	
	function SearchHandler($calledbyson=true){
		$this->Handler($calledbyson);
	}


	function searchByKeyword($request = array()) {
		if (empty($request['search'])) return $request;
		$selected=$this->DB->SelectArray("infotext as it
				left join infotext_lang as itl on itl.ownerid=it.id and itl.language=".$request['langid'],
				'it.name as url, itl.header as name',
				array('UCASE(itl.value)'=>array('like'=>'%'.strtoupper($request['search']).'%')),0,0,0,array(),'CND_COMPLEX',array());
		$request['curPage'] = $selected;
		return $request;
	}
}
?>