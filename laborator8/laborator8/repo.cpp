
#include "repo.h"
#include<algorithm>
#include <iterator>

void Repo::add_activitate(Activitate act)
{

	Activitate a(act);
	if (exist(a)) {
		throw ActivitateRepoException("Exista deja activitate titlu:" + a.get_titlu() + " descriere:" + a.get_descriere());
	}
	activitati[act.get_titlu()] = act;
}

void Repo::update_activitate(Activitate& act, std::string titlu, std::string descr, std::string tip, int durata)
{
	act.set_titlu(titlu);
	act.set_descriere(descr);
	act.set_tip(tip);
	act.set_durata(durata);
}

void Repo::delete_activitate(const string& titlu)
{
	activitati.erase(titlu);
}


Repo::~Repo()
{
}

int Repo::getSize()
{
	return (int)this->activitati.size();
}

std::vector<Activitate>Repo::getAll() const
{
	std::vector<Activitate> v;
	std::transform(activitati.begin(), activitati.end(), std::back_inserter(v), [](std::pair<string, Activitate> p) {
		return p.second;
		});
	return v;
}

Activitate& Repo::get_activitate(int pos)
{
	//auto it = activitati.find(i);
	//return it->second;

	std::unordered_map<string, Activitate>::iterator a = activitati.begin();
	for (int i = 0; i < pos; i++)
		a++;
	return a->second;

}

bool Repo::exist(const Activitate& p) const {
	try {
		find(p.get_titlu(), p.get_descriere());
		return true;
	}
	catch (ActivitateRepoException&) {
		return false;
	}
}

/*
Cauta
arunca exceptie daca nu exista activitate
*/
const Activitate& Repo::find(string tit, string descr) const {
	for (const auto& act : activitati) {
		if (act.second.get_titlu() == tit && act.second.get_descriere() == descr) {
			return act.second;
		}
	}
	//daca nu exista arunc o exceptie
	throw ActivitateRepoException("Nu exista activitate tip:" + tit + " specie:" + descr);
}

ostream& operator<<(ostream& out, const ActivitateRepoException& ex) {
	out << ex.msg;
	return out;
}
void RepoListaActivitati::add_list_activitate(Activitate& act) {
	Activitate a(act);
	lista_activitati[act.get_titlu()] = act;
}

std::vector<Activitate> RepoListaActivitati::get_lista_activitati() const
{
	std::vector<Activitate> v;
	std::transform(begin(lista_activitati), end(lista_activitati), back_inserter(v),
		[](decltype(lista_activitati)::value_type const& pair) {
			return pair.second;
		});
	return v;
}

void RepoListaActivitati::destroy_list_activity() {
	this->lista_activitati.clear();
}

int RepoListaActivitati::get_Size_list_activity()
{
	return (int)this->lista_activitati.size();
}