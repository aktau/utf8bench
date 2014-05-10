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
- [Björn Höhrmann's version](http://bjoern.hoehrmann.de/utf-8/decoder/dfa/)
