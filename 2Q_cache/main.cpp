#include "TwoQ.h"

int slow_get_page_int (int key) {return key;}

int main ()
{
    size_t cache_size = 0;
    size_t number_page = 0;
    std::cin>>cache_size>>number_page;

    caches::TwoQ_cache<int, int> cache_{cache_size};

    int hits = 0;

    int key = 0;
    bool hit_flag = 0;
    for (int i = 0; i <= number_page; i++)
    {
        std::cin>>key;
        
        hit_flag = cache_.lookup_update(key, slow_get_page_int);

        if (hit_flag)
        {
            hits++;
        }
    }

    std::cout<<hits<<std::endl;

    return 0;
}