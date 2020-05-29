#include <stdio.h>
#include <iostream>
using namespace std;

class Target {
public:
	virtual ~Target() = default;
	Target() = default;
	virtual void Foo() = 0;
	Target(const Target&) = delete;
	Target& operator=(const Target&) = delete;
};

class Adaptee{
	public:
	void oldFoo() {
		cout<<"call oldFoo"<<endl;
	}
};

class Adatper: public Target {
	public:
	Adatper(Adaptee* a): adaptee_(a) {
	}
	void Foo() override {
		adaptee_->oldFoo();
	}
	private:
	Adaptee* adaptee_;
};

int main(int argc, char* argv[])
{
	Adatper* a = new Adatper(new Adaptee);
	a->Foo();
	delete a;
	return 0;
}
