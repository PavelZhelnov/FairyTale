<?php

include_once($CORE_PATH.'/DB/debug.lib.inc');
include_once($CORE_PATH.'/DB/VersionException.class.inc');
include_once($CORE_PATH.'/DB/DBException.class.inc');

class DB_Sql extends RootRegistry{

	//public $Host = '';
	//public $Database = '';
	//public $User = '';
	//public $Password = '';

	public $Auto_Free = 1;
	public $Debug = 1;
	public $Halt_On_Error = 'no'; ## "yes" (halt with message), "no" (ignore errors quietly), "report" (ignore errror, but spit a warning)
	public $Seq_Table = 'db_sequence';

	public $Record = array();
	public $Row = 0;

	public $Errno = 0;
	public $Error = '';

	public $type = 'mysql';
	public $revision = '1.4';

	public $Link_ID = 0;
	public $Query_ID = 0;
	public $Last_ID = 0;

	function DB_Sql($query = '') {
		$this->query_count = 0;
		$this->query($query);
		$this->debugmessage = '';
	}

	function link_id() {
		return $this->Link_ID;
	}

	function query_id() {
		return $this->Query_ID;
	}

	function connect($Database = '',$Host = '',$User = '',$Password = '') {
		if('' == $Database) $Database = $this->Database;
		if('' == $Host) $Host = $this->Host;
		if('' == $User) $User = $this->User;
		if('' == $Password) $Password = $this->Password;
		if(0 == $this->Link_ID) {
			$this->Link_ID =  mysql_connect($Host,$User,$Password);
			if(!$this->Link_ID) {
				$this->halt("pconnect($Host, $User, \$Password) failed.");
				return 0;
			}
			if(!@mysql_select_db($Database,$this->Link_ID)) {
				$this->halt("cannot use database ".$Database);
				return 0;
			}
		}
		return $this->Link_ID;
	}

	function free() {
		@mysql_free_result($this->Query_ID);
		$this->Query_ID = 0;
	}

	function query($Query_String) {
		global $Debug;
		if($Query_String == '') return 0;
		if(!$this->connect()) return 0;
		if($this->Query_ID) $this->free();
		if($Debug) cd($Query_String,"Query",$this->debugmessage);
		ci("Query");
		$this->Query_ID = @mysql_query($Query_String,$this->Link_ID);
		$this->Last_ID = @mysql_insert_id($this->Link_ID);
		$this->Row = 0;
		$this->Errno = mysql_errno();
		$this->Error = mysql_error();
		cs("Query", "Query execution time (sec.) ");		
		if($Debug && !$this->Query_ID) cd($this->Error,"Error",$this->debugmessage);
		if ($this->Errno>0) {
			$this->halt($this->Error);
			throw new DBException($this->Error, $this->Errno);
		}		
		return $this->Query_ID;
	}

	function next_record() {
		if(!$this->Query_ID) {
			$this->halt("next_record called with no query pending.");
			return 0;
		}
		$this->Record = @mysql_fetch_array($this->Query_ID);
		$this->Row += 1;
		$this->Errno = mysql_errno();
		$this->Error = mysql_error();
		$stat = is_array($this->Record);
		if(!$stat && $this->Auto_Free) $this->free();
		return $stat;
	}

	function seek($pos = 0) {
		$status = @mysql_data_seek($this->Query_ID,$pos);
		if($status) $this->Row = $pos;
		else {
			$this->halt("seek($pos) failed: result has ".$this->num_rows()." rows.");
			@mysql_data_seek($this->Query_ID,$this->num_rows());
			$this->Row = $this->num_rows();
			return 0;
		}
		return 1;
	}

	function lock($table,$mode = 'write') {
		$query = 'lock tables ';
		if(is_array($table)) {
			foreach($table as $key => $value) {
				if(!is_int($key)) $query .= "$value $key, "; // texts key are "read", "read local", "write", "low priority write"
				else $query .= "$value $mode, ";
			}
			$query = substr($query,0,-2);
		}
		else $query .= "$table $mode";
		$res = $this->query($query);
		if(!$res) {
			$this->halt('lock() failed.');
			return 0;
		}
		return $res;
	}

	function unlock() {
		$res = $this->query('unlock tables');
		if(!$res) $this->halt('unlock() failed.');
		return $res;
	}

	function affected_rows() {
		return @mysql_affected_rows($this->Link_ID);
	}

	function num_rows() {
		return @mysql_num_rows($this->Query_ID);
	}

	function num_fields() {
		return @mysql_num_fields($this->Query_ID);
	}

	function nf() {
		return $this->num_rows();
	}

	function np() {
		print $this->num_rows();
	}

	function f($Name) {
		if(isset($this->Record[$Name])) return $this->Record[$Name];
	}

	function p($Name) {
		if(isset($this->Record[$Name])) print $this->Record[$Name];
	}

	function nextid($seq_name) {
		$this->connect();
		if($this->lock($this->Seq_Table)) {
			$q = sprintf("select nextid from %s where seq_name = '%s'",$this->Seq_Table,$seq_name);
			$id = $this->query($q);
			$res = @mysql_fetch_array($id);
			if(!is_array($res)) {
				$currentid = 0;
				$q = sprintf("insert into %s values('%s', %s)",$this->Seq_Table,$seq_name,$currentid);
				$id = $this->query($q);
			}
			else $currentid = $res["nextid"];
			$nextid = $currentid + 1;
			$q = sprintf("update %s set nextid = '%s' where seq_name = '%s'",$this->Seq_Table,$nextid,$seq_name);
			$id = $this->query($q);
			$this->unlock();
		}
		else {
			$this->halt("cannot lock ".$this->Seq_Table." - has it been created?");
			return 0;
		}
		return $nextid;
	}

	function nextvalue($table,$field,$id,$value=1) {
		$this->connect();
		if($this->lock($table)) {
			$q = sprintf("select %s from %s where id = '%s'",$field,strtolower($table),$id);
			$qid = $this->query($q);
			$res = @mysql_fetch_array($qid);
			if(is_array($res)) {
				$nextvalue = $res[$field];
				$nextvalue = $nextvalue + $value;	
				$q = sprintf("update %s set %s = '%s' where id = '%s'",strtolower($table),$field,$nextvalue,$id);
				$qid = $this->query($q);
				$this->unlock();
			}
		}
		else {
			$this->halt("cannot lock ".$this->Seq_Table." - has it been created?");
			return 0;
		}
		return $nextvalue;
	}



	function metadata($table) {
		$res = array();
		$this->query('select * from '.strtolower($table).' limit 1');
		for($i = 0; $i < $this->num_fields(); $i++) 
			$res[$i] = array(
				'table' => $table,
				'name' => @mysql_field_name($this->Query_ID,$i), 
				'type' => @mysql_field_type($this->Query_ID,$i),
				'len' => @mysql_field_len($this->Query_ID,$i),
				'flags' => @mysql_field_flags($this->Query_ID,$i)
			);
		if($table) @mysql_free_result($id);
		return $res;
	}

	function table_names() {
		$this->connect();
		$h = @mysql_query('show tables', $this->Link_ID);
		$i = 0;
		while($info = @mysql_fetch_row($h)) {
			$return[$i] = array(
				'table_name' => $info[0],
				'tablespace_name' => $this->Database,
				'database' => $this->Database,
			);
			$i++;
		}
		@mysql_free_result($h);
		return $return;
	}

	function halt($msg) {
		$headers = "MIME-Version: 1.0\r\n";
		$headers.= "Content-type: text/html; charset=windows-1251\r\n";
		$headers.= "From: DB_Error@memphisreo.com\r\n";
		$message = "Query: <b>$msg</b><br>\n\r";
		$message.="Error: <b>".$this->Error."</b><br>\n\r";
		$message.="Error Number: <b>".$this->Errno."</b></br>\n\r";
		$message.="Date : <b>".date("l dS of F Y H:i:s")."</b><br>\n\r";
		$message.="Script: <b><a href=\"http://".getenv('HTTP_HOST').getenv('REQUEST_URI')."\">http://".getenv('HTTP_HOST').getenv('REQUEST_URI')."</a></b><br>\n\r";
		$message.="Referer: <b>".getenv('HTTP_REFERER')."</b><br>\n\r";
		mail('willy2005@gmail.com',"MemphisReo DB Error!",$message,$headers);
	} 
	function haltmsg($msg) {
		printf("</td></tr></table><b>Database error:</b> %s<br>\n", $msg);
		printf("<b>MySQL Error</b>: %s (%s)<br>\n",$this->Errno,$this->Error);
	}
}
?>