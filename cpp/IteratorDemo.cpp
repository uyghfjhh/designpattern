//author sbkun
#include <vector>
#include <iostream>
#include <string>
using namespace std;

template<class Iter>
struct iter_traits {
    typedef typename Iter::value_type value_type;
};

template<class Type>
struct iter_traits<Type *> {
    typedef Type value_type;
};

template<class Iterator>
class my_reverse_iterator {
public:
    typedef typename iter_traits<Iterator>::value_type value_type;
    typedef my_reverse_iterator<Iterator> self;

    explicit my_reverse_iterator(Iterator i) : current_(i) {
    }

    Iterator base() const {
        return current_;
    }

    //因为current_ 最初指向的是MyArrary的end_
    value_type operator*() {
        return *(current_ - 1);
    }

    self &operator++() {
        --current_;
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        --current_;
        return tmp;
    }

private:
    Iterator current_;
};

template<class T>
class MyArrary {
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef class my_reverse_iterator<iterator> my_reverse_iterator;

    //need c++11
    MyArrary(std::initializer_list<T> l) {
        range_init(l.begin(), l.end());
    }

    template<class Iter>
    void range_init(Iter first, Iter last) {
        init_space(static_cast<size_t>(last - first));
        std::copy(first, last, begin_);
    }

    void init_space(size_t size) {
        begin_ = new T[size];
        end_ = begin_ + size;
    }

    iterator begin() {
        return begin_;
    }

    iterator end() {
        return end_;
    }

    my_reverse_iterator rend() {
        return my_reverse_iterator(begin());
    }

private:
    T *begin_;
    T *end_;
};

template<class Iterator>
bool operator==(const my_reverse_iterator<Iterator> &lhs,
                const my_reverse_iterator<Iterator> &rhs) {
    return lhs.base() == rhs.base();
}


template<class Iterator>
bool operator!=(const my_reverse_iterator<Iterator> &lhs,
                const my_reverse_iterator<Iterator> &rhs) {
    return !(lhs.base() == rhs.base());
}

void vector_test() {
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int>::iterator it = v.begin();
    for (; it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    vector<int>::reverse_iterator it1(v.end());
    for (; it1 != v.rend(); ++it1) {
        cout << *it1 << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    MyArrary<int> arrary = {1, 2, 3, 4, 5};
    MyArrary<int>::iterator it = arrary.begin();
    for (; it != arrary.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    MyArrary<int>::my_reverse_iterator it1(arrary.end());
    for (; it1 != arrary.rend(); ++it1) {
        cout << *it1 << " ";
    }
    cout << endl;

    return 0;
}
