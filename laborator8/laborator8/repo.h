#pragma once
#include <vector> 
#include "activitate.h"
#include <iostream>
#include<unordered_map>
#include<vector>
using std::ostream;

class Repo {

private:
	std::unordered_map<string, Activitate> activitati;
	/*
	metoda privata verifica daca exista deja p in repository
	*/
	bool exist(const Activitate& act) const;
public:
	// Constructors
	Repo() = default;
	Repo(const Repo& ot) = delete;
	/*
	adauga o activitate in lista
	*/
	void add_activitate(Activitate);
	/*
	Cauta
	arunca exceptie daca nu exista activitate
	*/
	const Activitate& find(string tit, string descr) const;
	/*
	modifica o activitate
	*/
	void update_activitate(Activitate&, std::string, std::string, std::string, int);
	/*
	sterge o activitate de la o pozitie specificata
	*/
	void delete_activitate(const string& titlu);
	int getSize();
	Activitate& get_activitate(int pos);
	std::vector<Activitate> getAll() const;
	// Destructor
	~Repo();
};

class RepoListaActivitati :public Repo {

private:
	std::unordered_map<string, Activitate> lista_activitati;
public:
	void add_list_activitate(Activitate&);

	std::vector<Activitate> get_lista_activitati() const;

	void destroy_list_activity();

	int get_Size_list_activity();
};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class ActivitateRepoException {
	string msg;
public:
	ActivitateRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ActivitateRepoException& ex);
};

ostream& operator<<(ostream& out, const ActivitateRepoException& ex);