#ifndef M_SETH__hh
#define M_SETH__hh
#include <set>

using namespace std;

template <class T1>
class M_SET
{
    set<T1> container;
    _mutex Mutex;
public:
    M_SET():Mutex("M_SET") {}
    set<T1> get_container()
    {
        MUTEX_LOCK kaka(Mutex);
        return container;
    }
    void assign(const set<T1>& m)
    {
        MUTEX_LOCK kaka(Mutex);
        container=m;
    }
    int count(const T1&key)
    {
        MUTEX_LOCK kaka(Mutex);
        return container.count(key);
    }
    void insert(const T1& key)
    {
        MUTEX_LOCK kaka(Mutex);
        container.insert(key);
    }
    void erase(const T1& key)
    {
        MUTEX_LOCK kaka(Mutex);
        typeof(container.begin()) i=container.find(key);
        if (i!=container.end())container.erase(i);
    }
    void clear()
    {
        MUTEX_LOCK kaka(Mutex);
        container.clear();
    }
    int size()
    {
        MUTEX_LOCK kaka(Mutex);
        return container.size();
    }

};

#endif
