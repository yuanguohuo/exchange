#include <iostream>

#include "binance-api/binance-api.h"
#include "executor.h"

using namespace std;

ExchExecutor::ExchExecutor(
    const char* sym, 
    const char* akey1, 
    const char* skey1, 
    const char* akey2, 
    const char* skey2, 
    const char* addr1, 
    const char* addr2)
       : symbol(sym), api_key1(akey1), sec_key1(skey1), api_key2(akey2), sec_key2(skey2)
{
  exchange1 = new Binance(addr1);
  exchange2 = new Binance(addr2);
}

ExchExecutor::~ExchExecutor()
{
  delete exchange1;
  delete exchange2;
  exchange1 = NULL;
  exchange2 = NULL;
}

void ExchExecutor::execute()
{
  double price1 = exchange1->getPrice(symbol);
  double price2 = exchange2->getPrice(symbol);

  cout << "price1=" << price1 << endl;
  cout << "price2=" << price2 << endl;

  /*
  price1 -= 0.0002;
  cout << "bid " << price1 << endl;
  exchange1->send_order(
      api_key1,
      sec_key1,
      symbol,
      Exchange::SIDE_BUY,
      Exchange::TYPE_LIMIT,
      Exchange::TIMEINFORCE_GTC,
      100,
      price1,
      5000);

  price2 += 0.0002;
  cout << "ask " << price2 << endl;
  exchange1->send_order(
      api_key1,
      sec_key1,
      symbol,
      Exchange::SIDE_SELL,
      Exchange::TYPE_LIMIT,
      Exchange::TIMEINFORCE_GTC,
      100,
      price2,
      5000);
  */
}
