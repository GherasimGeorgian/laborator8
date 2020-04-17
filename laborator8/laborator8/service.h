#pragma once
#include "repo.h"
#include "valid.h"
using std::ofstream;
class Service {
private:
	Repo& repo;
	RepoListaActivitati& repo_lista_activitati;
	ActivitateValidator& validator;
public:
	// Constructor
	Service(Repo& r, ActivitateValidator& v, RepoListaActivitati& rla) : repo{ r }, validator{ v }, repo_lista_activitati{ rla } {};

	vector<DTO> statistica();
	/*
	adauga o noua activitate in repo
	*/
	void add_elem(std::string, std::string, std::string, int);

	/*
	modifica o activitate
	cu ajutorul unei pozitii
	sunt modificate titlul, descrierea, tipul si durata
	*/
	void update(int, std::string, std::string, std::string, int);

	/*
	sterge o activitate dupa id
	*/
	void delete_elem(const string& name);


	std::vector<Activitate> afiseaza_activitati_serv();

	Activitate search_elem(int);

	/*
	filtreaza activitatile dupa descriere
	*/
	std::vector<Activitate> filterByDescription(std::string);

	/*
	filtreaza activitatile dupa tip
	*/
	std::vector<Activitate> filterByType(std::string);


	std::vector<Activitate> sortBy(bool(*compare)(const Activitate&, const Activitate&));


	Repo& getActivitati();

	void adauga_lista_activitati(std::string);

	std::vector<Activitate> afiseaza_lista_activitati_serv() const;

	void goleste_lista_activitati() const;

	void genereaza_aleator(int) const;

	void save_in_html(std::string) const;

	void save_in_cvs(std::string) const;

	int numar_oferte() const;

	double timeSum();
};