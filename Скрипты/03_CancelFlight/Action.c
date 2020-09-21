Action()
{
	int before;
	int after;
	int random;

	lr_start_transaction("03_CancelFlight");

	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	lr_start_transaction("loadWebTours");


			web_add_auto_header("Sec-Fetch-Site", 
				"none");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"document");
		
			web_add_auto_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_auto_header("DNT", 
				"1");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
		/*Correlation comment: Automatic rules - Do not change!  
		Original value='129607.526609964zzzzziHpVftAAAApVccQ' 
		Name ='userSession' 
		Type ='Rule' 
		AppName ='WebTours' 
		RuleName ='userSession'*/
			web_reg_save_param_attrib(
				"ParamName=userSession",
				"TagName=input",
				"Extract=value",
				"Name=userSession",
				"Type=hidden",
				SEARCH_FILTERS,
				"RequestUrl=*/nav.pl*",
				LAST);
		
			web_reg_find("Fail=NotFound",
						"Text=A Session ID has been created",
						LAST);
		
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours/", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
		
			/*Possible OAUTH authorization was detected. It is recommended to correlate the authorization parameters.*/
	
	lr_end_transaction("loadWebTours", LR_AUTO);


	lr_start_transaction("login");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			lr_think_time(8);
			
			web_reg_find("Fail=NotFound",
						"Text=User password was correct",
						LAST);
			
			web_reg_find("Fail=NotFound",
				"Text=Welcome, <b>{login}<\/b>",
				LAST);
		
			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=59", ENDITEM,
				"Name=login.y", "Value=8", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("click_itinerary");

			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(19);
			
			web_reg_find("Fail=NotFound",
				"Text=User wants the intineraries",
				LAST);
			
			web_reg_save_param("flightID_before",
			"LB=name=\"flightID\" value=\"",
			"RB=\"",
			"Ord=ALL",
			"NotFound=ERROR",
			LAST);
			
	
			web_url("Itinerary Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
			
			before = atoi(lr_eval_string("{flightID_before_count}"));
			lr_output_message("Value of before is %d, user is %s", before, lr_eval_string("{login}"));

	lr_end_transaction("click_itinerary",LR_AUTO);

	lr_start_transaction("cancel_flight");

			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(18);
			
			web_reg_save_param("flightID_after",
				"LB=name=\"flightID\" value=\"",
				"RB=\"",
				"Ord=ALL",
				"NotFound=WARNING",
				LAST);
			
//			web_reg_save_param("flights_after",
//		"LB=A total of ",
//		"RB= scheduled",
//		LAST);

				                                
//			web_reg_find("Fail=Found",
//				"Text=we could not delete",
//				LAST);
			
			random = atoi(lr_eval_string("{randomNum}"));
			
			lr_output_message("Random value is %d", random);
			
			submit_form();
		
			if ((random == 2) && (before >= random)) {
				
				submit_form();
			
			} else if ((random == 3) && (before >= random)) {
				
				submit_form();
				submit_form();
			}
		
			
			after = atoi(lr_eval_string("{flightID_after_count}"));
			
			if(before > after/2) {
				lr_output_message("Success. Value of before is %d value of after is %d", before, after/2);
			} else {
				lr_error_message("Fail");
			}
	
//	web_submit_data("itinerary.pl",
//		"Action=http://localhost:1080/cgi-bin/itinerary.pl",
//		"Method=POST",
//		"TargetFrame=",
//		"RecContentType=text/html",
//		"Referer=http://localhost:1080/cgi-bin/itinerary.pl",
//		"Snapshot=t4.inf",
//		"Mode=HTML",
//		ITEMDATA,
//		"Name=1", "Value=on", ENDITEM,
//		"Name=flightID", "Value=33852616-818-JB", ENDITEM,
//		"Name=flightID", "Value=164593463-1693160-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-2384716-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-3153947-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-3923178-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-4692408-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-5461639-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-6230870-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-7000101-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-7769331-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-8538562-JB", ENDITEM,
//		"Name=flightID", "Value=164593096-9307793-JB", ENDITEM,
//		"Name=removeFlights.x", "Value=50", ENDITEM,
//		"Name=removeFlights.y", "Value=12", ENDITEM,
//		"Name=.cgifields", "Value=6", ENDITEM,
//		"Name=.cgifields", "Value=11", ENDITEM,
//		"Name=.cgifields", "Value=3", ENDITEM,
//		"Name=.cgifields", "Value=7", ENDITEM,
//		"Name=.cgifields", "Value=9", ENDITEM,
//		"Name=.cgifields", "Value=12", ENDITEM,
//		"Name=.cgifields", "Value=2", ENDITEM,
//		"Name=.cgifields", "Value=8", ENDITEM,
//		"Name=.cgifields", "Value=1", ENDITEM,
//		"Name=.cgifields", "Value=4", ENDITEM,
//		"Name=.cgifields", "Value=10", ENDITEM,
//		"Name=.cgifields", "Value=5", ENDITEM,
//		LAST);
	


	lr_end_transaction("cancel_flight",LR_AUTO);

	lr_start_transaction("logout");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			lr_think_time(24);
			
			web_reg_find("Fail=NotFound",
						"Text=A Session ID has been created",
						LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("03_CancelFlight", LR_AUTO);


	return 0;
}