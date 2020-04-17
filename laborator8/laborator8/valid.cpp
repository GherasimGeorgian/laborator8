
#include "valid.h"
#include <assert.h>
#include <sstream>

void ActivitateValidator::validate(const Activitate& act) {
	vector<string> msgs;
	if (act.get_titlu().size() == 0) msgs.push_back("Titlu vid!!!");
	if (act.get_descriere().size() == 0) msgs.push_back("Descriere vida!!!");
	if (act.get_tip().size() == 0) msgs.push_back("Tip vid!!!");
	if (act.get_durata() < 0) msgs.push_back("Durata negativa!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

