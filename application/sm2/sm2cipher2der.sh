#!/bin/bash


function Help(){
       # Display Help
    echo "  ui2pem.sh FILENAME sm2_cipher_hex_string(x|y|c|h)"
    echo "or:"
    echo "  ui2pem.sh FILENAME sm2_cipher_x sm2_cipher_y sm2_cipher_h sm2_cipher_c"
    echo "      将sm2密文字符串转换为der格式"
    echo
    echo "当参数个数为2时："
    echo "  para1:    filename          生成的文件名"
    echo "  para2:    cipher_hex_string 密文hex字符串"
    echo "当参数个数为5时："
    echo "  para1:  filename 生成的文件名"
    echo "  x:      cipher_x 密文x"
    echo "  y:      cipher_y 密文y"
    echo "  h:      cipher_h 密文h"
    echo "  c:      cipher_c 密文c"
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

if [ $# -eq 2 ]; then
    # echo $#
    filename=$1
    data=$2

    len=`expr ${#data} - 192`
    # len=`expr ${l} * 2`
    echo $len

    x=${data:0:64}
    y=${data:64:64}
    c=${data:128:$len}
    h=${data:0-64:64}

    echo $x
    echo $y
    echo $h
    echo $c
    # exit
elif [ $# -eq 5 ]; then
    # echo $#
    filename=$1
    x=$2
    y=$3
    h=$4
    c=$5
else
    Help
    exit
fi

tfile=.tempfile$RANDOM

echo "asn1=SEQUENCE:seq_sect" > $tfile
echo "[seq_sect]" >> $tfile
echo "x=INT:0x$x" >> $tfile
echo "y=INT:0x$y" >> $tfile
echo "h=FORMAT:HEX,OCT:$h" >> $tfile 
echo "c=FORMAT:HEX,OCT:$c" >> $tfile

openssl asn1parse -genconf $tfile -noout -out $filename

rm $tfile
