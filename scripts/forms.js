function enableSubmit() {
	document.getElementById('formSubmit').disabled = false;	
}
function enableSubmit2() {
	document.getElementById('button1').disabled = false; 
	document.getElementById('button2').disabled = false;
}

function disableSubmit() {
	document.getElementById('formSubmit').disabled = true;
}
function disableSubmit2() {
	document.getElementById('button1').disabled = true; 
	document.getElementById('button2').disabled = true;
}

Array.prototype.in_array = function(p_val) {
	for(var i = 0, l = this.length; i < l; i++) {
		if(this[i] == p_val) {
			return true;
		}
	}
	return false;
}

function getContactId(obj) {
	return obj.value;
}
function getMemberId(obj) {
	return obj.value;
}

function getOrganizationId(obj) {
	return obj.value;
}
function inSelectedList(obj, value) {
	for (var i=0; i<obj.length; i++) {
		if (obj[i].value == value) return true;
	}
	return false;
}


function focusTheFirstElement(formName, elementName) {
	document.forms[formName].elements[elementName].focus();
}

function focusTheFirstElement() {
	var valForms = new Array("search","search_contact","auth");
	var invalElements = new Array("form[goToPage]","step","o","");
	var getform=null;
	var getelement=null;
	var i=0;
	while (getform==null && getelement==null && i<document.forms.length) {
   		var form = document.forms[i];
   		// if (valForms.in_array(form.name)) {
   			getform=i;
   			var j=0;
   			while(getelement==null && j<form.elements.length) {
   				var element = form.elements[j];
   				if (!invalElements.in_array(element.name) && element.type!=null && element.type.indexOf('text')>-1) {
   					getelement=j;
   				}
   				j++;
   			}
   		// }
   		i++;
	}
	if (getform!=null && getelement!=null) {
		// alert(document.forms[getform].elements[getelement].name);
		try {
			document.forms[getform].elements[getelement].focus();
		}
		catch (e) {
			// TODO move to another visible element
		}
	}
}

function expandSwap(listIdPrefix) {
    collapsedList = document.getElementById(listIdPrefix + "_collapsed");
    expandedList = document.getElementById(listIdPrefix + "_expanded");
    if (collapsedList.style.display == "block") {
        collapsedList.style.display = "none";
        expandedList.style.display = "block";
    } else {
        collapsedList.style.display = "block";
        expandedList.style.display = "none";
    }
}

function switchVisibilityForModifyButton(obj) {
	if (obj == null) return;
	var str = obj.id;
	if ((!document.getElementById(str)) || (!document.getElementById(str+"_bt"))) return;
	value = document.getElementById(str).value;
	if (value!=null && value>0) {
		document.getElementById(str+"_bt").style.visibility="visible"; 
	} else {
		document.getElementById(str+"_bt").style.visibility="hidden"
	}
}

function getUniqueId(prefix){
	return ((typeof(prefix) == 'undefined')?'uid_':prefix+'_') + (Math.random()*1000000);
}

function getMessageBoxHTML(id, body, classname, style, close_button){
	var close_button_pattern = '<input type="button" value="Close" onclick="javascript:hideMessageBox(\'{mbox_id}\');"/>';
	var mbox_pattern = '<div class="messagebox_container" id="{container_id}" style="visibility: visible"><div class="messagebox_form{class}" style="{style}"><div class="message_box_text">{body}</div>{close_button}</div></div>';
	var result = mbox_pattern.replace('{container_id}', id).replace('{body}', body).replace('{style}', style);
	result = result.replace('{close_button}', close_button?close_button_pattern.replace('{mbox_id}', id):'');
	result = result.replace('{class}', typeof(classname) == 'string' && classname != ''?' '+classname:'');
	return result;
}
function showActionMessage() {
    
	if(showMessageBox("error_text_1") || showMessageBox("action_message"))
    	return;

	
    if (document.getElementById("action_message")!=null && document.getElementById("action_message").innerHTML!="") {
		 document.getElementById("action_message").style.visibility = "visible";
         setTimeout("hideActionMessage()", 2000);
    }
    if (document.getElementById("action_message_error")!=null && document.getElementById("action_message_error").innerHTML!="") {
		 document.getElementById("action_message_error").style.visibility = "visible";
        setTimeout("hideActionMessageError()", 4000);
   }
}
/*
function showErrorBox(){
	return false;
	var textElement = document.getElementById("error_text_1");
	var text;
	if(textElement == null || (text = textElement.innerHTML) == "") // Если нет сообщения об ошибке - выходим
		return false;
	document.getElementById("messagebox_text_1").innerHTML = text;
	document.getElementById("message_background_1").style.visibility = "visible";
	document.getElementById("messagebox_container_1").style.visibility = "visible";
	return true;
}
function hideErrorBox(){
	document.getElementById("messagebox_container_1").style.visibility = "hidden";
	document.getElementById("message_background_1").style.visibility = "hidden";
}
*/
function showMessageBox(textElementId){
	var textElement = document.getElementById(textElementId);
	var text;
	if(textElement == null || (text = textElement.innerHTML) == "") // Если нет сообщения об ошибке - выходим
		return false;
	var style = '', classname = '';
	var close_button = (textElement.getAttribute('close') == 'button')?true:false;
	switch (textElement.getAttribute('type')) {
	case 'message':
		style = 'background-color: black;';
		break;
	case 'error':
		close_button = true;
		break;
		default:
			break;
	}
	var id = getUniqueId('message_box');
	var elText = getMessageBoxHTML(id, text, classname, style, close_button);
	$('body').append(elText);
	document.getElementById("message_background_1").style.visibility = "visible";
	if(!close_button)
		setTimeout('hideMessageBox("'+id+'")', 3000);
	return true;
}
function hideMessageBox(id){
	if(typeof(id) != 'string')
		id = 'messagebox_container_2';
	document.getElementById(id).style.visibility = "hidden";
	document.getElementById("message_background_1").style.visibility = "hidden";
}

/*
 * function showActionMessage(txt,val,sec) { if (txt!='' &&
 * document.getElementById("action_message")!=null) {
 * document.getElementById("action_message").style.visibility = "visible";
 * setTimeout("hideActionMessage()", 2000); } else if (txt!='' &&
 * document.getElementById(val)!=null) {
 * document.getElementById(val).style.visibility = "visible";
 * setTimeout("hideActionMessage1("+val+")", sec); } }
 */


function hideActionMessage() {
	document.getElementById("action_message").style.visibility = "hidden";
}
function hideActionMessageError() {
	document.getElementById("action_message_error").style.visibility = "hidden";
}
