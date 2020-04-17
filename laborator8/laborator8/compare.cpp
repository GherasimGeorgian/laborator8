#include "compare.h"
bool compareByTitle(const Activitate& a, const Activitate& b)
{
	if (a.get_titlu() < b.get_titlu()) return true;
	return false;
}

bool compareByDescription(const Activitate& a, const Activitate& b)
{
	if (a.get_descriere() < b.get_descriere()) return true;
	return false;
}


bool compareByTypeAndTime(const Activitate& a, const Activitate& b)
{
	if (a.get_tip() < b.get_tip()) return true;
	if (a.get_tip() == b.get_tip() && a.get_durata() < b.get_durata()) return true;
	return false;
}