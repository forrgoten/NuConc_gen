#include "database.h"

MYSQL* connect_to_database() 
{
  MYSQL* conn = mysql_init(NULL);

  if(conn == NULL)
  {
    fprintf(stderr, "Error occured when initializing MariaDB: %s\n", mysql_error(conn));
    return NULL;
  }

  mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, "10");

  if(mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0) == NULL) 
  {
    fprintf(stderr, "Error occured when connecting to the database: %s\n", mysql_error(conn));
    mysql_close(conn);
    return NULL;
  }

  if(mysql_set_character_set(conn, "utf8"))
  {
    fprintf(stderr, "Error occured when setting character encoding: %s\n", mysql_error(conn));
  }
  
  printf("Connected sucsessfully to MariaDB\n");
  return conn;
}

void disconnect_from_database(MYSQL* conn)
{
  if(conn != NULL)
  {
    mysql_close(conn);
    printf("Disconnected sucsessfully");
  }
}

int get_isotopes_data(MYSQL* conn, const char** isotope_names, int count, Isotope* isotopes)
{
  //char query[BUFFER_SIZE];
  //MYSQL_RES* res;
  //MYSQL_ROW row;
  int found_count = 0;

  for(int i = 0; i < count; i++)\
  {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(!stmt)
    {
      fprintf(stderr, "Error occured when initializing statement\n");
      continue;
    }
    
    const char* sql = "SELECT name, mass, density, abundance, content, fraction FROM isotopes WHERE name = ?";

    if(mysql_stmt_prepare(stmt, sql, strlen(sql))) 
    {
      fprintf(stderr, "Error occured while preparing call: %s\n", mysql_stmt_error(stmt));
      mysql_stmt_close(stmt);
      continue;
    }
    
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)isotope_names[i];
    bind[0].buffer_length = strlen(isotope_names[i]);

    if(mysql_stmt_bind_param(stmt, bind))
    {
      fprintf(stderr, "Error occured when binding parameters: %s\n", mysql_stmt_error(stmt));
      mysql_stmt_close(stmt);
      continue;
    }

    if(mysql_stmt_execute(stmt))
    {
      fprintf(stderr, "Error occured when executing call: %s\n", mysql_stmt_error(stmt));
      mysql_stmt_close(stmt);
      continue;
    }

    MYSQL_BIND result_bind[6];
    Isotope isotope;
    my_bool is_null[6];
    my_bool error[6];
    unsigned long length[6];

    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_STRING;
    result_bind[0].buffer = isotope.name;
    result_bind[0].buffer_length = MAX_NAME_LENGTH;
    result_bind[0].is_null = &is_null[0];
    result_bind[0].length = &length[0];
    result_bind[0].error = &error[0];

    result_bind[1].buffer_type = MYSQL_TYPE_INT24;
    result_bind[1].buffer = &isotope.mass;
    result_bind[1].is_null = &is_null[1];
    result_bind[1].error = &error[1];

    result_bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    result_bind[2].buffer = &isotope.density;
    result_bind[2].is_null = &is_null[2];
    result_bind[2].error = &error[2];

    result_bind[3].buffer_type = MYSQL_TYPE_DOUBLE;
    result_bind[3].buffer = &isotope.abundance;
    result_bind[3].is_null = &is_null[3];
    result_bind[3].error = &error[3];

    result_bind[4].buffer_type = MYSQL_TYPE_DOUBLE;
    result_bind[4].buffer = &isotope.content;
    result_bind[4].is_null = &is_null[4];
    result_bind[4].error = &error[4];

    result_bind[5].buffer_type = MYSQL_TYPE_DOUBLE;
    result_bind[5].buffer = &isotope.fraction;
    result_bind[5].is_null = &is_null[5];
    result_bind[5].error = &error[5];

    if(mysql_stmt_bind_result(stmt, result_bind))
    {
      fprintf(stderr, "Error occured when binding results: $s\n", mysql_stmt_error(stmt));
      mysql_stmt_close(stmt);
      continue;
    }

    if(mysql_stmt_fetch(stmt) == 0)
    {
      isotopes[found_count] = isotope;
      found_count++;
      printf("Found isotope: %s\n", isotope.name);
    }
    else
    {
      printf("Isotope %s was not found in database.\n", isotope_names[i]);
    }

    mysql_stmt_close(stmt);
  }

  return found_count;
}

int get_all_isotopes(MYSQL* conn,Isotope* isotopes, int max_count)
{
  const char* query = "SELECT name, mass, density, abundance, content, fraction FROM isotopes ORDER BY name";

  MYSQL_RES* res;
  MYSQL_ROW row;
  int count = 0;

  if(mysql_query(conn, query))
  {
    fprintf(stderr, "Error ocured when calling: %s\n", mysql_error(conn));
    return 1;
  }

  res = mysql_store_result(conn);
  if(res == NULL)
  {
    fprintf(stderr, "Error occured when fetching result\n");
    return 1;
  }

  while ((row = mysql_fetch_row(res)) && count < max_count)
  {
    strcpy(isotopes[count].name, row[0]);
    isotopes[count].mass = atoi(row[1]);
    isotopes[count].density = atof(row[2]);
    isotopes[count].abundance = atof(row[3]);
    isotopes[count].content = atof(row[4]);
    isotopes[count].fraction = atof(row[5]);
    count++;
  }

  mysql_free_result(res);
  return count;
}
