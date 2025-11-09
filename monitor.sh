#!/bin/bash

# Serial Monitor Script for PIR Motion Sensor
# This will open the serial monitor in your terminal

PORT="/dev/cu.usbserial-1130"
BAUDRATE=9600

echo "Opening serial monitor on $PORT at $BAUDRATE baud..."
echo "Press Ctrl+C to exit"
echo "----------------------------------------"
echo ""

arduino-cli monitor -p $PORT -c baudrate=$BAUDRATE

