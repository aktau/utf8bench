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
**text/utf8.txt  **| **vimCountCodePoints       **| **  20.8 ms** | **            2.3** | **300.8**
text/utf8.txt  | cmpBranchCountCodePoints |   24.4 ms |             2.3 | 257.3
text/utf8.txt  | bjorn2CountCodePoints    |   27.2 ms |             2.3 | 230.4
text/utf8.txt  | bjorn1CountCodePoints    |   28.4 ms |             2.3 | 221.0
text/utf8.txt  | cmpArithCountCodePoints  |   38.6 ms |             2.3 | 162.4

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/ascii.txt **| **cmpBranchCountCodePoints **| **  97.7 ms** | **            1.0** | **450.1**
text/ascii.txt | bjorn2CountCodePoints    |  180.5 ms |             1.0 | 243.6
text/ascii.txt | bjorn1CountCodePoints    |  181.5 ms |             1.0 | 242.2
text/ascii.txt | vimCountCodePoints       |  244.1 ms |             1.0 | 180.1
text/ascii.txt | cmpArithCountCodePoints  |  267.8 ms |             1.0 | 164.2

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/enwik8.txt**| **cmpBranchCountCodePoints **| ** 227.6 ms** | **            1.0** | **419.0**
text/enwik8.txt| bjorn1CountCodePoints    |  402.5 ms |             1.0 | 236.9
text/enwik8.txt| bjorn2CountCodePoints    |  404.9 ms |             1.0 | 235.6
text/enwik8.txt| vimCountCodePoints       |  511.7 ms |             1.0 | 186.4
text/enwik8.txt| cmpArithCountCodePoints  |  589.9 ms |             1.0 | 161.7

Gcc 4.9
-------

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/utf8.txt  **| **bjorn1CountCodePoints    **| **  20.3 ms** | **            2.3** | **308.9**
text/utf8.txt  | bjorn2CountCodePoints    |   22.3 ms |             2.3 | 280.7
text/utf8.txt  | vimCountCodePoints       |   27.1 ms |             2.3 | 231.2
text/utf8.txt  | cmpBranchCountCodePoints |   27.7 ms |             2.3 | 226.7
text/utf8.txt  | cmpArithCountCodePoints  |   28.8 ms |             2.3 | 217.4

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/ascii.txt **| **cmpBranchCountCodePoints **| ** 107.3 ms** | **            1.0** | **409.9**
text/ascii.txt | bjorn1CountCodePoints    |  132.7 ms |             1.0 | 331.2
text/ascii.txt | bjorn2CountCodePoints    |  149.3 ms |             1.0 | 294.5
text/ascii.txt | cmpArithCountCodePoints  |  211.1 ms |             1.0 | 208.3
text/ascii.txt | vimCountCodePoints       |  325.6 ms |             1.0 | 135.0

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/enwik8.txt**| **cmpBranchCountCodePoints **| ** 240.4 ms** | **            1.0** | **396.7**
text/enwik8.txt| bjorn1CountCodePoints    |  291.0 ms |             1.0 | 327.7
text/enwik8.txt| bjorn2CountCodePoints    |  330.0 ms |             1.0 | 289.0
text/enwik8.txt| cmpArithCountCodePoints  |  459.2 ms |             1.0 | 207.7
text/enwik8.txt| vimCountCodePoints       |  724.8 ms |             1.0 | 131.6
