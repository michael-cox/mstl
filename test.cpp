#include "vector.hpp"
#include <iostream>

mstl::Vector<int> test() {
    mstl::Vector<int> v;
    v.push_back(7);
    return v;
}

int main() {

    mstl::Vector<int> v;
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);

    std::cout << *v.begin() << ' ' << *v.end() << std::endl;
    std::cout << "Size: " << v.size() << " Capacity: " << v.capacity() << std::endl;
    for(mstl::Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    for(mstl::Vector<int>::iterator it = v.rbegin(); it != v.rend(); --it)
        std::cout << *it << std::endl;

    return 0;
}
