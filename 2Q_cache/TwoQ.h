#ifndef TWOQ_H
#define TWOQ_H

#include <iostream>
#include <list>
#include <unordered_map>

namespace caches
{
    
template <typename T, typename KeyT = int> class Q_cache
{
    size_t sz_;

    std::list<T> cache_;

    using ListIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    public:

    Q_cache(size_t sz) : sz_(sz) {}

    ~Q_cache() {}

    bool full() const {return (cache_.size == sz_);}

    void    push_front          (KeyT key);

    void    pop_back            ();

    void    pop_elem            (KeyT key);
};

template <typename T, typename KeyT = int> class TwoQ_cache
{
    size_t sz_;
    Q_cache<T, KeyT> lru;
    Q_cache<T, KeyT> que;

    public:

    TwoQ_cache(size_t sz) : sz_(sz), lru(sz), que(sz) {}

    ~TwoQ_cache() {}
    
    template <typename F> bool lookup_update (KeyT key, F slow_get_page);
  
    private:

    void bring_out (KeyT key);
};

}

#endif