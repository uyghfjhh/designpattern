#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//author sbkun
class Discount {
	public:
		virtual ~Discount() {}
		virtual float calculate(float price) = 0;
};

class Vip: public Discount {
public:
	float calculate(float price) override {
		return price*0.8;
	}
};

class GoldVip: public Discount {
public:
	float calculate(float price) override {
		return price*0.5;
	}
};

class DiscountFactory {
public:
	static DiscountFactory& getInstance() {
		static DiscountFactory instance;
		return instance;		
	}

	Discount* getDiscount(const string& vipType) {
		string t = vipType;
		std::transform(t.begin(), t.end(), t.begin(), ::tolower);
		return discounts_[t];
	}

private:
	DiscountFactory() {
		discounts_["vip"] = new Vip;
		discounts_["goldvip"] = new GoldVip;
	}

	map<string, Discount*> discounts_;
};

class Product {
public:
	Product(float price): price_(price) { }
	float getPrice(const string& vipType) {
		Discount* discout = DiscountFactory::getInstance().getDiscount(vipType);
		if (discout != NULL)	{
			return discout->calculate(price_);
		}	
		return price_;
	}

private:
	float price_;
};


int main(int argc, char* argv[]) {
	Product product(100);
	cout<<product.getPrice("vip")<<endl;
	cout<<product.getPrice("goldvip")<<endl;
	cout<<product.getPrice("haha")<<endl;
	return 0;
}
