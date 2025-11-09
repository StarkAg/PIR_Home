#!/bin/bash

# PIR Motion Sensor - Upload Script for Arduino CLI
# Usage: ./upload.sh [port]
# Example: ./upload.sh /dev/cu.usbmodem14101

SKETCH="pir_motion_sensor.ino"
FQBN="arduino:avr:uno"

# Check if port is provided as argument
if [ -z "$1" ]; then
    echo "Usage: $0 <port>"
    echo "Example: $0 /dev/cu.usbmodem14101"
    echo ""
    echo "Available ports:"
    arduino-cli board list
    exit 1
fi

PORT=$1

echo "Compiling $SKETCH..."
arduino-cli compile --fqbn $FQBN $SKETCH

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Uploading to $PORT..."
    arduino-cli upload -p $PORT --fqbn $FQBN $SKETCH
    
    if [ $? -eq 0 ]; then
        echo "Upload successful!"
        echo "Opening serial monitor..."
        sleep 2
        arduino-cli monitor -p $PORT -c baudrate=9600
    else
        echo "Upload failed!"
        exit 1
    fi
else
    echo "Compilation failed!"
    exit 1
fi

