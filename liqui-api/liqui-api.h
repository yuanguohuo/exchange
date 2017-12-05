#ifndef __LIQUI_H__
#define __LIQUI_H__

#include <string>
#include <curl/curl.h>

#include "../exchange-api.h"

using namespace std;

class Liqui : public Exchange
{
  private:
    map<string, double> fee_map;
  public:
    Liqui(const char* addr, const char* akey, const char* skey);
    virtual ~Liqui();

    const char* get_name() const
    {
      return "Liqui";
    }
    string get_symbol(const char* coin, const char* base_coin) const;

    double getPrice(const string& symbol);
    int getPrices(const char* base_coin, int num_trades, const Trade* trades, map<string,double> & ret_map);
    double getFee(const string& symbol);

    int send_order(
        const char* base_coin,
        const char* coin,
        const char *side,
        double quantity,
        double price,
        const char *type,          //not used
        const char *timeInForce,   //not used
        long recvWindow);          //not used
};

#endif
