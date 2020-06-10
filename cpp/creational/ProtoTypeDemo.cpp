#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

class MyString{
	public:
		MyString(const char* str) {
			if (str == NULL)	{
				data_ = new char[1];
				data_[0] = '\0';
			}
			else {
				size_t len = strlen(str);
				data_ = new char[len+1];		
				strcpy(data_, str);	
			}
		}

		~MyString() {
			delete [] data_;
		}

#if 1 //使用默认的拷贝构造，赋值函数，就是浅拷贝
		MyString(const MyString& rhs) {
			size_t len = strlen(rhs.data_);
			data_ = new char[len+1];		
			strcpy(data_, rhs.data_);	
		}

		MyString& operator=(const MyString& rhs) {
			if (this == &rhs) {
				return *this;
			}
			delete [] data_;

			size_t len = strlen(rhs.data_);
			data_ = new char[len+1];		
			strcpy(data_, rhs.data_);	

			return *this;
		}
#endif

		void sort() {
			size_t len = strlen(data_);
			std::sort(data_, data_+len-1);
		}

		ostream& print(ostream& os) {
			return os<<data_;
		}

	private:
		char* data_;
};

//等同于java的 toString
	ostream&
operator << (ostream& os, MyString& str)
{
	return str.print(os);
}


int main(int argc, char* argv[])
{	
	MyString str1("cba");
	MyString str2 = str1;
	str1.sort();
	cout<<"str1: "<<str1<<endl;
	cout<<"str2: "<<str2<<endl;
	return 0;
}
