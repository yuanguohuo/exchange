#include <iostream>
#include <assert.h>

#include "binance-api/binance-api.h"
#include "liqui-api/liqui-api.h"
#include "executor.h"

using namespace std;

int main(int argc, char** argv)
{

  const char* base_coin = argv[1];

  int num_trades = argc-2;
  if(num_trades%2 != 0)
  {
    cout << "Usage: " << argv[0] << " base_coin coin1 amount1 coin2 amount2 ..." << endl;
    return 1;
  }

  num_trades /= 2;
  Trade*  trades = new Trade[num_trades];
  for(int i=2; i<argc; i=i+2)
  {
    trades[(i-2)/2].coin = argv[i];

    double amount = atof(argv[i+1]);
    assert(amount>0);
    trades[(i-2)/2].amount = amount;
  }

  Exchange* binance = new Binance(
      "https://api.binance.com", 
      "Zz2Wx3pQJPFA1AmCYKpopg2OiJDj48YPh6mQfm6YsO49a7slUWNmHrvP8GDaWUHY", 
      "UvKM1JS1SQSOE8dAY9wRgK1TR9zxD2waLk1iGtWixX76t1kKsIrr9nw3MhSkDGc8");

  Exchange* liqui = new Liqui(
      "https://api.liqui.io", 
      NULL, 
      NULL);

  Exchange* exchanges[2] = {binance, liqui};


  ExchExecutor* executor = new ExchExecutor(2, exchanges, base_coin, num_trades, trades);
  executor->start();

  curl_global_cleanup();
  return 0;
}
