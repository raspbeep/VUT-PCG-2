# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /apps/all/CMake/3.24.3-GCCcore-12.2.0/bin/cmake

# The command to remove a file.
RM = /apps/all/CMake/3.24.3-GCCcore-12.2.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xkrato61/pcg/PCG-proj2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xkrato61/pcg/PCG-proj2/build

# Include any dependencies generated for this target.
include CMakeFiles/gen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gen.dir/flags.make

CMakeFiles/gen.dir/Commons/gen.cpp.o: CMakeFiles/gen.dir/flags.make
CMakeFiles/gen.dir/Commons/gen.cpp.o: /home/xkrato61/pcg/PCG-proj2/Commons/gen.cpp
CMakeFiles/gen.dir/Commons/gen.cpp.o: CMakeFiles/gen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xkrato61/pcg/PCG-proj2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gen.dir/Commons/gen.cpp.o"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gen.dir/Commons/gen.cpp.o -MF CMakeFiles/gen.dir/Commons/gen.cpp.o.d -o CMakeFiles/gen.dir/Commons/gen.cpp.o -c /home/xkrato61/pcg/PCG-proj2/Commons/gen.cpp

CMakeFiles/gen.dir/Commons/gen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gen.dir/Commons/gen.cpp.i"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xkrato61/pcg/PCG-proj2/Commons/gen.cpp > CMakeFiles/gen.dir/Commons/gen.cpp.i

CMakeFiles/gen.dir/Commons/gen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gen.dir/Commons/gen.cpp.s"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xkrato61/pcg/PCG-proj2/Commons/gen.cpp -o CMakeFiles/gen.dir/Commons/gen.cpp.s

# Object files for target gen
gen_OBJECTS = \
"CMakeFiles/gen.dir/Commons/gen.cpp.o"

# External object files for target gen
gen_EXTERNAL_OBJECTS =

gen: CMakeFiles/gen.dir/Commons/gen.cpp.o
gen: CMakeFiles/gen.dir/build.make
gen: /apps/all/HDF5/1.14.3-NVHPC-24.3-CUDA-12.3.0/lib/libhdf5.so
gen: /usr/lib64/libpthread.so
gen: /apps/all/Szip/2.1.1-GCCcore-12.2.0/lib/libsz.so
gen: /apps/all/zlib/1.2.12-GCCcore-12.2.0/lib/libz.so
gen: /usr/lib64/libdl.so
gen: /usr/lib64/libm.so
gen: CMakeFiles/gen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xkrato61/pcg/PCG-proj2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gen.dir/build: gen
.PHONY : CMakeFiles/gen.dir/build

CMakeFiles/gen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gen.dir/clean

CMakeFiles/gen.dir/depend:
	cd /home/xkrato61/pcg/PCG-proj2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xkrato61/pcg/PCG-proj2 /home/xkrato61/pcg/PCG-proj2 /home/xkrato61/pcg/PCG-proj2/build /home/xkrato61/pcg/PCG-proj2/build /home/xkrato61/pcg/PCG-proj2/build/CMakeFiles/gen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gen.dir/depend

