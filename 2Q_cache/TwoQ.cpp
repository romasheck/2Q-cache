#include "TwoQ.h"

using namespace caches;

//Q_cache methods
template <typename T, typename KeyT>
inline void Q_cache<T, KeyT>::pop_elem(KeyT key)
{
    auto tmp = hash_.find(key);
    cache_.erase(tmp);
    hash_.erase(tmp);
}

template <typename T, typename KeyT>
inline void Q_cache<T, KeyT>::push_front(KeyT key)
{
    cache_.push_front(key);
    hash_[key] = cache_.begin();
}

template <typename T, typename KeyT>
inline void Q_cache<T, KeyT>::pop_back()
{
    auto tmp = cache_.back();
    cache_.pop_back();
    hash_.erase(tmp);
}

//TwoQ_cache methods
template <typename T, typename KeyT>
inline void TwoQ_cache<T, KeyT>::bring_out (KeyT key)
{
    que.pop_elem(key);
    lru.push_front(key);
}

template <typename T, typename KeyT>
template <typename F>
inline bool TwoQ_cache<T, KeyT>:: lookup_update (KeyT key, F slow_get_page)
{
    if (lru.hash_.find(key) == lru.hash_.end())
    {
        if (lru.full())
        {
            if (que.hash_.find(key) == que.hash_.end())
            {
                if (que.full)
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