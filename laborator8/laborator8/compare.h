#pragma once
#include "activitate.h"

// compara doua activitati dupa tilu
bool compareByTitle(const Activitate& a, const Activitate& b);

// comapara doua activitati dupa descriere
bool compareByDescription(const Activitate& a, const Activitate& b);

// compara dupa tip si durata
bool compareByTypeAndTime(const Activitate& a, const Activitate& b);