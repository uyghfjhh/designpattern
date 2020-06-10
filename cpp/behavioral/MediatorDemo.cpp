//sbkun
#include "noncopyable.h"

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <assert.h>

using namespace std;
class ChatRoom;

class User: noncopyable {
	public:
		User(const string& name);
		~User();

		void send(const string& msg);
		void recv(const string& msg);

		void setRoom(weak_ptr<ChatRoom> room) {
			room_ = room;
		}

		const string& getName() const {
			return name_;
		}

	private:
		string name_;
		weak_ptr<ChatRoom> room_;
};

//mediator
class ChatRoom : noncopyable, public enable_shared_from_this<ChatRoom>{
	public:
		typedef map<string, weak_ptr<User>> Room;

		ChatRoom(const string& name) : name_(name) {
		}

		~ChatRoom() {
			cout<<this<<" "<<name_<<" destruct"<<endl;
		}

		void addRoom(shared_ptr<User> user) {
			room_[user->getName()] = user;
			user->setRoom(shared_from_this());
		}
	

		void send( const string& msg, const string& userName) {
			for(auto const& it: room_) {
				auto pUser = it.second.lock();
				if (pUser) {
					//自己不用收自己的消息	
					if (pUser->getName() != userName) {
						pUser->recv(msg);
					}
				}
			}
		}

		const string& getName() const {
			return name_;
		}

		void removeUser(const string& userName) {
			auto it = room_.find(userName);					
			if (it != room_.end()) {
				room_.erase(it);
				cout<<"erase "<<userName<<" "<<name_<<" remain user num "<<room_.size()<<endl;
			}
		}

	private:
		Room room_;
		string name_;
};

User::User(const string& name) : name_(name)
{
}

void User::send(const string& msg) {
	shared_ptr<ChatRoom> pRoom = room_.lock();
	if (pRoom) {
		cout<<name_<<" send "<<msg<<" to "<<pRoom->getName()<<endl;
		pRoom->send(msg, name_);
	}
}

void User::recv(const string& msg) {
	shared_ptr<ChatRoom> pRoom = room_.lock();
	if (pRoom) {
		cout<<getName()<<" recv "<<msg<<" from "<<pRoom->getName()<<endl;
	}
}

User::~User() {
	cout<<this<<" "<<name_<<" destruct"<<endl;
	shared_ptr<ChatRoom> p = room_.lock();
	if (p) {
		p->removeUser(name_);
	}
}

void test() {

	auto user1 = make_shared<User>("user1");
	auto user2 = make_shared<User>("user2");
	auto user3 = make_shared<User>("user3");
	auto user4 = make_shared<User>("user4");
	auto user5 = make_shared<User>("user5");

	auto chat1 = make_shared<ChatRoom>("chat1");
	auto chat2 = make_shared<ChatRoom>("chat2");

	chat1->addRoom(user1);
	chat1->addRoom(user2);

	chat2->addRoom(user3);
	chat2->addRoom(user4);
	chat2->addRoom(user5);

	user1->send("sbkun");

	cout<<endl;

	user3->send("sbkun");

	cout<<endl;
}

void testLongLifeChatroom() {
	auto chat1 = make_shared<ChatRoom>("chat1");
	{
		auto user1 = make_shared<User>("user1");
		auto user2 = make_shared<User>("user2");
		auto user3 = make_shared<User>("user3");

		chat1->addRoom(user1);
		chat1->addRoom(user2);
		chat1->addRoom(user3);

		user1->send("sbkun");
	}
}

void testShortLifeChatroom() {
		auto user1 = make_shared<User>("user1");
		auto user2 = make_shared<User>("user2");
		auto user3 = make_shared<User>("user3");

		{
			auto chat1 = make_shared<ChatRoom>("chat1");
			chat1->addRoom(user1);
			chat1->addRoom(user2);
			chat1->addRoom(user3);

		}
		user1->send("sbkun");
}

int main(int argc, char* argv[])
{
	//testLongLifeChatroom();
	//testShortLifeChatroom();
	test();
	return 0;
}
