| instruction | type       | size |
|-------------|:----------:|-----:|
| movb        | char       | 1    |
| movw        | short      | 2    |
| movl        | int        | 4    |
| movq        | long char* | 8    |
## float and double is another thing
| instruction | type       | size |
|-------------|:----------:|-----:|
| movs        | int        | 4    |
| movq        | long char* | 8    |


###register
%eax  return value 
%ebx  saved by callee
%ebp  saved by callee
%esp  stack pointer
%r10b saved by caller
%r11b saved by caller
%r12b saved by callee
%r13b saved by callee
%r14b saved by callee
$r15b saved by callee

---

leaq m %rax // %rax<=m

imulq signed mult // i for complement?
mulq unsigned mult
idivq signed div
divq unsigned mult
clto trans to oct word // 16words 128bit




