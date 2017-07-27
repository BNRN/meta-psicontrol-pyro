#!/bin/bash
#

echo "Starting petersime-switch.sh"
ifconfig eth0 up

#  write-mii-reg ( reg_nr, value )
#
write-mii-reg (){

  mii-reg eth0 $(($1 + 100)) $2     #  reg_nr > 100 triggers smi read/write routine  
}

# vlan table write ( bits19-16, bits15-8, bits7-0, entry_number) 
vlan_table_write_one_entry () {
    
	write-mii-reg  129 $1
	write-mii-reg  130 $2
	write-mii-reg  131 $3
	write-mii-reg  121 0x04
	write-mii-reg  122 $4
}

# vlan table init
#  
#  bit 19       valid 
#  bit 18-16    membership 
#  bit 15-12    Filter ID
#  bit 11-0     VLAN ID
#
# 23 20 19 16 15 12 11  8  7  4  3  0    bitnr
#  
#        1101  0000  1000  0000  0010         port3 and port1  vlan 2050
#        1110  0001  1000  0000  1100         port3 and port2  vlan 2060

vlan_table_write_one_entry 0x0d 0x08 0x02 0

vlan_table_write_one_entry 0x0e 0x18 0x0c 1 

# set port default vlan tag
#      port number    tag
#           1           2050
#           2           2060
#           3           2050
#

write-mii-reg 19 0x08    # port 1 vlan [11:8]
write-mii-reg 20 0x02    # port 1 vlan [7:0]

write-mii-reg 35 0x08    # port 2 vlan [11:8]
write-mii-reg 36 0x0c    # port 2 vlan [7:0]

write-mii-reg 51 0x08    # port 3 vlan [11:8]
write-mii-reg 52 0x02    # port 3 vlan [7:0]

# set tag removal
#      port 1
#      port 2

write-mii-reg 16 0x02    # port 1 tag removal
write-mii-reg 32 0x02    # port 2 tag removal

# set tag insertion
#      port 3
#
write-mii-reg 48 0x04    # port 3 tag insertion

# insert src port 2 PVID at port3 egress
#     

write-mii-reg 194 0x04    # src port2 PVID at egress port3 

# flush the dynamic mac table

write-mii-reg 2 0x20    # flush dynamic mac table

# enable the VLAN mode

write-mii-reg 5 0x80    # enable 802.1Q VLAN mode

write-mii-reg 29 0x0  #enable power on Port 1
write-mii-reg 45 0x0  #enable power on Port 2




