#include "SingleTon.hpp"
#include <string>
#include <iostream>

using namespace std;

class App : public SingleTon<App>
{
	friend class SingleTon<App>;

	public:

	void showName()
	{
		cout << "name " << endl;
	}

private:
	 App() = default;
};

int main()
{
	App::GetInstance().showName();
	return 0;
}
