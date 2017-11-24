#include <iostream>

#include "executor.h"

using namespace std;

int main(int argc, char** argv)
{
  cout << argv[0] << endl;
  if(argc != 4)
  {
    cout << "Usage: " << argv[0] << " amount coin1 coin2" << endl;
    return 1;
  }

  double amount = atof(argv[1]);
  if(amount<=0)
  {
    cout << "Error: amount must be positive." << endl;
    cout << "Usage: " << argv[0] << " amount coin1 coin2" << endl;
    return 2;
  }
  
  curl_global_init(CURL_GLOBAL_DEFAULT);

  ExchExecutor executor(
      amount,
      argv[2],
      argv[3],
      "Zz2Wx3pQJPFA1AmCYKpopg2OiJDj48YPh6mQfm6YsO49a7slUWNmHrvP8GDaWUHY",
      "UvKM1JS1SQSOE8dAY9wRgK1TR9zxD2waLk1iGtWixX76t1kKsIrr9nw3MhSkDGc8",
      "Zz2Wx3pQJPFA1AmCYKpopg2OiJDj48YPh6mQfm6YsO49a7slUWNmHrvP8GDaWUHY",
      "UvKM1JS1SQSOE8dAY9wRgK1TR9zxD2waLk1iGtWixX76t1kKsIrr9nw3MhSkDGc8",
      "https://api.binance.com", 
      "https://api.liqui.io");

  while(1)
    executor.execute();

  curl_global_cleanup();
  return 0;
}
