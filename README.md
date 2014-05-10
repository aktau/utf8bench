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
**text/utf8.txt**| **vim_count**            | **22.3** ms | **2.3** | **281.3**
text/utf8.txt  | campbell_branch_count    |   26.3 ms |             2.3 | 238.8
text/utf8.txt  | bjorn_regular_count      |   29.6 ms |             2.3 | 211.6
text/utf8.txt  | bjorn_reduced_count      |   29.9 ms |             2.3 | 210.1
text/utf8.txt  | campbell_arith_count     |   42.1 ms |             2.3 | 149.1

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/ascii.txt**| **campbell_branch_count**| **100.1** ms | **1.0** | **439.0**
text/ascii.txt | bjorn_reduced_count      |  184.5 ms |             1.0 | 238.3
text/ascii.txt | bjorn_regular_count      |  192.4 ms |             1.0 | 228.5
text/ascii.txt | vim_count                |  243.2 ms |             1.0 | 180.8
text/ascii.txt | campbell_arith_count     |  268.0 ms |             1.0 | 164.0

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/enwik8.txt**| **campbell_branch_count**| **222.0** ms | **1.0** | **429.5**
text/enwik8.txt| bjorn_regular_count      |  404.5 ms |             1.0 | 235.7
text/enwik8.txt| bjorn_reduced_count      |  411.3 ms |             1.0 | 231.9
text/enwik8.txt| vim_count                |  524.9 ms |             1.0 | 181.7
text/enwik8.txt| campbell_arith_count     |  592.2 ms |             1.0 | 161.1

Gcc 4.9
-------

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/utf8.txt**| **bjorn_regular_count**  | **20.4** ms | **2.3** | **307.2**
text/utf8.txt  | bjorn_reduced_count      |   22.8 ms |             2.3 | 275.3
text/utf8.txt  | vim_count                |   27.0 ms |             2.3 | 232.3
text/utf8.txt  | campbell_branch_count    |   28.9 ms |             2.3 | 217.4
text/utf8.txt  | campbell_arith_count     |   29.8 ms |             2.3 | 210.5

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/ascii.txt**| **campbell_branch_count**| **106.8** ms | **1.0** | **411.6**
text/ascii.txt | bjorn_regular_count      |  142.5 ms |             1.0 | 308.5
text/ascii.txt | bjorn_reduced_count      |  155.8 ms |             1.0 | 282.1
text/ascii.txt | campbell_arith_count     |  215.0 ms |             1.0 | 204.5
text/ascii.txt | vim_count                |  330.1 ms |             1.0 | 133.2

file           | function                 | runtime   | bytes/codepoint | mb/sec
---------------|--------------------------|-----------|-----------------|-------
**text/enwik8.txt**| **campbell_branch_count**| **245.4** ms | **1.0** | **388.7**
text/enwik8.txt| bjorn_regular_count      |  290.0 ms |             1.0 | 328.9
text/enwik8.txt| bjorn_reduced_count      |  324.7 ms |             1.0 | 293.7
text/enwik8.txt| campbell_arith_count     |  469.5 ms |             1.0 | 203.1
text/enwik8.txt| vim_count                |  733.4 ms |             1.0 | 130.0
