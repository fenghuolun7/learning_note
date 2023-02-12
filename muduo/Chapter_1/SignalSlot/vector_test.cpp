#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <iostream>
#include <memory>


using SlotList = std::vector<std::weak_ptr<int>> ;
using SlotListPtr = std::shared_ptr<SlotList>;


int main(){
    SlotListPtr slot_list_ptr_;
    slot_list_ptr_(new SlotList);
}