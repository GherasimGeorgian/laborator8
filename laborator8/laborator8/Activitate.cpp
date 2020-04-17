#include <string>
#include "activitate.h"
#include<iostream>
using std::to_string;
Activitate::Activitate()
{
	this->titlu = "";
	this->descriere = "";
	this->tip = "";
	this->durata = -1;
}

Activitate::Activitate(std::string titlu, std::string descriere, std::string tip, int durata)
{
	this->titlu = titlu;
	this->descriere = descriere;
	this->tip = tip;
	this->durata = durata;
}

Activitate::Activitate(const Activitate& act)
{

	this->titlu = act.titlu;
	this->descriere = act.descriere;
	this->tip = act.tip;
	this->durata = act.durata;
}

std::string Activitate::get_titlu() const
{
	return this->titlu;
}

std::string Activitate::get_descriere() const
{
	return this->descriere;
}

std::string Activitate::get_tip() const
{
	return this->tip;
}

int Activitate::get_durata() const
{
	return this->durata;
}

void Activitate::set_titlu(std::string t)
{
	this->titlu = t;
}

void Activitate::set_descriere(std::string d)
{
	this->descriere = d;
}

void Activitate::set_tip(std::string t)
{
	this->tip = t;
}

void Activitate::set_durata(int d)
{
	this->durata = d;
}

bool Activitate::operator==(const Activitate& act)
{
	if (this->titlu == act.titlu && this->descriere == act.descriere && this->tip == act.tip && this->durata == act.durata)
		return true;
	return false;
}

Activitate::~Activitate()
{
}

std::ostream& operator<<(std::ostream& os, const Activitate& act)
{
	os << act.titlu << ' ' << act.descriere << ' ' << act.tip << ' ' << act.durata << '\n';
	return os;
}

void DTO::increment()
{
	valori++;
}

void DTO::set_procent(int all)
{
	procent = (valori * 1.0 / all) * 100;
}

string DTO::get_str()
{
	string output = categorie + " " + to_string(procent) + "%\n";
	return output;
}
int DTO::get_procent() const
{
	return (int)procent;
}