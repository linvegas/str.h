# str.h

A simple abstraction for dynamic strings in C

## Quick Start

Copy `str.h` into your project and include it:

```c
#define STR_IMPLEMENTATION
#include "str.h"

int main()
{
    Str msg = str("Hello, World!");

    printf("%s\n", msg.data);

    return 0;
}
```

For more info, check the `examples` folder.
