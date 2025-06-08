# Benchmark comparing std::ranges::views with classic raw loops
## Test setup
- 50 items in initial range
- 1000 Iterations
## System
- Windows 11
- AMD Ryzen 5 5500
- 16 GB RAM
## Compilers
- MSVC 19.43 (Release /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MD /O2 /Ob2 /DNDEBUG -std:c++latest)
- llvm-MinGW 18.1.6 (-O3 -DNDEBUG -std=gnu++23 -fansi-escape-codes -fcolor-diagnostics)
- MinGW 13 (-O3 -DNDEBUG -std=gnu++23 -fdiagnostics-color=always)
- MinGW 14 (-O3 -DNDEBUG -std=gnu++23 -fdiagnostics-color=always)

If you think it's unfair to compare MSVC's O2 with O3 from other compilers...that's what I get when I configure "Release build" with C++23
## Results  
### Milliseconds for total run, per compiler 
```
|                                             | MSVC 19.43 | llvm-MinGW 18.1.6 | MinGW 13 | MinGW 14 |
| ------------------------------------------- | ---------- | ----------------- | -------- | -------- |
| Calculate result in loop                    |         61 |                50 |       73 |       73 |
| Build view→Reduce to result                 |        307 |               662 |      169 |      178 |
| Build vector in loop→Reduce                 |        893 |              1240 |      782 |      883 |
| Like above, but with preallocated vector    |        557 |               406 |      378 |      367 |
| View→Vector→Reduce                          |       1130 |              1880 |      829 |      954 |
```
### Relative speed (Baseline = 1.0, greater is slower)
```
|                                             | MSVC 19.43 | llvm-MinGW 18.1.6 | MinGW 13 | MinGW 14 |
| ------------------------------------------- | ---------- | ----------------- | -------- | -------- |
| Calculate result in loop                    | Baseline   |                   |          |          |
| Build view→Reduce to result                 |       5,03 |             13,24 |     2,32 |     2,44 |
| Build vector in loop→Reduce                 |      14,64 |             24,80 |    10,71 |    12,10 |
| Like above, but with preallocated vector    |       9,13 |              8,12 |     5,18 |     5,03 |
| View→Vector→Reduce                          |      18,52 |             37,60 |    11,36 |    13,07 |
```
### Speed in nanoseconds per item in intermediate range
```
|                                             | MSVC 19.43 | llvm-MinGW 18.1.6 | MinGW 13 | MinGW 14 |
| ------------------------------------------- | ---------- | ----------------- | -------- | -------- |
| Calculate result in loop                    |       0,21 |              0,17 |     0,25 |     0,25 |
| Build view→Reduce to result                 |       1,05 |              2,26 |     0,58 |     0,61 |
| Build vector in loop→Reduce                 |       3,05 |              4,23 |     2,67 |     3,02 |
| Like above, but with preallocated vector    |       1,90 |              1,39 |     1,29 |     1,25 |
| View→Vector→Reduce                          |       3,86 |              6,42 |     2,83 |     3,26 |

```

