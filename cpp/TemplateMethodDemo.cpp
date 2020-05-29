#include <iostream>
#include <string>
using namespace std;

class TvOperator {
	public:
	virtual ~TvOperator() = default;
	virtual void open() = 0;
	virtual void close() = 0;
	void play(){
		open();
		cout<<"playing..."<<endl;
		close();
	}
};

class XiaomiTvOp: public TvOperator {
public:
	void open() override {
		cout<<"Xiaomi TV open"<<endl;
	} 
	void close() override {
		cout<<"Xiaomi TV close"<<endl;
	}

};

class KangjiaTvOp: public TvOperator {
	void open() override {
		cout<<"Kangjia TV open"<<endl;
	} 
	void close() override {
		cout<<"Kangjia TV close"<<endl;
	}
};


int main(int argc, char* argv []) 
{
	TvOperator* tv1 = new XiaomiTvOp;
	tv1->play();
	delete tv1;	

	cout<<endl;

	TvOperator* tv2 = new KangjiaTvOp;
	tv2->play();
	delete tv2;	
}
