<?php
include_once($CORE_PATH.'/DB/db_mysql.inc');

class DB extends DB_Sql {

	public $classname = 'DB';
	
	public $Host      = 'localhost'; //tserv
	public $Database  = 'fairytale'; //alliedfin
	public $User      = 'root'; //root
	public $Password  = ''; //

	public $sqlLikeStringEquality = true;

	function quotedValue($value) {
		return "'".addslashes(stripslashes($value))."'";
	}

	function addSlashesToArray($arr){
		$slashedarr = array();
		foreach ($arr as $k=>$v){
			$slashedarr[$k]=addslashes(stripslashes($v));	
		}
	
		return $slashedarr;
	}


	function withTablePrefix($fields,$table) {
		alterArray($fields,$table.'.');
		return $fields;
	}

	function begin() {
		return $this->query('BEGIN');
	}

	function commit() {
		return $this->query('COMMIT');
	}

	function rollback() {
		return $this->query('ROLLBACK');
	}

	function selectNested($innerPm, $outerPm) {
		$innerQuery = $this->composeSelectQuery($innerPm['tables'],$innerPm['fields'],$innerPm['conditions'],$innerPm['orderby'],$innerPm['limit'],$innerPm['groupby'],$innerPm['type'],$innerPm['parameters']);
		$outerQuery = 'select '.(is_array($outerPm['fields'])? listArrayValuesLower($outerPm['fields']) : $outerPm['fields']).' from ('.$innerQuery.') as iq '.$this->composeQueryConditions($outerPm['conditions'],$outerPm['orderby'],$outerPm['limit'],$outerPm['groupby'],$outerPm['type'],$outerPm['parameters']);
		return $this->query($outerQuery);
	}
	function select($tables,$fields='*',$conditions='',$orderby=0, $limit=0, $groupby=0,$type='CND_HOMOGENIC',$parameters=array('relation' => '=', 'operation' => 'and')) {
		$query = $this->composeSelectQuery($tables,$fields,$conditions,$orderby,$limit,$groupby,$type,$parameters);
		return $this->query($query);
	}

	function update($table,$values = '',$conditions='',$prepared = 1) {
		if(empty($table)) return FALSE;
		$query = 'update '.strtolower($table).' set '.listArrayKeysAndValues($this->addSlashesToArray($values),'=',', ',$prepared);
//		$query = 'update '.$table.' set '.listArrayKeysAndValues($values,'=',', ',$prepared);
		$query.= ' where '.listArrayKeysAndValues($conditions,'=',' and ');
		return $this->query($query);
	}

	function insert($table,$values = '') {
		//print "<li>";printArray($values);

		if(empty($table)) return FALSE;
		if(!is_array($values) or !count($values)) 
			return $this->query("insert into ".strtolower($table)." DEFAULT VALUES");
		$query = "insert into ".strtolower($table)." (".listArrayKeys($values).") values (".listArrayValues($this->addSlashesToArray($values),',',1).")";
//		$query = "insert into ".$table." (".listArrayKeys($values).") values (".listArrayValues($values,',',1).")";
		return $this->query($query);
	}

	function replace($table,$values = '') {
		if(empty($table)) return FALSE;
		if(!is_array($values) or !count($values)) 
			return $this->query("replace into ".$table." DEFAULT VALUES");
		$query = "replace into ".$table." (".listArrayKeys($values).") values (".listArrayValues($values,',',1).")";
		return $this->query($query);
	}

	function delete($table,$conditions='',$type='CND_HOMOGENIC',$parameters=array('relation' => '=', 'operation' => 'and')) {
		$query = $this->composeDeleteQuery($table,$conditions,$type,$parameters);
		return $this->query($query);
		//return $this->query('optimize table '.$table);
	}

	function composeDeleteQuery($table,$conditions,$type='CND_HOMOGENIC',$parameters=array('relation' => '=', 'operation' => 'and')) {
		$query = 'delete from '.strtolower($table);
	//	$query .= $this->simpleConditions($conditions);
		$query .= $this->composeQueryConditions($conditions,0,0,0,$type,$parameters);
	
		return $query;
	}

	function composeSelectQuery($tables,$fields,$conditions,$orderby=0,$limit=0,$groupby=0,$type='CND_HOMOGENIC',$parameters=array('relation' => '=', 'operation' => 'and')) {
		$query = 'select ';
		$query .= is_array($fields)? listArrayValuesLower($fields) : $fields;
		$query .= ' from ';
		$query .= is_array($tables)? listArrayValuesLower($tables) : $tables;
		//$query .= $this->simpleConditions($conditions,$orderby,$limit,$groupby);
		$query .= is_array($conditions) ? $this->composeQueryConditions($conditions,$orderby,$limit,$groupby,$type,$parameters): ' '.$conditions;
		return $query;
	}

	function simpleConditions($conditions,$orderby=0,$limit=0,$groupby=0) {
		if($conditions)
			$result = is_array($conditions)? $this->composeQueryConditions($conditions,$orderby,$limit,$groupby) : ' '.$conditions;
		else $result = '';
		return $result;
	}

	function homogenicConditions($conditions,$relation='=',$operation='and') {
		prepareValuesOrExpressions($conditions);		
		$relation = ' '.$relation.' ';
		$operation = ' '.$operation.' ';
		return listArrayKeysAndValues($conditions,$relation,$operation);
	}

	function equalityConditions($conditions) {
		if($this->sqlLikeStringEquality) {
			prepareValuesOrExpressions($conditions);
			$equalities = '';
			foreach($conditions as $field => $value) {
				$equalities .= $field;
				$equalities .= is_string($value) && ($value[0] == "'")? ' like '.$value : ' = '.$value;
				$equalities .= ' and ';
			}
			$equalities = substr($equalities,0,-strlen(' and '));
		}
		else $equalities = $this->homogenicConditions($conditions);
		return $equalities;
	}

	function complexConditions($conditions,$operations) {
		$result='';
		foreach($conditions as $field => $condition) {
			list($relation, $value) = each($condition);
			$result .= $field.' '.$relation.' ';
			switch($relation) {
				case 'like':
				case '=': 
				case '<>': 
				case '!=':
				case '<': 
				case '>': 
				case '<=': 
				case '>=':
					prepareValueOrExpression($value);
					$result .= $value;
				break;
				case 'in': 
				case 'not in':
					prepareValuesOrExpressions($value);
					$result .= '('.listArrayValues($value).')';
				break;
				case 'between': 
				case 'not between':
					prepareValuesOrExpressions($value);
					$result .= $value[0]." and ".$value[1];
				break;
				case 'IS NULL': 
				case 'IS NOT NULL':
				break;
			}
			if($operation = next($operations)) $result .= ' '.$operation.' ';
		}
		return '('.$result.')';
	}

	function dummyCondition() {
		return '(1)';
	}

	function composeQueryConditions($conditions,$orderby=0,$limit=0,$groupby=0,$type='CND_HOMOGENIC',$parameters=array('relation' => '=', 'operation' => 'and')) {
		$where = '';		
		if (!empty($conditions)) {
			$where = " where ";
			switch($type) {
				case 'CND_EQUALITY':
					$where .= $this->equalityConditions($conditions);
				break;
				case 'CND_HOMOGENIC':
					$where .= $this->homogenicConditions($conditions,$parameters['relation'],$parameters['operation']);
				break;
				case 'CND_COMPLEX':
					$where .= $this->complexConditions ($conditions, $parameters);
				break;
				case 'CND_SIMPLE':
					$where .= $conditions;
				break;
				case 'CND_DUMMY':
					$where .= dummyCondition ();
				break;
			}
		}
		return $where.$this->composeOrderGroupSection($orderby,$limit, $groupby);
	}
	
	function composeOrderGroupSection($orderby=0,$limit=0,$groupby=0) {
		$section = '';
		if(($groupby) && is_array($groupby)) $section .= ' group by '.listArrayValues($groupby);
		elseif(($groupby) && is_string($groupby)) $section .= ' group by '.$groupby;
		if(($orderby) && is_array($orderby)) $section .= ' order by '.listArrayValues($orderby);
		elseif(($orderby) && is_string($orderby)) $section .= ' order by '.$orderby;
		if($limit) $section .= ' limit '.$limit[0].', '.$limit[1];
		return $section;
	}
}
?>