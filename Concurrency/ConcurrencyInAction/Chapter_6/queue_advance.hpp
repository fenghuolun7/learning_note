#include <memory>
#include <mutex>
#include <thread>

template <typename T>
class threadsafe_list {
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr next;
    mutable std::mutex mutex_;

    node() = default;

    node(T value) { data = std::make_shared<T>(std::move(value)); }
  };

  node* head;

 public:
  threadsafe_list() : head(new node()) {}

  ~threadsafe_list() {}

  threadsafe_list(threadsafe_list const& other) = delete;
  threadsafe_list& operator=(threadsafe_list const& other) = delete;

  void push_front(T const& value) {
    auto new_node = std::make_unique<node>(value);
    std::unique_lock lock1{head->mutex_, std::defer_lock};
    std::unique_lock lock2{head->next->mutex_, std::defer_lock};
    // lock both unique_locks without deadlock
    std::lock(lock1, lock2);
    new_node->next = std::move(head->next);
    head->next = std::move(new_node);
  }

  template <typename Function>
  void for_each(Function f) {
    std::unique_lock lk(head->mutex_);
    node* p = head;
    while (p->next != nullptr) {
      f(*p->data);
      p = p->next.get();
      lk = head->next->mutex_;
    }
  }

  template <typename Predicate>
  std::shared_ptr<T> find_first_if(Predicate p) {
    std::unique_lock lk(head->mutex_);
    node* q = head;
    while (q->next != nullptr) {
      if (p(*q->data))
        return q->data;
      else {
        p = p->next.get();
        lk = head->next->mutex_;
      }
    }
    return std::shared_ptr<T>();
  }

  template <typename Predicate>
  void remove_if(Predicate p) {
    std::unique_lock lk(head->mutex_);
    node* q = head;
    while (q->next != nullptr) {
      if (p(*q->data))
         std::unique_lock lk(head->next->mutex_);
      else {
        p = p->next.get();
        lk = head->next->mutex_;
      }
    }
    return std::shared_ptr<T>();
  }
};
