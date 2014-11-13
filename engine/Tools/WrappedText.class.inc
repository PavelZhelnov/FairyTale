<?php

class WrappedText {

	public $string;
	public $maxlength;
	public $length;
	public $endline;

	function WrappedText($string,$maxlength,$length,$endline="\n",$safe_returns=0,$striphtml=1,$allowed_tags='',$maillink=0,$urllink=0,$target='') {
		$this->string=trim($string)."\n";
		$this->maxlength=$maxlength;
		$this->length=$length;
		$this->endline=$endline;
		$target=empty($target)?'':' target="'.$target.'"';
		if($striphtml) $this->string = strip_tags($this->string,$allowed_tags);
		if($maillink) $this->string = preg_replace('/([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3}))/i','<a href="mailto:'."\\1".'">'."\\1".'</a>',$this->string);
		if($urllink) $this->string = preg_replace('/((http|https|ftp):\/\/(([A-Z0-9][A-Z0-9_-]*)(\.[A-Z0-9][A-Z0-9_-]*)+)(\/*)(:(\d+))?([A-Z0-9_\/.?~-]*))/i','<a href="'."\\1".'"'.$target.'>'."\\1".'</a>',$this->string);
		if($safe_returns) {
			$this->string=str_replace("\n",'<br>',$this->string);
		}
		$this->wordwrap_nonhtml_and_tallwords_only($this->string);
		$this->string = str_replace(array($this->endline.'|'.$this->endline.'|','|'.$this->endline.'|'),$this->endline,$this->string);
	}

	function wrap_only_tall_words($string,$start,$for=0) {
		$tempstring = '';
		if(strstr($string,' ')) $temparray = explode(' ',$string);
		else $temparray = array($string);
		for($i=0;$i<count($temparray);$i++) {
			if($i>0)$tempstring.=' ';
			if(strlen($temparray[$i])>$this->maxlength) {
				if($for)$tempstring.='|'.$this->endline.'|';
				$tempstring.= wordwrap($temparray[$i],$this->length,$this->endline,1);
			}
			else $tempstring.=$temparray[$i];
		}
		return $tempstring;
	}

	function wordwrap_nonhtml_and_tallwords_only(&$string) {
		$start=0;
		$temp='';
		$totaal=strlen($string);
		$for=0;
		while($start<=$totaal) {
			$begin=strpos($string,'<',$start);
			if($begin===false) {
				if(substr($string,$start-strlen($this->endline),strlen($this->endline))!=$this->endline) $temp.=$this->endline;
				$temp.=$this->wrap_only_tall_words(substr($string,$start,$for),$start);
				break;
			}
			else {
				if($start!=$begin) {
					$temp.=$this->wrap_only_tall_words(substr($string,$start,$begin-$start),$start,$for);
				}
				$end=strpos($string,'>',$begin);
				$temp.=substr($string,$begin,$end-$begin+1);
				$start=$end+1;
			}
			$for=0;
		}
		$string=$temp;
	}

	function printit() {
		echo $this->string;
	}

	function getit() {
		return stripslashes($this->string);
	}
}
?>