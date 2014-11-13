<?
//COUNTER


//---------------------------------------------------------------------//
// GraphiCookie Counter 1.1 par Matthieu Biscay (mbiscay@skyminds.net)
// Visisble sur http://www.skyminds.net/
//---------------------------------------------------------------------//


// Creation de compteur.txt //
// Creating compteur.txt //

		if(file_exists("compteur.txt")) {
			print "";
		}
		else {
			$fp=fopen("compteur.txt","a");
			fputs($fp,"0");
			fclose($fp);
		}
		
		
// Chemin des images du compteur //
// Images path //
// Default= img/ct (images located in img/ct) //

	$aspect= "http://localhost/fairytale/i/counter/";
	$fichier="compteur.txt";


// Cas o� le visiteur est d�j� venu //
// Cookie already here //

	if (isset($cookie_count) && $cookie_count =="deja_vu")
		{
		$fp=fopen($fichier,"r+");
		$hits=fgets($fp,10);
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
		}

// Cookie absent (nouveau visiteur) //

	else
		{
		
// dur�e de vie du cookie //
// set the cookie lifetime //
// default: 15min -- 900s //
	
		setcookie("cookie_count","deja_vu",time()+900,"");
		
		$fp=fopen($fichier,"r+");
		$hits=fgets($fp,10);
		$hits++;
		fseek($fp,0);
		fputs($fp,$hits);
		fclose($fp);
		//$count++;
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
		}
		
		
		echo $hits;

?>