//author sbkun
#include <iostream>
#include <string>
using namespace std;

class Spice {
public:

	class Builder {
	public:
		Builder(const string& ip, uint16_t port) : ip_(ip)
																						 , port_(port) 
																						 , isH264_(false){ }
		Builder& setIsH264(bool isH264) {
			isH264_ = isH264;
			return *this;
		}

		Spice* build() {
			//参数校验 略
			return new Spice(*this);
		}		 

private:
		string ip_;
		uint16_t port_;
		bool isH264_;
		//cpp的内部类不同与java的内部类
		//包裹类不能访问内部类的私有成员, 所以这里要使用友元类
		//但是cpp内部类可以访问包裹类的私有成元，这点和java内部类一样
		friend class Spice;
	};

	void connect() {
		cout<<ip_<<" : "<<port_<<" [isH264="<<boolalpha<<isH264_<<"]"<<endl;
	}

private:
	Spice(const Builder& builder) : ip_(builder.ip_) 
															 , port_(builder.port_)
															 , isH264_(builder.isH264_){ }
	string ip_;
	uint16_t port_;	
	bool isH264_;
};

int main(int argc, char* argv[])
{
	Spice* s = Spice::Builder("127.0.0.1", 9001).setIsH264(true).build();
	s->connect();
	delete s;
	return 0;
}
