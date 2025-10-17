#include "calculations.h"
#include <math.h>

void print_isotopes_data(Isotope* isotopes, int count)
{
  printf("\n=== ISOTOPES DATA ===\n");
  for(int i = 0; i < count; i++)
  {
    printf("Name: %s\n", isotopes[i].name);
    printf("Atomic mass: %d\n", isotopes[i].mass);
    printf("Density: %.6f\n", isotopes[i].density);
    printf("Abundance: %.6f\n", isotopes[i].abundance);
    printf("Content: %.6f\n", isotopes[i].content);
    printf("Fraction: %.6f\n", isotopes[i].fraction);
    printf("------------------------\n");
  }
}

double calculate_gross_mass(const Isotope* isotopes)
{
  if(isotopes == NULL)
  {
    return 0.0;
  }
  double gross_mass = (double)isotopes->mass * isotopes->abundance * isotopes->content * isotopes->fraction;
  return gross_mass;
}

double calculate_nuclear_concentration(const Isotope* isotopes)
{
  if(isotopes == NULL)
  {
    return 0.0;
  }
  double total_concentration = (isotopes->density * AVOGADRO_NUMBER) / (double)isotopes->mass;

  double nuclear_concentration = total_concentration * isotopes->abundance * isotopes->content * isotopes->fraction;

  return nuclear_concentration;
}

void perform_calculations(Isotope* isotopes, int count)
{
  printf("\n=== RESULTS OF CALCULATION ===\n");

  for(int i =0; i < count; i++)
  {
    printf("Name: %s\n", isotopes[i].name);
    double gross_mass = calculate_gross_mass(&isotopes[i]);
    printf("Gross mass: %.6e\n", gross_mass);
    double nuclear_concentration = calculate_nuclear_concentration(&isotopes[i]);
    printf("Nucear concentration: %.6e\n", nuclear_concentration);
  }
}



