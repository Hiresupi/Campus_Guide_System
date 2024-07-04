#pragma once

//通过预编译去掉Unicode字符集 改成多字节
#ifdef UNICODE
#undef UNICODE
#endif

#include<easyx.h>
#include<string>