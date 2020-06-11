//author sbkun
#include "noncopyable.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

string intToBinaryString(unsigned long n);

class Context {
public:
	explicit Context(const string& input) : input_(input) {
	}
	
	const string& getInput() const {
		return input_;
	}
	
	void setOutput(const string& output) {
		output_ = output;
	}	
	
	string getOutput() const {
		return output_;
	}	
private:
	string input_;	
	string output_;
};

class Expression: noncopyable {
public:
	virtual ~Expression() = default;
	virtual void interpret(Context& context) = 0;
};

class Int2Hex: public Expression{
public:
	void interpret(Context& context) override {
		const string& input= context.getInput();
		if (input.find("Hexadecimal") != string::npos) {
				int intArg = stoi(input.substr(0, input.find(" ")));	
				std::stringstream stream;
				stream << std::hex << intArg;
				context.setOutput(stream.str());
		}
	}
};

class Int2Binary: public Expression{
public:
	void interpret(Context& context) override {
		const string& input= context.getInput();
		if (input.find("Binary") != string::npos) {
				int intArg = stoi(input.substr(0, input.find(" ")));	
				context.setOutput(intToBinaryString(intArg));
		}
	}
};

class InterprtClient {
public:
	InterprtClient(){
		expressions_.emplace_back(new Int2Binary);
		expressions_.emplace_back(new Int2Hex);
	}

	void interpret(Context& context) {
		for(auto& e: expressions_) {
			e->interpret(context);
		}
	}

private:
	vector<unique_ptr<Expression>> expressions_;
};

string intToBinaryString(unsigned long n)
{
	char     bArray[ (sizeof( unsigned long ) * 8) + 1 ];
	unsigned index  = sizeof( unsigned long ) * 8;
	char temp =0;
	bArray[ index ] = '\0';
	do{          
		temp = (n & 1); 
		temp = temp + '0';
		bArray[ --index ] = temp;
	}while (n >>= 1);
	return string( bArray + index );
}

int main(int argc, char* argv[])
{
	string str1 = "28 in Binary";
	string str2 = "28 in Hexadecimal";

	Context context1(str1);
	Context context2(str2);

	InterprtClient client;
	client.interpret(context1);
	client.interpret(context2);

	cout<<str1<<" = "<<context1.getOutput()<<endl<<endl;
	cout<<str2<<" = "<<context2.getOutput()<<endl<<endl;

	return 0;
}
