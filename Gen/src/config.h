#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
  #include <winsock2.h>
  #define CLEAR_SCREEN "cls"
  #define MYSQL_LIB "libmariadb.dll"
#else
  #define CLEAR_SCREEN "clear"
  #define MYSQL_LIB "libmariadb.so"
#endif

#define DB_HOST "localhost"
#define DB_USER "isotope_user"
#define DB_PASS "1234"
#define DB_NAME "isotopes_db"
#define DB_PORT 3306

#endif
