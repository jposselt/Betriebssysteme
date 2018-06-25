#!/bin/bash

if [ $# -lt 2 ]
then
    echo Nicht genug Argumente
    exit 1
fi

DIV=$1
shift

PROD=$1
shift

while [ $# -gt 0 ]
do
    PROD=$((${PROD} * $1))
    shift
done

echo Produkt: $((${PROD}/${DIV}))
echo Name: $0
