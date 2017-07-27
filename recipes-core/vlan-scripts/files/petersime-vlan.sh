#!/bin/bash
#

#set -o xtrace

echo "Starting petersime-vlan.sh"

./petersime-switch.sh

./petersime-route.sh "192.168.0.2" "255.255.255.0" "192.168.0.0" 24 "192.168.0.1" "10.0.182.33" "255.255.255.0" "10.0.182.0" 24 "10.0.182.1" "00:04:9f:22:ea:d4"

