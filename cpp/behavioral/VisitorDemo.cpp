#include <iostream>
#include <vector>

using namespace std;

class Tv;
class Phone;

class Visitor {
	public:
		virtual ~Visitor() = default;
		
		virtual int visit(Tv* tv) = 0;
		virtual int visit(Phone* phone) = 0;
};

class Item {
	public:
		virtual ~Item() = default;
		virtual int accept(Visitor* visitor) = 0;
};
	
class Tv: public Item {
	public:
	Tv(int weight, int price) : weight_(weight)
														, price_(price)		
	{	 }			

	int getWeight() const {
		return weight_;
	}
	
	int getPrice() const {
		return price_;
	}	
	
	int accept(Visitor* visitor) override {
		return visitor->visit(this);
	}

	private:
	int weight_;	//重量	
	int price_;	 //价格
};

class Phone: public Item{
public:
	Phone(int weight, int price) : weight_(weight)
														, price_(price)		
	{	 }			

	int getWeight() const {
		return weight_;
	}
	
	int getPrice() const {
		return price_;
	}	
	
	int accept(Visitor* visitor) override {
		return visitor->visit(this);
	}

	private:
	int weight_;
	int price_;	 
};

class ShoppingCart: public Visitor {
public:
		int visit(Tv* tv) {
			//TODO 这里可以使用策略模式，
			//获取打折策略，然后计算出实际价格
			return tv->getPrice();
		}
		
		int visit(Phone* phone) {
			//TODO 这里可以使用策略模式，
			//获取打折策略，然后计算出实际价格
			return phone->getPrice();
		}
};

int main(int argc, char* argv[])
{
	Visitor* visitor = new ShoppingCart();
	vector<Item*>	items = {new Phone(2,2), new Tv(1,1)};

	int priceSum = 0;
	for (auto it: items) {
		priceSum += it->accept(visitor);
	}
	
	cout<<"total price "<<priceSum<<endl;	
	
	for (auto it: items) {
		delete it;
	}
	delete visitor;

	return 0;
}
