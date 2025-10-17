#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"


#define MAX_ISOTOPES 20
#define MAX_NAME_LENGTH 50
#define BUFFER_SIZE 1024

typedef struct 
{
  char name[MAX_NAME_LENGTH];
  int mass;
  double density;
  double abundance;
  double content;
  double fraction;
} Isotope;

MYSQL* connect_to_database();
void disconnect_from_database(MYSQL* conn);
int get_isotopes_data(MYSQL* conn, const char** isotopes_name, int count, Isotope* isotopes);
int get_all_isotopes(MYSQL* conn, Isotope* isotopes, int max_count);

#endif
