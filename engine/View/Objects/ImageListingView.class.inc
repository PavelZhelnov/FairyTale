<?php

class ImageListingView extends Slot {

	public $ID = 0;
	public $number = 0;
	public $preview = 0;
	public $small = 0;
	public $big = 0;
	public $type = 'jpeg';

	function ImageListingView($pquery) {
		global $REGISTRY;
		$this->Slot($pquery);
		$this->ImagePath = $REGISTRY['Core']['ListingPath'];
		$this->ImageWPath = $REGISTRY['Core']['ListingWPath'];
	}

	function init() {
		if(!empty($this->LocalTarget['0']) && validate((int) $this->LocalTarget['0'])) {
			switch(@$this->LocalTarget['1']) {
				case 'Temp':
				//die();
					if(!empty($this->LocalTarget['2']) && validate((int) $this->LocalTarget['2'])) {
						$this->ID = $this->LocalTarget['0'];
						$this->number = $this->LocalTarget['2'];
						if(!empty($this->LocalTarget['3']) && $this->LocalTarget['3']=='Preview') {
							$this->preview = 1;
						} else if ($this->LocalTarget['3']=='Small') {
							$this->small = 1;
						} else if ($this->LocalTarget['3']=='Big') {
							$this->big = 1;
						}

						else $this->preview = 0;
					}
				break;
				case 'Image':
					if(!empty($this->LocalTarget['2']) && validate((int) $this->LocalTarget['2'])) {
						$this->ID = $this->LocalTarget['0'];
						$this->number = $this->LocalTarget['2'];
						if(!empty($this->LocalTarget['3']) && $this->LocalTarget['3']=='Preview')
							$this->preview = 1;
						else $this->preview = 0;
						if(!empty($this->LocalTarget['3']) && $this->LocalTarget['3']=='Small')
							$this->small = 1;
						if(!empty($this->LocalTarget['3']) && $this->LocalTarget['3']=='Big')
							$this->big = 1;

					}
				break;
				default: break;
			}
		}
		$this->setSchemeTemplate($this->Scheme);
	}

	function fillElements() {
		header("Cache-Control: max-age=0");
		header("Content-type: image/".$this->type);
		$this->getImage();
	}

	function getImage() {
		if(validate($this->ID) && validate($this->number)) {
			if(file_exists($this->ImagePath.'/'.$this->ID.'_'.$this->number.($this->preview==1 || $this->small==1? 'prew' : '').'.jpg')) {
				$image = imagecreatefromjpeg($this->ImagePath.'/'.$this->ID.'_'.$this->number.($this->preview==1 || $this->small==1? 'prew' : '').'.jpg');
				$image1 = $this->preview==1? imagecreatetruecolor(150,120) : ($this->small==1? imagecreatetruecolor(100,imagesy($image)/(imagesx($image)/100)) : ($this->big==1? imagecreatetruecolor(210,imagesy($image)/(imagesx($image)/210)) : imagecreatetruecolor(400,300)));
				$bgcolor = imagecolorallocate($image1,214,226,238);
				if($this->preview==1) imagefilledrectangle($image1,0,0,150,120,$bgcolor);
				elseif($this->small==1) imagefilledrectangle($image1,0,0,100,imagesy($image)/(imagesx($image)/100),$bgcolor);
				elseif($this->big==1) imagefilledrectangle($image1,0,0,210,imagesy($image)/(imagesx($image)/210),$bgcolor);
				else imagefilledrectangle($image1,0,0,400,300,$bgcolor);
				if($this->preview==1) imagecopyresized($image1,$image,(150-imagesx($image))/2,(100-imagesy($image))/2,0,0,imagesx($image),imagesy($image),imagesx($image),imagesy($image));
				elseif($this->small==1) imagecopyresized($image1,$image,0,0,0,0,100,imagesy($image)/(imagesx($image)/100),imagesx($image),imagesy($image));
				elseif($this->big==1) imagecopyresized($image1,$image,0,0,0,0,210,imagesy($image)/(imagesx($image)/210),imagesx($image),imagesy($image));
				else imagecopyresized($image1,$image,(400-imagesx($image))/2,(300-imagesy($image))/2,0,0,imagesx($image),imagesy($image),imagesx($image),imagesy($image));
				imagejpeg($image1,'',100);
				imagedestroy($image1);
				imagedestroy($image);
				return '';
			}
			else $this->defaultImage();
		}
		else $this->defaultImage();
	}

	function defaultImage() {
		$image = imagecreatefromjpeg($this->ImagePath.'/listingnotavail.jpg');
		$image1 = $this->preview==1? imagecreatetruecolor(150,120) : ($this->small==1? imagecreatetruecolor(100,imagesy($image)/(imagesx($image)/100)) : ($this->big==1? imagecreatetruecolor(210,imagesy($image)/(imagesx($image)/210)) :imagecreatetruecolor(400,300)));
		$bgcolor = imagecolorallocate($image1,214,226,238);
		if($this->preview==1) imagefilledrectangle($image1,0,0,150,120,$bgcolor);
		elseif($this->small==1) imagefilledrectangle($image1,0,0,100,imagesy($image)/(imagesx($image)/100),$bgcolor);
		elseif($this->big==1) imagefilledrectangle($image1,0,0,210,imagesy($image)/(imagesx($image)/210),$bgcolor);
		else imagefilledrectangle($image1,0,0,400,300,$bgcolor);
		if($this->preview==1) imagecopyresized($image1,$image,(150-imagesx($image))/2,(100-imagesy($image))/2,0,0,imagesx($image),imagesy($image),imagesx($image),imagesy($image));
		elseif($this->small==1) imagecopyresized($image1,$image,0,0,0,0,100,imagesy($image)/(imagesx($image)/100),imagesx($image),imagesy($image));
		elseif($this->big==1) imagecopyresized($image1,$image,0,0,0,0,210,imagesy($image)/(imagesx($image)/210),imagesx($image),imagesy($image));
		else imagecopyresized($image1,$image,(400-imagesx($image))/2,(300-imagesy($image))/2,0,0,imagesx($image),imagesy($image),imagesx($image),imagesy($image));
		imagejpeg($image1,'',100);
		imagedestroy($image1);
		imagedestroy($image);
		return '';
	}

}
?>