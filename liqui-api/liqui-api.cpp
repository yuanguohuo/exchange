#include <iostream>
#include "../utils/utils.h"
#include "liqui-api.h"

Liqui::Liqui(const char* addr, const char* akey, const char* skey) : Exchange(addr, akey, skey)
{
}

Liqui::~Liqui()
{
}


string Liqui::get_symbol(const char* coin, const char* base_coin) const
{
  return string(coin) + "_" + base_coin;
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

  double p = atof(jsonValue[symbol.c_str()]["last"].asString().c_str());

  if (p <= 0)
  {
    cout << "p=" << p << endl;
    return -4;
  }

  return p;
}

int Liqui::getPrices(const char* base_coin, int num_trades, const Trade* trades, map<string,double> & ret_map)
{
  string url(server_addr);
  url += "/api/3/ticker/";

  bool first = true;
  for(int i=0;i<num_trades;i++)
  {
    if(first)
    {
      first = false;
    }
    else
    {
      url += "-";
    }

    url += get_symbol(trades[i].coin, base_coin);
  }

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


  for(int i=0;i<num_trades;i++)
  {
    string sym = get_symbol(trades[i].coin, base_coin);
    double p = atof(jsonValue[sym.c_str()]["last"].asString().c_str());
    if(p<=0)
    {
      cout << "WARN: price " << sym << ": " << p << endl;
    }
    else
    {
      ret_map[string(trades[i].coin)] = p;
    }
  }

  return 0;
}

double Liqui::getFee(const string& symbol)
{
  map<string, double>::const_iterator itr = fee_map.find(symbol);
  if (itr != fee_map.end())
  {
    return itr->second;
  }

  cout << "didn't find fee in map, get it!" << endl;

  string url(server_addr);
  url += "/api/3/info";

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

  double f = atof(jsonValue["pairs"][symbol.c_str()]["fee"].asString().c_str());
  if(f <= 0)
  {
    return -4;
  }

  f = f/((double)100);

  fee_map[symbol] = f;

  return f;
}

int Liqui::send_order(
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
