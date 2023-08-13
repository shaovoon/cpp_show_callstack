## C++23 Exception Class with Callstack

C++23 Standard ratified this year has introduced a `stacktrace` class that retrieves the call stack trace. The `stacktrace` can aid in troubleshooting during exceptions. Therefore I derived `Cpp23ExceptionWithCallstack` from `std::runtime_error` and added `stacktrace` as a member to get the trace information. My `stacktrace` usage heavily relies on Stephan T. Lavavej’s [Godbolt example](https://godbolt.org/z/MWfxKj43a).

Here is an example of how to use `Cpp23ExceptionWithCallstack`.

```Cpp
#include <iostream>
#include "Cpp23ExceptionWithCallstack.h"

using namespace std;

int inner(const int n)
{
    if (n < 0) 
    {
        throw Cpp23ExceptionWithCallstack{"Error"};
    }
    return n * n;
}

int outer(const int n) 
{
    return inner(n);
}

int main() 
{
    try 
    {
        cout << outer(-5) << "\n";
    }
    catch (const Cpp23ExceptionWithCallstack& except) 
    {
        cout << except.GetCallstack() << std::endl;
    }
    return 0;
}
```

The call stack output is as follows. Make sure to put the executable’s pdb file in the same folder to get function names in the output.

```
Cpp23CallStack!inner+0x3A, D:\GitHub\cpp_show_callstack\Cpp23CallStack\Cpp23CallStack.cpp(11)
Cpp23CallStack!outer+0x29, D:\GitHub\cpp_show_callstack\Cpp23CallStack\Cpp23CallStack.cpp(18)
Cpp23CallStack!main+0x37, D:\GitHub\cpp_show_callstack\Cpp23CallStack\Cpp23CallStack.cpp(22)
Cpp23CallStack!invoke_main+0x39, D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl(79)
Cpp23CallStack!__scrt_common_main_seh+0x12E, D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl(288)
Cpp23CallStack!__scrt_common_main+0xE, D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl(331)
Cpp23CallStack!mainCRTStartup+0xE, D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_main.cpp(17)
KERNEL32!BaseThreadInitThunk+0x1D, unknown(0)
ntdll!RtlUserThreadStart+0x28, unknown(0)
```

## C++ Exception Class with Callstack (Windows only)

What if you are not using C++23? Fret not. I have another C++ exception class, `CppExceptionWithCallstack`, based on [StackWalker](https://github.com/JochenKalmbach/StackWalker), created by [Jochen Kalmbach](https://github.com/JochenKalmbach), that relies on the Windows debugging API to do its work. In the beginning, I encountered a weird problem when `StackWalker` printed the full call stack in the first run and only the first function printed in the subsequent runs. I debugged the problem and found nothing is wrong in its operations: it reports no function caller after the first one. I filed this [issue](https://github.com/JochenKalmbach/StackWalker/issues/55) at StackWalker GitHub. Since then, I did not have this problem. If you encounter the same problem, please let me know.

Here is an example of how to use `CppExceptionWithCallstack`.

```Cpp
#include <iostream>
#include "CppExceptionWithCallstack.h"

using namespace std;

int inner(const int n) 
{
    if (n < 0) 
    {
        throw CppExceptionWithCallstack{"Error"};
    }
    return n * n;
}

int outer(const int n) 
{
    return inner(n);
}

int main() 
{
    try 
    {
        cout << outer(-5) << "\n";
    }
    catch (const CppExceptionWithCallstack& except) 
    {
        cout << except.GetCallstack() << std::endl;
    }
    return 0;
}
```

This is the call stack output. Do note that, as mentioned above, you must put the executable’s pdb file in the program’s folder to get the function names in the output.

```
D:\GitHub\cpp_show_callstack\WinCallStack\StackWalker.cpp (1140): StackWalker::ShowCallstack
D:\GitHub\cpp_show_callstack\WinCallStack\CppExceptionWithCallstack.h (19): CppExceptionWithCallstack::CppExceptionWithCallstack
D:\GitHub\cpp_show_callstack\WinCallStack\WinCallStack.cpp (10): inner
D:\GitHub\cpp_show_callstack\WinCallStack\WinCallStack.cpp (18): outer
D:\GitHub\cpp_show_callstack\WinCallStack\WinCallStack.cpp (24): main
D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl (79): invoke_main
D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl (288): __scrt_common_main_seh
D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl (331): __scrt_common_main
D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_main.cpp (17): mainCRTStartup
00007FFF7E7226AD (KERNEL32): (filename not available): BaseThreadInitThunk
00007FFF7F14AA68 (ntdll): (filename not available): RtlUserThreadStart
```
