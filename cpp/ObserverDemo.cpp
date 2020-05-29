#include <string>
#include <iostream>
#include <list>

using namespace std;

class Observer;

class Subject {
public:
	virtual ~Subject()  = default;
	virtual void regiterObserver(Observer* o) = 0;
	virtual void removeObserver(Observer* o) = 0;
	virtual void updateObservers(const string& message) = 0;
};

class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(const string& message)= 0;
};

class ConcreteSubject: public Subject {
	public:
	~ConcreteSubject() {}
	void regiterObserver(Observer* o) override {
		observers_.push_back(o);
	}

	void removeObserver(Observer* o) override {
		observers_.remove(o);
	}

	void updateObservers(const string& message) override {
		for(auto& o: observers_) {
			o->update(message);
		}
	}

	private:
	list<Observer*> observers_;

};

class ConcreteObserver: public Observer{
	public:
	~ConcreteObserver() {}
	ConcreteObserver(const string& name) : name_(name) {
	}

	void update(const string& message) override {
		cout<<name_<<" : "<<message<<endl;;	
	}

	private:
	string name_;
};


int main(int argc, char* argv[]) {
	ConcreteSubject subject;
	subject.regiterObserver(new ConcreteObserver("one"));
	subject.regiterObserver(new ConcreteObserver("two"));
	subject.updateObservers("message1");
}
