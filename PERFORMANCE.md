# Benchmark comparing std::ranges::views with classic raw loops
## Milliseconds for total run, per compiler 
- 50 items in initial range
- 1000 Iterations
```
|                                             | MSVC 19.43 | llvm-MinGW 18.1.6 | MinGW 13 | MinGW 14 |
| ------------------------------------------- | ---------- | ----------------- | -------- | -------- |
| Calculate result in loop                    | 61         | 50                | 73       | 73       |
| Build view→Reduce to result                 | 307        | 662               | 169      | 178      |
| Build vector in loop→Reduce                 | 893        | 1240              | 782      | 883      |
| Like above, but with preallocated vector    | 557        | 406               | 378      | 367      |
| View→Vector→Reduce                          | 1130       | 1880              | 829      | 954      |
```

