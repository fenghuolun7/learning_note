#include <algorithm>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

class Subject;

class Observer : public std::enable_shared_from_this<Observer>
{
public:
  virtual ~Observer();
  Observer() = default;
  Observer(int id) : id(id) {}
  virtual void update() = 0;

  void observe(const std::shared_ptr<Subject> &s);
  void read();
  void write();
  int id;
  int value = 0;

protected:
  std::shared_ptr<Subject> subject_;

private:
  mutable std::mutex mutex_;
};

class Subject
{
public:
  int id;
  int value = 0;
  Subject() = default;
  Subject(int id) : id(id) {}
  void register_(const std::weak_ptr<Observer> &x);
  void unregister();

  void notifyObservers()
  {
    std::lock_guard<std::mutex> lk(mutex_);
    for (auto it = observers_.begin(); it != observers_.end();)
    {
      if (!it->expired())
      {
        std::shared_ptr<Observer> obj(it->lock());
        obj->update();
        ++it;
      }
      else
      {
        printf("notifyObservers() erase\n");
        it = observers_.erase(it);
      }
    }
  }

private:
  mutable std::mutex mutex_;
  std::vector<std::weak_ptr<Observer>> observers_;
};

Observer::~Observer()
{
  subject_->unregister();
}

void Observer::observe(const std::shared_ptr<Subject> &s)
{
  s->register_(shared_from_this());
  subject_ = s;
}

void Subject::register_(const std::weak_ptr<Observer> &x)
{
  // i guess here use_count is 2
  std::lock_guard<std::mutex> lk(mutex_);
  observers_.push_back(x);
}

void Subject::unregister()
{
  std::lock_guard<std::mutex> lk(mutex_);
  for (auto it = observers_.begin(); it != observers_.end();)
  {
    // ??? not so sure
    if (it->expired())
    {
      printf("notifyObservers() erase\n");
      it = observers_.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

// ---------------------

class Foo : public Observer
{
public:
  Foo(int id) : Observer(id) {}

  virtual void update()
  {
    printf("Foo::update() %p\n", this);
    std::cout << "foo id is : " << id << std::endl;
  }
};

void process(std::shared_ptr<Foo> sp, std::shared_ptr<Subject> subject)
{
  sp->observe(subject);
  // std::this_thread::sleep_for(std::chrono::seconds(5));
}

void doit(const std::shared_ptr<Subject> &x)
{
  std::cout << "id is " << x->id << std::endl;
  (x->value)++;
  std::cout << "value is " << x->value << std::endl;
}

void Observer::read()
{
  std::shared_ptr<Subject> localPtr;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    localPtr = subject_; // read globalPtr
  }
  // use localPtr since here，读写localPtr 也无须加锁
  doit(localPtr);
}

void Observer::write()
{
  std::shared_ptr<Subject> newPtr(new Subject); // 注意，对象的创建在临界区之外
  std::shared_ptr<Subject> localPtr(new Subject);
  newPtr->value = 11;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (subject_.use_count() >= 2)
      subject_ = newPtr; // write to globalPtr
    else
      newPtr.swap(subject_);
  }
  // use newPtr since here，读写newPtr 无须加锁
  doit(newPtr);
}

int main()
{
  std::shared_ptr<Subject> subject(new Subject(1));

  std::shared_ptr<Foo> p1(new Foo(1));
  std::shared_ptr<Foo> p2(new Foo(2));

  std::thread t1(process, p1, subject);
  t1.join();
  // when it exit, I guess user_count is 2;
  std::thread t2(process, p2, subject);
  t2.join();
  subject->notifyObservers();

  // guess : it is the pointer that should be passed
  // std::thread t3(&Foo::read, &p1);

  std::cout << "#################################" << std::endl;
  std::thread t3(&Foo::read, p1);
  std::thread t7(&Foo::read, p1);
  std::thread t4(&Foo::read, p2);
  // std::thread t5(&Foo::write, p1);
  // std::thread t6(&Foo::write, p2);
  t3.join();
  t7.join();
  t4.join();
  // t5.join();
  // t6.join();

  // process(p1, subject);
  // process(p2, subject);
}