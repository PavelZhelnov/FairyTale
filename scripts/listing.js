function cOn(td){
	if(document.getElementById||(document.all && !(document.getElementById))){
		td.style.backgroundColor="#FDF7EA";
	}
}

function cOut(td){
	if(document.getElementById||(document.all && !(document.getElementById))){
		td.style.backgroundColor="";
	}
}
