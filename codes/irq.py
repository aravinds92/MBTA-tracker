import RPi.GPIO as GPIO  

irq_pin = 23

GPIO.setmode(GPIO.BCM)  
GPIO.setup(irq_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)  

var = 1

ctrl = open(".control","w")	
ctrl.write("")
ctrl.close()

  
def irq_start(channel):  
	global var
	print var
	ctrl = open(".control", "w")
	ctrl.seek(0)
	ctrl.write("")
	
	if var==1:
		var = 0
		print "Sending signal to start"
		ctrl.write("a")

	else:
		var = 1
		print "Sending signal to stop"
		ctrl.write("qwerty")
	
	ctrl.close()
    

print "IRQ setup"

GPIO.add_event_detect(irq_pin, GPIO.RISING, callback=irq_start)  
 
x = 1
while x==1:
	pass


print "Cleaning up"    
GPIO.cleanup()           # clean up GPIO on normal exit  
