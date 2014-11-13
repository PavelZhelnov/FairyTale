<?php

include_once($MODEL_PATH.'/Modules/Common/Action_Log.class.inc');
include_once($MODEL_PATH.'/CommonConstants.class.inc');

class CommonUtilsHandler extends Handler {
	
	function OrganizationHandler($calledbyson=true){
		//$this->Handler($calledbyson);
	}	
	
	/**
	* Executes ones when counters (contact ranks) are null or failed for some reason
	*/
	function updateContactCounters() {
		
		echo "selecting";
		$contactList = $this->DB->selectAny('select c.id from contact as c');
		
		foreach ($contactList as $k=>$v) {
			print "<li>".$v['id'];
			$contactCounter[$v['id']] = 0;
			//gathering info by contact
			//BPO
			$query = $this->DB->selectAny('select count(*) as cnt from bpo where bpo.asset_manager = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from bpo where bpo.contact_person = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from bpo where bpo.valuation_company = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			//ClOSING
			$query = $this->DB->selectAny('select count(*) as cnt from closing where closing.asset_manager = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from closing where closing.buyer_agent = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			
			//MMRs
			$query = $this->DB->selectAny('select count(*) as cnt from mmr where mmr.asset_manager = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from mmr where mmr.contact_person = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from mmr where mmr.valuation_company = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			
			
			//CHECKS
			$query = $this->DB->selectAny('select count(*) as cnt from bpo_check where bpo_check.asset_manager = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from bpo_check where bpo_check.contact_person = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from bpo_check where bpo_check.valuation_company = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			
			//OFFERS
			$query = $this->DB->selectAny('select count(*) as cnt from offer where offer.buyer_agent = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			
			
			//PROPERTIES
			$query = $this->DB->selectAny('select count(*) as cnt from property where property.listing_agent = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			$query = $this->DB->selectAny('select count(*) as cnt from property where property.proprietor = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			
			//SHOWINGS
			$query = $this->DB->selectAny('select count(*) as cnt from showing where showing.agent = '.$v['id']);
			$contactCounter[$v['id']] +=$query[0]['cnt'];
			echo "+".$query[0]['cnt'];
			
			echo "=".$contactCounter[$v['id']];
			$this->DB->selectAny('update contact set rank='.$contactCounter[$v['id']].' where id='.$v['id']);
		}
		return true;
	}
	

	function optimizeAllDBTables() {
		$selected = $this->DB->SelectAny('show tables');
		foreach ($selected as $k=>$v) {
			foreach ($v as $key => $value) {
				$this->DB->SelectAny('optimize table '.$value);
				
			}
		}
	}
	
	function getGlobalSystemSettingsHandler() {
		global $Server; 
		$GlobalSystemSettingsHandler = new GlobalSystemSettingsHandler(false);
		return $GlobalSystemSettingsHandler;
	}
	function getPropertyHandler() {
		global $Server; 
		$ph = new PropertyHandler(false);
		return $ph;
	}
	
	function isDocInTheDB($table, $file) {
		$substr_name = substr($file, strpos($file, "_")+1);
		$substr_id = substr($file, 0, strpos($file, "_"));
		$selec = $this->DB->SelectAny('select * from '.$table.' where file_name = "'.$substr_name.'" and id="'.$substr_id.'"');
		return (empty($selec)?false:true);
	}
	
	function listDocuments($table) {
		$selec = $this->DB->SelectAny('select * from '.$table);
		return $selec;
	}
	function listPropertiesWithDocs() {
		$selec = $this->DB->SelectAny('select p.id, s.name state, c.name city, pl.address, p.zip, m.last_name publisher_last_name, m.first_name publisher_first_name, count(pd.id) 
			from property p
			left join property_document pd on pd.ownerid = p.id
			left join property_lang pl on pl.ownerid = p.id and pl.language=1
			left join city_lang c on c.ownerid=p.city and c.lang=1
			left join state_lang s on s.ownerid=p.state and s.lang=1
			left join member m on m.id = p.publisher
			group by p.id, s.name, c.name, pl.address, p.zip, m.last_name, m.first_name
			having count(pd.id)>0'.$table);
		return $selec;
	}
	
	function selectPropertyDocuments($id) {
		$select = $this->DB->SelectAny('select file_name, category, id from property_document where ownerid='.$id);
		return $select;
	}
	
	function deleteDocument($table, $id) {
		$selec = $this->DB->SelectAny('delete from '.$table.' where id='.$id);
		return $selec;
	}
	
	function getApprovedAppointmentsReadyForFeedback() {
		$selected = $this->DB->SelectAny("select * from showing_schedule s
			where s.showing_date<date_format(now(),'%d/%m/%Y %h:%i %p')
			and s.showing_request_response = ".CommonConstants::SHOWING_SCHEDULE_RESPONSE_APPROVED);
		//update to waiting for feedback
		$this->DB->SelectAny("update showing_schedule s
			set s.showing_request_response = ".CommonConstants::SHOWING_SCHEDULE_RESPONSE_WAITING_FOR_FEEDBACK."
			where s.showing_date<date_format(now(),'%d/%m/%Y %h:%i %p')
			and s.showing_request_response = ".CommonConstants::SHOWING_SCHEDULE_RESPONSE_APPROVED); 
		return $selected;
	}
	
	//@Temporary
	private function moveObjectDocsToNewModel($root_path, $workflowid, $table, $classname) {
		$selected = $this->DB->SelectAny('select count(*) as qty from '.$table.'_document');
		$qt = $selected[0]['qty'];
		
		$selected = $this->DB->SelectAny('select id from '.$table.'_document');
		$bpodocpath = '/var/www/vhosts/adminmls.com/httpdocs/i/documents/'.$table.'/';
		$i=1;
		foreach ($selected as $k=>$v) {
			//echo $v['id'].' - ';
			$olddoc = new $classname;
			$olddoc->id = $v['id'];
			$this->DB->initObject($olddoc);
			

			$doc = new Document();
			$doc->category = (isset($olddoc->category)?$olddoc->category:1);
			$doc->description = $olddoc->description;
			$doc->doctype = $olddoc->doctype;
			$doc->file_name = $olddoc->file_name;
			$doc->owner_type = $workflowid;
			$doc->ownerid = $olddoc->ownerid;
			$doc->pubdate= $olddoc->pubdate;
			$doc->size = $olddoc->size;
			$doc->updated_date = $olddoc->updated_date;
			$doc->version = $olddoc->version;
			
			$this->DB->processObject($doc);

			$oldfilename = $bpodocpath.$v['id'].'_'.$doc->file_name;
			$newfilename = $bpodocpath.$doc->id.'_'.$doc->file_name;
			if(file_exists($oldfilename)) {
				rename($oldfilename,$newfilename);
				$this->DB->processObject($olddoc, 'delete');
				echo (round($i * 100 / $qt)) . '% - '.$oldfilename.' <br>';
			} else {
				echo "<font color=''>There is no file ".$oldfilename."</font><br>";
			}
			
			
			$i++;
			
		}
	}
	
	//@Temporary
	function moveDocsToNewModel($root_path) {
		//$this->moveObjectDocsToNewModel($root_path, CommonConstants::WORKFLOW_TABLE_ID_BPO, 'bpo', 'Bpo_Document');
		//$this->moveObjectDocsToNewModel($root_path, CommonConstants::WORKFLOW_TABLE_ID_OFFER, 'offer', 'Offer_Document');
		//$this->moveObjectDocsToNewModel($root_path, CommonConstants::WORKFLOW_TABLE_ID_CLOSING, 'closing', 'Closing_Document');
		//$this->moveObjectDocsToNewModel($root_path, CommonConstants::WORKFLOW_TABLE_ID_CONTACT, 'contact', 'Contact_Document');
		//$this->moveObjectDocsToNewModel($root_path, CommonConstants::WORKFLOW_TABLE_ID_PROPERTY, 'property', 'Property_Document');
		
	}
	

}
?>