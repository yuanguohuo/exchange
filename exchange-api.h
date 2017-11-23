#ifndef __EXCHANGE_API__
#define __EXCHANGE_API__

#include <string>
#include <curl/curl.h>
#include "thirdparty/jsoncpp-1.8.3/json.h" 

using namespace std;

class Exchange
{
  protected:
    string server_addr;
    CURL* curl_handle;

    int curl_perform_with_header(const string& url, const string& action, const string& post_data, const vector<string>& extra_http_header, string &str_result);
    int curl_perform(const string& url, string &str_result);
    int json_str2value(const string& jsonStr, Json::Value& jsonValue);

  public:
    static const char * SIDE_BUY;
    static const char * SIDE_SELL;

    static const char * TYPE_LIMIT;
    static const char * TYPE_MARKET;

    static const char * TIMEINFORCE_GTC;
    static const char * TIMEINFORCE_IOC;

    static const char * ORDERSTATUS_NEW;
    static const char * ORDERSTATUS_PARTIALLY_FILLED;
    static const char * ORDERSTATUS_FILLED;
    static const char * ORDERSTATUS_CANCELED;
    static const char * ORDERSTATUS_PENDING_CANCEL;
    static const char * ORDERSTATUS_REJECTED;
    static const char * ORDERSTATUS_EXPIRED;

    static size_t curl_write_cb(void* content, size_t size, size_t nmemb, string *buffer);

    Exchange(const char * addr);
    virtual ~Exchange();

    virtual string get_symbol(const char* coin1, const char* coin2) const =0;
    virtual double getPrice(const string& symbol) = 0;

    virtual int send_order(
         const string& api_key,
         const string& sec_key,
         const string& symbol,
         const char *side,
         const char *type,
         const char *timeInForce,
         double quantity,
         double price,
         long recvWindow) = 0;
};

#endif
