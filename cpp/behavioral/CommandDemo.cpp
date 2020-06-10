#include <iostream>
#include <functional>

using namespace std;

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class Tv {
	public: 
	void on() {
		cout<<"tv on"<<endl;
	}	
	void off() {
		cout<<"tv off"<<endl;
	}
	void watch(const string& channel) {
		cout<<"watch "<<channel<<endl;
	}
};

class TvOffCommand: public Command {
	public:
		TvOffCommand(Tv* tv): tv_(tv) {
		}
		void execute() override {
			tv_->off();	
		}
	private:
		Tv* tv_;
};

class TvWatchCommand: public Command{
	public:
	TvWatchCommand(Tv* tv, const string& channel) : tv_(tv) 
																								, channel_(channel){
	}

	void execute () override {
		tv_->on();
		tv_->watch(channel_);
	}

	private:
		Tv* tv_;
		string channel_;
};
void testCommandPattern() {
	cout<<__func__<<endl;

	Tv* tv = new Tv;

	Command* watch = new TvWatchCommand(tv, "cctv");
	Command* off = new TvOffCommand(tv);

	watch->execute();
	off->execute();
	
	delete tv;
	delete off;
	delete watch;
}

//c++11的bind/function ,lambda 也可以实现命令模式的意图，
//且更加灵活
void testBindFunction() {
	cout<<__func__<<endl;

	Tv tv;

	function<void(void)> tvOff= bind(&Tv::off, &tv);
	function<void(const string&)> watchTv = [&tv](const string& channel) {
		tv.on();
		tv.watch(channel);
	};

	watchTv("cctv");
	tvOff();
}

int main(int argc, char* argv[]) {
	testCommandPattern();
	cout<<endl<<"====="<<endl<<endl;
	testBindFunction();
	return 0;
}
