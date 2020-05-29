//author sbkun
#include <iostream>
using namespace std;

class Fstream{
public:
	virtual ~Fstream() = default;
	Fstream() = default;
	virtual void read() {
		cout<<"base read"<<endl;
	}

protected:
	Fstream(const Fstream&) = delete;
	Fstream& operator=(const Fstream&) = delete;
};

class FilterFstream : public Fstream {
public:
	virtual ~FilterFstream() {
		delete fstream_;
	}
	FilterFstream(Fstream* f) : fstream_(f) {}
protected:
	Fstream* fstream_;
};

class ZipFstream : public FilterFstream{
	public: 
	ZipFstream(Fstream* f): FilterFstream(f)	 { }	
	void read() override {
		cout<<"zip read"<<endl;
		fstream_->read();
	}
};
class CipherFstream : public FilterFstream{
	public:
	CipherFstream(Fstream* f): FilterFstream(f)	 { }	
	void read() override {
		cout<<"cipher read"<<endl;
		fstream_->read();
	}
};

class BufferFstream : public FilterFstream{
	public:
	BufferFstream(Fstream* f): FilterFstream(f)	 { }	
	
	void read() override {
		cout<<"buffer read"<<endl;
		fstream_->read();
	}
};

int main(int argc, char* argv[])
{
	Fstream* f1 = new BufferFstream(new ZipFstream(new CipherFstream(new Fstream)));	
	f1->read();
	delete f1;

	cout<<endl<<"====="<<endl<<endl;

	//可以任意组合需要的功能，酸爽	
	Fstream* f2 = new BufferFstream(new CipherFstream(new ZipFstream(new Fstream)));	
	f2->read();
	delete f2;
	return 0;
}
