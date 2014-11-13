<?php

class XTemplate {

	public $varkeys = array();
	public $varvals = array();

	public $blocks_templates = array();
	public $blocks_tree = array();

	public $TemplateID = '';

	function XTemplate($template) {
		$this->setTemplate($template);
	}

	function &getElements() {
		global $REGISTRY;
		$prep = &$REGISTRY['PreparedTemplates'];
		if(empty($this->TemplateID) or empty($prep[$this->TemplateID])) {
			$blocks_tree = array();
			debug('XTemplate','Building tree');
			$this->buildBlocksTree('_template', $blocks_tree);
			if(!empty($this->TemplateID)) {
				$prep[$this->TemplateID]['Tree'] = $blocks_tree['_template'];
				$prep[$this->TemplateID]['Blocks'] = $this->blocks_templates;
				$this->blocks_tree = &$prep[$this->TemplateID]['Tree'];
			}
			else $this->blocks_tree = &$blocks_tree['_template'];
		}
		else {
			debug('XTemplate','Getting tree from Cache');
			$this->blocks_tree = &$prep[$this->TemplateID]['Tree'];
			$this->blocks_templates = &$prep[$this->TemplateID]['Blocks'];
		}
		return $this->blocks_tree;
	}

	function buildBlocksTree($varname,&$parent) {
		$reg = '/<!--\s+BEGIN ([^\s]+)\s+-->(.*)<!--\s+END \1\s+-->/s';
		$template = $this->get_var($varname);
		$parent[$varname] = array();
		if(preg_match_all($reg,$template,$m)) {
			foreach(array_keys($m[2]) as $k) {
				$name = $m[1][$k];
				$this->set_var($name,$m[2][$k]);
				$template = preg_replace("/<!--\s+BEGIN $name\s+-->(.*)<!--\s+END $name\s+-->/sm", "{" . $name . "}", $template);
				$this->buildBlocksTree($name,$parent[$varname]);
			}
			$this->set_var($varname,$template);
		}
		$this->blocks_templates[$varname] = $template;
		foreach($this->get_undefined($varname) as $var)
			$parent[$varname][$var] = preg_match("/[:?]/",$var)? 'slot' : '';
	}

	function setTemplateID($id = '') {
		$this->TemplateID = $id;
	}

	function setTemplate(&$template) {
		$this->varkeys = array();
		$this->varvals = array();
		$this->set_var("_template",$template);
	}

	function parseTemplate(&$filled) {
		$this->reset_vars();
		$ret = $this->parseRecursive("_template",array(&$filled),$this->blocks_tree);
		return $ret;
	}

	function parseRecursive($varname,$filled,$tree = '') {
		$tmpvar = '_temp'.$varname;
		$this->set_var($tmpvar,'');
		$this->set_var($varname,isset($this->blocks_templates[$varname])? $this->blocks_templates[$varname] : '');
		foreach(array_keys($filled) as $i) {
			$vars = array();
			foreach(array_keys($tree) as $key) {
				if($tree[$key] == 'slot') {
					debug('parseRecursive', 'Slot found: '.$key.'<br>');
					$extra = isset($filled[$i][$key])? $filled[$i][$key] : '';
					$render = renderSlot($key,$extra,FALSE);
					$vars[$key] = $render;
				}
				elseif(isset($filled[$i][$key])) {
					$vars[$key] = is_array($tree[$key])? $this->parseRecursive($key,$filled[$i][$key],$tree[$key]) : $filled[$i][$key];
				}
				else {
					$vars[$key] = is_array($tree[$key])? $this->parseRecursive($key,array(), $tree[$key]) : $this->parseLanguage($key);
					$this->unset_var($key);
				}
			}
			$this->set_var($vars);
			$this->parse($tmpvar,$varname, TRUE);
		}
		return $this->get_var($tmpvar);
	}

	function parseLanguage($key,$value = '') {
		if(preg_match('/local\./i',$key)) {
			list($local,$type,$var) = explode('.',$key);
			$value = isset($this->localLangContent[$type][$var])? $this->localLangContent[$type][$var] : '';
		}
		if(preg_match('/global\./i',$key)) {
			list($global,$type,$var) = explode('.',$key);
			$value = isset($this->globalLangContent[$type][$var])? $this->globalLangContent[$type][$var] : '';
		}
		return $value;
	}

	function getTemplate() {
		return $this->get_var("_template");
	}

	function reset_vars() {
		$this->varkeys = array();
		$this->varvals = array();
		$this->set_var($this->blocks_templates);
	}

	//============ from Template.class.inc ==============

	function set_var($varname,$value = '') {
		if(!is_array($varname)) {
			$this->varkeys[$varname] = '/'.$this->varname($varname).'/';
			$this->varvals[$varname] = $value;
			return $value;
		}
		else
			foreach($varname as $k => $v) {
				$this->varkeys[$k] = '/'.$this->varname($k).'/';
				$this->varvals[$k] = $v;
			}
	}

	function prepare_value($value) {
		return str_replace('$','\$',$value);
	}

	function unset_var($varnames) {
		is_array($varnames) or $varnames = array($varnames);
		foreach($varnames as $varname) {
			if(isset($this->varkeys[$varname])) unset($this->varkeys[$varname]);
			if(isset($this->varvals[$varname])) unset($this->varvals[$varname]);
		}
	}

	function varname($varname) {
		return preg_quote('{'.$varname.'}');
	}

	function parse($target,$varname,$append = false) {
		if(!is_array($varname))
			return $this->set_var($target,($append? $this->get_var($target) : '').$this->subst($varname));
		else {
			foreach($varname as $h) {
				$str = $this->subst($h);
				$this->set_var($target,$str);
			}
			return $str;
		}
	}

	function subst($varname) {
		return @preg_replace($this->varkeys,$this->prepare_value($this->varvals),$this->get_var($varname));
	}

	function get_var($varname) {
		if(!is_array($varname)) return $this->varvals[$varname];
		else {
			foreach($varname as $v) $result[$v] = $this->varvals[$v];
			return empty($result)? array() : $result;
		}
	}

	function get_undefined($varname) {
		$result = array();
		preg_match_all("/\{([^}]+)\}/",$this->get_var($varname),$m);
		if(is_array($m[1]))
			foreach($m[1] as $v)
				if(!isset($this->varkeys[$v]))
					$result[$v] = $v;
		return empty($result)? array() : $result;
	}

	function get_vars() {
		foreach(array_keys($this->varkeys) as $k)
			$result[$k] = $this->get_var($k);
		return empty($result)? array() : $result;
	}
}
?>