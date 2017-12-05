#!/bin/bash


params="nonce=2&method=Trade&pair=zrx_eth&type=buy&rate=0.00002&amount=100"

sig=`echo -n "$params" | openssl dgst -sha256 -hmac "$sec" | sed -e 's/.*=//'`

echo $sig


echo "https://api.liqui.io/tapi?$params"

curl \
    -H "Key: 1W4ANVH1-8JQ1DVNF-ZX4TA6L6-3JZD4AP1-Z15HZH39"   \
    -H "Sign: $sign"                                         \
    -X "POST"                                                \
    "https://api.liqui.io/tapi?$params"



echo $?
