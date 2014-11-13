function changeSame() {
	if (document.forms[0].elements['same'].checked) {
		document.forms[0].elements['form[billing_address1]'].value = document.forms[0].elements['form[address1]'].value;
		document.forms[0].elements['form[billing_address2]'].value = document.forms[0].elements['form[address2]'].value;
		document.forms[0].elements['form[billing_city]'].value = document.forms[0].elements['form[city]'].value;
		document.forms[0].elements['form[billing_zip]'].value = document.forms[0].elements['form[zip]'].value;
		document.forms[0].elements['form[billing_state]'].selectedIndex = document.forms[0].elements['form[state]'].selectedIndex;
	} else {
		document.forms[0].elements['form[billing_address1]'].value = "";
		document.forms[0].elements['form[billing_address2]'].value = "";
		document.forms[0].elements['form[billing_city]'].value = "";
		document.forms[0].elements['form[billing_zip]'].value = "";
		document.forms[0].elements['form[billing_state]'].selectedIndex = 0;
	}
}

function updateProduct() {
	document.forms[0].elements['step'].value='update_product';
//	document.forms[0].submit();
}

function editContact(id) {
	document.forms[0].elements['form[groupid]'].value=id;
}

function submitAction(action) {
	document.forms[0].elements['step'].value = action;
	document.forms[0].submit();
}