<?php

	function inputCheckbox($name,$checked = FALSE,$event = '',$value='1', $tabindex='') {
		return "<input class='check' type=\"checkbox\" value=\"$value\" name=\"" . $name . "\"" . ($checked ? " checked" : "") . " ".$event." ".($tabindex!=''?"tabindex=".$tabindex:'').">";
	}

	function checkBox($key,$value,$group='',$selected = false,$additional='') {
		return '<input class="check" type=checkbox name='.$group.'['.$key.'] value='.$key.($selected? ' checked' : ' ').($additional!=''? ' '.$additional : '').'> '.$value; 
	}

	function checkBoxes($array,$group='',$select,$additional='') {
		$res = array();
		if(is_array($array)) {
			is_array($select) or $select = array();
			foreach($array as $key => $value) 
				$res[$key] = checkBox($key,$value,$group,(isset($select[$key])? true : false),$additional)."\n";
		}
		return $res;
	}

	function radioButtons($array,$group='',$select,$additional='') {
		$res = array();
		if(is_array($array))
			foreach($array as $key => $value) 
				$res[$key] = radioButton($key,$value,$group,($key==$select? true : false),$additional)."\n";
		return $res;
	}

	function radioButton($key,$value,$group='',$selected = false,$additional='') {
		return '<input class="check" type="radio" name='.$group.' value='.$key.($selected? ' checked' : ' ').($additional!=''? ' '.$additional : '').'> '.$value; 
	}

	function inputRadio($name,$value,$checked = '', $event = '') {
		return "<input class='check' type=\"radio\" ".$event." value=\"".$value."\" ".($checked !=''? " checked" : "")." name=\"".$name."\">";
	}

	function inputText($name,$value = '',$size = '',$event = '',$max = '', $tabindex='') {
		return "<input type=\"text\" name=\"".$name."\" value=\"".$value."\"".($max? " maxlength=\"".$max."\"" : "").($size? " size=\"".$size."\"" : "")." ".$event." ".(!empty($tabindex)?"tabindex=".$tabindex:'').">";
	}

	function inputPassword($name,$value = '',$size = '', $tabindex='', $extra='') {
		return "<input type=\"password\" name=\"".$name."\" value=\"".$value."\"".($size? " size=\"".$size."\"" : "")." ".(!empty($tabindex)?"tabindex=".$tabindex:'').' '.$extra.">";
	}

	function inputSelect($name,$values,$selected = '',$event = '', $tabindex='') {
		if(!is_array($values) or !count($values)) return '';
		$svalues = array();
		foreach($values as $key => $value) {
			$select = is_array($selected)? (in_array($key,$selected)? $key : '' ) : $selected;
			$svalues[] = "<option value=\"".$key."\"".(strval($select)===strval($key)? " selected" : "").">".$value."</option>\n\r";
		}
		return "<select name=\"".$name."\" ".$event." ".($tabindex!=''?"tabindex=".$tabindex:'').">\n".implode("\n",$svalues)."</select>";
	}

	function inputTextArea($name,$value = '',$cols = '',$rows = '',$event = '', $tabindex='') {
		return "<textarea ".($tabindex!=''?"tabindex=".$tabindex:'')." ".$event." name=\"".$name."\"".($cols? " cols=\"".$cols."\"" : "").($rows? " rows=\"".$rows."\"" : "").">".$value."</textarea>";
	}

	function inputHidden($name,$value, $extra='') {
		return "<input type=\"hidden\" name=\"".$name."\" value=\"".$value."\"".$extra.">";
	}
	
	function inputFile($name,$event = '') {
		return "<input type=\"file\" ".$event." name=\"".$name."\">";
	}

	function date2pg($num){
		if(strlen($num)==1) return '0'.$num;
		else return $num;
	}
	
	function getZodiac($month,$day) {
		if($month < 1 || $month > 12 || $day < 1 || $day > 31) return false;
		$signs = array(
			array("20" => "1"),
			array("19" => "2"),
			array("21" => "3"),
			array("20" => "4"),
			array("21" => "5"),
			array("22" => "6"),
			array("23" => "7"),
			array("23" => "8"),
			array("23" => "9"),
			array("24" => "10"),
			array("22" => "11"),
			array("22" => "12")
		);
		list($sign_start,$sign_name) = each($signs[(int)$month-1]);
		if($day < $sign_start)
			list($sign_start,$sign_name) = each($signs[($month-2 < 0)? $month = 11: $month -= 2]);
		return $sign_name;
	}

	function CheckDateJScript(){
		return "
			function CheckDate(year,month,day) {
				if(day>28){
					maxd=31;
		if(month=='02'){
			maxd-=3;
			if(((year/4)-Math.round(year/4))==0)
			maxd++;
		}
		else if(month=='04'||month=='06'||month=='09'||month=='11')
			maxd--;
		if(day>maxd)return false;
	}
	return true;
}";
}
function checkDateScript(){
	return CheckDateJScript()."
	function CheckDateSelect(element){
		forma=element.form;
		nam=element.name.substr(0,element.name.lastIndexOf('_'));
		//days=forma.elements[nam+'_day'];
		//day=days.options[days.selectedIndex].value;
		month=forma.elements[nam+'_month'].options[forma.elements[nam+'_month'].selectedIndex].value;
		year=forma.elements[nam+'_year'].options[forma.elements[nam+'_year'].selectedIndex].value;
		//if(!CheckDate(year,month,day)){
		//	window.alert('You had select wrong day value! Check it, please!');
		//	days.options[maxd-1].selected=true;
		//	days.focus();
		//	return false;
		//}
		return true;
	}";
}
function selDate($name,$today="no",$d="",$m="",$y="",$year_begin=10,$year_end=0,$get=true,$ismon=true,$hidden=false,$events=array()){
	$i=0;
	$event="";
	if($hidden){
		$hname=$name;
		$name="title_$name";
		$events["onchange"]="if(CheckDateSelect(this))this.form.elements[this.name.replace(/title_/,'')].value=this.options[this.selectedIndex].value;".(empty($events["onchange"])?"":$events["onchange"]);
	}
	else
		$events["onchange"]="CheckDateSelect(this);".(empty($events["onchange"])?"":$events["onchange"]);
	if($get){
		if(!$d){
			global ${$name."_day"};
			$d=${$name."_day"};
		}
		if(!$m){
			global ${$name."_month"};
			$m=${$name."_month"};
		}
		if(!$y){
			global ${$name."_year"};
			$y=${$name."_year"};
		}
	}
	$empty=($today=="empty"?"<option>":"");
	$ar=array("day"=>"d","month"=>"m","year"=>"y");
	foreach($events as $k=>$v)
		$event.=" $k=\"$v\"";
	foreach($ar as $k=>$v)
		${$k}="<select class=edit_l name=$name"."_$k>$empty\n";
	if(!$d && !$m && !$y){
		if($today!="no")
			list($y,$m,$d)=array(date("Y",time()),date("m",time()),date("d",time()));
		if($today=="begin"){
			$y=$y-$year_begin;
			$m="01";
			$d="01";
		}elseif($today=="month")
			$d="01";
	}
	if($d=="")$d="31";
	while ($i<31){
		$day.="<option value=".date2pg(++$i);
		if($d==$i && $today!="empty")$day.=" selected";
		$day.=">".date2pg($i)."\n";
	}
	$monthes=array("01"=>"01","02"=>"02","03"=>"03","04"=>"04","05"=>"05","06"=>"06","07"=>"07","08"=>"08","09"=>"09","10"=>"10","11"=>"11","12"=>"12");
	if($m=="")$m="Dec";
	while(list($v,$k)=each($monthes)){
		$month.="<option value=$v";
		if($m==$v && $today!="empty") $month.=" selected";
		$month.=">$k\n";
	}
	$nyear=date("Y",time());
	if($y=="") $y=$nyear+$year_end;
	for($i=($nyear)-$year_begin;$i<($nyear+$year_end+1);$i++){
		$year.="<option value=$i";
		if($y==$i && $today!="empty") $year.=" selected";
		$year.=">$i\n";
	}
	reset($ar);
	foreach($ar as $k=>$v)
		${$k}.="</select>\n".($hidden?hidden($hname."_$k",${$v}):"");
	if (!$ismon) $day="";
	$day = "";
	return $day.$month.$year;
}
?>