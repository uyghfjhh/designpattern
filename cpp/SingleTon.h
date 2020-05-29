#pragma once
template <class T>
class SingleTon
{
public:
    static T &getInstance()
    {
        static T t;
        return t;
    }
    SingleTon(const SingleTon &) = delete;
    SingleTon(SingleTon &&) = delete;
    SingleTon &operator=(const SingleTon &) = delete;
    SingleTon &operator=(SingleTon &&) = delete;

protected:
    virtual ~SingleTon()  = default;
    SingleTon() noexcept  = default;
};

