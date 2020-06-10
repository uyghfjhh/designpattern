#include <iostream>
#include <list>
#include <string>

using namespace std;

class Request {
	public:
		Request(const string& msg) : msg_(msg) {
		}

		const string& getMsg() const {
			return msg_;
		}
	private:
		string msg_;
};

class Response {
	public:

		void append(const string& msg) {
			msg_ += msg;
		}

		const string& getMsg() const {
			return msg_;
		}

	private:
		string msg_;
};

class Handler {
	public:
		virtual ~Handler() {}
		virtual bool handle(const Request& req, Response& rep) = 0;
};

class HandlerA : public Handler {
	public:
		bool handle(const Request& req, Response& rep) override {
			rep.append(req.getMsg()+"->handled by HandlerA ");
			return true;
		}
};

class HandlerB : public Handler {
	public:
		bool handle(const Request& req, Response& rep) override {
			rep.append("->handled by HandlerB ");
			return true;
		}
};

class Process {
	public:
		~Process() {
			for (auto &h: handlers_) {
				delete h;
			}
		}

		void addHandler(Handler* handler) {
			handlers_.push_back(handler);
		}

		void handle(const Request& req, Response& rsp) {
			for (auto& h: handlers_) {
				if (!h->handle(req, rsp)) {
					break;
				}
			}
		}

	private:
		list<Handler*> handlers_;
};

int main(int argc, char *argv[])
{
	Process* p = new Process();
	p->addHandler(new HandlerA());
	p->addHandler(new HandlerB());

	Request req("init");
	Response rsp;

	p->handle(req, rsp);

	cout<<rsp.getMsg()<<endl;

	delete p;
}
