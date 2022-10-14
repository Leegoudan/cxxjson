# cxxJSON

![GitHub](https://img.shields.io/github/license/Leegoudan/cxxjson)

`cxxJSON` is a `JSON` library based on C++2x standard. (yet another C++ homework)

## Feature
  - parsing based on PEG
  - used C++20(or later) language and library features where possible
  - head-only
  - supported standards:
    - [RFC8259](https://datatracker.ietf.org/doc/html/rfc8259): JSON Data Interchange Format.
    - [RFC6901](https://datatracker.ietf.org/doc/html/rfc6901): JSON Pointer.
    - [RFC6902](https://datatracker.ietf.org/doc/html/rfc6902): JSON Patch.
  - supported 128bit arithmetic type, only supported char8_t(or same size) charactor type.

## Build
  - vs2022, /std:c++latest
  - gcc12, -std=c++2b
  - clag13, -std=c++latest
## Example usage

## Thank You
  [The Art of C++](https://taocpp.github.io/) and their `PEGTL` library and `JSON` library.


## Licenses
`cxxJSON` is certified [Open Source](http://www.opensource.org/docs/definition.html)software. It is distributed under the terms of the [**BSL-1.0**](https://www.boost.org/LICENSE_1_0.txt).
`cxxJSON` contains modified portions some papers:
  - [Packrat Parsing](https://bford.info/pub/lang/packrat-icfp02.pdf)
  - [Incremental Packrat Parsing](https://dl.acm.org/doi/10.1145/3136014.3136022)
  - [Proxy: A Polymorphic Programming Library](http://wg21.link/p0957)

and open source librarys which is licensed as follows:
  - [tao/json](https://github.com/taocpp/json):
    >  Copyright (c) 2015-2022 Dr. Colin Hirsch and Daniel Frey
    >
    > Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    >
    > The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    >
    > THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  - [Ryu](https://github.com/ulfjack/ryu):
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
  
  - [James Edward Anhalt III's itoa library](https://github.com/jeaiii/itoa):
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
