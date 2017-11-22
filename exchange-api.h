#ifndef __EXCHANGE_API__
#define __EXCHANGE_API__

#include <string>
#include <curl/curl.h>
using namespace std;

class Exchange
{
  protected:
    string server_addr;
    CURL* curl_handle;

    int curl_perform_with_header(const string& url, const string& action, const string& post_data, const vector<string>& extra_http_header, string &str_result);
    int curl_perform(const string& url, string &str_result);

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

    Exchange(const char * addr, CURL* curl);
    virtual ~Exchange();

    int getAllPrices(map & price_map) = 0;
    double getPrice(const string symbol) = 0;

    int send_order(
         const char *symbol,
         const char *side,
         const char *type,
         const char *timeInForce,
         double quantity,
         double price,
         const char *newClientOrderId,
         double stopPrice,
         double icebergQty,
         long recvWindow) = 0;
};

#endif