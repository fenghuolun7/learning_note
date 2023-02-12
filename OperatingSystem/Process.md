# ps

RSS is the Resident Set Size
VSZ is the Virtual Memory Size
PRI 
Linux 给予程序一个所谓的优先执行顺序 (priority, PRI)， 这个 PRI 值越低代表越优先的意思。 不过这个 PRI 值是由内核动态调整的，用户无法直接调整 PRI 值的。
LWP 轻量化线程

PCB（进程控制块）

tty 通常使用tty来简称各种类型的终端设备

https://www.arkuu.com/article/198.html

其中STAT状态位常见的状态字符有
D      //无法中断的休眠状态（通常 IO 的进程）； 
R      //正在运行可中在队列中可过行的； 
S      //处于休眠状态； 
T      //停止或被追踪； 
W      //进入内存交换 （从内核2.6开始无效）； 
X      //死掉的进程 （基本很少见）； 
Z      //僵尸进程； 
<      //优先级高的进程 
N      //优先级较低的进程 
L      //有些页被锁进内存； 
s      //进程的领导者（在它之下有子进程）； 
l      //多线程，克隆线程（使用 CLONE_THREAD, 类似 NPTL pthreads）； 
+      //位于后台的进程组；

# ptree


gdb 打断点 可以选择条件分支比如

```
(gdb) b 7 if num>10
```

lsof
