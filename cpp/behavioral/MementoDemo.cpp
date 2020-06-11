#include <iostream>
#include <list>
#include <memory>
using namespace std;

class Memento{
//为了少写几个get函数, 使用友元
friend class Hero;
public:
		Memento(int gold, int hp, const string& name) 
			: gold_(gold)
			,	hp_(hp)
			, name_(name)
		{}
private:
		int gold_;
		int hp_;
		string name_;
};

class Hero{
	public:
		Hero() : gold_(9999)
					 , hp_(100)
					 , name_("mk")
		{} 

		void beingAttacked(int damage) {
			hp_ -= damage;
		}

		shared_ptr<Memento> saveToMemento() {
			return shared_ptr<Memento>(new Memento(gold_, hp_, name_));
		}
		
		void restoreFromMemento(shared_ptr<Memento> p) {
			gold_ = p->gold_;
			hp_ = p->hp_;
			name_= p->name_;
		}
	
		ostream& print(ostream& os) const {
			return os<<"hero:"<<name_<<" gold:"<<gold_<<" hp:"<<hp_;
		}
	
	private:
		int gold_;
		int hp_;
		string name_;
};

ostream& operator<<(ostream& os, const Hero& w){
	return w.print(os);
}

class War3{
public:
	void save(shared_ptr<Memento> pMemento) {
		mementos_.push_back(pMemento);		
	}

	void load(shared_ptr<Hero> pHero) {
		if (!mementos_.empty())
		{
			shared_ptr<Memento> pMemento = mementos_.back();
			mementos_.pop_back();
			pHero->restoreFromMemento(pMemento);
		}
	}
private:
	list<shared_ptr<Memento>> mementos_;
};

int main(int argc, char* argv[])
{
	War3 war3;
	{
		shared_ptr<Hero> pHero = make_shared<Hero>();	
		war3.save(pHero->saveToMemento());
		cout<<*pHero<<endl<<endl;

		pHero->beingAttacked(40);
		cout<<"fuck ! my hero was attacked, hp reduced 40..."<<endl;
		cout<<*pHero<<endl<<endl;;

		war3.load(pHero);
		cout<<"don't worry! hero state reload..."<<endl;
		cout<<*pHero<<endl;
	}	

	return 0;
}
