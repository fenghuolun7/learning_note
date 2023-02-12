#include <iostream>
#include <map>
#include <string>
#include <string_view>

void print_map(const std::map<int, std::string> &m)
{
    // C++11 alternative:
    for (const auto &n : m)
        std::cout << n.first << " = " << n.second << "; ";

    std::cout << '\n';
}

int main()
{
    std::map<int, std::string> example_1;
    // the sentence below can also create a key : value pair
    // notice that the value is empty;
    std::string s = example_1[1];

    print_map(example_1);
}