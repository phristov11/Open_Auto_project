#!/usr/bin/env python

import RPi.GPIO as GPIO
import subprocess
import time
import serial

IPIN = 3

def initialize_gpio():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(IPIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def initialize_serial():
    ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    time.sleep(3)
    ser.reset_input_buffer()
    return ser

def send_serial_data(ser, message):
    ser.write(message.encode('utf-8'))

def initiate_shutdown():
    subprocess.call(['shutdown', '-h', '1'], shell=False)
    print("Shutdown initiated")

def cancel_shutdown():
    subprocess.call(['shutdown', '-c'], shell=False)
    print("Shutdown canceled")

def main():
    initialize_gpio()
    ser = initialize_serial()

    shutdown_initiated = False
    shutdown_start_time = None
    shutdown_complete = False

    try:
        while not shutdown_complete:
            if GPIO.input(IPIN) == GPIO.LOW:
                send_serial_data(ser, "Hello from car while GPIO is HIGH!\n")
            
            if GPIO.input(IPIN) == GPIO.HIGH:
                if not shutdown_initiated:
                    shutdown_start_time = time.time()
                    initiate_shutdown()
                    shutdown_initiated = True
                else:
                    cancel_shutdown()
                    shutdown_initiated = False
            
            if shutdown_initiated:
                current_time = time.time()
                elapsed_time = current_time - shutdown_start_time
                if 5 <= elapsed_time < 60 - 5:
                    print("Sending data over serial during shutdown")
                    send_serial_data(ser, "Continuing to send data over serial\n")
                elif elapsed_time >= 60 - 5:
                    print("Stopping serial communication before shutdown completes")
                    send_serial_data(ser, "Stopping serial communication before shutdown completes\n")
                    ser.close()
                    shutdown_complete = True

            time.sleep(0.2)

    finally:
        GPIO.cleanup()
        ser.close()

if __name__ == '__main__':
    main()