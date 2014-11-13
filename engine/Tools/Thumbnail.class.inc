<?php

class Thumbnail {

	public $formats = array('gif' => 1, 'jpg' => 2, 'png' => 3, 'wbmp' => 15, 'bmp' => 6,
						'string' => 999);
	public $thumb_max_height = 100;
	public $thumb_max_width = 100;
	public $quality_thumb = TRUE;
	public $image_path;
	public $image_width;
	public $image_height;
	public $image_type;
	public $thumbnail_height;
	public $thumbnail_width;
	public $thumbnail_type = 3;
	public $image;
	public $thumbnail;
	public $version = '1.001';

	function Thumbnail($file = '') {
		$this->image_path = (string) $file;
	}

	function setOutputFormat($format = 'png') {
		if (array_key_exists(trim($format), $this->formats)) {
			$this->thumbnail_type = $this->formats[trim($format)];
		}
	}

	function setMaxHeight($height = 0) {
		$this->readSourceImageData();
		$height = (int) $height;
		if ($height < $this->image_height && $height > 0) {
			$this->thumb_max_height = $height;
			return (boolean) TRUE;
		}
		return (boolean) FALSE;
	}

	function setMaxWidth($width = 0) {
		$this->readSourceImageData();
		$width = (int) $width;
		if ($width < $this->image_width && $width > 0) {
			$this->thumb_max_width = $width;
			return (boolean) TRUE;
		}
		return (boolean) FALSE;
	}

	function setMaxSize($width = 0, $height = 0,$strict = false) {
		if ($this->setMaxWidth($width) === TRUE) {
			if($strict && $this->setMaxHeight($height) === TRUE)
				return (boolean) TRUE;
		} else {
			return (boolean) FALSE;
		}
	}

	function setQualityOutput($boolean = TRUE) {
		$this->quality_thumb = (boolean) $boolean;
	}

	function readSourceImageData() {
		if (!file_exists($this->image_path)) { // if source pic wasnt found
			$this->image_path = 'error_pic';
			$this->image_width =& $this->thumb_max_width;
			$this->image_height =& $this->thumb_max_height;
			$this->image = @imagecreatetruecolor($this->image_width, $this->image_height)
							or die ('Cannot Initialize new GD image stream');
			$text_color = imagecolorallocate($this->image, 255, 255, 255);
			imagestring($this->image, 1, 2,
					    ($this->image_height / 2 - 10),
					    "Could't find", $text_color);
			imagestring($this->image, 1, 2,
					    ($this->image_height / 2 - 4),
					    'source image', $text_color);
			imagestring($this->image, 1, 2,
						($this->image_height / 2 + 4),
						'(Thumbnail V' . $this->version . ')', $text_color);
		} else {
			if (!isset($this->image_width)) {
				list($this->image_width, $this->image_height, $this->image_type, $attr) = getimagesize($this->image_path);
				unset($attr);
				if (!in_array($this->image_type, $this->formats)) {
					die("Can't create thumbnail from '" . $this->image_type . "' source: " . $this->image_path);
				}
			}
		}
	}

	function readSourceImage() {
		if (!isset($this->image)) {
		    $this->readSourceImageData();
		    switch ($this->image_type) {
		        case 1:
		            $this->image = imagecreatefromgif($this->image_path);
		            break;
		        case 2:
		            $this->image = imagecreatefromjpeg($this->image_path);
		            break;
		        case 3:
		            $this->image = imagecreatefrompng($this->image_path);
		            break;
		        case 6:
		            $this->image = imagecreatefromwbmp($this->image_path);
		        break;
		        case 15:
		            $this->image = imagecreatefromwbmp($this->image_path);
		            break;
		        case 999:
		        default:
					$this->image = imagecreatefromstring($this->image_path);
					break;
		    }
		}
	}

	function setThumbnailSize() {
		$this->readSourceImageData();
		if($this->image_width > $this->thumb_max_width)
			$sizefactor = (double) $this->thumb_max_width / $this->image_width;
		else $sizefactor = (int) 1;
		$this->thumbnail_width = (int) ($this->image_width * $sizefactor);
		$this->thumbnail_height = (int) ($this->image_height * $sizefactor);
		if($this->thumbnail_height > $this->thumb_max_height && !empty($this->thumb_max_height)) {
			$sizefactor = (double) $this->image_height / $this->thumb_max_height;
			$this->thumbnail_width = (int) ($this->image_width / $sizefactor);
			$this->thumbnail_height = (int) ($this->image_height / $sizefactor);
		}
		unset($sizefactor);
	}

	function createThumbnail() {
		$this->setThumbnailSize();
		$this->readSourceImage();
		if (!isset($this->thumbnail)) {
			$this->thumbnail = imagecreatetruecolor($this->thumbnail_width,
													$this->thumbnail_height);
			if ($this->quality_thumb === TRUE) {
				imagecopyresampled($this->thumbnail, $this->image, 0, 0, 0, 0,
								   $this->thumbnail_width, $this->thumbnail_height,
								   $this->image_width, $this->image_height);
			} else {
				imagecopyresized($this->thumbnail, $this->image, 0, 0, 0, 0,
								 $this->thumbnail_width, $this->thumbnail_height,
								 $this->image_width, $this->image_height);
			}
		}
	}

	function outputThumbnail($format = 'png', $quality = 75) {
	    $this->setOutputFormat($format);
	    $this->createThumbnail();
	    switch ($this->thumbnail_type) {
	        case 1:
	        	header('Content-type: image/png');
	        	imagepng($this->thumbnail);
	            break;
	        case 2:
	        	$quality = (int) $quality;
	        	if ($quality < 0 || $quality > 100) {
					$quality = 75;
	        	} // end if

	        	header('Content-type: image/jpeg');
	        	imagejpeg($this->thumbnail, '', $quality);
	            break;
	        case 3:
	        	header('Content-type: image/png');
	            imagepng($this->thumbnail);
	        break;
	        case 6:
	            header('Content-type: image/vnd.wap.wbmp');
	            imagewbmp($this->thumbnail);
	        break;
	        case 15:
	            header('Content-type: image/vnd.wap.wbmp');
	            imagewbmp($this->thumbnail);
	        break;
	    }
	    imagedestroy($this->thumbnail);
	    imagedestroy($this->image);
	}

	function returnThumbnail($format = 'png', $quality = 75) {
		$this->setOutputFormat($format);
		$this->createThumbnail();
		return $this->thumbnail;
	}

	function getThumbHeight() {
		$this->createThumbnail();
		return (int) $this->thumbnail_height;
	}

	function getThumbWidth() {
		$this->createThumbnail();
		return (int) $this->thumbnail_width;
	}

	function getPictureName() {
		return (string) $this->image_path;
	}
}
?>
