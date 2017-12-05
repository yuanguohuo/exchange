#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <string>
#include <curl/curl.h>

#include "trade.h"
#include "thread/thread.h"
#include "exchange-api.h"

using namespace std;

class ExchExecutor
{
  public:
    class ExchThread : public Thread
    {
      private:
        int             pipe_read_cmd;
        int             pipe_write_done;

        Exchange*       exch;

        const char*     base_coin;
        int             num_trades;
        Trade*          trades;

      public:
        map<string, double>     price_map;
        map<string, int>        trade_ret;
        map<string, int>        order_status;
        int                     trade_index;

        ExchThread(
            int          _pipe_read_cmd,
            int          _pipe_write_done,
            Exchange*    _exch,
            const char*  _base_coin,
            int          _num_trades,
            Trade*       _trades) : 
                  pipe_read_cmd(_pipe_read_cmd), 
                  pipe_write_done(_pipe_write_done), 
                  exch(_exch), 
                  base_coin(_base_coin), 
                  num_trades(_num_trades), 
                  trades(_trades)
        {
        }

        ~ExchThread()
        {
        }

        const Exchange* get_exchange() const
        {
          return exch;
        }

        void* body();
    };

  private:
    int                 num_exchanges;
    ExchThread**        threads;
    int*                pipes_write_cmd;
    int*                pipes_read_done;

    const char*         base_coin;
    int                 num_trades;
    Trade*              trades;

  public:
    ExchExecutor(
        int             _num_exchanges,
        Exchange**      _exchanges,
        const char*     _base_coin,
        int             _num_trades,
        Trade*          _trades);

    virtual ~ExchExecutor();

    void start();
    void stop();
};

#endif
