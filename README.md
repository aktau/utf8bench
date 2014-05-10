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
text/utf8.txt  | bjorn1CountCodePoints    |   38.0 ms |             2.3 | 164.9
text/utf8.txt  | bjorn2CountCodePoints    |   27.7 ms |             2.3 | 226.8
text/utf8.txt  | cmpArithCountCodePoints  |   39.0 ms |             2.3 | 161.0
text/utf8.txt  | cmpBranchCountCodePoints |   24.7 ms |             2.3 | 253.7
text/utf8.txt  | vimCountCodePoints       |   20.7 ms |             2.3 | 303.6
text/ascii.txt | bjorn1CountCodePoints    |  191.1 ms |             1.0 | 230.0
text/ascii.txt | bjorn2CountCodePoints    |  184.4 ms |             1.0 | 238.4
text/ascii.txt | cmpArithCountCodePoints  |  267.3 ms |             1.0 | 164.5
text/ascii.txt | cmpBranchCountCodePoints |   98.0 ms |             1.0 | 448.7
text/ascii.txt | vimCountCodePoints       |  236.9 ms |             1.0 | 185.6
text/enwik8.txt| bjorn1CountCodePoints    |  405.9 ms |             1.0 | 235.0
text/enwik8.txt| bjorn2CountCodePoints    |  408.4 ms |             1.0 | 233.5
text/enwik8.txt| cmpArithCountCodePoints  |  600.2 ms |             1.0 | 158.9
text/enwik8.txt| cmpBranchCountCodePoints |  224.0 ms |             1.0 | 425.8
text/enwik8.txt| vimCountCodePoints       |  526.9 ms |             1.0 | 181.0

Gcc 4.9
-------

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
text/utf8.txt  | bjorn1CountCodePoints    |   22.2 ms |             2.3 | 281.9
text/utf8.txt  | bjorn2CountCodePoints    |   23.6 ms |             2.3 | 265.9
text/utf8.txt  | cmpArithCountCodePoints  |   31.1 ms |             2.3 | 202.0
text/utf8.txt  | cmpBranchCountCodePoints |   28.0 ms |             2.3 | 223.7
text/utf8.txt  | vimCountCodePoints       |   28.2 ms |             2.3 | 222.2
text/ascii.txt | bjorn1CountCodePoints    |  132.3 ms |             1.0 | 332.4
text/ascii.txt | bjorn2CountCodePoints    |  150.4 ms |             1.0 | 292.3
text/ascii.txt | cmpArithCountCodePoints  |  215.9 ms |             1.0 | 203.6
text/ascii.txt | cmpBranchCountCodePoints |  108.5 ms |             1.0 | 405.1
text/ascii.txt | vimCountCodePoints       |  343.9 ms |             1.0 | 127.8
text/enwik8.txt| bjorn1CountCodePoints    |  301.1 ms |             1.0 | 316.7
text/enwik8.txt| bjorn2CountCodePoints    |  330.7 ms |             1.0 | 288.4
text/enwik8.txt| cmpArithCountCodePoints  |  464.1 ms |             1.0 | 205.5
text/enwik8.txt| cmpBranchCountCodePoints |  239.1 ms |             1.0 | 398.9
text/enwik8.txt| vimCountCodePoints       |  736.7 ms |             1.0 | 129.5
