Action()
{

	lr_start_transaction("02_FindFlight");
	
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
		Original value='129607.382827055zzzzzHQpHftVzzzHtAAAApAHifcf' 
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
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
	
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
		
			lr_think_time(16);
			
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
				"Snapshot=t3.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=42", ENDITEM,
				"Name=login.y", "Value=12", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("click_Flights");

			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(32);
			
			web_reg_find("Fail=NotFound",
				"Text=User has returned to the search page",
				LAST);
		
			web_url("Search Flights Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				LAST);

	lr_end_transaction("click_Flights",LR_AUTO);

	lr_start_transaction("find_flight_continue");

			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(33);
			
			web_reg_find("Fail=NotFound",
				"Text/ALNUMIC=From {depart} (^) To {arrive}",
				LAST);
		
			web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=roundtrip", "Value=on", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=52", ENDITEM, 
				"Name=findFlights.y", "Value=8", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);

	lr_end_transaction("find_flight_continue",LR_AUTO);

	lr_start_transaction("logout");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			lr_think_time(17);
			
			web_reg_find("Fail=NotFound",
				"Text=A Session ID has been created",
				LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t6.inf", 
				"Mode=HTML", 
				LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("02_FindFlight", LR_AUTO);


	return 0;
}