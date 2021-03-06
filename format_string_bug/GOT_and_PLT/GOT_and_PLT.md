[Linux动态链接之GOT与PLT](https://www.cnblogs.com/xingyun/archive/2011/12/10/2283149.html)



我们知道函数名就是一个内存地址，这个地址指向函数的入口。调用函数就是压入参数，保存返回地址，然后跳转到函数名指向的代码。问题是，如果函数在共享库中，共享库加载的地址本身就不确定，函数地址也就不确定了，那如何调用共享库中的函数呢？这就是本文要回答的。

我们先来看一小段代码(test.c)：

[![复制代码](http://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

```
#include <stdio.h>

void hello_world(void)
{
    printf("Hello world!\n");

    return;
}

int main(int argc, char* argv[])
{
    hello_world();

    return 0;
}
```

[![复制代码](http://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

```

```

编译并反汇编：

gcc -g test.c -o test
objdump -S test

 

[![复制代码](http://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

```
void hello_world(void)
{
 80483b4:       55                      push   %ebp
 80483b5:       89 e5                   mov    %esp,%ebp
 80483b7:       83 ec 08                sub    $0x8,%esp
        printf("Hello world!\n");
 80483ba:       c7 04 24 b4 84 04 08    movl   $0x80484b4,(%esp)
 80483c1:       e8 2a ff ff ff          call   80482f0 <puts@plt>

        return;
}
 80483c6:       c9                      leave
 80483c7:       c3                      ret

080483c8 <main>:

int main(int argc, char* argv[])
{
 80483c8:       8d 4c 24 04             lea    0x4(%esp),%ecx
 80483cc:       83 e4 f0                and    $0xfffffff0,%esp
 80483cf:       ff 71 fc                pushl  -0x4(%ecx)
 80483d2:       55                      push   %ebp
 80483d3:       89 e5                   mov    %esp,%ebp
 80483d5:       51                      push   %ecx
 80483d6:       83 ec 04                sub    $0x4,%esp
        hello_world();
 80483d9:       e8 d6 ff ff ff          call   80483b4 <hello_world>

        return 0;
 80483de:       b8 00 00 00 00          mov    $0x0,%eax
}
```

[![复制代码](http://common.cnblogs.com/images/copycode.gif)](javascript:void(0);)

 

调用hello_world时，汇编代码对应于call   80483b4 <hello_world>，这是个绝对地址。hello_world是在可执行文件中，可执行文件是加载到一个固定地址的，因此hello_world的地址是确定的。

调用printf时，汇编代码对应于call   80482f0 <puts@plt>，这是个绝对地址。但函数名却是puts@plt，这是怎么回事呢？puts@plt显然是编译器加的一个中间函数，我们看一下这个函数对应的汇编代码：

```
080482f0 <puts@plt>:
 80482f0:   ff 25 2c 96 04 08       jmp    *0x804962c
 80482f6:   68 10 00 00 00          push   $0x10
 80482fb:   e9 c0 ff ff ff          jmp     <_init+0x30>

```

现在我们用调试器分析一下：

gdb test

(gdb) b main
Breakpoint 1 at 0×80483d9: file test.c, line 12.
(gdb) r
Starting program: /root/test/plt/test

Breakpoint 1, main () at test.c:12 12 hello_world();

puts@plt先跳到*0×804962c，我们看看*0×804962c里有什么？
(gdb) x 0×804962c 0×804962c <_GLOBAL_OFFSET_TABLE_+20>:   0×080482f6

*0×804962c等于0×080482f6，这正是puts@plt中的第二行汇编代码的地址。也就是说puts@plt整个函数会顺序执行，直到跳转到0×80482c0.

再来看看0×80482c0处有什么，通过汇编可以看到：
ff 25 20 96 04 08 jmp    *0×8049620

又跳到了*0×8049620，转的弯真多，没关系，我们再看*0×8049620：
(gdb) x 0×8049620 0×8049620 <_GLOBAL_OFFSET_TABLE_+8>:    0×009ce4c0
(gdb) x /wa 0×009ce4c0 0×9ce4c0 <_dl_runtime_resolve>: 0×8b525150

原来转来转去就是为了调用函数_dl_runtime_resolve， _dl_runtime_resolve的功能就是找到要调用函数(puts)的地址。

为什么不直接调用_dl_runtime_resolve，而要转这么多圈子呢？

先执行完这个函数hello_world：
(gdb) n

再回头来看看puts@plt的第一行代码：

80482f0:   ff 25 2c 96 04 08 jmp    *0×804962c

(gdb) x 0×804962c 0×804962c <_GLOBAL_OFFSET_TABLE_+20>:   0xa39a60 <puts>
对比前面的:
(gdb) x 0×804962c 0×804962c <_GLOBAL_OFFSET_TABLE_+20>:   0×080482f6

也就是说第一次执行时，通过_dl_runtime_resolve解析到函数地址，并保存puts的地址到0×804962c里，以后执行时就直接调用了。

