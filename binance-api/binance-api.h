#ifndef __BINANCE_H__
#define __BINANCE_H__

#include <string>
#include <curl/curl.h>

#include "../exchange-api.h"

using namespace std;

class Binance : public Exchange
{
  public:
    Binance(const char * addr, CURL* curl);
    virtual ~Binance();

    int getAllPrices(map & price_map);
    double getPrice(const string symbol);
};

#endif
