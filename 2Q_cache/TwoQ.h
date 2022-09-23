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

    Q_cache (size_t sz) : sz_(sz) {}

    ~Q_cache () {}

    bool    full () const 
    {return (cache_.size() == sz_);}

    bool    miss (KeyT key) const 
    {return (hash_.find(key) == hash_.end());}

    void    push_front          (KeyT key)
    {
        cache_.push_front(key);
        hash_[key] = cache_.begin();
    }

    void    pop_back            ()
    {
        auto tmp = cache_.back();
        cache_.pop_back();
        hash_.erase(tmp);
    }

    void    pop_elem            (KeyT key)
    {
        auto tmp = hash_.find(key);
        cache_.erase(tmp);
        hash_.erase(tmp);
    }
};

template <typename T, typename KeyT = int> class TwoQ_cache
{
    size_t sz_;
    Q_cache<T, KeyT> lru;
    Q_cache<T, KeyT> que;

    public:

    TwoQ_cache(size_t sz) : sz_(sz), lru(sz), que(sz) {}

    ~TwoQ_cache() {}
    
    template <typename F> bool lookup_update (KeyT key, F slow_get_page)
    {
        if (lru.miss(key))
        {
            if (lru.full())
            {
                if (que.miss(key))
                {
                    if (que.full())
                    {
                        que.pop_back();
                    }
                    que.push_front(slow_get_page(key));

                    return false;
                }
                else
                {
                    bring_out(key);
                }                
            }
            else
            {
                lru.push_front(slow_get_page(key));

                return false;
            }
        }
        else
        {
            lru.pop_elem(key);
            lru.push_front(key);
        }

        return true;
    }
  
    private:

    void bring_out (KeyT key)
    {
        que.pop_elem(key);
        lru.push_front(key);
    }
};

};

#endif