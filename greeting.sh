#!/bin/bash

HOUR=$(date +%H)
#HOUR=13

if [ $HOUR -lt 12 ]
then
    echo Guten Morgen $(whoami)
elif [ $HOUR -ge 17 ]
then
    echo Guten Abend $(whoami)
else
    echo Guten Tag $(whoami)
fi
