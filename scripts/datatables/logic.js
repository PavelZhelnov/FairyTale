WidgetDocument = function(category, instance_id) {
	this.instance_id = instance_id;
	this.category = category;
	this.init = function() {
		var instance = this;

//		if (jQuery.browser.msie && jQuery.browser.version < 10) {
//			$(".selectchange").change(function() {
//				console.log('sdfsdf');
//				$('.formajaxsubmt').attr("onsubmit", "return true");
//				document.forms['step1'].step.value = "step1";
//				$('.formajaxsubmt').submit();
//			});
//			$('#formsubmit').click(function() {
//
//				if (document.getElementById("step1") != null) {
//					console.log('xcvxcv');
//					document.forms['step1'].o.value = "DocumentView";
//					document.forms['step1'].step.value = "add_document";
//				}
//				if (document.getElementById("bpo") != null) {
//					document.forms['bpo'].o.value = "DocumentView";
//					document.forms['bpo'].step.value = "add_document";
//				}
//				if (document.getElementById("offer") != null) {
//					document.forms['offer'].o.value = "DocumentView";
//					document.forms['offer'].step.value = "add_document";
//				}
//				if (document.getElementById("closing") != null) {
//					document.forms['closing'].o.value = "DocumentView";
//					document.forms['closing'].step.value = "add_document";
//				}
//
//				if (document.getElementById("contact") != null) {
//					document.forms['contact'].o.value = "DocumentView";
//					document.forms['contact'].step.value = "add_document";
//				}
//				$('.formajaxsubmt').attr("onsubmit", "return true");
//				$('.formajaxsubmt').submit();
//			});
//			//$('.formajaxsubmt').attr("onsubmit","return true")
//
//		} else {
//			$(".selectchange").change(function() {
//				console.log('sdfsdf');
//				$('.formajaxsubmt').attr("onsubmit", "return true");
//				document.forms['step1'].step.value = "step1";
//				$('.formajaxsubmt').submit();
//			});
//			$('#formsubmit').click(function() {
//				$('.formajaxsubmt').submit();
//			$('.formajaxsubmt').attr("onsubmit", "return true");
//			instance.ajaxFormFileSubmit(instance_id, category);
//			});
//		}
//		if (window.File && window.FileList && window.FileReader) {
//			var fileselect = $("#filestoupload_" + instance_id);
//			fileselect.live('change', function(e) {
//				FileSelectHandler(e, category, instance_id);
//			});
//		}

		$.blockUI.defaults.css = {
			padding : 0,
			margin : 0,
			width : '30%',
			top : '40%',
			left : '35%',
			textAlign : 'center',
			cursor : 'wait'
		};
		var propertyvalue = instance.getIdProperty();
		instance.initTable(propertyvalue, instance_id, category);

		$('.heightuto').parent('div').css("height", "auto");
		$('.heightuto').parent('div').parent('div').css("height", "auto");
		$('.checkall').click(function() {
			$(this).parents('table:eq(0)').find(':checkbox').attr('checked', this.checked);
		});

	};
//	this.fileUploadSuccess = function(instance_id, category) {
//		var instance = this;
//		$('#filestoupload_' + instance_id).val('');
//		$('#filesUplaodedDetail_' + instance_id).dataTable().fnDestroy();
//		var propertyvalue = instance.getIdProperty();
//		$('#fileList_' + instance_id).html('');
//		instance.initTable(propertyvalue, instance_id, category);
//	}
//	this.ajaxFormFileSubmit = function(instance_id, category) {
//		var instance = this;
//		$('.formajaxsubmt').ajaxForm({
//			beforeSubmit : function(formData, jqForm, options) {
//				$('.formajaxsubmt').attr("onsubmit", "return true");
//				console.log(formData);
//				formData[0].value = 'DocumentView';
//				formData[1].value = 'add_document';
//
//				$.blockUI({
//					message : '<img src="' + picPath + '/elements/ajax-loader.gif" />'
//				});
//
//			},
//			complete : function(xhr) {
//				console.log(xhr);
//				var arr = JSON.parse(xhr.responseText);
//
//				$.unblockUI();
//
//				instance.fileUploadSuccess(arr.instance_id, arr.category);
//
//			},
//			error : function(XMLHttpRequest, textStatus, errorThrown) {
//				$.unblockUI();
//				var a = JSON.parse(XMLHttpRequest.responseText);
//
//				alert(a.error_message);
//
//			}
//		});
//	};
	this.getIdProperty = function() {
		var propertyitem = $('#propertyvalue').val();
		return propertyitem;
	};
	this.initTable = function(propertyvalue, instance_id, category) {

		var ownerid = propertyvalue;
		$('#filesUplaodedDetail_' + instance_id).dataTable({

			"bServerSide" : false,
			"sAjaxSource" : domain_sub_path + "Admin/Document/search/",
			'fnServerParams' : function(aoData) {

				aoData.push({
					"name" : "ownerid",
					"value" : ownerid
				});
				aoData.push({
					"name" : "category",
					"value" : category
				});
				aoData.push({
					"name" : "owner_type",
					"value" : instance_id
				});

			},
			"bJQueryUI" : true,
			"sPaginationType" : "full_numbers",

			"aoColumns" : [{
				"mData" : "id",
				"bUseRendered" : false,
				"bSortable" : false,
				"fnRender" : function(value) {

					return '<input type="checkbox" id="' + value.aData.id + '" name="delete-row"/>';
				}
			}, {
				"mData" : "type",
				"fnRender" : function(value) {

					return value.aData.db_row_id;
				}
			}, {
				"mData" : "file_name"
			}, {
				"mData" : "description",

				"fnRender" : function(value) {
					var descvalue;
					if (value.aData.description == null) {
						descvalue = '';
					} else {
						descvalue = value.aData.description;
					};
					return '<input class="form_field_' + instance_id + '" type="text" id="' + value.aData.id + '" value="' + descvalue + '" maxlength="255" name="edit-description" class="edit-description"/>';
				}
			}, {
				"mData" : "date"
			}, {
				"mData" : "size"
			}],
			"sDom" : 'R<"H"lfr>t<"F"ip>'
		});
		$("#filesUplaodedDetail_" + instance_id + "_length").append('<div class="tDiv"><button id="delete_' + instance_id + '" class="delete ui-button ui-widget ui-state-default ui-corner-all ui-button-text-only"><span class="ui-button-text">Delete</span></button></div>');
		$('#delete_' + instance_id).live('click', function() {
			var instance = this;
			deleteRows(instance_id, category);
			return false;
		});

		$(".form_field_" + instance_id).live('blur', function() {
			updateDesc(this, category);

		});
		$(".form_field_" + instance_id).live('keyup', function(e, category) {
			var instance = this;
			if (e.keyCode == 13) {

				$(instance).parent().parent().next('tr').children('td:eq(3)').children('input').focus();
				e.preventDefault();
				return false;
			}
		});
	};

};
function updateDesc(item, category) {
	var field = item;
	var sel = $(item).val();
	var id = $(item).attr('id');
	$.ajax({
		url : domain_sub_path + "Admin/Document/edit/",
		type : 'POST',
		data : {
			id : id,
			description : sel,
			category : category
		},
		success : function(msg) {
			$(field).css({
				"border" : "2px solid green"
			});
		},
		error : function() {
			console.log(field);
			$(field).css({
				"border" : "2px solid red"
			});
		} // end success
	});
	// end ajax

};
// end change

function deleteRows(instance_id, category) {
	var oTable = $('#filesUplaodedDetail_' + instance_id).dataTable();
	var sData = jQuery('input:checked', oTable.fnGetNodes()).serialize();
	var aTrs = oTable.fnGetNodes();
	var data = [];
	var params = {};

	for (var i = 0; i < aTrs.length; i++) {
		if (jQuery('input:checked', aTrs[i]).val()) {
			oTable.fnDeleteRow(aTrs[i]);
			data.push({
				'id' : $('input:checked', aTrs[i]).attr('id'),
				'category' : category
			});

		}
	}
	params.list = data;

	var myJsonString = JSON.stringify(params);
	$.blockUI({
		message : '<img src="' + picPath + '/elements/ajax-loader.gif" />'
	});
	$.ajax({
		url : domain_sub_path + "Admin/Document/delete/",
		dataType : 'json',
		data : params,
		success : function() {
			$('.checkall').attr('checked', false);
			$.unblockUI();
			//alert("Documents were deleted!");
		}
	});
}

//function FileSelectHandler(e, category, instance_id) {
//
//	var files = e.target.files || e.dataTransfer.files;
//	var html = '';
//	// process all File objects
//	for (var i = 0, f; f = files[i]; i++) {
//		html += "<table><tr><td width=600>File : <strong><input type='hidden' name='form[document][" + i + "][filename]' value='" + f.name + "' id='d" + i + "' />" + f.name +
//		// "</strong> type: <strong>" + file.type +
//		"</strong> size: <strong><input type='hidden' name='form[document][" + i + "][filesize]' value='" + f.size + "' id='d" + i + "' />" + f.size + "</strong> bytes&nbsp;" + "</td><td width=200><strong>Description : </strong><input type='hidden' name='form[document][" + i + "][category]' value='" + category + "' id='c" + i + "'/><input type='text' name='form[document][" + i + "][description]' id='d" + i + "' /></td></tr></table>";
//
//	}
//	$('#fileList_' + instance_id).html(html);
//};
