#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <string>
#include <curl/curl.h>

#include "exchange-api.h"

using namespace std;

class ExchExecutor
{
  private:
    const char*         coin1;
    const char*         coin2;

    Exchange*     exchange1;
    string        api_key1;
    string        sec_key1;

    Exchange*     exchange2;
    string        api_key2;
    string        sec_key2;

  public:
    ExchExecutor(
        const char* c1,
        const char* c2,
        const char* akey1, 
        const char* skey1, 
        const char* akey2, 
        const char* skey2, 
        const char* addr1, 
        const char* addr2);
    virtual ~ExchExecutor();

    void execute();
};

#endif
