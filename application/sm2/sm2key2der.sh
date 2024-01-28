#!/bin/bash


function Help(){
       # Display Help
    echo "bash ui2pem.sh FILENAME PRIVATE_KEY PUBLIC_KEY"
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

if [ $# -eq 3 ]; then
    # echo $#
    filename=$1
    sk=$2
    pk=$3
else
    Help
    exit
fi

tfile=.tempfile$RANDOM

echo "asn1=SEQUENCE:seq" > $tfile
echo "[seq]" >> $tfile
echo "int=INT:01" >> $tfile
echo "s1=SEQUENCE:seq1" >> $tfile
echo "s2=OCTWRAP,SEQUENCE:seq_sect" >> $tfile

echo "[seq1]" >> $tfile
echo "obj1=OID:sm2" >> $tfile
echo "obj2=OID:sm2" >> $tfile
echo "[seq_sect]" >> $tfile 

echo "field1=INTEGER:01"  >> $tfile
echo "private=FORMAT:HEX,OCT:$sk"  >> $tfile
echo "public=EXP:1,FORMAT:HEX,BITSTRING:04$pk"  >> $tfile

# echo $asn1conf
# echo $asn1conf > $tfile

openssl asn1parse -genconf $tfile -noout -out $filename

rm $tfile
