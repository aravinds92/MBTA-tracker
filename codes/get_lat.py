import requests
import xml.etree.ElementTree as ET
import os
import time
import atexit


url_Red = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Red&format=xml'
url_Orange = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Orange&format=xml'
url_Blue = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Blue&format=xml'
url_greenB = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Green-B&format=xml'
url_greenC = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Green-C&format=xml'
url_greenD = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Green-D&format=xml'
url_greenE = 'http://realtime.mbta.com/developer/api/v2/vehiclesbyroute?api_key=wX9NwuHnZU2ToO7GmGR9uw&route=Green-E&format=xml'


level1 = 'direction'											#Constants for that particular api query
level2 = 'trip'
level3 = 'vehicle'



lat = 'vehicle_lat'												#Strings used to detemine query string
lon = 'vehicle_lon'
direction = 'direction_name'
West = 'Westbound'
East = 'Eastbound'
North = 'Northbound'
South = 'Southbound'


Url_list = [url_Red,url_Orange,url_Blue,url_greenB,url_greenC,url_greenD,url_greenE]			#Store urls in a list to make access easier


x=1
while x==1:

	ctrl = open(".control","r")										#Open file to check if the API can be queried
	ctrl_str = ctrl.read()
	ctrl.close()

	if ctrl_str=="a" or ctrl_str == "z":
		
		input_file = open(".input", "r")								
		a = input_file.read();
		l = a.split("\n")												#Split the string with the \n delimiter
		input_file.close()												
		i = int(l[0])												#Deermine route and direction received from gumstix
		input_direction = l[1]		
		#print l[1]

		if i>=0 and i<=6:
			if input_direction==East or input_direction == West or input_direction == North or input_direction == South:

				#print input_direction
				lat_file = open(".lat_file", "w")								#Open files to write latitude and longitude data
				lon_file = open(".lon_file", "w")

				api_call = requests.get(Url_list[i])							#Make the api call
				api_data = api_call.content
				root = ET.fromstring(api_data)

				for element in root.findall(level1):							#Go through the xml to get the list of latitudes and longitudes
					for child in element.findall(level2):
						for child1 in child.findall(level3):
							veh_lat =  child1.get(lat)
							veh_lon = child1.get(lon)
							#print veh_lat + "\t" +veh_lon
							if element.get(direction) == l[1]:
								lat_file.write(veh_lat + "\n")
								lon_file.write(veh_lon + "\n")

				#print "here"
				ctrl = open(".control","w")										#Open file to check if the API can be queried
				ctrl.seek(0)
				ctrl.write("z")	
				ctrl.close()

				lat_file.seek(0)
				lat_file.close()

				lon_file.seek(0)
				lon_file.close()
				time.sleep(10)
				print "Wakeup from sleep"

		else:
			print "Invalid input"
	

	else:
		pass
