#!/bin/bash

ifconfig eth0 192.168.1.100

while !(ifconfig | grep "192.168.1." > /dev/null); do 
    echo "Waiting for 192.168.1.100 - network interface might be down..."
    sleep 1
done

ping -W 1000 -c1 192.168.1.111 

cd /tmp

tftp -p -l ColorTest.txt 192.168.1.111 69
