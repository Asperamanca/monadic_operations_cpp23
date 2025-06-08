# Benchmark comparing std::ranges::views with classic raw loops

```
                      Classic | Integrated |   Views  | Views2Vector |
-------------------------------------------------------------------------------------------
MinGW 14 Release -O3 -DNDEBUG -std=gnu++23 -fdiagnostics-color=always
                          875 |         71 |      178 |          751 |
-------------------------------------------------------------------------------------------
MinGW 13 Release -O3 -DNDEBUG -std=gnu++23 -fdiagnostics-color=always
                          778 |         73 |      171 |          664 |
-------------------------------------------------------------------------------------------
llvm-MinGW 18.1.6 Release -O3 -DNDEBUG -std=gnu++23 -fansi-escape-codes -fcolor-diagnostics
                         1140 |         49 |      662 |         1550 |
-------------------------------------------------------------------------------------------
MSVC 19.43 Release /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MD /O2 /Ob2 /DNDEBUG -std:c++latest
                          845 |         61 |      302 |          789 |
-------------------------------------------------------------------------------------------
                      Classic | Integrated |   Views  | Views2Vector |

```
