<?php

class CounterView extends Slot {

	public $url = '';
	public $imagePath='';
	
	
	public $ModuleID = 5;
	public $SectionID = 7;
	public $Task = 'view';
	
	function CounterView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->imagePath = $REGISTRY['Core']['ImageWPath'];
	}

	function init() {
		$url = parse_url(getenv('REQUEST_URI'));
		$this->Scheme = $this->Action->setScheme($this->SectionID);
		$this->Action->processEvent($this->SectionID,'addTodayUser',array(),$this);
	}

	function fillElements() {
		$request = $this->getCounter();
		$this->TempFillEls['counter_today'] = $request['cnt_today'];
		$this->TempFillEls['counter_total'] = $request['cnt_total'];
	}


	function getCounter() {
				
		
			
		
		
			$hits=$this->PreparedTemplates['cnt_today'];
			$hits=$this->addZeros($hits);
			$hits = $this->addReplaces($hits);

			$hits_t=$this->PreparedTemplates['cnt_total'];
			$hits_t=$this->addZeros($hits_t);
			$hits_t = $this->addReplaces($hits_t);
				
			$request['cnt_today'] = $hits;
			$request['cnt_total'] = $hits_t;
			return $request;
		
	}
	
	function addReplaces($hits) {
			$aspect= $this->imagePath.'/counter/';
			$hits = ereg_replace("0","<img src='$aspect/0.jpg' alt=ct>","$hits");
			$hits = ereg_replace("1","<img src='$aspect/1.jpg' alt=ct>","$hits");
			$hits = ereg_replace("2","<img src='$aspect/2.jpg' alt=ct>","$hits");
			$hits = ereg_replace("3","<img src='$aspect/3.jpg' alt=ct>","$hits");
			$hits = ereg_replace("4","<img src='$aspect/4.jpg' alt=ct>","$hits");
			$hits = ereg_replace("5","<img src='$aspect/5.jpg' alt=ct>","$hits");
			$hits = ereg_replace("6","<img src='$aspect/6.jpg' alt=ct>","$hits");
			$hits = ereg_replace("7","<img src='$aspect/7.jpg' alt=ct>","$hits");
			$hits = ereg_replace("8","<img src='$aspect/8.jpg' alt=ct>","$hits");
			$hits = ereg_replace("9","<img src='$aspect/9.jpg' alt=ct>","$hits");
			return $hits;
		
	}
	
	function addZeros($hits) {
		$y = 1000000/$hits;
		while ($y>1) {
			$y=$y/10;
			$hits='0'.$hits;
		}
		return $hits;
	}
	
}
?>
