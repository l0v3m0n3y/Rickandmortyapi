# Rickandmortyapi
api for Rickandmortyapi.com site for getting info about rick and morty 
# main
```cpp
#include "Rickandmortyapi.h"
#include <iostream>
#include <locale>
#include <codecvt>

int main() {
   Rickandmortyapi api;
    auto episodes = api.get_episode(28).then([](json::value result) {
        std::cout << "Search results: " << result.serialize() << std::endl;
    });
    episodes.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```
