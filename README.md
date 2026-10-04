## Lab 1. C++ STL Containers
### Tasks
1. Count unique words in a text file (output format: `word - count`).
2. Index word positions in a text file (0-based).
3. STL algorithms on `vector<int>`:
   - **3a.** Square prime numbers (`std::transform`).
   - **3b.** Sort: odd ascending, then even descending (`std::sort`).
   - **3c.** Unique elements in a given range (`std::set`).
4. Measure execution time of each main function (`std::chrono`).
### Project structure
- `л61.cpp` — entry point, console menu.
- `textAnalyz.h` / `textAnalyz.cpp` — `TextAnalyzer` class (tasks 1, 2).
- `NumbProcess.h` / `NumbProcess.cpp` — `NumberProcessor` class (tasks 3a, 3b, 3c).
- `war1.txt` — test data (War and Peace, all 4 volumes).
### Build
Open `л61.slnx` in Visual Studio, build (Ctrl+Shift+B), run (Ctrl+F5).
### Sources
- [std::map — cppreference](https://en.cppreference.com/w/cpp/container/map)
- [std::vector — cppreference](https://en.cppreference.com/w/cpp/container/vector)
- [std::set — cppreference](https://en.cppreference.com/w/cpp/container/set)
- [std::transform — cppreference](https://en.cppreference.com/w/cpp/algorithm/transform)
- [std::sort — cppreference](https://en.cppreference.com/w/cpp/algorithm/sort)
- [std::chrono — cppreference](https://en.cppreference.com/w/cpp/chrono)
- [UTF-8 encoding — Wikipedia](https://en.wikipedia.org/wiki/UTF-8)
