Benchmarking vim's utf8 implementation
======================================

Tries to get an idea for how good vim's utf8 implementation is and if it
can be improved by swapping it out with an alternative implementation.

To run:

```bash
# fill in the compilers you want to test with
$ edit bench.sh
# run the benchmark
$ ./bench.sh
```

Implementations
===============

- vim's
- [Björn Höhrmann's versions](http://bjoern.hoehrmann.de/utf-8/decoder/dfa/)
- [Taylor R. Campbell's versions](https://github.com/hoehrmann/utf-8-misc)

Results
=======

I have an early 2011 Macbook Pro with a 2GHz core i7 chip (and 16GB
RAM).

Clang 3.4
---------

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/utf8.txt**| **vimCountCodePoints**   | **20.9** | **2.3** | **300.3**
text/utf8.txt  | cmpBranchCountCodePoints |   24.4 ms |             2.3 | 256.7
text/utf8.txt  | bjorn2CountCodePoints    |   27.1 ms |             2.3 | 231.1
text/utf8.txt  | bjorn1CountCodePoints    |   28.6 ms |             2.3 | 219.5
text/utf8.txt  | cmpArithCountCodePoints  |   39.3 ms |             2.3 | 159.8

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/ascii.txt**| **cmpBranchCountCodePoints**| **100.0** | **1.0** | **439.4**
text/ascii.txt | bjorn1CountCodePoints    |  182.6 ms |             1.0 | 240.7
text/ascii.txt | bjorn2CountCodePoints    |  182.4 ms |             1.0 | 241.1
text/ascii.txt | vimCountCodePoints       |  232.3 ms |             1.0 | 189.3
text/ascii.txt | cmpArithCountCodePoints  |  268.4 ms |             1.0 | 163.8

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/enwik8.txt**| **cmpBranchCountCodePoints**| **215.8** | **1.0** | **441.9**
text/enwik8.txt| bjorn1CountCodePoints    |  398.0 ms |             1.0 | 239.6
text/enwik8.txt| bjorn2CountCodePoints    |  399.3 ms |             1.0 | 238.8
text/enwik8.txt| vimCountCodePoints       |  517.8 ms |             1.0 | 184.2
text/enwik8.txt| cmpArithCountCodePoints  |  586.4 ms |             1.0 | 162.6

Gcc 4.9
-------

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/utf8.txt**| **bjorn1CountCodePoints**| **20.9** | **2.3** | **300.4**
text/utf8.txt  | bjorn2CountCodePoints    |   22.3 ms |             2.3 | 280.6
text/utf8.txt  | vimCountCodePoints       |   27.0 ms |             2.3 | 232.5
text/utf8.txt  | cmpBranchCountCodePoints |   28.3 ms |             2.3 | 221.8
text/utf8.txt  | cmpArithCountCodePoints  |   29.1 ms |             2.3 | 215.6

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/ascii.txt**| **cmpBranchCountCodePoints**| **107.5** | **1.0** | **409.0**
text/ascii.txt | bjorn1CountCodePoints    |  134.9 ms |             1.0 | 326.0
text/ascii.txt | bjorn2CountCodePoints    |  151.0 ms |             1.0 | 291.2
text/ascii.txt | cmpArithCountCodePoints  |  204.5 ms |             1.0 | 214.9
text/ascii.txt | vimCountCodePoints       |  329.5 ms |             1.0 | 133.4

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/enwik8.txt**| **cmpBranchCountCodePoints**| **247.9** | **1.0** | **384.7**
text/enwik8.txt| bjorn1CountCodePoints    |  294.1 ms |             1.0 | 324.3
text/enwik8.txt| bjorn2CountCodePoints    |  323.1 ms |             1.0 | 295.2
text/enwik8.txt| cmpArithCountCodePoints  |  462.6 ms |             1.0 | 206.1
text/enwik8.txt| vimCountCodePoints       |  730.8 ms |             1.0 | 130.5
