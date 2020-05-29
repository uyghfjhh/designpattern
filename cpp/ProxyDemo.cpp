#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Server{
	public:
		virtual ~Server(){}
		virtual void service(const string& req, string& rsp) = 0;
};

class HttpServer: public Server{
	public:
		void service(const string& req, string& rsp) {
			cout<<"handle req"<<req<<endl;;
		}
};


class HttpServerProxy: public Server{
	public:
		void service(const string& req, string& rsp)	{
			if (req.find("sbkun") !=  string::npos) {
				cout<<"not handle req"<<req<<endl;
			}
			else{
				server_.service(req, rsp);
			}
		}
	private:
		HttpServer server_;
};


int main(int argc, char* argv[])
{
	HttpServerProxy sp;
	string rsp;
	sp.service("sbkun", rsp);
	sp.service("haha", rsp);
	return 0;
}
