var cache = new Object;
var global_object = new Object;

function getElement(el) {
	var tagList = new Object;
	for (var i = 1; i < arguments.length; i++) {
	   tagList[arguments[i]] = true;
	}
	while ((el!=null) && (tagList[el.tagName]==null)) {
	  el = el.parentElement;
	}
	return el;
}

function Highlight(e) {	
	if (event==null) {return;}
  var el = getElement(event.srcElement,"TD");
  
  if (el==null) {
   	return;
  }

   var row = getElement(el,"TR");
 
     if (row.className != "listheader" &&  (row.className=="listline_item" || row.className=="listrover"))
     {
      row.className = "listrover";
      cache.className = "listline_item";
      cache = row;
     }
}

/*function selectTr(id){
 eval ("if (document.all.list"+id+"!=null) {cache = document.all.list"+id+"; document.all.list"+id+".className='listrover';}");
// eval("cache = document.all.list"+id+";");
// eval("document.all.list"+id+".className='rover';");
}*/
function selectTr(id){
 if (id==null) return;
 if (document.getElementById("list"+id)!=null)
 {
   //cache = document.getElementById['list"+id+"'];
   document.getElementById("list"+id).className='rover';
 }
}
