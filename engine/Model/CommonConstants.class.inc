<?php
class CommonConstants {
	//TIMEZONES
	const TIME_MILLISECONDS_OFFSET = 0;//21600;
	const TIME_SCHEDULED_FUNCTIONS_INTERVAL = 80000; //a little less than one 24 hours
	const TIME_LOSTPASSWORD_ACTIVE_LINK_INTERVAL = 86400; //second in 24 hours
	
	//WORKFLOW
		//tables
	const WORKFLOW_TABLE_ID_BPO = 1;
	const WORKFLOW_TABLE_ID_CLOSING = 2;
	const WORKFLOW_TABLE_ID_SHOWING = 3;
	const WORKFLOW_TABLE_ID_OFFER = 4;
	const WORKFLOW_TABLE_ID_PROPERTY = 5;
	const WORKFLOW_TABLE_ID_OFFER_HISTORY = 6;
	const WORKFLOW_TABLE_ID_TASK = 7;
	const WORKFLOW_TABLE_ID_NOTE = 8;
	const WORKFLOW_TABLE_ID_BPO_CHECK = 10;
	const WORKFLOW_TABLE_ID_MMR = 11;
	const WORKFLOW_TABLE_ID_CONTACT = 12;
	const WORKFLOW_TABLE_ID_MEMBER = 15;
	const WORKFLOW_TABLE_ID_PROPERTY_STATUS = 16;
	
		//statuses 
	const WORKFLOW_STATUS_ID_CLOSED = 1;
	const WORKFLOW_STATUS_ID_INACTIVE = 2;
	const WORKFLOW_STATUS_ID_ACTIVE = 3;
	
		//log actions
	const LOG_ACTION_LOGIN = 1;
	const LOG_ACTION_LOGOUT = 2;
	const LOG_ACTION_SAVE = 3;
	const LOG_ACTION_UPDATE = 4;
	const LOG_ACTION_DELETE = 5;
	const LOG_ACTION_APPROVE = 6;
	const LOG_ACTION_REJECT = 7;
	const LOG_ACTION_FEEDBACK = 8;
	const LOG_ACTION_CLOSE = 9;
	const LOG_ACTION_SCHEDULE = 10;
	const LOG_ACTION_VIEW = 11;
	
	const LOG_ACTION_SECTION_COMMON = 1;
	const LOG_ACTION_SECTION_PROPERTY = 2;
	const LOG_ACTION_SECTION_OFFER = 3;
	const LOG_ACTION_SECTION_CLOSING = 4;
	const LOG_ACTION_SECTION_SHOWING = 5;
	const LOG_ACTION_SECTION_BPO = 6;
	const LOG_ACTION_SECTION_ORGANIZATION = 7;
	const LOG_ACTION_SECTION_PROPERTY_PHOTO = 8;
	const LOG_ACTION_SECTION_PROPERTY_PRICE = 11;
	const LOG_ACTION_SECTION_OFFER_CONFIRMATION = 13;
	const LOG_ACTION_SECTION_OFFER_HISTORY = 14;
	const LOG_ACTION_SECTION_SHOWING_SCHEDULE = 16;
	const LOG_ACTION_SECTION_CONTACT = 21;
	const LOG_ACTION_SECTION_GENERAL_TASK = 23;
	const LOG_ACTION_SECTION_CLOSING_HISTORY = 24;
	const LOG_ACTION_SECTION_BPO_PHOTO = 25; 
	const LOG_ACTION_SECTION_GENERAL_NOTE = 26;
	const LOG_ACTION_SECTION_DOCUMENT = 27;
	
	
		//showing schedule responses
	const SHOWING_SCHEDULE_RESPONSE_NOT_PROCESSED = 1;
	const SHOWING_SCHEDULE_RESPONSE_APPROVED = 2;
	const SHOWING_SCHEDULE_RESPONSE_REJECTED = 3;
	const SHOWING_SCHEDULE_RESPONSE_FEEDBACK_RECEIVED = 4;
	const SHOWING_SCHEDULE_RESPONSE_CLOSED = 5;
	const SHOWING_SCHEDULE_RESPONSE_WAITING_FOR_FEEDBACK = 6;
	
	
	//PROPERTY
		//PRICES
	const PROPERTY_PRICE_HISTORY_AUTOMATIC_MESSAGE = 'First automatic price history';
	const PROPERTY_PRICE_DEFAULT_VALUE = 'TBA';
	
		//PROPERTY_STATUS
	const PROPERTY_STATUS_PREFORECLOSURE_REO = 1;
	const PROPERTY_STATUS_NEWASSIGNMENT_REO = 2;
	const PROPERTY_STATUS_FOR_SALE_ACTIVE = 6;
	const PROPERTY_STATUS_NEGOTIATED_SALE_PENDING = 7;
	const PROPERTY_STATUS_POTENTIAL_LISTING = 8;
	const PROPERTY_STATUS_SOLD = 9;
	const PROPERTY_STATUS_SOLD_AND_RECONCILED = 10;
	const PROPERTY_STATUS_INACTIVE = 11;
	const PROPERTY_STATUS_FOR_RENT_ACTIVE = 12;
	const PROPERTY_STATUS_CURRENTLY_RENTED = 13;
	const PROPERTY_STATUS_AGENT_REFERRAL = 14;

		//PROPERTY_TYPE
	const PROPERTY_TYPE_ATTACHED = 1;
	const PROPERTY_TYPE_COMMERCIAL = 2;
	const PROPERTY_TYPE_TIMESHARE = 4;
	const PROPERTY_TYPE_CONDO = 5;
	const PROPERTY_TYPE_MULTIFAMILY = 6;
	const PROPERTY_TYPE_PUD = 7;
	const PROPERTY_TYPE_SINGLEFAMILY = 8;
	const PROPERTY_TYPE_LANDONLY = 9;
	const PROPERTY_TYPE_MOBILE = 10;
	const PROPERTY_TYPE_MANUFACTURED = 11;
	const PROPERTY_TYPE_TRIPLEX = 12;
	const PROPERTY_TYPE_DUPLEX = 14;
	
	//CONTACT TYPE
	const CONTACT_TYPE_OTHER = 1;
	const CONTACT_TYPE_AGENT = 2;
	const CONTACT_TYPE_CONTRACTING_PARTY = 3;
	const CONTACT_TYPE_ADMINISTRATOR = 4;
	const CONTACT_TYPE_OFFICE_PERSONNEL = 5;
	const CONTACT_TYPE_AGENT_FNR_AGENT = 6;
	const CONTACT_TYPE_9_TO_5_AGENT = 7;
	
	
	//PERMISSION LEVEL
	const LEVEL_ADMINISTRATOR = 1;
	const LEVEL_AUDIT = 10;
	const LEVEL_GUEST = 12;
	const LEVEL_ATTORNEY = 14;
	const LEVEL_TYPE_ADMIN = 1;
	const LEVEL_TYPE_AGENT = 2;
	const LEVEL_TYPE_CLIENT = 3;
	const LEVEL_TYPE_GUEST = 4;
	
	//recaptcha keys
	const RECAPTCHA_PRIVATE = '6LcPvQkAAAAAAPVvQRUXSQ8GA9n2tXAns7jV5pbL';
	const RECAPTCHA_PUBLIC = '6LcPvQkAAAAAAGQ9PLZYyI6ozDn_KbQyHwOHrmCX';
	
	//OFFER
	  //OFFER HISTORY SELLER_REPLY
	  const OFFER_HISTORY_SELLER_REPLY_ACCEPTED = 1;
	  const OFFER_HISTORY_SELLER_REPLY_COUNTER = 2;
	  const OFFER_HISTORY_SELLER_REPLY_REJECTED = 3;
	  const OFFER_HISTORY_SELLER_REPLY_UNKNOWN = 4;
	  
	  //OFFER STATUS
	  const OFFER_STATUS_ACTIVE = 1;
	  const OFFER_STATUS_INACTIVE = 2;
	  const OFFER_STATUS_NEW_SUBMISSION = 3;
	  
	//CLOSING
	  //CLOSING STATUSES
	  const CLOSING_STATUS_UNDER_CONTRACT=1;
	  const CLOSING_STATUS_SCHEDULED=2;
	  const CLOSING_STATUS_CANCELLED=3;
	  const CLOSING_STATUS_SOLD=4;
	  const CLOSING_STATUS_FUNDS_WIRED=5;
	  const CLOSING_STATUS_RECONCILED=6;
	  const CLOSING_STATUS_PENDING_CLOSE=7;
	  const CLOSING_STATUS_CLOSED=8;
	  
	  //CLOSING TYPE
	  const CLOSING_TYPE_CASH=1;
	  const CLOSING_TYPE_CONVENTIONAL=2;
	  const CLOSING_TYPE_FHA=3;
	  const CLOSING_TYPE_VA=4;
	  
	  //CLOSING EARNEST MONEY STEP
	  const CLOSING_EM_STEP_RECEIVED = 1;
	  const CLOSING_EM_STEP_SENT_FOR_CLOSING = 2;
	  const CLOSING_EM_STEP_SENT_CONFIRMED = 3;
	  const CLOSING_EM_STEP_CONTRACT_FAILED = 4;
	  const CLOSING_EM_STEP_FINAL_DISBURSMENT = 5;
	  const CLOSING_EM_STEP_NOT_RECEIVED = 6;
	  
	  //CLOSING EM DOCUMENT TYPE
	  const CLOSING_EM_DOCUMENT_TYPE_COPY_OF_CHECK = 1; 
	  const CLOSING_EM_DOCUMENT_TYPE_DEPOSIT_SLIP = 2;
	  const CLOSING_EM_DOCUMENT_TYPE_DISBURSMENT_CHECK = 3;
		
}
?>