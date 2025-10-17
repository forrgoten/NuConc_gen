#include "database.h"
#include "calculations.h"
#include "config.h"

void print_available_isotopes(MYSQL* conn)
{
  Isotope all_isotopes[MAX_ISOTOPES];
  int count = get_all_isotopes(conn, all_isotopes, MAX_ISOTOPES);

  if(count > 0)
  {
    printf("\n=== AVAILABLE ISOTOPES IN DATABASE ===\n");
    for(int i = 0; i < count; i++)
    {
      printf("%s ", all_isotopes[i].name);
      if((i + 1) % 5 == 0) printf("\n");
    }
    printf("\n");
  }
}

void print_menu()
{
  printf("\n=== MENU ===\n");
  printf("1. Enter name of isotopes\n");
  printf("2. Show available isotopes\n");
  printf("3. Exit\n");
  printf("Awaiting input: ");
}

int main()
{
  MYSQL* conn;
  Isotope isotopes[MAX_ISOTOPES];
  int choice;
  char input[256];

  printf("=== NuCons_gen ===\n");

  conn = connect_to_database();
  if(conn == NULL)
  {
    return 1;
  }
  while(1)
  {
    print_menu();

    if(fgets(input, sizeof(input), stdin) == NULL) break;

    choice = atoi(input);

    switch (choice) 
    {
      case 1: 
        {
          printf("Enter names of isotopes separated by spaces (max: %d): ", MAX_ISOTOPES);
          if(fgets(input, sizeof(input), stdin) == NULL) break;

          const char* isotope_names[MAX_ISOTOPES];
          char* token = strtok(input, " \n");
          int isotope_count = 0;

          while(token != NULL && isotope_count < MAX_ISOTOPES)
          {
            isotope_names[isotope_count] = token;
            isotope_count++;
            token = strtok(NULL, " \n");
          }

          if(isotope_count == 0)
          {
            printf("Names of isotopes was not entered\n");
            break;
          }

          int found_count = get_isotopes_data(conn, isotope_names, isotope_count, isotopes);

          if(found_count > 0)
          {
            print_isotopes_data(isotopes, found_count);
            perform_calculations(isotopes, found_count);
          }
          else
          {
            printf("Isotopes not found\n");
          }
          break;
        }
      case 2:
        {
          print_available_isotopes(conn);
          break;
        }
      case 3:
        {
          disconnect_from_database(conn);
          printf("\nExiting...\n");
          return 0;
        }
      default:
        printf("Invalid input, try again.\n");
    }
  }
  disconnect_from_database(conn);
  return 0;
}
