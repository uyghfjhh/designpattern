#include "SingleTon.h"

#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

class TCPState;

class TCPConnetion
{
	public:
		TCPConnetion();
		~TCPConnetion() {}

		//used for client
		void ActiveOpen();
		//used for server
		void PassiveOpen();
		void Close();

		void Send(string& msg);
		void Recv(const string& msg);

	private:
		friend class TCPState;
		void ChangeState(TCPState*);

	private:
		TCPState* state_;
};

class TCPState
{
	public:
		virtual void ActiveOpen(TCPConnetion* ) {}
		virtual void PassiveOpen(TCPConnetion* ) {}
		virtual void Close(TCPConnetion*)	{}
		virtual void Send(TCPConnetion*, string& msg) {}
		virtual void Recv(TCPConnetion*, const string& msg) {}

		virtual ~TCPState() = default;
		virtual const string& getStateName() const = 0;

	protected:
		void ChangeState(TCPConnetion*, TCPState*);
};

class TCPListen: public TCPState, public SingleTon<TCPListen>
{
	public:
		void Send(TCPConnetion* c, string& msg) override;
		void Recv(TCPConnetion* c, const string& msg) override;
		const string& getStateName() const override {
			return name_;
		}
	private:
		const string name_ = "LISTEN";
};

class TCPEstablished : public TCPState, public SingleTon<TCPEstablished>
{
	public:
		const string& getStateName() const override{
			return name_;
		}
	private:
		const string name_ = "ESTABLISHED";
};

class TCPClosed : public TCPState, public SingleTon<TCPClosed>
{
	public:
		void ActiveOpen(TCPConnetion* c) override {
			ChangeState(c, &TCPEstablished::getInstance());
		}

		void PassiveOpen(TCPConnetion* c) override {
			ChangeState(c, &TCPListen::getInstance());
		}

		const string& getStateName() const override{
			return name_;
		}
	private:
		const string name_ = "CLOSED";

};

class TCPSynReceived: public TCPState, public SingleTon<TCPSynReceived> 
{
	public:
		void Recv(TCPConnetion* c, const string& msg) override {
			if (msg=="ACK")	 {
				ChangeState(c, &TCPEstablished::getInstance());
			}
		}

		const string& getStateName() const override {
			return name_;
		}
	private:
		const string name_ = "SYN-RECEIVED";
};

void TCPListen::Send(TCPConnetion* t, string& msg)
{
	cout<<"Send "<<msg<<endl;
	ChangeState(t, &TCPSynReceived::getInstance());
}

void TCPListen::Recv(TCPConnetion* c, const string& msg) {
	if (msg == "ACK") {
		string msg = "SYN+ACK";
		Send(c, msg);
	}
}

TCPConnetion::TCPConnetion()
{
	state_ = &TCPClosed::getInstance();
	cout<<"TCPConnetion init state "<<state_->getStateName()<<endl;
}

void TCPConnetion::ChangeState(TCPState* s)
{
	state_ = s;
}

void TCPConnetion::ActiveOpen()
{
	state_->ActiveOpen(this);
}

void TCPConnetion::PassiveOpen()
{
	cout<<"TCPConnetion setup tcb"<<endl;
	state_->PassiveOpen(this);
}

void TCPConnetion::Close()
{
	state_->Close(this);
}

void TCPConnetion::Send(string& msg)
{
	state_->Send(this, msg);
}

void TCPConnetion::Recv(const string& msg)
{
	cout<<"TCPConnetion Recvd [ "<<msg<<" ]"<<endl;
	state_->Recv(this, msg);
}

void TCPState::ChangeState(TCPConnetion* t, TCPState* s)
{
	cout<<"[ "<<getStateName()<<" ] goto "<<"[ "<<s->getStateName()<<"] "<<endl<<endl;
	t->ChangeState(s);
}

int main(int argc, char *argv[])
{
	TCPConnetion c;
	c.PassiveOpen();
	c.Recv("ACK");	
	c.Recv("ACK");


	return 0;
}
