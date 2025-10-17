#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "database.h"

void print_isotopes_data(Isotope* isotopes, int count);
double calculate_gross_mass(const Isotope* isotopes);
double calculate_nuclear_concentration(const Isotope* isotopes);
void perform_calculations(Isotope* isotopes, int count);

#define AVOGADRO_NUMBER 0.602

#endif

