import urllib
import os
import time
import RPi.GPIO as GPIO  

directory = os.getcwd()									#Find out directory to store image
image_name = "map.png"
directory += "/" + image_name

url = 	"https://maps.googleapis.com/maps/api/staticmap?&zoom="
image_size = 	"&size=640x640&format=png32&maptype=terrain"


center_red = "&center=42.351526,-71.118900"
center_blue = "&center=42.351526,-71.118900"
center_green = "&center=42.351526,-71.118900"
center_orange = "&center=42.351526,-71.118900"

marker_red_northbound = "&markers=color:red%7Clabel:N%7C"
marker_red_southbound = "&markers=color:red%7Clabel:S%7C"
marker_blue_westbound = "&markers=color:blue%7Clabel:W%7C"
marker_blue_eastbound = "&markers=color:blue%7Clabel:E%7C"
marker_green_westbound = "&markers=color:green%7Clabel:W%7C"
marker_green_eastbound = "&markers=color:green%7Clabel:E%7C"
marker_orange_northbound = "&markers=color:orange%7Clabel:N%7C"
marker_orange_southbound = "&markers=color:orange%7Clabel:S%7C"

key = "&key=AIzaSyBaysPgYQfk4DRsgVK_1NJMv100nYrm6Mg"

West = 'Westbound'
East = 'Eastbound'
North = 'Northbound'
South = 'Southbound'

output_pin = 24

GPIO.setmode(GPIO.BCM)            							# choose BCM or BOARD  

GPIO.setup(output_pin, GPIO.OUT) 									# set a pin 24 as an output
cnt = 0
abc = 0
n = 1
while n==1:
	ctrl = open(".control","r")								#Open file to check if the API can be queried
	ctrl_str = ctrl.read(3)
	ctrl.close()

	if ctrl_str == "z":
		cnt=cnt+1
		if cnt>1:
			input_file = open(".input", "r")					#Open file to find out which route to display

	
			x = input_file.read()
			#print x
			l = x.split("\n")
			mode = int(l[0])
			direction = l[1]

			#print direction

			lat_file = open(".lat_file","r")					#Open the files containing latitude and longitude locations
			lon_file = open(".lon_file","r")	

			y = lat_file.read()									#Split the file to store the latitude and longitude in a list
			lat = y.split("\n")

			z = lon_file.read()
			lon = z.split("\n")

			list_len = len(lat) - 1								#Find length of the list
			#print list_len


			if list_len==0:										#Check if trains are available in that route
				print "no trains available"
				image = 0
				time.sleep(10)
				os.system("cp map.png .. .")
				GPIO.output(output_pin, 1) 										#Interrupt gumstix to inform it that the image has been transferred
				GPIO.output(output_pin, 0)     
				print  "Empty map generated"	
				
			else:
				image = 1										#Trains available	
		
				lat_center = 0
				lon_center = 0

				for i in range(0,list_len):							#Find center of the map	
					lat_center += float(lat[i])
					lon_center += float(lon[i])


				lat_center = lat_center/(list_len)
				lon_center = lon_center/(list_len)

				zoom_val = 12
				lat_str = url + str(zoom_val) + "&scale=1&" + image_size + "&center=" + str(lat_center) + "," + str(lon_center)			#Store the initial contents in the URL string

				#print lat_center 
				#print lon_center


				if mode==0 and direction==North:													#Branches to determine the rest of the URL
					#for i, item in enumerate(lat):
					for i in range(0,list_len):
						lat_str += marker_red_northbound + lat[i] + ",%20" + lon[i]
					lat_str += key


				elif mode==0 and direction==South:
					#Red South
					for i in range(0,list_len):
						lat_str += marker_red_southbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				elif mode==1 and direction==North:
					#Orange North
					for i in range(0,list_len):
						lat_str += marker_orange_northbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				elif mode==1 and direction==South:
					#Orange South
					for i in range(0,list_len):
						lat_str += marker_orange_southbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				elif mode==2 and direction==East:
					#Blue East
					for i in range(0,list_len):
						lat_str += marker_blue_eastbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				elif mode==2 and direction==West:
					#Blue west
					for i in range(0,list_len):
						lat_str += marker_blue_westbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				elif direction==East and (mode>=3 or mode<=6):
					#GB East
					#print "inside1"
					for i in range(0,list_len):
						lat_str += marker_green_eastbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				elif direction==West and (mode>=3 or mode<=6) :
					#GB West
					#print "inside2"
					for i in range(0,list_len):
						lat_str += marker_green_westbound + lat[i] + ",%20" + lon[i]
					lat_str += key

				else:
					print "Invalid value of route or direction"

				#print "Going to access api"
				urllib.urlretrieve(lat_str,directory)													#Store image in a file
				print "Generated"
			
				#os.system("xdg-open map.png")
				GPIO.output(output_pin, 1) 										#Interrupt gumstix to inform it that the image has been transferred
				GPIO.output(output_pin, 0)     
				print  "Int generated"	
  									
				lat_file.close()
				lon_file.close()
				input_file.close()
				time.sleep(10)
		else:
			print "Inside the other one"
			pass	
			time.sleep(5)
		

	else:
		if cnt!=0:
			print "No control received"
		cnt=0
		#print "no control recieved"												#control = 0
		pass

