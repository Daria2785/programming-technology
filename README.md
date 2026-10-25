---

## Lab 2. C++ Regular Expressions (HTML)

### Tasks
1. Validate if the text is HTML.
2. Find headings, paragraphs, and lists using `std::regex`.
3. Form validation:
   - **3a.** Input user data.
   - **3b.** Validate and format data (e.g., `Сидоров ИваН` -> `Сидоров Иван`, `2002-03-01` -> `01.03.2002`).
   - **3c.** Generate random user data.

### Structure
- `lb2.cpp` — entry point with menu.
- `HtmlParser.h` / `.cpp` — HTML validation and parsing (tasks 1, 2).
- `FormValidator.h` / `.cpp` — form validation and generator (tasks 3a, 3b, 3c).
- `test.html` — test data (valid HTML).
- `wrong.html` — test data (invalid HTML/Markdown).

### Sources
- [std::regex](https://en.cppreference.com/w/cpp/regex)
- [std::regex_search](https://en.cppreference.com/w/cpp/regex/regex_search)
- [UTF-8 to wide string conversion](https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar)
