
#include <string>
#include "service.h"
#include<algorithm>
#include <map>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <vector>
#include <fstream>
#include <iterator>
#include <numeric>
using std::map;

int  Service::numar_oferte() const {
	return repo_lista_activitati.get_Size_list_activity();
}

void Service::adauga_lista_activitati(std::string titlu) {
	for (auto& act : repo.getAll()) {
		if (act.get_titlu() == titlu)
			this->repo_lista_activitati.add_list_activitate(act);
	}
}

void Service::add_elem(std::string titlu, std::string descr, std::string tip, int durata)
{
	Activitate act(titlu, descr, tip, durata);
	validator.validate(act);
	this->repo.add_activitate(act);
}

void Service::update(int pos, std::string titlu, std::string descr, std::string tip, int durata)
{
	if (pos<0 || pos>repo.getSize())
		throw std::exception("Pozitie incorecta!!! '");
	Activitate act(titlu, descr, tip, durata);
	validator.validate(act);
	this->repo.update_activitate(this->repo.get_activitate(pos), titlu, descr, tip, durata);
}

void Service::delete_elem(const string& name)
{
	if (name == "")
		throw std::exception("Pozitie incorecta!!! '");
	this->repo.delete_activitate(name);
}

Activitate Service::search_elem(int pos)
{
	if (pos<0 || pos>repo.getSize())
		throw std::exception("Pozitie incorecta!!! '");
	return this->repo.get_activitate(pos);
}

std::vector<Activitate> Service::filterByDescription(std::string descr)
{
	std::vector<Activitate> activitati = repo.getAll();
	std::vector<Activitate> v;
	std::copy_if(activitati.begin(), activitati.end(), std::back_inserter(v), [&descr](const Activitate& c) { return c.get_descriere().find(descr) != std::string::npos; });

	//for (int i = 0; i < (int)this->repo.getSize(); i++)
	//	if ((this->repo.get_activitate(i).get_descriere()).find(descr) != std::string::npos)
	//		v.push_back(this->repo.get_activitate(i));
	return v;
}


std::vector<Activitate> Service::filterByType(std::string tip)
{

	std::vector<Activitate> activitati = repo.getAll();
	std::vector<Activitate> v;
	std::copy_if(activitati.begin(), activitati.end(), std::back_inserter(v), [&tip](const Activitate& c) { return c.get_tip().find(tip) != std::string::npos; });
	return v;

	//std::vector<Activitate> v;
	//for (int i = 0; i < (int)this->repo.getSize(); i++)
	//	if (this->repo.get_activitate(i).get_tip() == tip)
		//	v.push_back(this->repo.get_activitate(i));

}

std::vector<Activitate> Service::sortBy(bool(*compare)(const Activitate&, const Activitate&))
{
	std::vector<Activitate> v = this->repo.getAll();
	//v.sort(compare);
	sort(v.begin(), v.end(), compare);

	return v;

}

Repo& Service::getActivitati()
{
	return this->repo;
}
std::vector<Activitate> Service::afiseaza_activitati_serv()
{
	auto activitati = repo.getAll();
	return activitati;
}
std::vector<Activitate> Service::afiseaza_lista_activitati_serv() const {
	auto lista_activitati = repo_lista_activitati.get_lista_activitati();
	return lista_activitati;
}

void Service::goleste_lista_activitati() const {
	repo_lista_activitati.destroy_list_activity();
}
void Service::genereaza_aleator(int nr_activitati) const {

	auto activitati = repo.getAll();
	//std::mt19937 mt{ std::random_device{}() };
	//std::uniform_int_distribution<> dist(0, activitati.size() - 1);
	//int rndNr = dist(mt);// numar aleator intre [0,size-1]
	vector<Activitate> lista_activitati;
	for (auto activitate : activitati)
	{
		lista_activitati.push_back(activitate);
	}
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(lista_activitati.begin(), lista_activitati.end(), std::default_random_engine((int)seed)); //amesteca vectorul lista_activitati


	for (int i = 0; i < nr_activitati; i++)
	{
		this->repo_lista_activitati.add_list_activitate(lista_activitati[i]);
	}
}

void Service::save_in_html(string nume_fisier) const {
	ofstream myfile;
	myfile.open("C:\\Users\\Geo\\Desktop\\OOP\\aplicatielap78\\" + nume_fisier + ".html");
	myfile << "<!DOCTYPE html><html><head></head><body>"; //starting html

	auto lista_activitati = repo_lista_activitati.get_lista_activitati();


	for (int i = 0; i < (int)lista_activitati.size(); i++)
		myfile << "<p><span style='font-weight: bold'>" << lista_activitati[i] << "</span></p>";

	//ending html
	myfile << "</body></html>";
	myfile.close();
}

void Service::save_in_cvs(string nume_fisier) const {
	std::ofstream myfile;
	myfile.open("C:\\Users\\Geo\\Desktop\\OOP\\aplicatielap78\\" + nume_fisier + ".csv");
	auto lista_activitati = repo_lista_activitati.get_lista_activitati();

	for (int i = 0; i < (int)lista_activitati.size(); i++)
		myfile << lista_activitati[i];
	myfile.close();
}


vector<DTO> Service::statistica()
{
	auto activitati = repo.getAll();


	int numar_activitati = repo.getSize();


	map<string, DTO> statistica;

	for (auto activitate : activitati) {
		if (statistica.find(activitate.get_titlu()) == statistica.end()) {
			DTO nou{ activitate.get_titlu() };
			statistica.insert({ activitate.get_titlu(), nou });
		}
		else {
			DTO aux = statistica[activitate.get_titlu()];
			aux.increment();
			statistica[activitate.get_titlu()] = aux;
		}

	}


	map<string, DTO>::iterator it = statistica.begin();

	vector <DTO> output;

	while (it != statistica.end()) {
		it->second.set_procent(numar_activitati);
		output.push_back(it->second);
		it++;
	}

	return output;
}

double Service::timeSum() {
	vector<Activitate> all = repo.getAll();
	double sum = 0;
	sum = std::accumulate(all.begin(), all.end(), static_cast<double>(0.0), [](double _sum, const Activitate& med) {
		return _sum + med.get_durata();
		});
	return sum;
}