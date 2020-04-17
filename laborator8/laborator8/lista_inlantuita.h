#pragma once
#include <string>
using namespace std;


template <typename T>
struct Nod {
	T val;
	Nod* urm;
	Nod(T v) :val{ v }, urm{ nullptr } {};
	Nod(T v, Nod* urm) :val{ v }, urm{ urm } {};
};

//forward declaration - clasa iterator e definit mai jos 
//Avem nevoie de asta fiindca clasa iterator este folosit in clasa MyLista dar definitia apare mai jos
template <typename T>
class ListaInlantuitaIterator;

template <typename T>
class ListaInlantuita {

	Nod<T>* cap;
	/*
	dealoca toate nodurile
	*/
	void elibereazaNoduri();

	/*
	Face o copie a listei inlantuite
	Parcurge recursiv lista si creaza noduri in care copieaza valorile
	*/
	Nod<T>* copieaza(Nod<T>* current);

public:
	ListaInlantuita() :cap{ nullptr } {};

	/*
	Constructor de copiere
	- apelat automat la transmitere prin valoare, la return prin valoare, explicit ex: MyList l2{l1};

	Rule of three
	*/
	ListaInlantuita(const ListaInlantuita& ot);
	/*
	Operator de assignment
	- apelat automat la expresii a = b; unde a si b sunt de tip MyLista
	Rule of three
	*/
	void operator=(const ListaInlantuita& ot);

	/*
	Destructor - apelat cand obiectul este distrus (out of scope sau delete)
	Elibereaza memoria pentru fiecare nod
	Rule of three
	*/
	~ListaInlantuita();
	/*
	Returneaza numarul de elemente
	*/
	size_t size() const;

	/*
	Adauga la inceput
	*/
	void addInceput(T v);

	/*
	adauga la sfarsit
	*/
	void push_back(T v);


	/*
	sterge un element de pe o pozitie
	*/
	void erase(size_t position);
	/*
	Primul element
	*/
	T& first() const;

	/*
	Returneaza un iterator pozitionat pe primul element
	E nevoie de el ex. daca vrem sa folosim lista in range for
	*/
	ListaInlantuitaIterator<T> begin() const;

	/*
	Returneaza un iterator cu nodul nullptr (dupa ultimul element)
	*/
	ListaInlantuitaIterator<T> end() const;

	/*
	Acces dupa pozitie
	Operatie ineficienta, trebuie sa parcurg lista pana la poz
	*/
	T& operator[](size_t poz);

	//sort
	void ListaInlantuita<T>::sort(bool(*compare)(const T&, const T&));
	//
	void goleste_lista();

};



template <typename T>
void ListaInlantuita<T>::sort(bool(*compare)(const T&, const T&))
{
	// Initialize previous and current nodes 
	auto prev = cap;
	auto curr = cap->urm;

	// Traverse list 
	while (curr != NULL)
	{
		// If curr is smaller than prev, then 
		// it must be moved to head 
		if (compare(curr->val, prev->val))
		{
			// Detach curr from linked list 
			prev->urm = curr->urm;

			// Move current node to beginning 
			curr->urm = cap;
			cap = curr;

			// Update current 
			curr = prev;
		}

		// Nothing to do if current element 
		// is at right place 
		else
			prev = curr;

		// Move current 
		curr = curr->urm;
	}

}

template <typename T>
ListaInlantuita<T>::ListaInlantuita(const ListaInlantuita& ot) {
	//obiectul acum se creaza (constructor) 
	//copiez din ot in this
	cap = copieaza(ot.cap);
}
/*
Operator de assignment
- apelat automat la expresii a = b; unde a si b sunt de tip MyLista
Rule of three
*/
template <typename T>
void ListaInlantuita<T>::operator=(const ListaInlantuita& ot) {
	//poate destinate (this) contine deja ceva
	elibereazaNoduri();
	//copiez din ot in this
	cap = copieaza(ot.cap);
}

/*
Destructor - apelat cand obiectul este distrus (out of scope sau delete)
Rule of three
*/
template <typename T>
ListaInlantuita<T>::~ListaInlantuita() {
	elibereazaNoduri();
}

template <typename T>
Nod<T>* ListaInlantuita<T>::copieaza(Nod<T>* current) {
	if (current == nullptr) {
		return nullptr;
	}
	auto n = new Nod<T>{ current->val };
	n->urm = copieaza(current->urm);
	return n;
}

template <typename T>
void ListaInlantuita<T>::addInceput(T v) {
	Nod<T>* n = new Nod<T>{ v,cap };
	cap = n;
}
template <typename T>
void ListaInlantuita<T>::erase(size_t position)
{
	if (cap == NULL)
		return;

	// Store head node 
	auto temp = cap;

	// If head needs to be removed 
	if (position == 0)
	{
		cap = temp->urm;   // Change head 
		delete temp;               // free old head 
		return;
	}

	// Find previous node of the node to be deleted 
	for (size_t i = 0; temp != NULL && i < position - 1; i++)
		temp = temp->urm;

	// If position is more than number of ndoes 
	if (temp == NULL || temp->urm == NULL)
		return;

	// Node temp->next is the node to be deleted 
	// Store pointer to the next of node to be deleted 
	auto next = temp->urm->urm;

	// Unlink the node from linked list 
	delete temp->urm;  // Free memory 

	temp->urm = next;  // Unlink the deleted node from list 
}

template <typename T>
void ListaInlantuita<T>::push_back(T v) {
	//ma pun pe ultimul element
	auto nCurent = cap;
	while (nCurent != nullptr && nCurent->urm != nullptr) {
		nCurent = nCurent->urm;
	}

	if (nCurent == nullptr) {
		cap = new Nod<T>{ v,nullptr };//poate era o lista vida
	}
	else {
		nCurent->urm = new Nod<T>{ v,nullptr };
	}
}

template <typename T>
size_t ListaInlantuita<T>::size() const {
	auto nCurent = cap;
	int lg = 0;
	while (nCurent != nullptr) {
		lg++;
		nCurent = nCurent->urm;
	}
	return lg;
}

template <typename T>
T& ListaInlantuita<T>::operator[](size_t poz) {
	auto nCurent = cap;
	size_t lg = 0;
	while (lg < poz) {
		lg++;
		nCurent = nCurent->urm;
	}
	return nCurent->val;
}

template <typename T>
T& ListaInlantuita<T>::first() const {
	return cap->val;
}
template <typename T>
void ListaInlantuita<T>::elibereazaNoduri() {
	auto nCurent = cap;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	cap = nullptr;
}


template <typename T>
void ListaInlantuita<T>::goleste_lista() {
	auto nCurent = cap;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	cap = nullptr;
}
/*
Iterator pentru lista inlantuita
*/
template<typename T>
class ListaInlantuitaIterator {
	//pozitia curenta - este nullptr daca am ajuns la sfarsitul listei
	Nod<T>* current;
public:
	ListaInlantuitaIterator(Nod<T>* c) :current{ c } {
	}

	/*
	Este nevoie de operator != pentru range for
	*/
	bool operator!=(const ListaInlantuitaIterator& ot);

	/*
	trece la urmatorul element din interatie
	Este nevoie de operator ++ pentru range for
	*/
	void operator++();
	/*
	Returneaza elementul curent din interatir
	Este nevoie de operator * pentru range for
	*/
	T& operator*();
};


template <typename T>
ListaInlantuitaIterator<T> ListaInlantuita<T>::begin() const {
	return ListaInlantuitaIterator<T>{ cap };
}


template <typename T>
ListaInlantuitaIterator<T> ListaInlantuita<T>::end() const {
	return ListaInlantuitaIterator<T>{ nullptr };
}


/*
Este nevoie de operator != pentru range for
*/
template <typename T>
bool ListaInlantuitaIterator<T>::operator!=(const ListaInlantuitaIterator& ot) {
	return current != ot.current;
}

/*
trece la urmatorul element din interatie
Este nevoie de operator ++ pentru range for
*/
template <typename T>
void ListaInlantuitaIterator<T>::operator++() {
	current = current->urm;
}
/*
Returneaza elementul curent din interatir
Este nevoie de operator * pentru range for
*/
template <typename T>
T& ListaInlantuitaIterator<T>::operator*() {
	return current->val;
}