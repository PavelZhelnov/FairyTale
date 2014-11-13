var CurrentItem=0;
var CurrentItem2=0;
var CurrentItem3=0;

function hidePanel() {
	document.getElementById('CtrlPanel').style.visibility='hidden';
}

function submitAction(act, target){
	var reLocation = act;
	if (CurrentItem!=null) reLocation = act.replace(/(\*1)/, CurrentItem);
	if (CurrentItem2!=null) reLocation = reLocation.replace(/(\*2)/, CurrentItem2);
	if (CurrentItem3!=null) reLocation = reLocation.replace(/(\*3)/, CurrentItem3);
	if (target==null || target=='' || target=="undefined") {
		document.location=reLocation;
	} else {
		popBox = window.open(reLocation,target,'status=yes,resizable=yes,scrollbars=yes');
	}
}

function getObj(name){
    obj=document.getElementById(name);
	return obj;
}

function setCurrentItem( item, num ){
  if(num == 1){
    CurrentItem=item;
  }
  if(num == 2){
    CurrentItem2=item;
  }
  if(num == 3){
    CurrentItem3=item;
  }
}

function hideCtrlPanel(){
     if( document.getElementById['CtrlPanel'] )
        document.getElementById['CtrlPanel'].style.visibility='hidden';
}

function move_cp(curCP,obj,id, id2, id3) {
	   CurrentItem = id;
	   CurrentItem2 = id2;
	   CurrentItem3 = id3;
       var a=move_cp.arguments;
       if(a.length>2){num = a[2];}
       else{num = 1;}

        var panel,dar,img,i,hv/* ,gre=/\.gif/i,re=/_off/i; */;//save for netscape
        pobj=obj.parentNode;

        if(panel=getObj(curCP)){
                trobj=panel.rows[0];

                for(i=1;i<trobj.cells.length;i++){
                        if(img){
                                img=trobj.cells[i].childNodes[0];
//              img.src=img.src.replace(re,'');//save for netscape
                                if(img.onclick)img.defaultOnClick=img.onclick;
                                        trobj.cells[i].style.filter='';
                                img.style.cursor='hand';
                                img.onclick=img.defaultOnClick;
                        }
                }
				objct = getObj('hcp_'+pobj);
                if(objct!=null){
                        dar=hv.value.split(',');
                        for(i=0;i<dar.length;i++){
                                if(img){
                                        img=trobj.cells[dar[i]].childNodes[0];
                                        img.style.filter='gray()';
                                        img.style.cursor='default';
                                        img.onclick=null;
                                }
                        }
                }

                panel.style.visibility='visible';
                panel.style.top=pobj.offsetTop+(pobj.offsetHeight-panel.offsetHeight)/2;
                panel.style.left=pobj.offsetLeft;
        }

        //setCurrentItem( obj.name, num );
}

