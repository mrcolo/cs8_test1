# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/calc/cs8_test1/Simple-Web-Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/calc/cs8_test1/Simple-Web-Server/build

# Include any dependencies generated for this target.
include CMakeFiles/http_examples.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/http_examples.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/http_examples.dir/flags.make

CMakeFiles/http_examples.dir/http_examples.cpp.o: CMakeFiles/http_examples.dir/flags.make
CMakeFiles/http_examples.dir/http_examples.cpp.o: ../http_examples.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/calc/cs8_test1/Simple-Web-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/http_examples.dir/http_examples.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http_examples.dir/http_examples.cpp.o -c /root/calc/cs8_test1/Simple-Web-Server/http_examples.cpp

CMakeFiles/http_examples.dir/http_examples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http_examples.dir/http_examples.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/calc/cs8_test1/Simple-Web-Server/http_examples.cpp > CMakeFiles/http_examples.dir/http_examples.cpp.i

CMakeFiles/http_examples.dir/http_examples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http_examples.dir/http_examples.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/calc/cs8_test1/Simple-Web-Server/http_examples.cpp -o CMakeFiles/http_examples.dir/http_examples.cpp.s

CMakeFiles/http_examples.dir/http_examples.cpp.o.requires:

.PHONY : CMakeFiles/http_examples.dir/http_examples.cpp.o.requires

CMakeFiles/http_examples.dir/http_examples.cpp.o.provides: CMakeFiles/http_examples.dir/http_examples.cpp.o.requires
	$(MAKE) -f CMakeFiles/http_examples.dir/build.make CMakeFiles/http_examples.dir/http_examples.cpp.o.provides.build
.PHONY : CMakeFiles/http_examples.dir/http_examples.cpp.o.provides

CMakeFiles/http_examples.dir/http_examples.cpp.o.provides.build: CMakeFiles/http_examples.dir/http_examples.cpp.o


# Object files for target http_examples
http_examples_OBJECTS = \
"CMakeFiles/http_examples.dir/http_examples.cpp.o"

# External object files for target http_examples
http_examples_EXTERNAL_OBJECTS =

http_examples: CMakeFiles/http_examples.dir/http_examples.cpp.o
http_examples: CMakeFiles/http_examples.dir/build.make
http_examples: /usr/lib/x86_64-linux-gnu/libboost_system.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_thread.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
http_examples: /usr/lib/x86_64-linux-gnu/libpthread.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_system.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_thread.so
http_examples: /usr/lib/x86_64-linux-gnu/libssl.so
http_examples: /usr/lib/x86_64-linux-gnu/libcrypto.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
http_examples: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
http_examples: /usr/lib/x86_64-linux-gnu/libpthread.so
http_examples: CMakeFiles/http_examples.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/calc/cs8_test1/Simple-Web-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable http_examples"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http_examples.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/http_examples.dir/build: http_examples

.PHONY : CMakeFiles/http_examples.dir/build

CMakeFiles/http_examples.dir/requires: CMakeFiles/http_examples.dir/http_examples.cpp.o.requires

.PHONY : CMakeFiles/http_examples.dir/requires

CMakeFiles/http_examples.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/http_examples.dir/cmake_clean.cmake
.PHONY : CMakeFiles/http_examples.dir/clean

CMakeFiles/http_examples.dir/depend:
	cd /root/calc/cs8_test1/Simple-Web-Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/calc/cs8_test1/Simple-Web-Server /root/calc/cs8_test1/Simple-Web-Server /root/calc/cs8_test1/Simple-Web-Server/build /root/calc/cs8_test1/Simple-Web-Server/build /root/calc/cs8_test1/Simple-Web-Server/build/CMakeFiles/http_examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/http_examples.dir/depend

