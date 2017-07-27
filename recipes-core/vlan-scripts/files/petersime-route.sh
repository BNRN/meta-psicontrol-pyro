#!/bin/bash
#

#set -o xtrace

echo "Starting petersime-route.sh"

if [ "$#" -ne 11 ]; then
   echo "illegal number of parameters"
   echo 'expected something like ./petersime-route.sh "10.0.182.33" "255.255.255.0" "10.0.182.0" 24 "10.0.182.1" "10.1.20.77" "255.255.248.0" "10.1.16.0" 21 "10.1.16.1" "00:04:9f:22:ea:d4" '
   exit 1
fi

IP1=$1  #interface IP
NM1=$2  #interface netmask
NW1=$3  #interface network address
PR1=$4  #interface prefix (based on netmask)
GW1=$5  #interface gateway
 
shift 5
 
IP2=$1
NM2=$2
NW2=$3
PR2=$4
GW2=$5
MAC2=$6
 
# create eth1 interface through vlan tag 2060 on eth0

ip link add link eth0 name eth1 type vlan id 2060
ip link set dev eth1 up

 
 
 
#down the interfaces and wipe the existing config
ifconfig eth0 down
ifconfig eth1 down
 
#set ips
ifconfig eth0 up
ifconfig eth1 up
ifconfig eth0 $IP1 netmask $NM1
ifconfig eth1 $IP2 netmask $NM2 hw ether $MAC2
 
#add default gw
route add default gw $GW1 # set gw1 as system's default gw
 
#create routing table if needed

PATTERN="WAN1"
FILE="/etc/iproute2/rt_tables"

if grep -q $PATTERN $FILE
  then
   echo "rt_tables has already WAN1 routing table defined\n"
  else 
   echo "create entry WAN1 in rt_tables\n"
   echo "101 WAN1" >> /etc/iproute2/rt_tables
 fi
 
#iproute2 routing

ip route add $NW2/$PR2 dev eth1 src $IP2 table WAN1
ip route add default via $GW2 table WAN1

#delete route eth1 in main table 

ip route delete $NW2/$PR2  table main 


ip rule add from $IP2 table WAN1
ip rule add to $IP2 table WAN1

# commit those changes

ip route flush cache 
#
ifconfig eth0 up
ifconfig eth1 up
#