#include <iostream>
#include <functional>
using namespace std;

void oldFoo(int arg) {
	cout<<"call oldFoo: "<<arg<<endl;
}

int main(int argc, char* argv[])
{
	function<void()> f = bind(oldFoo, 1);
	f();
	return 0;
}
