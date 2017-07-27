#!/bin/sh

# hold device in reset
echo 170 > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio170/direction
echo 0 > /sys/class/gpio/gpio170/value 

# perform upgrade

