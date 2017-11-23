#ifndef __BINANCE_H__
#define __BINANCE_H__

#include <string>
#include <curl/curl.h>

#include "../exchange-api.h"

using namespace std;

class Binance : public Exchange
{
  public:
    Binance(const char * addr);
    virtual ~Binance();

    int getAllPrices(map<string,double>& price_map);
    double getPrice(const string& symbol);
    int send_order(
         const string& api_key,
         const string& sec_key,
         const string& symbol,
         const char *side,
         const char *type,
         const char *timeInForce,
         double quantity,
         double price,
         long recvWindow);
};

#endif
