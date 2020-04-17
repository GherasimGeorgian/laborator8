// lab66.cpp : Defines the entry point for the console application.
//

#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include "ui.h"
#include "test.h"

int main()
{
	{
		std::cout << "Bun venit in aplicatie!\n";
		run_all_tests();
		RepoListaActivitati rla;
		ActivitateValidator valid;
		Repo r;
		Service s(r, valid, rla);
		UI ui(s);
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

