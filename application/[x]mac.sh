#!/bin/bash

function Help(){
       # Display Help
    echo "mac计算"
    echo
    echo "金融相关MAC计算，from IBM"
    echo "x99:      ANSI X9.9 MAC"
    echo "x919:     [x] ANSI X9.19 MAC"
    echo "emv:      [x] EMV MAC" 
    echo "tdes:     [x] ISO 16609 TDES MAC"
    echo "HMAC:     [x] Keyed-hash MAC(HMAC)"
    echo
}

function check_digits()
{
    local count=${#1}
    if [[ "$1" =~ [0-9a-fA-F]{$count} ]]; then
        # echo "All digits."
        return 0
    else
        echo "Not all hex digits."
        echo $1
        exit
    fi
}

function check_data()
{
    local len=${#1}
    check_digits $1
    remaining=`expr $len % 2`
    if [ 1 == $remaining ]; then
        echo Data Length Not Double!
        echo $len
        exit 1
    fi
}

function x99()
{
    local len=${#1}
    remaining=`expr $len % 16`
    remaining=`expr 16 - $remaining`
    if [ 0 != $remaining ]; then
        str=`printf "%*s" $remaining 0`
        echo "${str// /0}"
        str=`printf %*s 10 a`
        echo $str
    fi
}

while getopts ":h" option; do
    case $option in
        h) # display Help
            Help
            exit;;
        \?) # Error!
            echo "Error: Invalid option"
            exit;;
   esac
done

check_data $1
x99 $1

echo $?
