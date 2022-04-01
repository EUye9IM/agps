#include <agps/const_str.h>

#include <iostream>
using namespace std;
using namespace agps;
int main(){
	ConstStr a;
	a.set("test1");
	cout << a.cstr() << endl;
	// not allowed
	// a.set(a.cstr());
	cout << a.cstr() << endl;
	
	return 0;
}