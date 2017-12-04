#include <iostream>
#include <assert.h>
#include <unistd.h>

#include "binance-api/binance-api.h"
#include "liqui-api/liqui-api.h"
#include "executor.h"

using namespace std;


ExchExecutor::ExchExecutor(
    int             _num_exchanges,
    Exchange**      _exchanges,
    const char*     _base_coin,
    int             _num_trades,
    Trade*          _trades) : num_exchanges(_num_exchanges), base_coin(_base_coin), num_trades(_num_trades), trades(_trades)
{
  threads = new ExchThread*[num_exchanges];
  pipes_write_cmd = new int[num_exchanges];
  pipes_read_done = new int[num_exchanges];

  for (int i=0; i<num_exchanges; ++i)
  {
    int ret;
    int pipe_cmd[2];
    int pipe_done[2];

    ret = pipe(pipe_cmd);
    assert(ret == 0);

    ret = pipe(pipe_done);
    assert(ret == 0);

    threads[i] = new ExchThread(pipe_cmd[0], pipe_done[1], _exchanges[i], base_coin, _num_trades, _trades);
    pipes_write_cmd[i] = pipe_cmd[2];
    pipes_read_done[i] = pipe_done[1];
  }
}

ExchExecutor::~ExchExecutor()
{
  for(int i=0;i<num_exchanges;++i)
  {
    threads[i]->join();
    delete threads[i];
  }
  delete[] threads;
  delete[] pipes_write_cmd;
  delete[] pipes_read_done;

  threads = NULL;
  pipes_write_cmd = NULL;
  pipes_read_done = NULL;
}

void* ExchExecutor::ExchThread::body()
{
  while(true)
  {
    char buf[1];
    ssize_t c;
    while(true)
    {
      c = read(pipe_read_cmd, buf, 1);

      if(c==0)  //EOF, terminate;
      {
        return NULL;
      }

      if(c==1) //successful read;
      {
        break;
      }

      //error
      if(errno == EINTR)  //interrupted by a signal, re-try
      {
        continue;
      }

      assert(false);
    }

    if(buf[0] == 'a')  //get prices
    {
      for(int i=0;i<num_trades;++i)
      {
        price_map[string(trades[i].coin)] = -9999;
      }

      exch->getPrices(base_coin, num_trades, trades, price_map);

      while(true)
      {
        c = write(pipe_write_done, buf, 1);
        if(c==1)  //success write;
        {
          break;
        }

        //error
        if(errno == EINTR) //interrupted by a signal, re-try
        {
          continue;
        }

        assert(false);
      }
    }
    else if(buf[0] == 'b')
    {
      assert(false);
    }
  }
}

void ExchExecutor::start()
{
  for(int i=0;i<num_exchanges;++i)
  {
    threads[i]->create(threads[i]->get_exchange()->get_name());
  }

  while(true)
  {
    ssize_t c;
    for(int i=0;i<num_exchanges;++i)
    {
      while(true)
      {
        c = write(pipes_write_cmd[i], "a", 1);
        if(c==1) //success write;
        {
          break;
        }

        if(errno == EINTR) //interrupted by a signal, re-try
        {
          continue;
        }

        assert(false);
      }
    }

    for(int i=0;i<num_exchanges;++i)
    {
      while(true)
      {
        char buf[1];
        c = read(pipes_read_done[i], buf, 1);
        if(c==1) //success read;
        {
          break;
        }

        if(errno == EINTR) //interrupted by a signal, re-try
        {
          continue;
        }

        assert(false);
      }
    }

    for(int i=0; i<num_trades; i++)
    {
      cout << trades[i].coin;

      for(int j=0;j<num_exchanges;++j)
      {
        cout << "\t" << threads[j]->price_map[string(trades[i].coin)];
      }
    }
  }


  /*
  double price1 = exchange1->getPrice(exchange1->get_symbol(coin1, coin2));
  double price2 = exchange2->getPrice(exchange2->get_symbol(coin1, coin2));

  cout << endl << endl << "--------------------------------------------" << endl;

  double value1 = amount * price1; 
  double value2 = amount * price2; 
  double gap = value1>value2?(value1-value2):(value2-value1);

  double f1 = exchange1->getFee(exchange1->get_symbol(coin1, coin2));
  double f2 = exchange2->getFee(exchange2->get_symbol(coin1, coin2));

  double fee1 = value1 * f1; 
  double fee2 = value2 * f2;
  double total_fee = fee1 + fee2;

  double net_gap = gap - total_fee;

  cout << "amount     = " << amount << endl;
  cout << "price1     = " << price1 << endl;
  cout << "price2     = " << price2 << endl;
  cout << "value1     = " << value1 << endl;
  cout << "value2     = " << value2 << endl;
  cout << "gap        = " << gap << " (abs(" << value1 << "-" << value2 << "))" << endl;
  cout << "fee1       = " << fee1 << " (" << value1 << "*" << f1 << ")" << endl;
  cout << "fee2       = " << fee2 << " (" << value2 << "*" << f2 << ")" << endl;
  cout << "total_fee  = " << total_fee << endl;
  cout << "net_gap    = " << net_gap << endl;
  
  if (net_gap > 0)
  {
    cout << endl << "Yes!!! net_gap=" << net_gap << endl;
    sleep(30);
  }
  else
  {
    cout << ".";
  }


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

void ExchExecutor::stop()
{
  for(int i=0;i<num_exchanges;++i)
  {
    threads[i]->join();
  }
}
