<?php

//Added by Serg Belonogko
	$dump_array = array();
	function toDA($key, $val)
	{
		global $dump_array;
		if(empty($key))
			$dump_array['just_vals'][] = $val;
		elseif (isset($dump_array[$key]) and !is_array($dump_array[$key]))
			$dump_array[$key] = array();
		$dump_array[$key][] = $val;
	}
//Added by Serg Belonogko
define ("BR", "<br>");
define ("NBSP", "&nbsp;");
define ("FONTTEXT", "<font face=\"Arial\" color=\"%s\" style=\"font-size:%dpt\">%s</font>");
define ("BOLDTEXT", "<b>%s</b>");
define ("debug_DIE_SCREAM", "<br>debug MUST DIE!<br>");
define ("debug_PREFIX", "&nbsp;Debug Info [%d]:&nbsp;");

$debug_counter = 0;
$debug_blabla = true;
$debug_color = array (
	"prefix"	=> "gray",
	"die"		=> "red",
	"comment"	=> "teal",
	"boolean"	=> "green",
	"integer"	=> "red",
	"double"	=> "magenta",
	"string"	=> "blue",
	"array"		=> "navy",
	"object"	=> "olive",
	"resource"	=> "maroon",
	"null"		=> "black"
);

/**
 * Outputs a debug message.
 *
 * cd() outputs a debug message. Supported PHP variable types:
 * <ul>
 * 	<li>boolean (green color);</li>
 * 	<li>integer (red color);</li>
 * 	<li>double (magenta color);</li>
 * 	<li>string (blue color);</li>
 * 	<li>array (navy color);</li>
 * 	<li>object (olive color);</li>
 * 	<li>resource (maroon color).</li>
 * </ul>
 * Note: The NULL type is not supported. If the variable type is NULL, the folowing message will be displayed: "...is not set or NULL".
 *
 * You can use this function to output control debug messages or in case you want to check value and type of the specific variable.
 *
 * Output format:
 *
 * [Debug prefix Calls counter:] [Debug message comment] ( Variable name | Variable type) = (Variable value | "is not set" | "is empty")
 *
 * <b>Example:</b>
 *
 * <pre>
 *  //Include required files
 *  require_once "debug.lib.php";
 * 		require_once "sqlstorage.class.php";
 *
 *  //Outputs the $HTTP_POST_VARS array
 *  cd ($HTTP_POST_VARS, "HTTP_POST_VARS");
 *
 * 		$storage = new sqlStorage ();
 *  //Outputs information on all the $storage object properties
 *  cd ($storage);
 * </pre>
 *
 * @param	mixed		$val		Variable
 * @param	string		$name		Variable name to display
 * @param	string		$comment	Comment for variable
 * @param	boolean		$die		Defines to die or not after displaying
 * @access	public
 * @see		debug_dear()
 */
function cd ($val, $name="", $comment="", $die=false)
{
	debug_dear ($val, $name, $comment, $die);
} // end function cd

/**
 * Inits the specified timer.
 *
 * <b>Example:</b>
 * <pre>
 *  require_once "debug.lib.php";
 *
 *  // Init timer with name "query"
 *  ci ("query");
 *
 *  $query = "select * from USERS";
 *  mysql_query ($query, $connection);
 *
 *  // Show timer with name "query"
 *  cs ("query");
 * </pre>
 *
 * @param	mixed		$name		Timer name
 * @see		debug_inittimer(), cs(), debug_showtimer()
 * @access	public
 */
function ci ($name=0)
{
	debug_inittimer ($name);
} // end function ci

/**
 * Displays timer value.
 *
 * @param	mixed	$name		Timer name
 * @param	string	$comment	Some comment text
 * @see		debug_inittimer(), ci(), debug_showtimer()
 * @access	public
 */
function cs ($name=0, $comment="")
{
	debug_showtimer ($name, $comment);
} // end function cs

/**
 * Outputs a debug message.
 *
 * @param	mixed		$val		Variable
 * @param	string		$name		Variable name to display
 * @param	string		$comment	Comment for variable
 * @param	boolean		$die		Defines to die or not after displaying
 * @param	string		$internal	Function call type
 * @access	private
 * @global	integer		$debug_counter	Internal calls counter
 * @global	boolean		$debug_blabla	Defines need to output debug_PREFIX
 * @global	array		$debug_color	Used colors array
 */
function debug_dear ($val, $name="", $comment="", $die=false, $internal="")
{
	global $debug_counter, $debug_blabla, $debug_color;

	$type = gettype ($val);
	if (!$internal)
	{
		$debug_counter++;
		if ($debug_blabla)
			$debug_message = debug_format (sprintf (debug_PREFIX, $debug_counter), $debug_color["prefix"]);
		if ($comment)
			$debug_message .= debug_format ($comment, $debug_color["comment"]);
		if ($name)
			$debug_message .= debug_format (debug_bold ("\$$name")) . NBSP;
		elseif (!isset ($val))
			$debug_message .= debug_format (debug_bold ("VARIABLE")) . NBSP;
		else
			$debug_message .= debug_format (debug_bold (strtoupper ($type)));
	}
	else $debug_message = $internal;
	if (!isset ($val)) echo $debug_message . debug_format (" is not set or NULL".BR);
	else
	{
		switch ($type)
		{
			case "boolean":
				$val = $val ? "true" : "false";
			case "integer":
			case "double":
			case "string":
				debug_scalar (htmlspecialchars($val), $type, $debug_message);
			break;
			case "array":
				debug_array ($val , $debug_message);
			break;
			case "object":
				debug_object ($val, $debug_message);
			break;
			case "resource":
				debug_resource ($val, $debug_message);
			break;
			default:
				debug_scalar (strval ($val), "string", $debug_message);
			break;
		}
	}
	if ($die) debug_die ($die);
} // end function debug_dear

/**
 * Outputs the die message and die a script.
 *
 * @param	boolean		$die
 * @access	private
 * @global	boolean		$debug_blabla	Defines need to output debug_PREFIX
 * @global	array		$debug_color	Used colors array
 */
function debug_die ($die)
{
	global $debug_blabla, $debug_color;
	if (!is_string ($die))
	{
		if ($debug_blabla)
			$die = debug_DIE_SCREAM;
		else
			$die = "";
	}
	$die = debug_format ($die, $debug_color["die"], 3);
	die ($die);
} // end function debug_die

/**
 * Applies bold style to text.
 *
 * @param	string		$text
 * @return	string		Bold formatted text
 * @access	private
 */
function debug_bold ($text)
{
	return sprintf (BOLDTEXT, $text);
} // end function debug_bold

/**
 * Formats text with specified color and size.
 *
 * @param	string		$text	Text string
 * @param	string		$color	Text color
 * @param	integer		$size	Text size in pt.
 * @return	string		Formatted string
 * @access	private
 */
function debug_format ($text, $color="black", $size=10)
{
	return sprintf (FONTTEXT, $color, $size, $text);
} // end function debug_format

/**
 * Prints a debug message.
 *
 * @param	string		$val	Variable value
 * @param	string		$type	Variable type
 * @param	string		$prefix Output prefix
 * @global	array		$debug_color	Used colors array
 * @access	private
 */
function debug_scalar ($val, $type, $prefix)
{
	global $debug_color,$highlighter;
	echo $prefix . debug_format (NBSP."=".NBSP) . debug_format ($val, $debug_color[$type]) . BR;
} // end function debug_scalar

/**
 * Outputs an array.
 *
 * @param	array		$arr		Array to output
 * @param	string		$prefix		Message	prefix
 * @access	private
 * @global	array		$debug_color	Used colors array
 */
function debug_array ($arr, $prefix)
{
	global $debug_color;
	if (!$arr) echo $prefix . debug_format (" is empty array") . BR;
	while (list ($key, $value) = each ($arr))
	{
		$curprefix = $prefix . debug_format (" [") . debug_format ($key , $debug_color["array"]) . debug_format ("]");
		debug_dear ($value, false, false, false, $curprefix);
	}
} // end function debug_array

/**
 * Gets and returns a variable from a serialized object or its part.
 *
 * @param	string		&$varlist	Serialized object or it's part
 * @return	mixed		Unseralized value of object property
 * @access	private
 */
function debug_unserialize (&$varlist)
{
	if (strtolower ($varlist[0])=="o" || strtolower ($varlist[0])=="a")
	{
		$pos=strpos ($varlist, "{")+1;
		$intcnt = 0;
		while ($pos<strlen ($varlist))
		{
			if ($varlist[$pos]=="{") $intcnt++;
			elseif ($varlist[$pos]=="}")
			{
				if ($intcnt) $intcnt--;
				else
				{
					$pos++;
					break;
				}
			}
			$pos++;
		}
	}
	else $pos = strpos ($varlist, ";")+1;
	$value = unserialize (substr ($varlist, 0, $pos));
	$varlist = substr ($varlist, $pos);
	return $value;
} // end function debug_unserialize

/**
 * Outputs an object.
 *
 * @param	object		stdClass	$obj	Object to output
 * @param	string		$prefix Debug prefix
 * @access	private
 * @global	array		$debug_color	Used colors array
 */
function debug_object ($obj, $prefix)
{
	global $debug_color;
	$ver = phpversion ();
	$php4add = ($ver[0] == "4") ? 2 : 0;
	$objAsStr = serialize ($obj);
	$objAsArr = split (":", $objAsStr, 3 + $php4add);
	$objPropCount = $objAsArr[3];
	if ($php4add) $objClassName = ucfirst(substr($objAsArr[2], 1, $objAsArr[1]));
	else $objClassName = "Unknown";
	$objPropList = substr ($objAsArr[2+$php4add], 1, -1);
	if (strlen ($objPropList)==0) echo $prefix . debug_format (NBSP . $objClassName, $debug_color["object"]) . debug_format (" is empty object") . BR;
	while (strlen ($objPropList))
	{
		$curprefix = $prefix . debug_format (NBSP . $objClassName."->", $debug_color["object"]) . debug_format (debug_unserialize ($objPropList), $debug_color["object"]);
		debug_dear (debug_unserialize ($objPropList), false, false, false, $curprefix);
	}
} // end function debug_object

/**
 * Outputs a resourse.
 *
 * @param	resource	$res	Resource to output
 * @param	string		$prefix Debug prefix
 * @access	private
 * @global	array		$debug_color	Used colors array
 */
function debug_resource ($res, $prefix)
{
	global $debug_color;
	if (!$res) echo $prefix . debug_format (" is empty resource") . BR;
	$curprefix = $prefix . debug_format (" [") . debug_format (ucwords(get_resource_type ($res)) , $debug_color["resource"]) . debug_format ("]");
	debug_dear (strval ($res), false, false, false, $curprefix);
} // end function debug_resource

/**
 * Returns current time in microseconds.
 *
 * Returns current time measured in the number of  microseconds since the Unix Epoch (0:00:00 January 1, 1970 GMT).
 *
 * @return	double
 * @access	private
 */
function debug_microtime ()
{
	$time = explode (" ", microtime ());
	return doubleval ($time[0]) + doubleval ($time[1]);
} // end function debug_microtime

/**
 * Returns the specified timer value.
 *
 * @param	mixed		$name		Timer name
 * @return	double		Specified timer value
 * @global	array		$debug_timer	Array of timers
 * @access	private
 */
function debug_timer ($name=0)
{
	global $debug_timer;
	return debug_microtime () - $debug_timer[$name];
} // end function debug_timer

/**
 * Inits the specified timer.
 *
 * @param	mixed		$name		Timer name
 * @see		ci(), cs(), debug_showtimer()
 * @global	array		$debug_timer	Array of timers
 * @access	private
 */
function debug_inittimer ($name=0)
{
	global $debug_timer;
	$debug_timer[$name] = debug_microtime ();
} // end function debug_inittimer

/**
 * Displays timer value.
 *
 * @param	mixed	$name		Timer name
 * @param	string	$comment	Some comment text
 * @see		debug_inittimer(), ci(), cs()
 * @access	private
 */
function debug_showtimer ($name=0, $comment="")
{
	global $REGISTRY, $Debug;
	if(!$comment) $comment = "debug TIMER {$name} ";
	$counter = sprintf("%.6f", debug_timer ($name));
	if($Debug) cd($counter, "time", $comment);
	$REGISTRY['SQLtime'] += $counter;
} // end function debug_showtimer
?>