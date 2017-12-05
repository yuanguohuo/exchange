#include <iostream>
#include <assert.h>

#include "../utils/utils.h"
#include "binance-api.h"

Binance::Binance(const char* addr, const char* akey, const char* skey) : Exchange(addr, akey, skey)
{
}

Binance::~Binance()
{
}

int Binance::getAllPrices(map<string,double>& price_map)
{
  string url(server_addr);
  url += "/api/v1/ticker/allPrices";

  string str_result;
  if(curl_perform(url, str_result))
  {
    return 1;
  }

  if(str_result.size() <= 0)
  {
    return 2;
  }

  Json::Value jsonValue;
  if(json_str2value(str_result, jsonValue))
  {
    return 3;
  }

	for (int i=0; i<jsonValue.size(); i++)
  {
    price_map[jsonValue[i]["symbol"].asString()] = atof(jsonValue[i]["price"].asString().c_str());
  }

  return 0;
}

string Binance::get_symbol(const char* coin, const char* base_coin) const
{
  return string_toupper(coin) + string_toupper(base_coin);
}

double Binance::getPrice(const string& symbol)
{
  map<string,double> price_map;
  if(getAllPrices(price_map))
  {
    return -1;
  }

  map<string,double>::iterator itr = price_map.find(symbol);
  if(itr == price_map.end())
  {
    return -2;
  }

  return itr->second;
}

int Binance::getPrices(const char* base_coin, int num_trades, const Trade* trades, map<string,double> & ret_map)
{
  map<string,double> price_map;
  if(getAllPrices(price_map))
  {
    return 1;
  }

  for(int i=0; i<num_trades; ++i)
  {
    map<string,double>::iterator itr = price_map.find(get_symbol(trades[i].coin, base_coin));
    if(itr == price_map.end())
    {
      assert(false);
    }

    ret_map[string(trades[i].coin)] = itr->second;
  }
  return 0;
}

double Binance::getFee(const string& symbol)
{
  return 0.0025;
}

int Binance::send_order(
    const char* base_coin,
    const char* coin,
    const char *side,
    double quantity,
    double price,
    const char *type,
    const char *timeInForce,
    long recvWindow)
{
  string url(server_addr);
  url += "/api/v3/order";

  string action = "POST";

  string post_data("symbol=");
  post_data.append(get_symbol(coin, base_coin));

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

  string signature = hmac_sha256(sec_key, post_data.c_str());
  post_data.append("&signature=");
  post_data.append(signature);

  vector <string> extra_http_header;
  string header_chunk("X-MBX-APIKEY: ");
  header_chunk.append(api_key);
  extra_http_header.push_back(header_chunk);

  cout << "url: " << url <<endl;
  cout << "action: " << action <<endl;
  cout << "post_data: " << post_data <<endl;

  //string str_result;
  //if(curl_perform_with_header(url, action, post_data, extra_http_header, str_result))
  //{
  //  return 1;
  //}

  //cout << "str_result: " << str_result <<endl;

  //if (str_result.size() <= 0)
  //{
  //  return 2;
  //}

  //Json::Value jsonValue;
  //if(json_str2value(str_result, jsonValue))
  //{
  //  return 3;
  //}

  return 0;
}
