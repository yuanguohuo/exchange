#!/bin/bash

pub=Zz2Wx3pQJPFA1AmCYKpopg2OiJDj48YPh6mQfm6YsO49a7slUWNmHrvP8GDaWUHY
sec=UvKM1JS1SQSOE8dAY9wRgK1TR9zxD2waLk1iGtWixX76t1kKsIrr9nw3MhSkDGc8


curl -X GET "https://api.binance.com/api/v1/time"
#     {"serverTime":1511279346325}

curl -X GET "https://api.binance.com/api/v1/depth?symbol=LTCBTC&limit=5"   #Yuanguo: buy LTC with BTC
#     {"lastUpdateId":14795198,
#     "bids":[
#         ["0.00859200","0.23000000",[]],     #bid 0.00859200 BTC for 1 LTC, quantity=0.23000000
#         ["0.00859100","25.39000000",[]],
#         ["0.00858500","14.83000000",[]],
#         ["0.00858400","11.63000000",[]],
#         ["0.00858100","61.39000000",[]],
#     ]
#
#     "asks":[
#         ["0.00863200","4.81000000",[]],     #ask 0.00863200 BTC for 1 LTC, quantity=4.81000000
#         ["0.00863400","34.87000000",[]],
#         ["0.00863700","1.30000000",[]],
#         ["0.00863900","50.38000000",[]],
#         ["0.00864300","33.15000000",[]],
#     ]}

curl -X GET "https://api.binance.com/api/v1/aggTrades?symbol=LTCBTC&limit=10"
#    [
#        {"a":1271748,"p":"0.00862100","q":"16.22000000","f":1302991,"l":1302991,"T":1511317469546,"m":true,"M":true},
#        {"a":1271749,"p":"0.00860900","q":"0.01000000","f":1302992,"l":1302992, "T":1511317494785,"m":true,"M":true},
#        {"a":1271750,"p":"0.00862600","q":"10.06000000","f":1302993,"l":1302993,"T":1511317510350,"m":true,"M":true},
#        {"a":1271751,"p":"0.00861100","q":"1.92000000","f":1302994,"l":1302994, "T":1511317510977,"m":true,"M":true},
#        {"a":1271752,"p":"0.00860900","q":"0.51000000","f":1302995,"l":1302995, "T":1511317511499,"m":false,"M":true},
#        {"a":1271753,"p":"0.00861800","q":"8.58000000","f":1302996,"l":1302996, "T":1511317540206,"m":true,"M":true},
#        {"a":1271754,"p":"0.00861400","q":"9.20000000","f":1302997,"l":1302997, "T":1511317540264,"m":true,"M":true},
#        {"a":1271755,"p":"0.00862600","q":"2.88000000","f":1302998,"l":1302998, "T":1511317601472,"m":true,"M":true},
#        {"a":1271756,"p":"0.00862600","q":"18.54000000","f":1302999,"l":1302999,"T":1511317601517,"m":true,"M":true},
#        {"a":1271757,"p":"0.00862600","q":"0.17000000","f":1303000,"l":1303000, "T":1511317621096,"m":true,"M":true}
#    ]


curl -X GET "https://api.binance.com/api/v1/klines?symbol=LTCBTC&interval=5m&limit=10"
#[
#  open-time        open         high          low         close        volume      close-time    Quote-asset-volume num-trades  Taker buy base/quote asset volume
#[1511319000000,"0.00863100","0.00863600","0.00859300","0.00859400","125.09000000",1511319299999,   "1.07720829",        14,        "51.80000000","0.44675910",     "145751.33564939"],
#[1511319300000,"0.00863200","0.00863200","0.00858400","0.00859200","248.66000000",1511319599999,   "2.13639125",        28,        "68.75000000","0.59063564",     "145715.67919790"],
#[1511319600000,"0.00858800","0.00859800","0.00858000","0.00859800","263.16000000",1511319899999,   "2.26021778",        29,        "113.89000000","0.97809328",    "145755.41481690"],
#[1511319900000,"0.00859000","0.00863100","0.00859000","0.00860700","209.27000000",1511320199999,   "1.80014158",        18,        "126.31000000","1.08733062",    "145628.58971590"],
#[1511320200000,"0.00860200","0.00860400","0.00858100","0.00860100","159.87000000",1511320499999,   "1.37447118",        21,        "103.36000000","0.88905535",    "145628.58971590"],
#[1511320500000,"0.00859000","0.00860500","0.00858300","0.00859300","274.83000000",1511320799999,   "2.36059932",        32,        "17.91000000","0.15400381",     "145627.58971590"],
#[1511320800000,"0.00858900","0.00860400","0.00858300","0.00860400","268.59000000",1511321099999,   "2.30780248",        30,        "92.52000000","0.79540374",     "145561.38501145"],
#[1511321100000,"0.00859200","0.00861600","0.00858300","0.00860200","262.00000000",1511321399999,   "2.25362055",        36,        "136.54000000","1.17542953",    "145561.38501145"],
#[1511321400000,"0.00860600","0.00861600","0.00860000","0.00860600","251.15000000",1511321699999,   "2.16167987",        30,        "113.52000000","0.97740966",    "145608.51049350"],
#[1511321700000,"0.00860200","0.00860600","0.00857700","0.00857700","231.85000000",1511321999999,   "1.99163113",        32,        "69.70000000","0.59931486",     "145661.26909869"]
#]


curl -X GET "https://api.binance.com/api/v1/ticker/24hr?symbol=LTCBTC"
#    {
#        "priceChange":"-0.00016000",
#        "priceChangePercent":"-1.826",        Yuanguo: priceChange/prevClosePrice
#        "weightedAvgPrice":"0.00861766",
#        "prevClosePrice":"0.00876000",
#        "lastPrice":"0.00860000",
#        "lastQty":"42.26000000",
#        "bidPrice":"0.00858700",
#        "bidQty":"45.14000000",
#        "askPrice":"0.00860000",
#        "askQty":"0.71000000",
#        "openPrice":"0.00876000",
#        "highPrice":"0.00876100",
#        "lowPrice":"0.00852400",
#        "volume":"73906.90000000",
#        "quoteVolume":"636.90477924",
#        "openTime":1511236028990,
#        "closeTime":1511322428990,
#        "firstId":1295071,
#        "lastId":1303380,
#        "count":8309
#    }


curl -X GET "https://api.binance.com/api/v1/ticker/allPrices"
#    [
#        {"symbol":"ETHBTC","price":"0.04443500"},
#        {"symbol":"LTCBTC","price":"0.00860700"},
#        {"symbol":"BNBBTC","price":"0.00019599"},
#        {"symbol":"NEOBTC","price":"0.00424800"},
#        {"symbol":"123456","price":"0.00030000"},
#        ......
#    ]


curl -X GET "https://api.binance.com/api/v1/ticker/allBookTickers"
#    [
#        {"symbol":"ETHBTC","bidPrice":"0.04490100","bidQty":"5.33000000","askPrice":"0.04501800","askQty":"15.00000000"},
#        {"symbol":"LTCBTC","bidPrice":"0.00856400","bidQty":"1.00000000","askPrice":"0.00858800","askQty":"7.00000000"},
#        {"symbol":"BNBBTC","bidPrice":"0.00019301","bidQty":"90.00000000","askPrice":"0.00019389","askQty":"507.00000000"},
#        {"symbol":"NEOBTC","bidPrice":"0.00442500","bidQty":"35.89000000","askPrice":"0.00442600","askQty":"6.00000000"},
#        {"symbol":"123456","bidPrice":"0.00000000","bidQty":"0.00000000","askPrice":"0.00000000","askQty":"0.00000000"},
#        {"symbol":"QTUMETH","bidPrice":"0.03774500","bidQty":"19.99000000","askPrice":"0.03826700","askQty":"24.24000000"},
#        {"symbol":"EOSETH","bidPrice":"0.00517400","bidQty":"57.00000000","askPrice":"0.00517900","askQty":"479.52000000"},
#        {"symbol":"SNTETH","bidPrice":"0.00010901","bidQty":"34923.00000000","askPrice":"0.00010949","askQty":"4000.00000000"},
#        {"symbol":"BNTETH","bidPrice":"0.00581900","bidQty":"68.00000000","askPrice":"0.00591600","askQty":"0.90000000"},
#        ......
#    ]



function get_account()
{
    local recv_wind=$1

    local ts=`date +%s`
    ts=`expr $ts + 13`   #Yuanguo: time difference with server is 13 seconds;
    ts=${ts}000          # seconds to milli-seconds

    local queryStr="timestamp=$ts"

    if [ -n "$recv_wind" ] ; then
        queryStr="$queryStr&recvWindow=$recv_wind"
    fi

    local sig=`echo -n "$queryStr" | openssl dgst -sha256 -hmac "$sec" | sed -e 's/.*= //'`
    queryStr="$queryStr&signature=$sig"

    echo $queryStr

    curl -H "X-MBX-APIKEY: $pub" -X GET "https://api.binance.com/api/v3/account?$queryStr"
    #   {
    #       "makerCommission":10,
    #       "takerCommission":10,
    #       "buyerCommission":0,
    #       "sellerCommission":0,
    #       "canTrade":true,
    #       "canWithdraw":true,
    #       "canDeposit":true,
    #       "balances":[
    #           {"asset":"BTC","free":"0.00000000","locked":"0.00000000"},
    #           {"asset":"LTC","free":"0.00000000","locked":"0.00000000"},
    #           {"asset":"ETH","free":"0.20050000","locked":"0.00000000"},
    #           {"asset":"BNC","free":"0.00000000","locked":"0.00000000"},
    #           {"asset":"ZRX","free":"300.00000000","locked":"0.00000000"},
    #           ......
    #       ]
    #   }

}

function get_myTrades()
{
    local sym=$1
    local lim=$2
    local fromId=$3
    local recv_wind=$4

    [ -z "$sym" ] && sym=ZRXETH

    local ts=`date +%s`
    ts=`expr $ts + 13`   #Yuanguo: time difference with server is 13 seconds;
    ts=${ts}000          # seconds to milli-seconds


    local queryStr="symbol=$sym"
    [ -n "$lim" ] && queryStr="$queryStr&limit=$lim"
    [ -n "$fromId" ] && queryStr="$queryStr&fromId=$fromId"
    [ -n "$recv_wind" ] && queryStr="$queryStr&recvWindow=$recv_wind"
    queryStr="$queryStr&timestamp=$ts"

    local sig=`echo -n "$queryStr" | openssl dgst -sha256 -hmac "$sec" | sed -e 's/.*= //'`
    queryStr="$queryStr&signature=$sig"

    echo $queryStr

    curl -H "X-MBX-APIKEY: $pub" -X GET "https://api.binance.com/api/v3/myTrades?$queryStr"
}

function get_order()
{
    local symbol=$1
    local orderId=$2
    local origClientOrderId=$3
    local recvWindow=$4

    [ -z "$symbol" ] && symbol=ZRXETH

    local ts=`date +%s`
    ts=`expr $ts + 13`   #Yuanguo: time difference with server is 13 seconds;
    ts=${ts}000          # seconds to milli-seconds

    local queryStr="symbol=$symbol"

    [ -n "$orderId" ] && queryStr="$queryStr&orderId=$orderId"
    [ -n "$origClientOrderId" ] && queryStr="$queryStr&origClientOrderId=$origClientOrderId"
    [ -n "$recvWindow" ] && queryStr="$queryStr&recvWindow=$recvWindow"
    queryStr="$queryStr&timestamp=$ts"

    local sig=`echo -n "$queryStr" | openssl dgst -sha256 -hmac "$sec" | sed -e 's/.*= //'`
    queryStr="$queryStr&signature=$sig"

    echo $queryStr

    curl -H "X-MBX-APIKEY: $pub" -X GET "https://api.binance.com/api/v3/order?$queryStr"
}


get_account
get_myTrades
get_order ZRXETH 1


#ts=`date +%s`
#ts=${ts}000
#
#recvwind=50000
#
#query="symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=$recvwind&timestamp=$ts"
#
#
#sig=`echo -n "$query" | openssl dgst -sha256 -hmac "$sec" | sed -e 's/.*=//'`
#
#echo $sig
#curl -H "X-MBX-APIKEY: $pub" -X POST "https://api.binance.com/api/v3/order?$query&signature=$sig"
