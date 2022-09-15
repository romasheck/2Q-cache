# 2Q-cache
Realization of simple version 2Q algorithm

Brief about the algorithm:
It is like LRU strategy, but have second queue. When the program faces a page, which is not placed in lru-queue (just "lru") and scnd-queue (just "que"), this page will be placed in que and the  last page in que will deleted from cache. When the program faces a page, which is not placed in lru, but is placed in que, this page will be placed in lru and deleted from que. When ..., which is placed in lru, program will behave as just LRU algorithm.

The first doing in real C++
Delighted and interested experience are recieved and good, modular program was created.
