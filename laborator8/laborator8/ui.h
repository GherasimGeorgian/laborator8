#pragma once
#include "service.h"
#include <iostream>

class UI {
public:
	UI(Service& s) : srv{ s } {};
	void run();
	~UI();

private:
	Service& srv;
	void add();
	void print();
	void update();
	void del();
	void search();
	void filterByDescription();
	void filterByType();
	void sortByTitle();
	void sortByDescription();
	void sortByTypeAndTime();
	void printCommands();
	void ui_statistica();
	void add_activity_list();
	void show_add_activity_list();
	void clear_list_activities();
	void random_add_list_activity();
	void save_in_file();
	void show_number_of_list_activity();
	void show_sum_of_time();
};