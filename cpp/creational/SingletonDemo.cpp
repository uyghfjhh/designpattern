//author sbkun
#include <stdio.h>
#include <iostream>

using namespace std;

class EagerSingleton {
public:
	static EagerSingleton& getInstance() {
		cout<<"EagerSingleton init"<<endl;
		return instance;
	}
	
	void foo() {
		cout<<"in foo"<<endl;
	}

private:
	static EagerSingleton instance;
	EagerSingleton() {
		cout<<"EagerSingleton construct"<<endl;
	}
  ~EagerSingleton() {
		cout<<"EagerSingleton destruct"<<endl;
	}
	EagerSingleton(const EagerSingleton& ) = delete;
	EagerSingleton& operator=(const EagerSingleton&) = delete;
};

EagerSingleton EagerSingleton::instance;

class LazySingleton {
public:
	//c++11 保证instance的初始化是线程安全的
	//但是c++03不是
	//具体见：https://stackoverflow.com/questions/335369/finding-c-static-initialization-order-problems/335746#335746
	//如过不用c++11，要写出能延迟加载,线程安全的单例，就得使用内存屏障(memory barrier)，或者pthread_once等手段。
	//和java一样DCL(双重检测)也存在指令重排问题
	static LazySingleton& getInstance() {
		static LazySingleton instance;
		return instance;
	}	

	void foo() {
		cout<<"in foo"<<endl;
	}

private:
	LazySingleton() {
		cout<<"LazySingleton construct"<<endl;
	}
	LazySingleton (const LazySingleton& ) = delete;
	LazySingleton& operator=(const LazySingleton&) = delete;
};

int main(int argc, char* argv[])
{
	cout<<"in main"<<endl;
//	EagerSingleton::getInstance().foo();
	LazySingleton::getInstance().foo();

	return 0;
}
