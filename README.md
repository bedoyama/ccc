[![C++ Crash Course](http://ccc.codes/cppcc.png "C++ Crash Course")](http://ccc.codes/)

# Get the Book

[C++ Crash Course is currently available at No Starch Press.](https://nostarch.com/cppcrashcourse)

# Install Software

1. Follow the instructions in Chapter 1 for setting up a development environment.
2. [Download and install CMake](https://cmake.org/download/)
3. [Download and install Boost](https://www.boost.org/doc/libs/1_68_0/more/getting_started/index.html)
4. [Download and install Git](https://git-scm.com/downloads)

# Build the Examples

[![Docker Repository on Quay](https://quay.io/repository/jlospinoso/ccc/status "Docker Repository on Quay")](https://quay.io/repository/jlospinoso/ccc)

First, clone this repository:

```
git clone git@github.com:JLospinoso/ccc
```

Next, perform an [out-of-source CMake build](https://gitlab.kitware.com/cmake/community/wikis/home). For example:

```
cd ccc
git submodule init
git submodule update
mkdir build
cd build
cmake ..
cmake --build .
```

Your build directory should now contain requisite files for building on your current platform. On Windows, for example, you should find a `.sln` Visual Studio Solution file. On macOS/Linux, you should find a `make` file.

---

## Appendix: macOS Apple Silicon (ARM64) Build Fixes

If you're building on macOS with Apple Silicon and encounter build errors, the following fixes have been applied to make the project compatible:

### 1. Boost Installation and Configuration

Install Boost via Homebrew:

```bash
brew install boost
```

The CMakeLists.txt has been updated to:

- Use the new CMake policy `CMP0167` for Boost configuration
- Remove the deprecated `system` component (now header-only in Boost 1.89)
- Find and link ICU libraries required by Boost on macOS

### 2. GoogleTest Compiler Warnings

The GoogleTest library has been patched to suppress deprecated copy constructor warnings that are treated as errors on modern Clang compilers. The flag `-Wno-error=deprecated-copy` has been added to the Clang compiler flags in `third_party/google/googletest/googletest/cmake/internal_utils.cmake`.

### 3. Catch2 ARM64 Compatibility

The Catch2 library has been updated to use `__builtin_debugtrap()` on ARM64 instead of the x86-specific `int $3` instruction in `third_party/catchorg/Catch2/single_include/catch2/catch.hpp`.

### 4. Filesystem Library Linking

On macOS, the C++ filesystem library is part of the standard library and doesn't require linking to `stdc++fs`. The `chapter_17/CMakeLists.txt` has been updated to skip this library on Apple platforms.

### 5. ICU Library Configuration

ICU (International Components for Unicode) is a keg-only formula on Homebrew, meaning it's not symlinked into `/usr/local`. The build configuration has been updated to explicitly find and link ICU libraries from `/opt/homebrew/opt/icu4c@78`.

### 6. Code Compatibility Updates

- Fixed `chapter_20/connect_async.cpp` to explicitly specify the endpoint type instead of using `auto` in the lambda callback.

These changes ensure full compatibility with modern macOS development tools while maintaining backward compatibility with other platforms.

---

## Appendix: Debugging with LLDB on macOS

macOS uses LLDB as the default debugger (rather than GDB). Here's a quick guide to debugging the examples:

### Starting LLDB

From the build directory, launch LLDB with any executable:

```bash
lldb ./chapter_1/listing_1_1
```

Or attach to a running process:

```bash
lldb -p <process-id>
```

### Basic LLDB Commands

| Command                 | Description                  | Example                            |
| ----------------------- | ---------------------------- | ---------------------------------- |
| `run` or `r`            | Start the program            | `r`                                |
| `run <args>`            | Start with arguments         | `r arg1 arg2`                      |
| `breakpoint set` or `b` | Set a breakpoint             | `b main` or `b listing_1_1.cpp:10` |
| `breakpoint list`       | List all breakpoints         | `breakpoint list`                  |
| `breakpoint delete`     | Delete breakpoint            | `breakpoint delete 1`              |
| `next` or `n`           | Step over (next line)        | `n`                                |
| `step` or `s`           | Step into functions          | `s`                                |
| `finish` or `f`         | Step out of current function | `f`                                |
| `continue` or `c`       | Continue execution           | `c`                                |
| `print` or `p`          | Print variable value         | `p variable_name`                  |
| `frame variable` or `v` | Print local variables        | `v`                                |
| `bt` or `backtrace`     | Show call stack              | `bt`                               |
| `quit` or `q`           | Exit LLDB                    | `q`                                |

### Example Debug Session

```bash
# Build with debug symbols
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Start debugger
lldb ./chapter_1/listing_1_1

# In LLDB:
(lldb) breakpoint set --name main
(lldb) run
(lldb) next
(lldb) print my_variable
(lldb) continue
(lldb) quit
```

### Useful Tips

- **Enable debug symbols**: Add `-DCMAKE_BUILD_TYPE=Debug` when running cmake to include debugging information
- **Set breakpoint by function**: `b function_name`
- **Set breakpoint by file/line**: `b filename.cpp:42`
- **Watch expressions**: `watchpoint set variable my_var`
- **Conditional breakpoints**: `b main -c "argc > 1"`
- **Help command**: Type `help` or `help <command>` for detailed information

For more information, see the [LLDB Tutorial](https://lldb.llvm.org/use/tutorial.html) or run `help` within LLDB.
