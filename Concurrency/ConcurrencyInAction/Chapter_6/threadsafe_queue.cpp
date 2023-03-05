#include <memory>
#include <iostream>
#include <mutex>

template <typename T>
class Queue
{
private:
    // question:
    // whether without explict constructor is ok ?
    struct Node
    {
        std::unique_ptr<Node> next;
        std::shared_ptr<T> data;

        // Node()
        // {
        //     data = std::make_shared<T>();
        // }

        Node() = default;

        // Node(const T &value)
        // {
        //     // question:
        //     // whether use std::move() here is ok ?
        //     data = std::move(std::make_shared<T>(value));
        // }
        // Node(T &&value)
        // {
        //     // question:
        //     // whether use std::move() here is ok ?
        //     data = std::move(std::make_shared<T>(std::move(value)));
        // }

        Node(T value)
        {
            // question:
            // whether use std::move() here is ok ?
            // data = std::move(std::make_shared<T>(std::move(value)));
            data = std::make_shared<T>(std::move(value));
        }

        Node(const Node &node) = delete;

        Node(Node &&node)
        {
            this->next = std::move(node.next);
            this->data = std::move(data);
        }
    };

    std::unique_ptr<Node> unique_tail;
    Node *tail = nullptr;
    Node *head = nullptr;

public:
    // Queue() : tail(std::make_unique<Node>().get()), head(tail) {}
    Queue()
    {
        unique_tail = std::make_unique<Node>();
        tail = unique_tail.get();
        head = tail;
    }
    // Queue() : tail(new Node()), head(tail) {}

    Queue(const Queue &) = delete;

    Queue(Queue &&);

    void push(T value)
    {
        // std::unique_ptr<Node> new_node (new Node(value));
        std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
        tail->next = std::move(new_node);
        tail = (tail->next).get();
    }

    std::shared_ptr<T> try_pop()
    {
        if (head == tail)
            return std::shared_ptr<T>();
        std::unique_ptr<Node> poped_node = std::move(head->next);
        std::shared_ptr<T> res = std::move(poped_node->data);
        head->next = std::move(poped_node->next);
        return res;
    }

    // ~Queue(){
    //     delete tail;
    //     delete head;
    // }
};

int main()
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    std::shared_ptr<int> a = q.try_pop();
    std::cout << *a << std::endl;

    std::shared_ptr<int> b = q.try_pop();
    std::cout << *b << std::endl;
    std::shared_ptr<int> c = q.try_pop();
    std::cout << *c << std::endl;
}