#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
  #include <winsock2.h>
  #define CLEAR_SCREEN "cls"
#else
  #define CLEAR_SCREEN "clear"
  #include <stdio.h>
  #include <stdlib.h>
#endif

#define DB_HOST "localhost"
#define DB_USER "isotope_user"
#define DB_PASS "1234"
#define DB_NAME "isotopes_db"
#define DB_PORT 3306

#define MAX_NAME_LENGTH 50
#define MAX_ISOTOPES 100
#define BUFFER_SIZE 1024

#define SUCCESS 0
#define ERROR_DB_CONNECTION -1
#define ERROR_DB_QUERY -2 
#define ERROR_INVALID_INPUT -3

#endif
