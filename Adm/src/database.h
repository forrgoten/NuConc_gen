#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

typedef struct {
  int id;
  char name[MAX_NAME_LENGTH];
  int mass;
  double density;
  double abundance;
  double content;
  double fraction;
} Isotope;

MYSQL* connect_to_database();
void disconnect_from_database(MYSQL* conn);
void print_db_error(MYSQL* conn);

int get_all_isotopes(MYSQL* conn, Isotope* isotopes, int max_count);
int find_isotope_by_name(MYSQL* conn, const char* name, Isotope* isotope);
int find_isotope_by_id(MYSQL* conn, int id, Isotope* isotope);

int add_isotope(MYSQL* conn, const Isotope* isotope);
int update_isotope(MYSQL* conn, const Isotope* isotope);
int delete_isotope(MYSQL* conn, int id);
int delete_isotope_by_name(MYSQL* conn, const char* name);

void print_isotope(const Isotope* isotope);
int isotope_exists(MYSQL* conn, const char* name);

#endif
