strace
按照strace官网的描述, strace是一个可用于诊断、调试和教学的Linux用户空间跟踪器。我们用它来监控用户空间进程和内核的交互，比如系统调用、信号传递、进程状态变更等。

dup

telnet

pipe no block

当读管道时，如果管道中没有数据，则会阻塞，直到管道另一端写入数据。

当写管道时，如果管道中已经满了，则会阻塞，直到管道另一端读出数据(读出的数据会从管道中清除)。
send/write recv/read difference
