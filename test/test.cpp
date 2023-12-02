#include "../src/my_vector.hpp"
#include <iostream>
#include <unistd.h>
#include <cassert>

using namespace std;

int main()
{
    my_vector<int> vec(20);
    for(int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }
    
    my_vector<int> vec2(vec);
    
    for(int i = 0; i < vec2.size(); ++i)
    {
        cout << vec2[i] << endl;
    }
    
    
}