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
text/utf8.txt  | bjorn1CountCodePoints    |   29.0 ms |             2.3 | 216.4
text/utf8.txt  | bjorn2CountCodePoints    |   29.1 ms |             2.3 | 215.3
text/utf8.txt  | cmpArithCountCodePoints  |   44.1 ms |             2.3 | 142.3
text/utf8.txt  | cmpBranchCountCodePoints |   25.5 ms |             2.3 | 246.2
text/utf8.txt  | vimCountCodePoints       |   22.1 ms |             2.3 | 284.4

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
text/ascii.txt | bjorn1CountCodePoints    |  191.8 ms |             1.0 | 229.2
text/ascii.txt | bjorn2CountCodePoints    |  184.1 ms |             1.0 | 238.8
text/ascii.txt | cmpArithCountCodePoints  |  279.6 ms |             1.0 | 157.2
text/ascii.txt | cmpBranchCountCodePoints |  100.2 ms |             1.0 | 438.8
text/ascii.txt | vimCountCodePoints       |  244.1 ms |             1.0 | 180.1

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
text/enwik8.txt| bjorn1CountCodePoints    |  400.6 ms |             1.0 | 238.0
text/enwik8.txt| bjorn2CountCodePoints    |  416.1 ms |             1.0 | 229.2
text/enwik8.txt| cmpArithCountCodePoints  |  595.1 ms |             1.0 | 160.3
text/enwik8.txt| cmpBranchCountCodePoints |  218.5 ms |             1.0 | 436.4
text/enwik8.txt| vimCountCodePoints       |  519.1 ms |             1.0 | 183.7

Gcc 4.9
-------

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
text/utf8.txt  | bjorn1CountCodePoints    |   20.9 ms |             2.3 | 299.4
text/utf8.txt  | bjorn2CountCodePoints    |   24.0 ms |             2.3 | 261.2
text/utf8.txt  | cmpArithCountCodePoints  |   33.2 ms |             2.3 | 189.1
text/utf8.txt  | cmpBranchCountCodePoints |   29.7 ms |             2.3 | 211.5
text/utf8.txt  | vimCountCodePoints       |   28.6 ms |             2.3 | 219.2

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
text/ascii.txt | bjorn1CountCodePoints    |  136.6 ms |             1.0 | 321.7
text/ascii.txt | bjorn2CountCodePoints    |  153.4 ms |             1.0 | 286.6
text/ascii.txt | cmpArithCountCodePoints  |  208.9 ms |             1.0 | 210.4
text/ascii.txt | cmpBranchCountCodePoints |  108.6 ms |             1.0 | 404.9
text/ascii.txt | vimCountCodePoints       |  337.8 ms |             1.0 | 130.1

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
text/enwik8.txt| bjorn1CountCodePoints    |  310.4 ms |             1.0 | 307.2
text/enwik8.txt| bjorn2CountCodePoints    |  335.2 ms |             1.0 | 284.5
text/enwik8.txt| cmpArithCountCodePoints  |  484.5 ms |             1.0 | 196.8
text/enwik8.txt| cmpBranchCountCodePoints |  239.2 ms |             1.0 | 398.7
text/enwik8.txt| vimCountCodePoints       |  725.9 ms |             1.0 | 131.4
