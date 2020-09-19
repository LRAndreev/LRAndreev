Action()
{
	int x;
	
	lr_start_transaction("04_BuyTicket");
	
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
		Original value='129606.705062778zzzzzttpiQVzzzzHDQQQQpizQDf' 
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
			
			lr_think_time(5);
			
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
				"Name=login.x", "Value=48", ENDITEM,
				"Name=login.y", "Value=6", ENDITEM,
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
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
			

	lr_end_transaction("click_Flights",LR_AUTO);

	lr_start_transaction("find_flight_continue");

			web_add_auto_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(78);
			
			
			
			
		
		/*Correlation comment: Automatic rules - Do not change!  
		Original value='023;519;09/14/2020' 
		Name ='outboundFlight' 
		Type ='Rule' 
		AppName ='WebTours' 
		RuleName ='outboundFlight'*/
			web_reg_save_param_attrib(
				"ParamName=outboundFlight",
				"TagName=input",
				"Extract=value",
				"Name=outboundFlight",
				"Type=radio",
				"Ordinal=4",
				LAST);
		
		/*Correlation comment - Do not change!  Original value='201;565;09/21/2020' Name ='returnFlight' Type ='ResponseBased'*/
			web_reg_save_param_attrib(
				"ParamName=returnFlight",
				"TagName=input",
				"Extract=value",
				"Name=returnFlight",
				"Type=radio",
				SEARCH_FILTERS,
				"IgnoreRedirections=No",
				LAST);
		
			web_reg_find("Fail=NotFound",
				"Text/ALNUMIC=From {depart} (^) To {arrive}",
				LAST);
		
		web_submit_data("reservations.pl",
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
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
				"Name=findFlights.x", "Value=54", ENDITEM, 
				"Name=findFlights.y", "Value=11", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);

	lr_end_transaction("find_flight_continue",LR_AUTO);

	lr_start_transaction("choose_flight");
	
			lr_think_time(45);
			
			web_reg_find("Text=name\=\"firstName\" value\=\"{firstName}\"",
				LAST);

			x = atoi(lr_eval_string("{numPassengers}"));
			lr_output_message("x is %d", x);
			
			web_submit_data("reservations.pl_2",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t5.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
				"Name=returnFlight", "Value={returnFlight}", ENDITEM,
				"Name=numPassengers", "Value={numPassengers}", ENDITEM,
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				"Name=reserveFlights.x", "Value=44", ENDITEM,
				"Name=reserveFlights.y", "Value=7", ENDITEM,
				LAST);

	lr_end_transaction("choose_flight",LR_AUTO);

	lr_start_transaction("payment_details");

			web_revert_auto_header("Origin");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(24);
			
			web_reg_find("Fail=NotFound",
				"Text=Reservation Made",
				LAST);
		
			web_reg_find("Fail=NotFound",
				"Text=leaves {depart}  for {arrive}",
				LAST);
			
			web_reg_find("Fail=NotFound",
				"Text=leaves {arrive}  for {depart}",
				LAST);
			
			web_reg_find("Text=Charged to Credit Card # {creditCard}",
				LAST);

		if (x == 1) {
			
				pass1();
				
			} else if (x == 2) {
				
				pass2();
				
			} else {
				pass3();
			}

	lr_end_transaction("payment_details",LR_AUTO);

	lr_start_transaction("logout");

			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(34);
			
			web_reg_find("Fail=NotFound",
			"Text=A Session ID has been created",
			LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("04_BuyTicket", LR_AUTO);


	return 0;
}