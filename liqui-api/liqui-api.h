#ifndef __LIQUI_H__
#define __LIQUI_H__

#include <string>
#include <curl/curl.h>

#include "../exchange-api.h"

using namespace std;

class Liqui : public Exchange
{
  public:
    Liqui(const char * addr);
    virtual ~Liqui();

    string get_symbol(const char* coin1, const char* coin2) const;
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
