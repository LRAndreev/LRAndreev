Action()
{
	lr_start_transaction("06_LoginLogout");

	
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
		Original value='129607.998622924zzzzHVVptcQVzzzHtAAAApczifHf' 
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
				"Snapshot=t3.inf", 
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
		
			lr_think_time(24);
			
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
				"Snapshot=t4.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=35", ENDITEM,
				"Name=login.y", "Value=9", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);

	lr_end_transaction("login",LR_AUTO);
	
	lr_start_transaction("logout");

			web_revert_auto_header("Sec-Fetch-User");
		
			lr_think_time(21);
			
			web_reg_find("Fail=NotFound",
						"Text=A Session ID has been created",
						LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
				"Snapshot=t6.inf", 
				"Mode=HTML", 
				LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("06_LoginLogout", LR_AUTO);
	
	return 0;
}
