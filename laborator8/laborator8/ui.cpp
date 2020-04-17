
#include "compare.h"
#include<sstream>
#include "ui.h"


void UI::run()
{
	while (true) {
		this->printCommands();
		int cmd = 0;
		try {
			std::cout << "\nInsert command's number: ";
			std::cin >> cmd;
		}
		catch (int) {
			std::cout << "Invalid command";
		}
		if (!cmd) break;
		else
			switch (cmd) {
			case -1: system("CLS"); break;
			case 1: this->add(); break;
			case 2: this->print(); break;
			case 3: this->update(); break;
			case 4: this->del(); break;
			case 5: this->search(); break;
			case 6: this->filterByDescription(); break;
			case 7: this->filterByType(); break;
			case 8: this->sortByTitle(); break;
			case 9: this->sortByDescription(); break;
			case 10: this->sortByTypeAndTime(); break;
			case 11: this->ui_statistica(); break;
			case 12: this->add_activity_list(); break;
			case 13: this->show_add_activity_list(); break;
			case 14: this->clear_list_activities(); break;
			case 15: this->random_add_list_activity(); break;
			case 16: this->save_in_file(); break;
			case 17: this->show_sum_of_time(); break;
			default: break;
			}
		this->show_number_of_list_activity();
	}
}

UI::~UI() {}

void UI::show_sum_of_time() {
	std::cout << "\nSuma duratei tuturor activitatilor este: " << srv.timeSum();
}

void UI::show_number_of_list_activity() {
	int numar_oferte = this->srv.numar_oferte();
	std::cout << "Numarul ofertelor din cos este: " << numar_oferte << std::endl;

}

void UI::save_in_file() {
	std::cout << "1.Write in HTML\n";
	std::cout << "2.Write in CVS\n";
	std::cout << "3.Back\n";
	int option;
	std::cin >> option;

	if (option == 1)
	{
		std::string nume_fisier;
		std::cout << "Titlu: "; std::cin.ignore();
		getline(std::cin, nume_fisier);
		this->srv.save_in_html(nume_fisier);
	}
	if (option == 2)
	{
		std::string nume_fisier;
		std::cout << "Titlu: "; std::cin.ignore();
		getline(std::cin, nume_fisier);
		this->srv.save_in_cvs(nume_fisier);
	}


}
void UI::random_add_list_activity() {
	int numar_activitati;
	std::cout << "Introdu numarul de activitati pe care vrei sa le generezi aleator: "; std::cin >> numar_activitati;
	this->srv.genereaza_aleator(numar_activitati);
}
void UI::show_add_activity_list()
{
	auto v = srv.afiseaza_lista_activitati_serv();
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}
void UI::add_activity_list() {
	std::string titlu;
	std::cout << "Titlu: "; std::cin.ignore();
	getline(std::cin, titlu);
	this->srv.adauga_lista_activitati(titlu);
}
void UI::clear_list_activities() {
	this->srv.goleste_lista_activitati();
}

void UI::ui_statistica()
{
	std::cout << "Statistica:\n";
	vector<DTO> vectoras = this->srv.statistica();
	for (auto val : vectoras) {
		std::cout << val.get_str();
	}

}

void UI::add()
{
	try {
		std::string titlu, descriere, tip;
		int durata;
		std::cout << "Titlu: "; std::cin.ignore();
		getline(std::cin, titlu);
		std::cout << "Descriere: "; //std::cin.ignore();
		getline(std::cin, descriere);
		std::cout << "Tip: "; //std::cin.ignore();
		getline(std::cin, tip);
		std::cout << "Durata: "; std::cin >> durata;
		this->srv.add_elem(titlu, descriere, tip, durata);
	}
	catch (const ValidateException& ex) {
		std::cout << ex << '\n';
	}
	catch (const ActivitateRepoException& ex) {
		std::cout << ex << '\n';
	}
}

void UI::print()
{
	auto v = srv.afiseaza_activitati_serv();
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}

void UI::update()
{
	try {
		int durata, pos;
		std::cout << "ID: "; std::cin >> pos;
		std::string titlu, descriere, tip;
		std::cout << "Titlu: "; std::cin.ignore();
		getline(std::cin, titlu);
		std::cout << "Descriere: "; //std::cin.ignore();
		getline(std::cin, descriere);
		std::cout << "Tip: "; //std::cin.ignore();
		getline(std::cin, tip);
		std::cout << "Durata: "; std::cin >> durata;
		this->srv.update(pos, titlu, descriere, tip, durata);
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
	catch (const ValidateException& ex) {
		std::cout << ex << '\n';
	}
}

void UI::del()
{
	try {
		std::string titlu;
		std::cout << "Titlu: "; std::cin.ignore();
		getline(std::cin, titlu);
		this->srv.delete_elem(titlu);
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
}
void UI::search()
{
	try {
		int pos;
		std::cout << "Id: ";
		std::cin >> pos;
		std::cout << srv.search_elem(pos);
	}
	catch (const std::exception& exc)
	{
		std::cerr << exc.what();
	}
}
void UI::filterByDescription()
{
	std::string descriere;
	std::cout << "Descriere: "; std::cin.ignore();
	getline(std::cin, descriere);
	std::vector<Activitate> v = this->srv.filterByDescription(descriere);
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}
void UI::filterByType()
{
	std::string tip;
	std::cout << "Tip: "; std::cin.ignore();
	getline(std::cin, tip);
	std::vector<Activitate> v = this->srv.filterByType(tip);
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}

void UI::sortByTitle()
{
	std::vector<Activitate> v = this->srv.sortBy(compareByTitle);
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}
void UI::sortByDescription()
{
	std::vector<Activitate> v = this->srv.sortBy(compareByDescription);
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}
void UI::sortByTypeAndTime()
{
	std::vector<Activitate> v = this->srv.sortBy(compareByTypeAndTime);
	for (int i = 0; i < (int)v.size(); i++)
		std::cout << v[i];
}


void UI::printCommands()
{
	std::cout << "\n";
	std::cout << "1.Adauga o activitate\n";
	std::cout << "2.Afiseaza activitatilr\n";
	std::cout << "3.Modifica o activitate\n";
	std::cout << "4.Sterge o activitate\n";
	std::cout << "5.Cauta o activitate\n";
	std::cout << "6.Filtreaza dupa descriere\n";
	std::cout << "7.Filtreaza dupa tip\n";
	std::cout << "8.Sorteaza dupa titlu\n";
	std::cout << "9.Sorteaza dupa descriere\n";
	std::cout << "10.Sorteaza dupa tip si durata\n";
	std::cout << "11.Statistica obiecte\n";
	std::cout << "12.Adauga in lista de activitati dupa titlu\n";
	std::cout << "13.Afiseaza lista de activitati\n";
	std::cout << "14.Goleste lista de activitati\n";
	std::cout << "15.Genereaza activitati in lista de activitati\n";
	std::cout << "16.Salveaza in fisier\n";
	std::cout << "0.Exit application";
}