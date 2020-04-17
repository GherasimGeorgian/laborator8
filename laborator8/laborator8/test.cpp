
#include "test.h"
#include "assert.h"
#include<sstream>
#include<unordered_map>
void test_activitate()
{
	Activitate act;
	assert(act.get_titlu() == "");
	assert(act.get_descriere() == "");
	assert(act.get_tip() == "");
	assert(act.get_durata() == -1);

	act.set_titlu("absolvire");
	assert(act.get_titlu() == "absolvire");

	act.set_descriere("descriere absolvire");
	assert(act.get_descriere() == "descriere absolvire");

	act.set_tip("personal");
	assert(act.get_tip() == "personal");

	act.set_durata(300);
	assert(act.get_durata() == 300);

	Activitate activ(act);
	assert(activ.get_titlu() == "absolvire");
	assert(activ.get_descriere() == "descriere absolvire");
	assert(activ.get_tip() == "personal");
	assert(activ.get_durata() == 300);

	Activitate activ2("Nunta", "descriere nunta", "juridic", 2000);
	assert(activ2.get_titlu() == "Nunta");
	assert(activ2.get_descriere() == "descriere nunta");
	assert(activ2.get_tip() == "juridic");
	assert(activ2.get_durata() == 2000);

	std::stringstream out;
	out << activ2;
	assert(out.str() == "Nunta descriere nunta juridic 2000\n");

	assert(!(act == activ2));
}

void test_repo_add()
{
	Repo r;
	Activitate act1("Nunta", "descriere nunta", "juridic", 2000);
	Activitate act2("Absolvire", "descriere absolvire", "social", 100);
	r.add_activitate(act1);
	assert(r.getSize() == 1);
	assert(r.get_activitate(0).get_titlu() == "Nunta");
	assert(r.get_activitate(0).get_descriere() == "descriere nunta");
	assert(r.get_activitate(0).get_tip() == "juridic");
	assert(r.get_activitate(0).get_durata() == 2000);
	r.add_activitate(act2);
	assert(r.getSize() == 2);
	assert(r.get_activitate(1).get_titlu() == "Absolvire");
	assert(r.get_activitate(1).get_descriere() == "descriere absolvire");
	assert(r.get_activitate(1).get_tip() == "social");
	assert(r.get_activitate(1).get_durata() == 100);
}

void test_service_add()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta", "juridic", 2000);
	s.add_elem("Absolvire", "descriere absolvire", "social", 100);

	assert(s.getActivitati().get_activitate(0).get_titlu() == "Nunta");
	assert(s.getActivitati().get_activitate(0).get_descriere() == "descriere nunta");
	assert(s.getActivitati().get_activitate(0).get_tip() == "juridic");
	assert(s.getActivitati().get_activitate(0).get_durata() == 2000);

	assert(s.getActivitati().get_activitate(1).get_titlu() == "Absolvire");
	assert(s.getActivitati().get_activitate(1).get_descriere() == "descriere absolvire");
	assert(s.getActivitati().get_activitate(1).get_tip() == "social");
	assert(s.getActivitati().get_activitate(1).get_durata() == 100);

}

void test_repo_update()
{
	Repo r;
	Activitate act1("Nunta", "descriere nunta", "juridic", 2000);
	Activitate act2("Absolvire", "descriere absolvire", "social", 100);
	r.add_activitate(act1);
	r.add_activitate(act2);
	r.update_activitate(act1, "Absolvire", "descriere absolvire", "social", 100);
	assert(act1 == act2);
}

void test_service_update()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta", "juridic", 2000);
	s.update(0, "Absolvire", "descriere absolvire", "social", 100);

	assert(s.getActivitati().get_activitate(0).get_titlu() == "Absolvire");
	assert(s.getActivitati().get_activitate(0).get_descriere() == "descriere absolvire");
	assert(s.getActivitati().get_activitate(0).get_tip() == "social");
	assert(s.getActivitati().get_activitate(0).get_durata() == 100);
}

void test_repo_delete()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	Activitate act1("Nunta", "descriere nunta", "juridic", 2000);
	Activitate act2("Absolvire", "descriere absolvire", "social", 100);
	r.add_activitate(act1);
	r.add_activitate(act2);
	assert(r.getSize() == 2);
	r.delete_activitate("Nunta");
	assert(r.getSize() == 1);
	assert(r.get_activitate(0).get_titlu() == "Absolvire");
	assert(r.get_activitate(0).get_descriere() == "descriere absolvire");
	assert(r.get_activitate(0).get_tip() == "social");
	assert(r.get_activitate(0).get_durata() == 100);
}

void test_service_delete()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta", "juridic", 2000);
	s.add_elem("Absolvire", "descriere absolvire", "social", 100);

	s.delete_elem("Nunta");

	assert(s.getActivitati().get_activitate(0).get_titlu() == "Absolvire");
	assert(s.getActivitati().get_activitate(0).get_descriere() == "descriere absolvire");
	assert(s.getActivitati().get_activitate(0).get_tip() == "social");
	assert(s.getActivitati().get_activitate(0).get_durata() == 100);
}

void test_service_search()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta", "juridic", 2000);
	s.add_elem("Absolvire", "descriere absolvire", "social", 100);
	Activitate act3;
	act3 = s.search_elem(1);

	assert(act3.get_titlu() == "Absolvire");
	assert(act3.get_descriere() == "descriere absolvire");
	assert(act3.get_tip() == "social");
	assert(act3.get_durata() == 100);
}

void test_service_filterByDescription()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere ceva", "juridic", 2000);
	s.add_elem("Absolvire", "descriere absolvire", "social", 100);

	std::vector<Activitate> v = s.filterByDescription("descriere");
	assert((int)v.size() == 2);
	assert(v[0].get_titlu() == "Nunta");
	assert(v[0].get_descriere() == "descriere ceva");
	assert(v[0].get_tip() == "juridic");
	assert(v[0].get_durata() == 2000);
}
void test_service_filterByType()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "descriere absolvire", "social", 100);

	std::vector<Activitate> v = s.filterByType("juridic");
	assert((int)v.size() == 1);
	assert(v[0].get_titlu() == "Nunta");
	assert(v[0].get_descriere() == "descriere nunta mare");
	assert(v[0].get_tip() == "juridic");
	assert(v[0].get_durata() == 2000);
}

void test_service_sortByTitle()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "descriere absolvire", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	std::vector<Activitate> v = s.sortBy(compareByTitle);
	assert((int)v.size() == 3);
	assert(v[0].get_titlu() == "Absolvire");
	assert(v[1].get_titlu() == "Nunta");
	assert(v[2].get_titlu() == "Partyboyyy");

}
void test_service_sortByDescription()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	std::vector<Activitate> v = s.sortBy(compareByDescription);
	assert((int)v.size() == 3);
	assert(v[0].get_titlu() == "Absolvire");
	assert(v[1].get_titlu() == "Nunta");
	assert(v[2].get_titlu() == "Partyboyyy");

}
void test_service_sortByTypeAndTime()
{
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	std::vector<Activitate> v = s.sortBy(compareByTypeAndTime);
	assert((int)v.size() == 3);
	assert(v[0].get_titlu() == "Nunta");
	assert(v[1].get_titlu() == "Absolvire");
	assert(v[2].get_titlu() == "Partyboyyy");

}
void teste_srv_statistica() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.add_elem("Olarit", "descriere olarit", "social", 2009);
	s.add_elem("Nunta", "descriere nuntaww mare", "juridic", 2000);


	auto test = s.statistica();
	assert(test.size() == 4);
	for (auto val : test) {
		string x = val.get_str();
		assert(x.size() > 0);
	}




}
void test_adauga_in_cos() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.adauga_lista_activitati("Nunta");
	assert(rla.get_Size_list_activity() == 1);
	s.adauga_lista_activitati("Absolvire");
	assert(rla.get_Size_list_activity() == 2);

}
void test_goleste_lista_activitati() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.adauga_lista_activitati("Nunta");
	s.adauga_lista_activitati("Absolvire");
	assert(rla.get_Size_list_activity() == 2);
	s.goleste_lista_activitati();
	assert(rla.get_Size_list_activity() == 0);
	s.adauga_lista_activitati("Nunta");
	assert(rla.get_Size_list_activity() == 1);
	s.goleste_lista_activitati();
	assert(rla.get_Size_list_activity() == 0);


}
void test_genereaza_lista_activitati() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.add_elem("Olarit", "descriere olarit", "social", 2009);
	s.genereaza_aleator(4);
	assert(rla.get_Size_list_activity() == 4);
	s.goleste_lista_activitati();
	s.genereaza_aleator(3);
	assert(rla.get_Size_list_activity() == 3);
	s.goleste_lista_activitati();
	s.genereaza_aleator(0);
	assert(rla.get_Size_list_activity() == 0);
	s.goleste_lista_activitati();
	assert(rla.get_Size_list_activity() == 0);
}
void test_export_in_html() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.add_elem("Olarit", "descriere olarit", "social", 2009);
	s.genereaza_aleator(4);
	assert(rla.get_Size_list_activity() == 4);
	s.save_in_html("fisier");
}
void test_export_in_cvs() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.add_elem("Olarit", "descriere olarit", "social", 2009);
	s.genereaza_aleator(4);
	assert(rla.get_Size_list_activity() == 4);
	s.save_in_cvs("fisier");
}
void testValidator() {
	ActivitateValidator v;
	Activitate act{ "","","",-1 };
	try {
		v.validate(act);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}
void test_numar_oferte() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.add_elem("Olarit", "descriere olarit", "social", 2009);
	s.genereaza_aleator(4);
	assert(rla.get_Size_list_activity() == 4);
	int numar_oferte = s.numar_oferte();
	assert(numar_oferte == 4);
}
void test_afisare_activitati() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.add_elem("Olarit", "descriere olarit", "social", 2009);
	auto v = s.afiseaza_activitati_serv();
	assert(v.size() == 4);

}
void test_afiseaza_lista_activitati_serv() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	s.genereaza_aleator(3);
	assert(rla.get_Size_list_activity() == 3);
	auto v = s.afiseaza_lista_activitati_serv();
	assert(v.size() == 3);
}
void test_show_sum_of_time() {
	ActivitateValidator valid;
	RepoListaActivitati rla;
	Repo r;
	Service s(r, valid, rla);
	s.add_elem("Nunta", "descriere nunta mare", "juridic", 2000);
	s.add_elem("Absolvire", "absolvire blana", "social", 100);
	s.add_elem("Partyboyyy", "descriere party", "social", 1952);
	double suma_duratei_tuturor_activitatilor = s.timeSum();
	assert((int)suma_duratei_tuturor_activitatilor == 4052);
}

void run_all_tests()
{
	test_activitate();
	test_repo_add();
	test_service_add();
	test_repo_update();
	test_service_update();
	test_repo_delete();
	test_service_delete();
	test_service_search();
	test_service_filterByDescription();
	test_service_filterByType();
	test_service_sortByTitle();
	test_service_sortByDescription();
	test_service_sortByTypeAndTime();
	teste_srv_statistica();
	test_adauga_in_cos();
	test_goleste_lista_activitati();
	test_genereaza_lista_activitati();
	test_export_in_html();
	test_export_in_cvs();
	testValidator();
	test_numar_oferte();
	test_afisare_activitati();
	test_afiseaza_lista_activitati_serv();
	test_show_sum_of_time();
	std::cout << "Testele au fost rulate cu succes!/n";

}