#pragma once
#include<string>
using std::string;
class Activitate {
private:
	std::string titlu;
	std::string descriere;
	std::string tip;
	int durata;
public:
	//Constructors
	Activitate();
	Activitate(std::string, std::string, std::string, int);
	Activitate(const Activitate&);

	//Getters
	std::string get_titlu() const;
	std::string get_descriere() const;
	std::string get_tip() const;
	int get_durata() const;

	//Setters
	void set_titlu(std::string);
	void set_descriere(std::string);
	void set_tip(std::string);
	void set_durata(int);

	//Override operators
	bool operator==(const Activitate&);
	friend std::ostream& operator<<(std::ostream& os, const Activitate&);

	//Destructor
	~Activitate();
};
class DTO {

private:
	string categorie;

	int valori;

	double procent;
public:

	DTO(const string& key) : categorie{ key },
		valori{ 1 },
		procent{ 0 } {};
	DTO() = default;


	void increment();

	void set_procent(int all);

	string get_str();

	int get_procent() const;
};