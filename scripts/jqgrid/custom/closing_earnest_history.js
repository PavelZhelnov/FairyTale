function LoadComplete(data){
	var messageEl = $(data).find('message');
	var text = messageEl.text();
	if(text != ''){
		$('#message').html('<p>' + text + '</p>').dialog({
		title:messageEl.attr('title'),
		closeOnEscape:true,
		dialogClass:'dialog_text_center',
		modal:true,
		minHeight: 100
		});
	}
}
jQuery(document).ready(function(){
var lastSel;
//load a list of state dynamically, define the variable before the definition of the jqGrid:
var p= jQuery ($('#pagerEH'));
jQuery.jgrid.del.msg =  "Delete selected Earnest Money?";
jQuery.jgrid.nav.deltitle = "Delete selected Earnest Money";
jQuery("#closingEH").jqGrid({ 
	   //url:t,
	   datatype: 'xml',
	   url:homePath+listURL,
	   editurl : homePath+'/AdminClosing/jquery/',
	   mtype: 'POST',
	   colNames:[ '#','Earnest Date','Step','Description', 'Document'],
	   colModel:[ 
	      {name:'row_index',index:'row_index',width:60}, 
	      {name:'pubdate',index:'pubdate', width:150 },
	      {name:'em_step',index:'em_step', width:150 },
	      {name:'description',index:'description', width:320 },
	      {name:'document',index:'document', width:180},
	      ],
	    
	    pager:p,
		rowNum:50,
		//autowidth: true, 
		rowList:[5,10,20,30,40,50],
		viewrecords: true,
		sortname: 'id',
		sortorder: "asc",
		imgpath: homePath+'/scripts/jqgrid/css/themes/ui-lightness/images',
		caption: "Earnest Money History",
		height:170,
		loadComplete:LoadComplete,
		//editurl: homePath+'/AdminCity/jquery/edit',

ondblClickRow: function(id) {
                if (id && id != lastSel) {
                    jQuery("#closingEH").restoreRow(lastSel);
                    jQuery("#closingEH").editRow(id,true);
                    lastSel = id;
                }
            }
            
}).navGrid('#pagerEH',
		{add:false,edit:false,del:true,search:false},
		{},
		{},
		{closeOnEscape:true, closeAfterDel : true, delData:{object:'AdminClosingView',step:'delete_closing_history'}}//delete init data
		); 
		
 		
//jQuery("#list").editGridRow( "new", options );

/*(function($) {
    $.jgrid.extend({
        onErrorHighlight: GridErrorHighlight,
        onUnHighlight: GridErrorUnHighlight,
    });
})(jQuery);

GridErrorHighlight = function(el, er, ev) {
    $(el)
        .addClass('ui-state-error')
    .parent()
        .addClass('ui-state-error');
}

GridErrorUnHighlight = function(el, er, ev) {
    $(el)
        .removeClass('ui-state-error')
    .parent()
       .removeClass('ui-state-error');
}
var table = $('#tableid').jqGrid({});

var validateOpt = {
        meta: "validate",
        highlight: table.onErrorHighlight,
        unhighlight: table.onUnHighlight
    };
$('#formId').validate(val);*/

function reload() {
	jQuery("#closingEH").trigger("reloadGrid"); 
} 

});
