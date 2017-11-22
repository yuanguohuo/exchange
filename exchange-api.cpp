#include <assert.h>
#include "exchange-api.h"

const char * Exchange::SIDE_BUY                        = "BUY";
const char * Exchange::SIDE_SELL                       = "SELL";

const char * Exchange::TYPE_LIMIT                      = "LIMIT";
const char * Exchange::TYPE_MARKET                     = "MARKET";

const char * Exchange::TIMEINFORCE_GTC                 = "GTC";
const char * Exchange::TIMEINFORCE_IOC                 = "IOC";

const char * Exchange::ORDERSTATUS_NEW                 = "NEW";
const char * Exchange::ORDERSTATUS_PARTIALLY_FILLED    = "PARTIALLY_FILLED";
const char * Exchange::ORDERSTATUS_FILLED              = "FILLED";
const char * Exchange::ORDERSTATUS_CANCELED            = "CANCELED";
const char * Exchange::ORDERSTATUS_PENDING_CANCEL      = "PENDING_CANCEL";
const char * Exchange::ORDERSTATUS_REJECTED            = "REJECTED";
const char * Exchange::ORDERSTATUS_EXPIRED             = "EXPIRED";

Exchange::Exchange(const char * addr, CURL* curl) : server_addr(addr), curl_handle(curl)
{
}

Exchange::~Exchange()
{
}

int Exchange::curl_perform_with_header(const string& url, const string& action, const string& post_data, const vector<string>& extra_http_header, string &str_result)
{
  assert(curl_handle);
  curl_easy_reset(curl_handle);

  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str() );
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_write_cb);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &str_result);
  curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, false);

  if (extra_http_header.size() > 0)
  {
    struct curl_slist *chunk = NULL;
    for (int i=0; i<extra_http_header.size(); i++)
    {
      chunk = curl_slist_append(chunk, extra_http_header[i].c_str() );
    }
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, chunk);
  }

  if ( post_data.size() > 0 || action == "POST" || action == "PUT" || action == "DELETE" )
  {
    if (action == "PUT" || action == "DELETE")
    {
      curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, action.c_str());
    }
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post_data.c_str());
  }

  CURLcode res = curl_easy_perform(curl_handle);

  if ( res != CURLE_OK )
  {
    return 1;
  } 	
}

int Exchange::curl_perform(const string& url, string &str_result)
{
  vector <string> headers;
  string action = "GET";
  string post_data = "";
  return curl_perform_with_header(url, action, post_data, headers, str_result);
}

size_t Exchange::curl_write_cb(void* content, size_t size, size_t nmemb, string *buffer)
{
  size_t newLength = size*nmemb;
  size_t oldLength = buffer->size();

  try
  {
    buffer->resize(oldLength + newLength);
  }
  catch(std::bad_alloc &e)
  {
    //TODO
    assert(false);
    return 0;
  }

  std::copy((char*)content,(char*)content + newLength,buffer->begin()+oldLength);
  return size*nmemb;
}
