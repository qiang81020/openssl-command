#!/bin/bash

# echo "sh gensm2.sh sm2_key_file_name"

skfile=$1.sk.pem
pkfile=$1.pk.pem

echo private key file: $1.pem
echo  public key file: $1.pk.pem

openssl ecparam -name SM2 -genkey -outform DER -out $skfile

openssl ec -in $skfile -pubout -outform DER -out $pkfile
 