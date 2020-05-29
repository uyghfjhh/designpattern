#include <iostream>
using namespace std;

class SubSystemA{
	public:
		void MethodA(){
			cout<<"call MethodA"<<endl;
		}
};

class SubSystemB{
	public:
		void MethodB(){
			cout<<"call MethodB"<<endl;
		}
};

class Fasade{
public: 
	void Method() {
		a_.MethodA();
		b_.MethodB();
	}
private:
	SubSystemA a_;
	SubSystemB b_;
};

int main(int argc, char* argv[])
{
	Fasade fasade;
	fasade.Method();
	return 0;
}
