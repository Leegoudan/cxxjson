# cxxJSON

![GitHub](https://img.shields.io/github/license/Leegoudan/cxxjson)

`cxxJSON`是一个C++2x标准编写`JSON` library (C++ homework)

## Feature
  - based on PEG
  - 使用C++20或更新标准
  - head-only
  - 支持json标准：
    - [RFC8259](https://datatracker.ietf.org/doc/html/rfc8259): JSON Data Interchange Format.
    - [RFC6901](https://datatracker.ietf.org/doc/html/rfc6901): JSON Pointer.
    - [RFC6902](https://datatracker.ietf.org/doc/html/rfc6902): JSON Patch.
  - 仅支持char8_t类型(或相同大小)字符

## Build
  - vs2022, /std:c++latest
  - gcc12, -std=c++2b
  - clag13, -std=c++latest
## Example usage

## Thank You
  本项目学习于[The Art of C++](https://taocpp.github.io/)的`PEGTL`库和`JSON库`

## Licenses
`cxxJSON`符合[Open Source](http://www.opensource.org/docs/definition.html)定义，以[**BSL-1.0**](https://www.boost.org/LICENSE_1_0.txt)协议发布。
`cxxJSON`还引用、修改一些论文和开源项目：
  - [Packrat Parsing](https://bford.info/pub/lang/packrat-icfp02.pdf)
  - [Incremental Packrat Parsing](https://dl.acm.org/doi/10.1145/3136014.3136022)
  - [Proxy: A Polymorphic Programming Library](http://wg21.link/p0957)
  - [tao/json](https://github.com/taocpp/json) 协议如下:
    >  Copyright (c) 2015-2022 Dr. Colin Hirsch and Daniel Frey
    >
    > Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    >
    > The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    >
    > THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  - [Ryu](https://github.com/ulfjack/ryu) 协议如下:
    > Copyright 2018 Ulf Adams
    >
    > The contents of this file may be used under the terms of the Apache License, Version 2.0.
    >
    >    (See accompanying file LICENSE.ryu or copy at
    >     http://www.apache.org/licenses/LICENSE-2.0)
    >
    > Alternatively, the contents of this file may be used under the terms of the Boost Software License, Version 1.0.
    >    (See accompanying file LICENSE-Boost or copy at
    >     https://www.boost.org/LICENSE_1_0.txt)
    >
    > Unless required by applicable law or agreed to in writing, this software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  
  - [James Edward Anhalt III's itoa library](https://github.com/jeaiii/itoa) 协议如下：
    > Copyright (c) 2017 James Edward Anhalt III - https://github.com/jeaiii/itoa
    >
    > Permission is hereby granted, free of charge, to any person obtaining a copy
    > of this software and associated documentation files (the "Software"), to deal
    > in the Software without restriction, including without limitation the rights
    > to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    > copies of the Software, and to permit persons to whom the Software is
    > furnished to do so, subject to the following conditions:
    >
    > The above copyright notice and this permission notice shall be included in all
    > copies or substantial portions of the Software.
    >
    > THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    > IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    > FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    > AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    > LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    > OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    > SOFTWARE.
