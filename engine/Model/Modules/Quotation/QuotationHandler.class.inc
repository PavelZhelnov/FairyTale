<?php

include_once($MODEL_PATH.'/Modules/Quotation/Quotation.class.inc');
include_once($MODEL_PATH.'/Modules/Quotation/Quotation_Lang.class.inc');

class QuotationHandler extends Handler {
	
	public $currentuser;
	public $categorylist;
	public $categorylistid;

	
	function QuotationHandler($calledbyson=true){
		$this->Handler($calledbyson);
		$this->currentuser = new User();
	}

	function getCurrentUser($request){
		return $this->currentuser;
	}

	function selectQuotes($request) {		
		if(empty($request['fields'])) $request['fields']='q.id as id, ql.ownerid as owner, ql.language, ql.value as value';
		//if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		//if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='5';
		if(empty($request['conditions']['ql.language'])) $request['conditions']['ql.language']=array('='=>$request['langid']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('quotation as q left join quotation_lang as ql on q.id=ql.ownerid'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		//$request['recordsTotal']=$selected[0]['qty'];
		//$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);

		$request['curPage']=$this->DB->SelectArray(Array('quotation as q left join quotation_lang as ql on q.id=ql.ownerid'),$request['fields'],$request['conditions'],$this->getOrderBy($request),0,0,array(),'CND_COMPLEX',$relarr);
		return $request;
	} 
	
	function selectQuotationsAdmin($request) {		
		if(empty($request['fields'])) $request['fields']='q.id as id, ql.ownerid as owner, ql.language, ql.value as value';
		//if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		//if(empty($request['pageRecordsQty'])) $request['pageRecordsQty']='5';
		if(empty($request['conditions']['ql.language'])) $request['conditions']['ql.language']=array('='=>$request['langid']);
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('quotation as q left join quotation_lang as ql on q.id=ql.ownerid'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);

		$request['curPage']=$this->DB->SelectArray(Array('quotation as q left join quotation_lang as ql on q.id=ql.ownerid'),$request['fields'],$request['conditions'],$this->getOrderBy($request),0,0,array(),'CND_COMPLEX',$relarr);
		return $request;
	} 
	
	
	function getQuotation($request) {
   		$q = $this->createQuotation();
   		$this->parseRequest($request,$q);
   		$request['curPage']=$this->DB->SelectArray(Array('quotation'),'id','where id='.$q->id,0,0);
   		if (empty($request['curPage'])) {
   			$q->_error = '21';
   			return $q;
   		}
   		$this->DB->initObject($q);
   		return $q;
	}

	function saveQuotation($request) {
		$q=$this->createQuotation();
		$this->parseRequest($request,$q);
		$this->DB->processObject($q);
		return $q;
		
	}

	function deleteQuotation($request) {
		$q=$this->createQuotation();
		$this->parseRequest($request,$q);
		$selected=$this->DB->SelectArray(Array('quotation'),'*',array('id'=>$q->id),0,0);
		if(empty($selected)) {
			$q->_error='21'; //no such quotation
			return $q;	
		}
		$this->DB->processObject($q, 'delete');
		return $q;
	}
	
	// ******************************************************
	
	function createQuotation() {
		$q = new Quotation();
		$q->name_langs=new ObjectsList();
		$q->name_langs->type=new Quotation_Lang();
		return $q;
	}
	

}
?>