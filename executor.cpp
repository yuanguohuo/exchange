#include <iostream>

#include "binance-api/binance-api.h"
#include "liqui-api/liqui-api.h"
#include "executor.h"

using namespace std;

ExchExecutor::ExchExecutor(
    const double a,
    const char* c1, 
    const char* c2, 
    const char* akey1, 
    const char* skey1, 
    const char* akey2, 
    const char* skey2, 
    const char* addr1, 
    const char* addr2)
       : amount(a), coin1(c1), coin2(c2), api_key1(akey1), sec_key1(skey1), api_key2(akey2), sec_key2(skey2)
{
  exchange1 = new Binance(addr1);
  exchange2 = new Liqui(addr2);
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
  double price1 = exchange1->getPrice(exchange1->get_symbol(coin1, coin2));
  double price2 = exchange2->getPrice(exchange2->get_symbol(coin1, coin2));

  cerr << endl << endl << "--------------------------------------------" << endl;

  double value1 = amount * price1; 
  double value2 = amount * price2; 
  double gap = value1>value2?(value1-value2):(value2-value1);

  double f1 = exchange1->getFee(exchange1->get_symbol(coin1, coin2));
  double f2 = exchange2->getFee(exchange2->get_symbol(coin1, coin2));

  double fee1 = value1 * f1; 
  double fee2 = value2 * f2;
  double total_fee = fee1 + fee2;

  double net_gap = gap - total_fee;

  cerr << "amount     = " << amount << endl;
  cerr << "price1     = " << price1 << endl;
  cerr << "price2     = " << price2 << endl;
  cerr << "value1     = " << value1 << endl;
  cerr << "value2     = " << value2 << endl;
  cerr << "gap        = " << gap << " (abs(" << value1 << "-" << value2 << "))" << endl;
  cerr << "fee1       = " << fee1 << " (" << value1 << "*" << f1 << ")" << endl;
  cerr << "fee2       = " << fee2 << " (" << value2 << "*" << f2 << ")" << endl;
  cerr << "total_fee  = " << total_fee << endl;
  cerr << "net_gap    = " << net_gap << endl;
  
  if (net_gap > 0)
  {
    cout << "Yes!!! net_gap=" << net_gap << endl;
  }
  else
  {
    cout << ".";
  }

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
