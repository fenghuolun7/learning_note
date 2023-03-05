#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>

template <typename T>
struct Node
{
    std::unique_ptr<Node> next;
    std::shared_ptr<T> data;

    Node() = default;

    Node(T value)
    {
        // question:
        // whether use std::move() here is ok ?
        // data = std::move(std::make_shared<T>(std::move(value)));
        data = std::make_shared<T>(std::move(value));
    }
};

int main()
{
    // when one unique_ptr destructed, and the other take over its
    // content, the address will not change and the destructor of 
    // the managed content will not be called. 
    auto node_ptr = std::make_unique<Node<int>>();
    std::cout << node_ptr.get() << std::endl;
    auto node_ptr_1 = std::move(node_ptr);
    std::cout << node_ptr.get() << std::endl;
    std::cout << node_ptr_1.get() << std::endl;

std::cout << "---------------------------------------" << std::endl;


    auto node_ptr_2 = std::make_unique<Node<int>>(5);
    std::cout << node_ptr_2.get() << std::endl;
    auto node_ptr_3 = std::move(node_ptr_2);
    std::cout << node_ptr_2.get() << std::endl;
    std::cout << node_ptr_3.get() << std::endl;
}