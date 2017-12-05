#!/bin/bash

skey=dc2e949d3b9f83f8fcb8d19cd160397adb95007c01fa7077a52f4eba67c5a0ef
akey=9HXTWTI0-21HLGAY6-5TDDS128-KRMEJSDF-KBTGOJ0C

postbody="nonce=`date +%s`&method=Trade&pair=zrx_eth&type=BUY&rate=0.00006793&amount=100"

length=$(echo -en ${#postbody})

sig=`echo -n "$postbody" | openssl dgst -sha512 -hmac "$skey" | sed -e 's/.*=//'`

echo $sig

curl -v                                                       \
     -H "Key: $akey"                                          \
     -H "Sign: $sig"                                          \
     -H "Content-Length: $length"                             \
     -L -X POST "https://api.liqui.io/tapi"                   \
     -d "$postbody"
