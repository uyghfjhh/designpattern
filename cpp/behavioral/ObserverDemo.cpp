#include "noncopyable.h"

#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <map>
#include <set>
#include <math.h>

using namespace std;

const double EPS = 1e-6;

class Stock : noncopyable {
	public:
		Stock(const string& name, float price) : name_(name)
																					 , price_(price) 
	  {
			cout<<"Stock "<<name_<<" addr "<<this<<" Ctor"<<endl; 
		}

		~Stock() {
			cout<<"Stock "<<name_<<" addr "<<this<<" Dtor"<<endl; 
		}

		const string& getName() const {
			return name_;
		}

		float getPrice() const {
			return price_;
		}

		void setPrice(float price) {
			price_ = price;
		}

	private:
		string name_;
		float price_;
};

class StockObserver : noncopyable {
	public:
		explicit StockObserver(const string& name) : name_(name) {
			cout<<name_<<" addr "<<this<<" Ctor"<<endl; 
		}

		virtual ~StockObserver() {
			cout<<name_<<" addr "<<this<<" Dtor"<<endl; 
		}
		virtual void onPriceChaned(const Stock& stock) = 0;

	protected:
	string name_;
};

class Investor: public StockObserver {
	public:
		explicit Investor(const string& name = "Investor"):StockObserver(name) {
		}
		void onPriceChaned(const Stock& pStock) override {
			cout<<name_<<" know that stock's price changed->"<<pStock.getPrice()<<endl;
		}
};

class Admin: public StockObserver {
	public:
		explicit Admin(const string& name = "Admin"):StockObserver(name) {
		}
	
		void onPriceChaned(const Stock& pStock) override {
			cout<<name_<<" know that stock's price changed->"<<pStock.getPrice()<<endl;
		}
};

class Market : noncopyable {
	using ObSharedPtr = shared_ptr<StockObserver>;
	using StockSharedPtr = shared_ptr<Stock>;
	using StockMap = map<string, StockSharedPtr>;
	using ObMap = map<string, set<ObSharedPtr>>;

	public:

	void addStock(shared_ptr<Stock> pStock) {
		if (stocks_.count(pStock->getName()) == 0) {
			stocks_[pStock->getName()] = pStock;
			obmap_[pStock->getName()] = move(set<ObSharedPtr>());
		}
	}

	void registerStockOb(const string& name, ObSharedPtr pOb) {
		const auto& entry = obmap_.find(name);
		if (entry != obmap_.end()) {
			auto& oblist = entry->second;	
			oblist.insert(pOb);
		}
	}

	void unregisterStockOb(const string& name, ObSharedPtr pOb) {
		const auto& entry = obmap_.find(name);
		if (entry != obmap_.end()) {
			auto& oblist = entry->second;	
			oblist.erase(pOb);
		}
	}

	void setPrice(const string& name, double price) {
		const auto& entry = stocks_.find(name);
		if (entry != stocks_.end())	{
			auto& pStock = entry->second;
			if (fabs(pStock->getPrice() - price ) > EPS ) {
				auto& oblist = obmap_[name];
				for(auto& ob: oblist) {
					ob->onPriceChaned(*entry->second);				
				}
			}
		}	
	}

	private:
	StockMap stocks_;
	ObMap obmap_;
};


int main(int argc, char* argv[]) {
	Market market;
	{
		market.addStock(make_shared<Stock>("a", 1.1));
		market.addStock(make_shared<Stock>("b", 2.2));
		market.addStock(make_shared<Stock>("c", 3.3));

		shared_ptr<StockObserver>	investorA = make_shared<Investor>("InvestorA");
		shared_ptr<StockObserver>	investorB = make_shared<Investor>("InvestorB");
		shared_ptr<StockObserver>	admin    = make_shared<Admin>("Admin");

		market.registerStockOb("a", investorA);
		market.registerStockOb("a", investorB);
		market.registerStockOb("a", admin);

		market.registerStockOb("b", admin);
		market.registerStockOb("b", investorB);

		market.registerStockOb("c", investorA);
		market.registerStockOb("c", admin);

		cout<<endl;
		market.setPrice("a", 1.2);
		cout<<endl;
		market.setPrice("b", 2.3);
		cout<<endl;
		market.setPrice("c", 3.4);
		cout<<endl;

		market.unregisterStockOb("a", investorA);
		market.unregisterStockOb("c", investorA);

		market.setPrice("a", 1.5);

	}
	cout<<endl<<"main finished"<<endl<<endl;
}
