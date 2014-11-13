<?php

include_once($MODEL_PATH.'/Modules/Workflow/Document/Document.class.inc');
include_once($MODEL_PATH.'/Modules/Workflow/Document/Document_Lang.class.inc');

include_once($MODEL_PATH.'/Security/Member.class.inc');

class CounterHandler extends Handler {
	
	public $currentuser;
	public $categorylist;
	public $categorylistid;
	
	function CounterHandler($calledbyson=true){		
		$this->Handler($calledbyson);
		if ($calledbyson==true) {
			$this->currentuser = new User();
		}
	}
	
	function addTodayUser($request) {
		$ip=$_SERVER['REMOTE_ADDR'];
		
		//check for new day
		$day = $this->DB->selectAny('select DATE_FORMAT(ltime,\'%Y-%m-%d\') as ldate from counter_today order by ltime desc limit 1');
		if (!empty($day)) {
			if ($day[0]['ldate']!=date('Y-m-d',time())) {
				//new day!

				$today = $this->DB->selectAny('select count(*) as cnt from counter_today');
				$this->DB->selectAny('update counter_total set total = total+ '.$today[0]['cnt']);
				$this->DB->selectAny('delete from counter_today');
			}
		}
		
		$currentTime = date('Y-m-d H:i:s',time());

		$exist = $this->DB->selectAny('select * from counter_today where ipaddress=\''.$ip.'\'');
		if (empty($exist)) {
			$this->DB->selectAny('insert into counter_today (ipaddress, ltime) values (\''.$ip.'\', \''.$currentTime.'\');');
		}
		$today = $this->DB->selectAny('select count(*) as cnt from counter_today');
		$request['cnt_today'] = $today[0]['cnt'];
		$total = $this->DB->selectAny('select total from counter_total where id=1');
		$request['cnt_total'] = $total[0]['total'] + $request['cnt_today'];
		
		return $request;
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