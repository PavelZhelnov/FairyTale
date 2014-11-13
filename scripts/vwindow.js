        var browser = "";
        var browsername = navigator.appName;
        var browserversion = parseInt(navigator.appVersion);
        if (browsername == "Netscape") {
                browser = "ns" + browserversion;
        } else {
                if (browsername == "Microsoft Internet Explorer") {
                        if (browserversion >= 4) {
                                browser = "ie" + browserversion;
                        } else {
                                browser = "ie3";
                        }
                }
        }

        if (browserversion >= 4) {
                PopLeft = (screen.width-640)/2;
                PopTop = (screen.height-480)/2;
        } else {
                PopLeft = 0;
                PopTop = 0;
        }

        function popNav(url,name,features) {
                popBox = window.open(url,name,features);
        }

        function popModal(url,name,features) {
          	popBox = showModalDialog(url,name,features);
        }

function page(form,num){
        if(frm=document.forms[form]){
                frm.page.value=num;
                frm.submit();
        }
}
/*
function sb(form,num){
        var sortt="lastname";
        var desc="asc";
        if (num==sortt) {
                if (desc=="asc") desc="desc"; else desc="asc";
        } else desc="asc";
        befsubmit();
        document.forms[form].sortby.value=num;
        document.forms[form].des.value="false";
        document.forms[form].direct.value=desc;
        document.forms[form].submit();
}
function someFunction (form) {
        confirm ("Submit?");
}
*/
//почему бы не сделать еще и таргет?
function submitFormAction (form, action, target) {
        if(frm=document.forms[form]){
                old_action=frm.action;
                frm.action=action;
                old_target = frm.target;
                if (target!="") frm.target=target;
                frm.submit();
                frm.action=old_action;
                frm.target=old_target;
        }
}


//------- paneljs.php3
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

var CurrentItem=0;
var CurrentItem2=0;
var CurrentItem3=0;

/*
function move_cp2(curCP,obj) {
alert("ok");
  move_cp(curCP,obj,1);
}
*/
function move_cp(curCP,obj) {

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
//                      img.src=img.src.replace(gre,'')+'_off.gif';//save for netscape
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

        setCurrentItem( obj.name, num );
}
var global_sort_name;
function move_sort(curCP,obj) {
       var foo,tutu = new String;
       foo=obj.name;
       foo=foo.slice(7);
       foo=foo.toLowerCase();
       document.forms[0].sortColumn.value=foo;
       var a=move_sort.arguments;
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
//                      img.src=img.src.replace(gre,'')+'_off.gif';//save for netscape
                                        img.style.filter='gray()';
                                        img.style.cursor='default';
                                        img.onclick=null;
                                }
                        }
                }

                panel.style.visibility='visible';
                panel.style.top=pobj.offsetTop;//+(pobj.offsetHeight-panel.offsetHeight)/2;
                panel.style.left=pobj.offsetLeft;
//              panel.style.left=obj.offsetWidth;
        }
//        CurrentItem=obj.name;

        setCurrentItem( obj.name, num );
        global_object= obj;
//        alert(global_object.name);


}

function set_sort(pic)
{

     for (i=0;i<collArray.length;i++)
     {
      document.forms[0].elements[collArray[i]].value="block.gif";
     }
    document.forms[0].elements['sortType'].value=pic;
    switch (pic)
    {
     case "0":
     pic="block.gif"
     break;
     case "1":
     pic="up.gif"
     break;
     case "2":
     pic="down.gif"
     break;
    }
    document.forms[0].elements[global_object.name].value=pic;
}

function set_report_sort(pic)
{

     for (i=0;i<collArray.length;i++)
     {
      document.forms[0].elements[collArray[i]].value="reportblock.gif";
     }
    document.forms[0].elements['sortType'].value=pic;
    switch (pic)
    {
     case "0":
     pic="reportblock.gif"
     break;
     case "1":
     pic="reportup.gif"
     break;
     case "2":
     pic="reportdown.gif"
     break;
    }
    document.forms[0].elements[global_object.name].value=pic;
}

//------- sortjs.php3
var block=false;
var hdorder;
var hdnum;
var srtimg;
var delimg;

function findForm(name){
        //return document.all[name].form;
        return document.getElementById(name).form;
}

function sortinit(form,name){
        frm=document.forms[form];
        hdorder=frm['srt_'+name+'order'];
        hdnum=frm['srt_'+name+'num'];
        srtimg=document.images[name];
        delimg=document.images['del'+name];
}

function resort(frm){
        if(confirm('Reload page?'))
                frm.submit();
}

function numcomp (a,b){
        return a - b;
}

function sort(form,name){
        if(!block){
                sortinit(form,name);
                var i,j=0,re=/srt_\w+num/,nums = Array();
                for(i=0;i<frm.length;i++){
                        if(re.test(frm[i].name) && frm[i].value){
                                nums[nums.length]=frm[i].value;
                        }
                }
                nums.sort(numcomp);
                j=nums.length?parseInt(nums[nums.length-1])+1:1;
                hdnum.value=hdnum.value?hdnum.value:j;
                if(hdorder.value == 'asc'){
                        hdorder.value='desc';
                        srtimg.src='pic/descending.gif';
                }
                else{
                        hdorder.value='asc';
                        srtimg.src='pic/ascending.gif';
                }
                delimg.src='pic/block.gif';
                resort(frm);
        }
        else block=false;
}

function unsort(form,name){
        block=true;
        sortinit(form,name);
        hdorder.value='';
        hdnum.value='';
        srtimg.src='pic/trans.gif';
        delimg.src='pic/trans.gif';
        resort(frm);
}
