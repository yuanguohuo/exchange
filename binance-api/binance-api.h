#ifndef __BINANCE_H__
#define __BINANCE_H__

#include <string>
#include <curl/curl.h>

#include "../exchange-api.h"

using namespace std;

class Binance : public Exchange
{
  public:
    Binance(const char* addr, const char* akey, const char* skey);
    virtual ~Binance();

    const char* get_name() const
    {
      return "Binance";
    }

    string get_symbol(const char* coin, const char* base_coin) const;

    double getPrice(const string& symbol);
    int getPrices(const char* base_coin, int num_trades, const Trade* trades, map<string,double> & ret_map);
    double getFee(const string& symbol);
    int send_order(
         const string& symbol,
         const char *side,
         const char *type,
         const char *timeInForce,
         double quantity,
         double price,
         long recvWindow);

  private:
    int getAllPrices(map<string,double>& price_map);
};

#endif
