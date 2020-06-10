//author sbkun
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Icon {
public:
	explicit Icon(const string& name) : name_(name) 
	{}

	void draw(){
		cout<<"icon ["<<name_<<"] draw"<<endl; 	
	}
private:
	string name_;	
};

class IconFactory{
	public:
	Icon* getIcon(const string& name) {
		auto it = icons_.find(name);
		if (it != icons_.end()) {
			return it->second;
		}

		Icon* icon = new Icon(name);
		icons_[name] = icon;
		return icon;
	}

	static IconFactory& getInstance() {
		static IconFactory instance;
		return instance;
	}
	private:
	IconFactory() = default;
	map<string, Icon*>	icons_;
};

int main(int argc, char* argv[])
{
	Icon* icon1 = IconFactory::getInstance().getIcon("sbkun");
	icon1->draw();

	Icon* icon2 = IconFactory::getInstance().getIcon("sbkun");
	icon2->draw();

	return 0;
}
