# 重复定义

## 错误信息 :
```shell
/home/scapy/extdisk/vsomeip_v3/prebuilts/gcc/linux-x86/x86_64/x86_64-linux-glibc2.23-10.2.0/bin/../lib/gcc/x86_64-linux-gnu/10.2.0/../../../../x86_64-linux-gnu/bin/ld: out/target/ap_x86_64/x86_64/obj/EXECUTABLES/sm_sample_intermediates/src/trigger-for-aa/trigggerInfgsserver.o:(.bss+0x40): multiple definition of `ara::sm::functionGroupsMap[abi:cxx11]'; out/target/ap_x86_64/x86_64/obj/EXECUTABLES/sm_sample_intermediates/tests/sm_sample/sm_sample.o:(.bss+0x40): first defined here
```

## 错误重现：
g++ -g src1.cpp src2.cpp

## 解释 :
#include literally copies and pastes the contents of the header into the other file.

## correction :
如果非要在头文件中使用变量，则在变量前加 extern， 然后把相关的变量放到一个cpp文件中
