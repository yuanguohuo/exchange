#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>
#include <sstream>
#include <sys/time.h>

using namespace std;

void split_string( string &s, char delim, vector <string> &result);
bool replace_string( string& str, const char *from, const char *to);
int replace_string_once( string& str, const char *from, const char *to , int offset);


string b2a_hex( char *byte_arr, int n );
time_t get_current_epoch();
unsigned long get_current_ms_epoch();

  template <class T>
inline string to_string (const T& t)
{
  stringstream ss;
  ss << t;
  return ss.str();
}

/*
inline bool file_exists (const std::string& name)
{
  return ( access( name.c_str(), F_OK ) != -1 );
}
*/

string hmac_sha256( const char *key, const char *data);
string hmac_sha512( const char *key, const char *data);
string sha256( const char *data );
void string_toupper( string &src);
string string_toupper( const char *cstr );

ssize_t safe_read(int fd, void *buf, size_t count);
ssize_t safe_write(int fd, const void *buf, size_t count);
#endif
