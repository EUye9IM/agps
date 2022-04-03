#include <agps/agps.h>
#include <cstring>
#include <iostream>
using namespace std;
using namespace agps;
void static pri(Parser &p, Type t, const char n) {
	if (p.isExist(n))
		switch (t) {
		case Type::STR:
			cout << n << ":1 " << p.get(n).Str << endl;
			break;
		case Type::INT:
			cout << n << ":1 " << p.get(n).Int << endl;
			break;

		default:
		case Type::FLAG:
			cout << n << ":1 " << p.get(n).Exist << endl;
			break;
		}
	else {
		cout << n << ":0" << endl;
	}
}
int main(int argc, const char **argv) {
	// cout << argc << endl;
	// for (int i = 0; i < argc; i++) {
	// 	cout << argv[i] << endl;
	// }
	Parser pa;
	pa.add(Type::FLAG, 'f', "flag", "this is flag");
	pa.add(Type::INT, 'i', "int-1", "this is int1");
	pa.add(Type::INT, 'I', "int-2", "this is int2", false, VALUE_NONE,
		   [](const Value &val) -> bool { return val.Int >= 0; });
	pa.add(Type::STR, 's', "s-1", "this is s", false);
	pa.add(Type::STR, 'S', "s-2", "this is s2", true, VALUE_NONE,
		   [](const Value &val) -> bool {
			   return !(stricmp(val.Str, "yes") && stricmp(val.Str, "y") &&
						stricmp(val.Str, "no") && stricmp(val.Str, "n"));
		   });
	pa.parse(argc, argv);
	if (!pa.success()) {
		pa.printUsage(argv[0]);
		return 0;
	} else
		cout << "success." << endl;
	cout << "  "
		 << "e "
		 << "val" << endl;
	pri(pa, Type::FLAG, 'f');
	pri(pa, Type::INT, 'i');
	pri(pa, Type::INT, 'I');
	pri(pa, Type::STR, 's');
	pri(pa, Type::STR, 'S');
	return 0;
}