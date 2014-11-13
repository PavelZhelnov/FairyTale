<?php

include_once($MODEL_PATH.'/Modules/Workflow/Document/Document.class.inc');
include_once($MODEL_PATH.'/Modules/Workflow/Document/Document_Lang.class.inc');

include_once($MODEL_PATH.'/Security/Member.class.inc');

class DocumentHandler extends Handler {
	
	public $currentuser;
	public $categorylist;
	public $categorylistid;
	public $document;
	
	function DocumentHandler($calledbyson=true){		
		$this->Handler($calledbyson);
		if ($calledbyson==true) {
			$this->currentuser = new User();
			$this->document = $this->createDocument();
		}
	}

	function setSearch($request = array()) {
		global $Server;
		//$Server->settings['PropertySearch'] = array();
		foreach($request as $key => $value) $Server->settings['AdminDocumentSearch'][$key] = $value;
		return array();
	}

	function getSearch($request = array()) {
		global $Server;		
		return $Server->settings['AdminDocumentSearch'];
	}


	function getConditions($request = array(), $search = array()) {
		
		//if (isset($search['bpo_vendor_first']) && (validate($search['bpo_vendor_first']))) {
			$request['conditions']['d.id'] = array('like'=>'%');
		//}

		return $request;
	}

	function createNewDocument($request) {
		$this->cleanError($this->document);
		$this->document = $this->createDocument();

		$this->document->_dialog = 0;
		return $this->document;
	}

	
	function viewDocumentAdmin($request=array()) {
		$this->document = $this->createDocument();
		$id = $this->DB->SelectSingle(array('document'),'id',array('id' => $request['id']));
		if(!empty($id)) {
			$this->document->id = $id;
			
			$this->DB->initObject($this->document);
			
		} else {
			$this->document->_error='27'; //no such document
			return $this->document;
		}	
		return $this->document;
	}

	function getDocumentAdmin($request) {
		$this->cleanError($this->document);
		if(!empty($request['id']) && empty($this->document->id)) {
			$id = $this->DB->SelectSingle(array('document'),'id',array('id' => $request['id']));
			if(!empty($id)) {
				$this->bpo->id = $id;
				$this->DB->initObject($this->document);
			} else {
				$this->document->_error='27'; //no such document
				return $this->document;
			}
		}
		
		return $this->document;
	}

	
	function validateDocumentAdmin($request, $action = '') {
		//bpo checking - by property id and agent		
		return true;
	}


	
	//******************** DOCUMENTS ************************

	function selectDocumentListAdmin($request) {
		
		$search = $this->getSearch();
		$request = $this->getConditions($request,$search);
		
		$request['conditions']['dl.language'] = array('='=>$request['langid']);
		
		if(empty($request['fields'])) $request['fields']='d.id, DATE_FORMAT(d.pubdate,\'%Y-%m-%d\') as pubdate, d.size as size, d.file_name, d.doctype, dl.name, dl.description';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 20;
		if(empty($request['sortColumn'])) { $request['sortColumn']='name'; $request['sortType']='desc';}
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('document as d left join document_lang as dl on d.id=dl.ownerid'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('document as d left join document_lang as dl on d.id=dl.ownerid'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),' d.id ',array(),'CND_COMPLEX',$relarr);
		return $request;
	}
	
	function selectDocumentList($request) {
		
		$search = $this->getSearch();
		$request = $this->getConditions($request,$search);
		
		$request['conditions']['dl.language'] = array('='=>$request['langid']);
		if(empty($request['fields'])) $request['fields']='d.id, DATE_FORMAT(d.pubdate,\'%Y-%m-%d\') as pubdate, d.size as size, d.file_name, d.doctype, dl.name, dl.description';
		if(empty($request['curPageNumber'])) $request['curPageNumber']='1';
		$request['pageRecordsQty'] = !empty($search['amount'])? $search['amount'] : 20;
		if(empty($request['sortColumn'])) { $request['sortColumn']='name'; $request['sortType']='desc';}
		foreach($request['conditions'] as $k=>$v) $relarr[]='and';
		$selected=$this->DB->SelectArray(Array('document as d left join document_lang as dl on d.id=dl.ownerid'),'count(*) as qty',$request['conditions'],0,0,0,array(),'CND_COMPLEX',$relarr);
		$request['recordsTotal']=$selected[0]['qty'];
		$request['pagesTotal'] = ceil($request['recordsTotal']/$request['pageRecordsQty']);
		$request['curPage']=$this->DB->SelectArray(Array('document as d left join document_lang as dl on d.id=dl.ownerid'),$request['fields'],$request['conditions'],$this->getOrderBy($request),$this->getLimit($request),' d.id ',array(),'CND_COMPLEX',$relarr);
		return $request;
	}

	function saveDocumentAdmin($request){
		$this->document = $this->createDocument();
		if (!isset($this->document->pubdate)) {$this->document->pubdate = date('Y-m-d H:i:s',time());}
		$this->parseRequest($request,$this->document);
		$this->DB->processObject($this->document);
		return $this->document;
	} 
	function deleteDocumentAdmin($request) {
		$id = $this->DB->SelectSingle(array('document'),'id',array('id' => $request['id']));
		$this->document= $this->createDocument();
		if(!empty($id)) {
			$this->document->id = $id;
			$this->DB->initObject($this->document);
		} else {
			$this->document->_error='39'; //no such document
			return $this->document;
		}		
		$temp_doc = $this->document;
		$this->DB->processObject($this->document, 'delete');
		return $temp_doc;
	} 
	// ******************************************************
	
	function createDocument() {
		$doc=new Document();
		$doc->name_langs=new ObjectsList();
		$doc->name_langs->type=new Document_Lang();		
		return $doc;
	} 

	function createUser() {
		$user = new User();
		return $user;
	}

	function MakeHash()	{
		return md5(time());
	}
	
}
?>