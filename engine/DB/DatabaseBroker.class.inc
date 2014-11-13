<?php
include_once($DB_PATH.'/DB.class.inc');

class DatabaseBroker extends DB{

	public $lang;
	public $MetaData = array();

	function DatabaseBroker($name = 'DatabaseBroker') {
		global $HOME_PATH;
		$this->RootRegistry($name);
		$this->lang = $HOME_PATH;
		$this->DB_Sql();
	}
	function incrementField($table,$field,$id,&$object,$value=1) {
		$object->{$field} = $this->nextvalue($table,$field,$id,$value);
	}

	function getID($table,$values,&$Obj) {
		$Obj->id = $values['id'] = $this->nextid($table.'_sequence');
		$this->insert(strtolower($table),$values);
	}


	
	
	function SelectAll($tables,$fields='*',$conditions='') {
		$this->select($tables,$fields,$conditions);
		if($this->next_record()) return removeIntegerKeysFromArray($this->Record);
	}


	function SelectAny($query) {
		$array=array();
		$this->query($query);
		while($this->next_record()) $array[] = removeIntegerKeysFromArray($this->Record);
		return $array;
	}



	function SelectNestedArray($innerPm, $outerPm) {
		$array = array();
		$this->selectNested($innerPm, $outerPm);
		while($this->next_record()) $array[] = removeIntegerKeysFromArray($this->Record);
		return $array;
	}
	
	function SelectArray($tables,$fields='*',$conditions='',$orderby=0, $limit=0, $groupby=0, $array = array(),$type='CND_HOMOGENIC',$parameters=array('relation' => '=', 'operation' => 'and')) {
		$this->select($tables,$fields,$conditions,$orderby,$limit,$groupby,$type,$parameters);
		while($this->next_record()) $array[] = removeIntegerKeysFromArray($this->Record);
		return $array;
	}

	function SelectList($name,$tables,$fields='*',$conditions='',$orderby=0, $limit=0, $groupby=0, $array = array()) {
		$this->select($tables,$fields,$conditions,$orderby,$limit,$groupby);
		while($this->next_record()) $array[] = $this->f($name);
		return $array;
	}

	function SelectLang($tables,$fields='*',$conditions='',$orderby=0, $limit=0, $groupby=0, $array = array()) {
		$this->select($tables,$fields,$conditions,$orderby,$limit,$groupby);
		while($this->next_record()) $array[$this->f('name')][$this->f('var')] = $this->f('value');
		return $array;
	}

	function SelectSingle($tables,$fields='*',$conditions='') {
		$this->select($tables,$fields,$conditions);
		while($this->next_record()) return current(removeIntegerKeysFromArray($this->Record));
	}

	function SelectGuide($tables,$fields='*',$conditions='',$array = array(),$nameFieldName='name') {
		$this->select($tables,$fields,$conditions,' '.$nameFieldName.' ');
		while($this->next_record()) $array[$this->f('id')] = $this->f($nameFieldName);
		return $array;
	}
	function SelectGuideQuery($query=array(), $array=array()) {
		$this->query = $this->SelectAny($query);
		foreach ($this->query as $k=>$v) {
			$array[$v['id']] = $v['name'];
		}
		return $array;
	}

	function correctFields($values,$array = array()) {
		return $values;
		//foreach($values as $key => $value) if(!empty($value) || $value == '0') $array[$key] = $value;
		//return $array;
	}

	function compareFields($fields,$table,$olddata=array()) {
		if(!empty($this->MetaData[$table])) $array = $this->MetaData[$table];
		else $array = $this->MetaData[$table] = $this->metadata($table);		
		$metadata = array();
		foreach($array as $k => $v) {
			$correct_fields[] = $v['name'];
			$metadata[$v['name']] = $v;
		}
		
		if (!isset($olddata['version'])) $olddata['version'] =0;
		//echo "versionold=".$olddata['version'].' fields'.$fields['version'];
		if (($olddata['version']+1)!=$fields['version']) throw new VersionException("The object has been modified in parallel");
		foreach($fields as $k => $v) {
			if(!in_array($k,$correct_fields)) unset($fields[$k]); else {
				if ($metadata[$k]['type']=='datetime' && ($fields[$k]=='0000-00-00 00:00:00' || empty($fields[$k]) || $fields[$k]=='')) {
					$fields[$k] = null; 
				}
				if (strpos($metadata[$k]['flags'],'ot_null')>0 && $fields[$k]==null) {
					if ($metadata[$k]['type']=='int' || $metadata[$k]['type']=='double' || $metadata[$k]['type']=='real') {
						$fields[$k]=0; 
					} else
					$fields[$k]='';
				}
			}
		}
		//get rid of unchanged data
		if (!empty($olddata)) {
			foreach ($fields as $k=>$v) {
				if (isset($olddata[$k]) && $olddata[$k]==$fields[$k] && $k!='id') {
					unset($fields[$k]);
				}
			}
		}
		return $fields; 
	}

	function processObject(&$object,$type='save',$Tables = array(),$deletedidspr = array()) {
		$Obj = get_object_vars($object);
		$ObjName = get_class($object);
		foreach($Obj as $k => $v)
			switch(gettype($v)) {
				case 'object':
					if(strtolower(get_class($v))=='objectslist') $Tables[] = $v;
					else {
						$ObjTable[$k] = $v->id;
					}
				break;
				default: $ObjTable[$k] = $v; break;
			}
		if($type=='save') {
			if (!empty($Obj['id'])) {
				$OldObj = new $ObjName; 
				$OldObj->id = $Obj['id'];
				$this->initObject($OldObj);
				$ObjTable['updated_date'] = time();
				$ObjTable['version']++;
				try {
					$this->update(strtolower($ObjName),$this->correctFields($this->compareFields($ObjTable,$ObjName,ObjToArray($OldObj))),array('id'=>$Obj['id']));
				}
				catch (VersionException $e) {
					$object->_error='56_concurrent_exception';
					$ObjTable['version']--;
					return;
				}
			} else {
				$ObjTable['updated_date'] = time();
				$ObjTable['version']=1;
				$this->getID($ObjName, $this->correctFields($this->compareFields($ObjTable,$ObjName)),$object);
			}
		}
		foreach($Tables as $k => $v) {

//////////////////////////////// Added for deleting objectslists in objectslists in objectslists......			
			$selected=$this->SelectArray(strtolower(get_class($v->type)),'id',array('ownerid' => $object->id));
			if(!empty($selected)){
				foreach($selected as $p=>$m){
					$deletedids[]=$m['id'];
				}
			}
			else $deletedids=array();

			if (!empty($deletedidspr)) {
				foreach ($deletedidspr as $z=>$x) $this->delete(strtolower(get_class($v->type)),array('ownerid' => $x));			
			}
			else $this->delete(strtolower(get_class($v->type)),array('ownerid' => $object->id));
///////////////////////////////
			
//			$this->delete(get_class($v->type),array('ownerid' => $object->id));			
						
			if($type=='save')
				foreach($v->data as $key => $obj) {
					$obj->ownerid = $object->id;
					$obj->id = '';
					$this->processObject($obj,'save',array(),$deletedids);
				}
		}
		if($type=='delete') $this->delete(strtolower($ObjName),array('id' => $object->id));
	}

	function initObject($object,$Temp = array(),$Tables = array()) {
		if(!empty($object->id)) {
			$Obj = get_object_vars($object);
			$ObjName = get_class($object);
			$Obj = removePrivateKeysFromArray($Obj);
			$this->select(strtolower($ObjName),'*',array('id'=>$Obj['id']));
			while($this->next_record()) $Temp = removeIntegerKeysFromArray($this->Record);
			foreach($Obj as $k => $v) {
				$ttp = gettype($v); 
				switch(strtolower(gettype($v))) {
					case 'object':
						if(strtolower( get_class($v))=='objectslist') {
							$table = get_class($v->type);
							$object->{$k}->data = array();
							$i=0;
							foreach($this->SelectList('id',strtolower($table),'id',array('ownerid'=>$Obj['id'])) as $key => $value) {
								$data = new $v->type;
								$data->id = $value;
								$this->initObject($data);
								$object->{$k}->data[$i++] = $data;
							}
						}
						else {
							$object->{$k}->id = isset($Temp[$k])? $Temp[$k] : '';
							!empty($object->{$k}->id) and $this->initObject($object->{$k});
						}	
					break;
					default: if(in_array($k,array_keys($Temp))) $object->{$k} = $Temp[$k]; break;
				}
			}
		}
	}
	
	function beginTransaction() {
		$this->query("BEGIN");
	}
	function commitTransaction() {
		$this->query("COMMIT");
	}
	function rollbackTransaction() {
		$this->query("ROLLBACK");
	}
	
}
?>