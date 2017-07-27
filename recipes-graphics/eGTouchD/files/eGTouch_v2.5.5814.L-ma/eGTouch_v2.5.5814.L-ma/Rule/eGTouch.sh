#!/bin/sh

export DISPLAY=:0

if [ -e /var/lib/lightdm/.Xauthority ]; then # ubuntu 15.04
        export XAUTHORITY=/var/lib/lightdm/.Xauthority
elif [ -e /root/.xauth* ]; then # RHEL 6.7
        export XAUTHORITY=`ls /root/.xauth*`
elif [ -e /var/run/gdm ]; then # ubuntu 10.04
        export XAUTHORITY=`ls /var/run/gdm/*/database`
else
        export XAUTHORITY=`ls /home/*/.Xauthority`
fi

/usr/bin/eGTouchD

exit 0