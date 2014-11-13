<?php
function utf8_to_win($s){
	$out="";$c1="";$byte2=false;
	for ($c=0;$c<strlen($s);$c++){
		$i=ord($s[$c]);
		if ($i<=127) $out.=$s[$c];
		if ($byte2){
			$new_c2=($c1&3)*64+($i&63);
			$new_c1=($c1>>2)&5;
			$new_i=$new_c1*256+$new_c2;
			if ($new_i==1025) $out_i=168; 
			else if ($new_i==1105) $out_i=184; 
			else $out_i=$new_i-848;
			$out.=chr($out_i);
			$byte2=false;
		}
		if (($i>>5)==6) {$c1=$i;$byte2=true;}
	}
	return $out;
}

function utf8_to_win_old($str){
	$str = utf8_decode ($str); // utf8 to iso8859-5 
	$str = convert_cyr_string($str, 'i','w'); // w - windows-1251 to i - iso8859-5 
	return $str;
}

function correctWord($word) {
	return strip_tags(trim($word));
}
?>