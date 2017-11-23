#include <iostream>

#include "executor.h"

using namespace std;

int main()
{
  curl_global_init(CURL_GLOBAL_DEFAULT);

  ExchExecutor executor(
      "zrx",
      "eth",
      "Zz2Wx3pQJPFA1AmCYKpopg2OiJDj48YPh6mQfm6YsO49a7slUWNmHrvP8GDaWUHY",
      "UvKM1JS1SQSOE8dAY9wRgK1TR9zxD2waLk1iGtWixX76t1kKsIrr9nw3MhSkDGc8",
      "Zz2Wx3pQJPFA1AmCYKpopg2OiJDj48YPh6mQfm6YsO49a7slUWNmHrvP8GDaWUHY",
      "UvKM1JS1SQSOE8dAY9wRgK1TR9zxD2waLk1iGtWixX76t1kKsIrr9nw3MhSkDGc8",
      "https://api.binance.com", 
      "https://api.liqui.io");
  executor.execute();

  curl_global_cleanup();
  return 0;
}
