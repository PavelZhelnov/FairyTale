<?php
// REGISTRY/_RestrictedAreas
	$REGISTRY['RestrictedAreas'] = array (
		'/Admin' => array (
			'Administrator'
		)
	);
// ~REGISTRY/_RestrictedAreas
// REGISTRY/_MemberAreas
	$REGISTRY['MemberAreas'] = array(
		'/Register' => array (
			'Member'
		),

	);
// ~REGISTRY/_RestrictedAreas
// REGISTRY/_GuestAreas
	$REGISTRY['GuestAreas'] = array(
//		'/Admin' => array (
			//'Guest'
		//)
	);
// ~REGISTRY/_RestrictedAreas
$REGISTRY['Permissions'] = array();
// ~REGISTRY/_Permissions

// REGISTRY/_Templates
$REGISTRY['Templates'] = array (
	'Layout' => 'default.layout.html',
	'WideLayout' => 'wide.layout.html',
	'AdminLayout' => 'admin.layout.html',
	'EmptyLayout' => 'main.html',
);
// ~REGISTRY/_Templates

// REGISTRY/_VirtualSlotTarget
$REGISTRY['VirtualSlotTarget'] = array(
	'langpanel' => array(
		'' => array(
			'inherit' => 'LangPanelView:object',
			'Locate' => FALSE,
		),
	),
	'counter' => array(
		'' => array(
			'inherit' => 'CounterView:object',
			'Locate' => FALSE,
		),
	),	
	'header' => array(
		'' => array(
			'inherit' => 'HeaderView:object',
			'Locate' => FALSE,
		),
	),
	'metainfo_description' => array(
		'' => array(
			'inherit' => 'MetaInfoView:object?scheme=description',
			'Locate' => FALSE,
		),
	),
	'metainfo_keywords' => array(
		'' => array(
			'inherit' => 'MetaInfoView:object?scheme=keywords',
			'Locate' => FALSE,
		),
	),
	'metainfo_title' => array(
		'' => array(
			'inherit' => 'MetaInfoView:object?scheme=title',
			'Locate' => FALSE,
		),
	),
	'autoimage' => array(
		'' => array(
			'inherit' => 'AutoImageView:object',
			'Locate' => FALSE,
		),
	),
	'shipimage' => array(
		'' => array(
			'inherit' => 'ShipImageView:object',
			'Locate' => FALSE,
		),
	),
	
	'agentmenupanel' => array(
		'' => array(
			'inherit' => 'AgentMenuPanelView:object',
			'Locate' => FALSE,
		),
	),
	'menupanel' => array(
		'' => array(
			'inherit' => 'MenuView:object',
			'Locate' => FALSE,
		),
	),
	'menupanel_bottom' => array(
		'' => array(
			'inherit' => 'MenuView:object?scheme=bottom',
			'Locate' => FALSE,
		),
	),

	'quotation' => array(
		'' => array(
			'inherit' => 'QuotationView:object',
			'Locate' => FALSE,
		),
	),	
	'message' => array(
		'' => array(
			'inherit' => 'MessageView:object',
			'Locate' => FALSE,
		),
	),
	'adminmenupanel' => array(
		'' => array(
			'inherit' => 'AdminMenuPanelView:object',
			'Locate' => FALSE,
		),
	),
	'admin' => array(
		'' => array(
			'inherit' => 'AdminView:object',
			'Locate' => FALSE,
		),
	),
	'statistic' => array(
		'' => array(
			'inherit' => 'StatisticView:object',
			'Locate' => FALSE,
		),
	),
	'adminstatistic' => array(
		'' => array(
			'inherit' => 'AdminStatisticView:object',
			'Locate' => FALSE,
		),
	),
	'tracking_preview' => array(
		'' => array(
			'inherit' => 'TrackingView:object?scheme=preview',
			'Locate' => FALSE,
		),
	),
	'search_preview' => array(
		'' => array(
			'inherit' => 'SearchView:object?scheme=preview',
			'Locate' => FALSE,
		),
	),

	'' => array(
		'' => array(
			'inherit' => 'Layout',
			'Locate' => FALSE,
		),
		'/Admin' => array(
			'inherit' => 'AdminLayout',
			'Locate' => FALSE,
		),
		'/ImageListing' => array(
			'inherit' => 'ImageListingView:object',
			'Locate' => FALSE,
		),
		'/ImageListingViewer' => array(
			'inherit' => 'ImageListingViewerView:object',
			'Locate' => FALSE,
		),
		'/Docs/View' => array(
			'inherit' => 'EmptyLayout',
			'Locate' => FALSE,
		),
		
	),
	'main' => array (
		'' => array(
			'inherit' => 'ThingsView:object',
			'Locate' => FALSE,
		),
		'/Docs' => array(
			'inherit' => 'DocsView:object',
			'Locate' => FALSE,
		),		
		'/Things' => array(
			'inherit' => 'ThingsView:object',
			'Locate' => FALSE,
		),
		'/Statistic' => array(
			'inherit' => 'StatisticView:object',
			'Locate' => FALSE,
		),
		'/tracking' => array(
			'inherit' => 'TrackingView:object',
			'Locate' => FALSE,
		),
		'/search' => array(
			'inherit' => 'SearchView:object',
			'Locate' => FALSE,
		),
	),
);
//var_dump ($REGISTRY['VirtualSlotTarget']['metainfo_title'][""]["Locate"]);
//$REGISTRY['VirtualSlotTarget']['metainfo_title']["virtual"] = '1111';
//var_dump ($REGISTRY['VirtualSlotTarget']['metainfo_title'][""]["Locate"]);

// ~REGISTRY/_VirtualSlotTarget
?>