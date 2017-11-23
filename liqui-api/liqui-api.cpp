#include <iostream>
#include "../utils/utils.h"
#include "liqui-api.h"

Liqui::Liqui(const char * addr) : Exchange(addr)
{
}

Liqui::~Liqui()
{
}


string Liqui::get_symbol(const char* coin1, const char* coin2) const
{
  return string(coin1) + "_" + coin2;
}

double Liqui::getPrice(const string& symbol)
{
  string url(server_addr);
  url += "/api/3/ticker/";
  url += symbol;

  string str_result;
  if(curl_perform(url, str_result))
  {
    return -1;
  }

  if(str_result.size() <= 0)
  {
    return -2;
  }

  Json::Value jsonValue;
  if(json_str2value(str_result, jsonValue))
  {
    return -3;
  }

  cout <<  str_result << endl;
  cout << "--" << jsonValue[symbol.c_str()]["buy"].asString() << endl;
  cout << "--" << jsonValue[symbol.c_str()]["sell"].asString() << endl;
  cout << "--" << jsonValue[symbol.c_str()]["last"].asString() << endl;

  double buy = atof(jsonValue[symbol.c_str()]["buy"].asString().c_str());
  double sell = atof(jsonValue[symbol.c_str()]["sell"].asString().c_str());
  cout << "avg: " <<  (buy + sell)/2 << endl;

  double p = atof(jsonValue[symbol.c_str()]["last"].asString().c_str());

  if (p <= 0)
  {
    cout << "p=" << p << endl;
    return -4;
  }

  return p;
}

int Liqui::send_order(
    const string& api_key,
    const string& sec_key,
    const string& symbol,
    const char *side,
    const char *type,
    const char *timeInForce,
    double quantity,
    double price,
    long recvWindow)
{
  string url(server_addr);
  url += "/api/v3/order";

  string action = "POST";

  string post_data("symbol=");
  post_data.append(symbol);

  post_data.append("&side=");
  post_data.append( side );

  post_data.append("&type=");
  post_data.append(type);

  post_data.append("&timeInForce=");
  post_data.append(timeInForce);

  post_data.append("&quantity=");
  post_data.append(to_string(quantity));

  post_data.append("&price=");
  post_data.append(to_string(price));

  if (recvWindow > 0)
  {
    post_data.append("&recvWindow=");
    post_data.append(to_string(recvWindow));
  }

  post_data.append("&timestamp=");
  post_data.append(to_string(get_current_ms_epoch()));

  string signature = hmac_sha256(sec_key.c_str(), post_data.c_str());
  post_data.append("&signature=");
  post_data.append(signature);

  vector <string> extra_http_header;
  string header_chunk("X-MBX-APIKEY: ");
  header_chunk.append(api_key);
  extra_http_header.push_back(header_chunk);

  cout << "url: " << url <<endl;
  cout << "action: " << action <<endl;
  cout << "post_data: " << post_data <<endl;

  string str_result;
  if(curl_perform_with_header(url, action, post_data, extra_http_header, str_result))
  {
    return 1;
  }

  cout << "str_result: " << str_result <<endl;

  if (str_result.size() <= 0)
  {
    return 2;
  }

  Json::Value jsonValue;
  if(json_str2value(str_result, jsonValue))
  {
    return 3;
  }

  return 0;
}
