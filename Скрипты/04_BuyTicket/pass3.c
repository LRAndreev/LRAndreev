pass3()
{
	web_submit_data("reservations.pl_3",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t6.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=firstName", "Value={firstName}", ENDITEM,
				"Name=lastName", "Value=", ENDITEM,
				"Name=address1", "Value={address1} str", ENDITEM,
				"Name=address2", "Value={depart} {address2}", ENDITEM,
				"Name=pass1", "Value={firstName} ", ENDITEM,
				"Name=pass2", "Value={firstName}1 ", ENDITEM,
				"Name=pass3", "Value={firstName}2 ", ENDITEM,
				"Name=creditCard", "Value={creditCard}", ENDITEM,
				"Name=expDate", "Value={expDate}", ENDITEM,
				"Name=oldCCOption", "Value=", ENDITEM,
				"Name=numPassengers", "Value=3", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=returnFlight", "Value={returnFlight}", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				"Name=buyFlights.x", "Value=51", ENDITEM,
				"Name=buyFlights.y", "Value=13", ENDITEM,
				"Name=.cgifields", "Value=saveCC", ENDITEM,
				LAST);
	return 0;
}
