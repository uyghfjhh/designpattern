#include <iostream>
#include <string>

using namespace std;

class TV {
	public:
		virtual ~TV(){}
		virtual void play() = 0;
};

class HaierTV : public TV{
	public:
		void play() override {
			cout<<"play HaierTV"<<endl;
		}
};

class XiaomiTV: public TV{
	public:
		void play() override {
			cout<<"play XiaomiTV"<<endl;
		}
};

class SimpleFactory{
	public:
		static TV* createTv(const string& brand) {
			if (brand=="haier") {
				return new HaierTV;
			}
			else if(brand=="xiaomi") {
				return new XiaomiTV;
			}
			return NULL;
		}
};

//为了消除if-else，使用另一种模式： 工厂方法
class FactoryMethod {
	public:
		virtual ~FactoryMethod() {
		}
		virtual TV* createTV() = 0;
};

class HaierFactoryMethod: public FactoryMethod{
	public:
		virtual TV* createTV() override{
			return new HaierTV;
		}
};

class Xiaomi: public FactoryMethod {
	public:
	virtual TV* createTV() override {
		return new XiaomiTV;
	}
};

void testSimleFactory() {
	TV* tv = SimpleFactory::createTv("haier");
	tv->play();
}

void testFactoryMethod(){
	FactoryMethod* method = new HaierFactoryMethod;
	TV* tv = method->createTV();
	tv->play();
}

int main(int argc, char* argv[])
{
	//testSimleFactory();
	testFactoryMethod();
	return 0;
}
