//author sbkun
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//华为手机抽象类
class HwPhone {
	public:
		explicit HwPhone(const string& model): model_(model) {}
		virtual ~HwPhone() = default;

		virtual void call(const string& to) {
			if (!model_.empty()){
				cout<<model_<<" is calling "<<to<<endl;
			}
		}
	protected:
	//具体型号
		string model_;

	public:
	//低配版 Mate30 Honour6 Honour7
 	static constexpr const char* LowMate30  = "LowMate30";
	static constexpr const char* LowHonour6 = "LowHonour6";
	static constexpr const char* LowHonour7 = "LowHonour7";

	//高配版 Mate30 Honour6 Honour7
 	static constexpr const char* HighMate30  = "HighMate30";
	static constexpr const char* HighHonour6 = "HighHonour6";
	static constexpr const char* HighHonour7 = "HighHonour7";
};

//Huawe mate30 手机
class LowMate30: public HwPhone{
	public:
		LowMate30() : HwPhone(HwPhone::LowMate30) {}		
};

//Huawe Honour6 手机
class LowHonour6: public HwPhone{
	public:
		LowHonour6() : HwPhone(HwPhone::LowHonour6) {}		
};

//Huawe Honour7 手机
class LowHonour7: public HwPhone{
	public:
		LowHonour7() : HwPhone(HwPhone::LowHonour7) {}		
};

//简单工厂: 一个方法负责创建所有产品
class SimpleFactory {
	public:
		static HwPhone* makePhone(const string& model) {
			if (strcasecmp(model.c_str(), HwPhone::LowMate30) == 0) {
				return new LowMate30;
			}
			if (strcasecmp(model.c_str(), HwPhone::LowHonour6) == 0) {
				return new LowHonour6;
			}
			if (strcasecmp(model.c_str(), HwPhone::LowHonour7) == 0) {
				return new LowHonour7;
			}
			return NULL;
		}
};

//工厂方法: 一个工厂负责创建一个产品
class PhoneFactory {
	public:
		virtual ~PhoneFactory() = default;
		virtual HwPhone* makePhone() = 0;
};

class LowMate30Factory: public PhoneFactory{
	public:
		HwPhone* makePhone() override{
			return new LowMate30;
		}
};

class LowHonour6Factory: public PhoneFactory {
	public:
		virtual HwPhone* makePhone() override {
			return new LowHonour6;
		}
};

//抽象工厂： 一个工厂创建一个产品族
class HonourFactory {
	//抽象工厂，负责创建荣耀系列手机
	public:
	virtual ~HonourFactory() = default;
	virtual HwPhone* makeHonour6() = 0; 
	virtual HwPhone* makeHonour7() = 0;
};

//具体工厂类，负责创建低配的，荣耀系列手机
class LowHonourFactory: public HonourFactory{
	public:
	HwPhone* makeHonour6() override {
		return new LowHonour6;		
	}

	HwPhone* makeHonour7() override {
		return new LowHonour7;
	}
};

void testSimleFactory() {
	cout<<__func__<<endl<<endl;

	HwPhone* p1 = SimpleFactory::makePhone(HwPhone::LowMate30);
	p1->call("110");
	delete p1;

	HwPhone* p2 = SimpleFactory::makePhone(HwPhone::LowHonour6);
	p2->call("110");
	delete p2;

	cout<<endl<<"========="<<endl<<endl;
}

void testFactoryMethod(){
	cout<<__func__<<endl<<endl;

	PhoneFactory* f1 = new LowMate30Factory;
	HwPhone* p1 = f1->makePhone();
	p1->call("110")	;
	delete f1;
	delete p1;
	
	PhoneFactory* f2 = new LowHonour6Factory;
	HwPhone* p2 = f2->makePhone();
	p2->call("110")	;
	delete f2;
	delete p2;

	cout<<endl<<"========="<<endl<<endl;
}

void testAbstractFactory() {
	cout<<__func__<<endl<<endl;

	HonourFactory* f1 = new LowHonourFactory;
	HwPhone* p1 = f1->makeHonour6();
	p1->call("110")	;
	
	HwPhone* p2 = f1->makeHonour7();
	p2->call("110")	;
	delete f1;
	delete p1;
	delete p2;
}

int main(int argc, char* argv[])
{
	testSimleFactory();
	testFactoryMethod();
	testAbstractFactory();
	return 0;
}
