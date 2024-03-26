# OpenAuto Pro Raspberry Pi Start Up And Shut Down Script

In the bellow diagram i introduce startup and shutdown process of the OAP.
the raspberry listens for shortage on GPIO 3 and when the same is missing executes shutdown command
Arduino is in loop lisens for serial communication comming from raspberry, if there is no such sends start command to the relay and Global/EN


![](/wiring_bb.jpg)


## startup script
Load the `esp_arduino.ino` to your Arduiono Nano 

## shutdown script
download `listen_for_shutdown.py` to your `/home/pi/` folder

type in terminal
`sudo su` to swich into root account then:
`crontab -e`

add this to the end of crontab

`@reboot /usr/bin/python3 /home/pi/listen_for_shutdown.py >/dev/null 2>&1`

## Option that I use 

I created .sh file to execute the python and then in the corontab job I select the shell script.