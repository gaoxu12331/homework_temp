# Project4: do your best to optimize SM3 implementation (software)

## 运行环境

操作系统：Ubuntu 22.04.2 LTS 64位

编译环境：C++ 使用 g++ (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0，
不使用编译优化

硬件环境：11th Gen Intel® Core™ i5-1135G7 @ 2.40G   16.0 GiB

## 优化途径

1：SM3杂凑过程中存在诸多“简易步骤”，例如：循环左移、P0置换、P1置换等等。
对于这些操作，我们使用宏来代替函数，通过预处理的方式进行加速。
例如计算循环左移：

``` C

#define lift32(input, n) ((input << n) | (input >> (32 - n)))

```

2：最终生成的杂凑值由上一步得到的V和消息扩展值运算得到。我们发现“消息扩展”步骤
仅仅依赖于输入B，可并行，因此我们将消息扩展进行提前运算，对消息扩展进行自动并行加速。

## 结果展示
