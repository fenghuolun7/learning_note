#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <iostream>
#include <memory>

template <typename CallBackArgs>
class Slot;

using GlobalSlot = std::shared_ptr<void>;
GlobalSlot global_slot;

template <typename CallBackArgs>
class SignalImpl
{
};

template <typename Ret, typename... Args>
class SignalImpl<Ret(Args...)> : std::enable_shared_from_this<SignalImpl<Ret(Args...)>>
{
public:
    using CallBack = std::function<Ret(Args...)>;
    using SlotPtr = std::weak_ptr<Slot<Ret(Args...)>>;
    using SlotList = std::vector<std::weak_ptr<Slot<Ret(Args...)>>>;
    using SlotListPtr = std::shared_ptr<SlotList>;

    SignalImpl()
    {
        slot_list_ptr_ = std::make_shared<SlotList>();
    }

    SignalImpl(const SignalImpl &) = delete;

    void copy_on_write()
    {
    }

    GlobalSlot connect(std::shared_ptr<SignalImpl<Ret(Args...)>> signal_, const CallBack &func)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (slot_list_ptr_.use_count() > 1)
        {
            slot_list_ptr_.reset(new SlotList(*slot_list_ptr_));
        }
        auto slot = std::make_shared<Slot<Ret(Args...)>>(signal_, func);
        slot_list_ptr_->push_back(std::forward<SlotPtr>(slot));
        return slot;
    }

    void call(Args &&...args)
    {
        SlotListPtr local_slots_ptr;
        {ssss
            std::lock_guard<std::mutex> lk(mutex_);
            local_slots_ptr = slot_list_ptr_;
        }

        for (auto it = local_slots_ptr->begin(); it != local_slots_ptr->end(); ++it)
        {
            auto slot = it->lock();
            slot->callback_(std::forward<Args>(args)...);
        }
    }

    void clean()
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (slot_list_ptr_.use_count() > 1)
        {
            slot_list_ptr_.reset(new SlotList(*slot_list_ptr_));
        }

        for (auto it = slot_list_ptr_->begin(); it != slot_list_ptr_->end();)
        {
            if (it->expired())
            {
                it = slot_list_ptr_->erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    // notice public here:
public:
    mutable std::mutex mutex_;
    SlotListPtr slot_list_ptr_;
};

template <typename CallBackArgs>
class Signal
{
};

template <typename Ret, typename... Args>
class Signal<Ret(Args...)>
{
public:
    using CallBack = std::function<Ret(Args...)>;
    Signal() : signal_(new SignalImpl<Ret(Args...)>())
    {
    }

    GlobalSlot connect(CallBack &&func)
    {
        auto slot = signal_->connect(signal_, std::forward<CallBack>(func));
        return slot;
    }

    void call(Args &&...args)
    {
        signal_->call(std::forward<Args>(args)...);
    }

    void clean()
    {
        signal_->clean();
    }

private:
    // Impl should not be changed.
    const std::shared_ptr<SignalImpl<Ret(Args...)>> signal_;
};

template <typename CallBackArgs>
class Slot
{
    using SignalPtr = std::shared_ptr<SignalImpl<CallBackArgs>>;

public:
    Slot(const SignalPtr &signal_ptr, const std::function<CallBackArgs> &callback) : signal_ptr_(signal_ptr), callback_(callback)

    {
    }

    Slot(const Slot &) = delete;

    ~Slot()
    {
        auto signal_sptr = signal_ptr_.lock();
        if (signal_sptr)
        {
            signal_sptr->clean();
        }
    }

public:
    std::weak_ptr<SignalImpl<CallBackArgs>> signal_ptr_;
    std::function<CallBackArgs> callback_;
};
