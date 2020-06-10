#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <map>
#include <vector>

using namespace std;

class Stock {
public:
	Stock(const string& name, float price) : name_(name)
																					 , price_(price) {
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

class StockObserver {
	public:
		virtual ~StockObserver() = default;
		virtual void onPriceChaned(const Stock& stock) = 0;
};

class Market{
	using ObSharedPtr = shared_ptr<StockObserver>;
	using StockSharedPtr = shared_ptr<Stock>;
	using StockMap = map<string, StockSharedPtr>;
	using ObMap =  map<string, vector<ObSharedPtr>>;

	public:
	Market() {
		stocks_["a"] = make_shared<Stock>("a", 1.1);
		stocks_["b"] = make_shared<Stock>("b", 2.2);
	}

	void registerStockOb(const string& name, ObSharedPtr pOb) {

	}
	void unregisterStockOb(const string& name, ObWeakPtr pOb) {

	}

	private:
	StockMap stocks_;
	ObMap obs_;
};


int main(int argc, char* argv[]) {
}
