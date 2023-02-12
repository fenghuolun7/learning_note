# Disadvantages and solutions of observer in chapter 1.8
## Invasive
Observer must be manageed by shared_ptr.
### solution:
divide observer into slotimpl and slot. slot holds the sharedptr of slotimpl

## Not fully thread safe
```c++
subject_->unregister(this)
```
requires that object is also managed by shared_ptr.if subject does not exist anymore, the program will not coredump.
### solution:
use weak callback
create a global shared_ptr of subject.

## lock contention
### solution:
copy-on-write technique