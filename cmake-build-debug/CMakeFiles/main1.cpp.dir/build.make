# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Viktoria/Desktop/bigint

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Viktoria/Desktop/bigint/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main1.cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main1.cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main1.cpp.dir/flags.make

CMakeFiles/main1.cpp.dir/main1.cpp.o: CMakeFiles/main1.cpp.dir/flags.make
CMakeFiles/main1.cpp.dir/main1.cpp.o: ../main1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Viktoria/Desktop/bigint/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main1.cpp.dir/main1.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main1.cpp.dir/main1.cpp.o -c /Users/Viktoria/Desktop/bigint/main1.cpp

CMakeFiles/main1.cpp.dir/main1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main1.cpp.dir/main1.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Viktoria/Desktop/bigint/main1.cpp > CMakeFiles/main1.cpp.dir/main1.cpp.i

CMakeFiles/main1.cpp.dir/main1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main1.cpp.dir/main1.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Viktoria/Desktop/bigint/main1.cpp -o CMakeFiles/main1.cpp.dir/main1.cpp.s

CMakeFiles/main1.cpp.dir/main1.cpp.o.requires:

.PHONY : CMakeFiles/main1.cpp.dir/main1.cpp.o.requires

CMakeFiles/main1.cpp.dir/main1.cpp.o.provides: CMakeFiles/main1.cpp.dir/main1.cpp.o.requires
	$(MAKE) -f CMakeFiles/main1.cpp.dir/build.make CMakeFiles/main1.cpp.dir/main1.cpp.o.provides.build
.PHONY : CMakeFiles/main1.cpp.dir/main1.cpp.o.provides

CMakeFiles/main1.cpp.dir/main1.cpp.o.provides.build: CMakeFiles/main1.cpp.dir/main1.cpp.o


CMakeFiles/main1.cpp.dir/big_integer.cpp.o: CMakeFiles/main1.cpp.dir/flags.make
CMakeFiles/main1.cpp.dir/big_integer.cpp.o: ../big_integer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Viktoria/Desktop/bigint/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main1.cpp.dir/big_integer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main1.cpp.dir/big_integer.cpp.o -c /Users/Viktoria/Desktop/bigint/big_integer.cpp

CMakeFiles/main1.cpp.dir/big_integer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main1.cpp.dir/big_integer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Viktoria/Desktop/bigint/big_integer.cpp > CMakeFiles/main1.cpp.dir/big_integer.cpp.i

CMakeFiles/main1.cpp.dir/big_integer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main1.cpp.dir/big_integer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Viktoria/Desktop/bigint/big_integer.cpp -o CMakeFiles/main1.cpp.dir/big_integer.cpp.s

CMakeFiles/main1.cpp.dir/big_integer.cpp.o.requires:

.PHONY : CMakeFiles/main1.cpp.dir/big_integer.cpp.o.requires

CMakeFiles/main1.cpp.dir/big_integer.cpp.o.provides: CMakeFiles/main1.cpp.dir/big_integer.cpp.o.requires
	$(MAKE) -f CMakeFiles/main1.cpp.dir/build.make CMakeFiles/main1.cpp.dir/big_integer.cpp.o.provides.build
.PHONY : CMakeFiles/main1.cpp.dir/big_integer.cpp.o.provides

CMakeFiles/main1.cpp.dir/big_integer.cpp.o.provides.build: CMakeFiles/main1.cpp.dir/big_integer.cpp.o


# Object files for target main1.cpp
main1_cpp_OBJECTS = \
"CMakeFiles/main1.cpp.dir/main1.cpp.o" \
"CMakeFiles/main1.cpp.dir/big_integer.cpp.o"

# External object files for target main1.cpp
main1_cpp_EXTERNAL_OBJECTS =

main1.cpp: CMakeFiles/main1.cpp.dir/main1.cpp.o
main1.cpp: CMakeFiles/main1.cpp.dir/big_integer.cpp.o
main1.cpp: CMakeFiles/main1.cpp.dir/build.make
main1.cpp: CMakeFiles/main1.cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Viktoria/Desktop/bigint/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable main1.cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main1.cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main1.cpp.dir/build: main1.cpp

.PHONY : CMakeFiles/main1.cpp.dir/build

CMakeFiles/main1.cpp.dir/requires: CMakeFiles/main1.cpp.dir/main1.cpp.o.requires
CMakeFiles/main1.cpp.dir/requires: CMakeFiles/main1.cpp.dir/big_integer.cpp.o.requires

.PHONY : CMakeFiles/main1.cpp.dir/requires

CMakeFiles/main1.cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main1.cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main1.cpp.dir/clean

CMakeFiles/main1.cpp.dir/depend:
	cd /Users/Viktoria/Desktop/bigint/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Viktoria/Desktop/bigint /Users/Viktoria/Desktop/bigint /Users/Viktoria/Desktop/bigint/cmake-build-debug /Users/Viktoria/Desktop/bigint/cmake-build-debug /Users/Viktoria/Desktop/bigint/cmake-build-debug/CMakeFiles/main1.cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main1.cpp.dir/depend
