delete_three()
{
	web_submit_form("web_submit_form",
				ITEMDATA,
				"Name=1", "Value=on", ENDITEM,
				"Name=2", "Value=on", ENDITEM,
				"Name=3", "Value=on", ENDITEM,
				"Name=removeFlights.x", "Value=52", ENDITEM, 
				"Name=removeFlights.y", "Value=9", ENDITEM,
				EXTRARES,		
				"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
				"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
				LAST);
	return 0;
}
