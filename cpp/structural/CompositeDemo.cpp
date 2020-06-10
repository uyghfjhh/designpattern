#include <iostream>
#include <string>
#include <list>

using namespace std;

class HumResoure {
	public: 
		HumResoure() = default;
		virtual ~HumResoure() = default;
		virtual void showDetails() = 0;
		HumResoure(const HumResoure& ) = delete;
		HumResoure& operator=(const HumResoure&) = delete;
};

class Employee: public HumResoure {
public:
	Employee(const string& name, uint32_t age) : name_(name)
																						 , age_(age) 
	{}

	void showDetails() override {
		cout<<"name:"<<name_<<" age:"<<age_<<endl;
	}
private:
	string name_;
	uint32_t age_;
};

class Department: public HumResoure {
	public:
	void addEmployee(Employee* e) {
		employees_.push_back(e);
	}

	void showDetails() override {
		for(auto &e: employees_) {
			e->showDetails();
		}
	}

	private:
	list<Employee*> employees_;
};

int main(int argc, char* argv[])
{
	Department* d = new Department;
	d->addEmployee(new Employee("sbkun", 13));
	d->addEmployee(new Employee("kunsb", 31));
	d->showDetails();
	delete d;
	return 0;
}
