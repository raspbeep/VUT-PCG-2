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
include CMakeFiles/nbody1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nbody1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nbody1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nbody1.dir/flags.make

CMakeFiles/nbody1.dir/Step1/main.cpp.o: CMakeFiles/nbody1.dir/flags.make
CMakeFiles/nbody1.dir/Step1/main.cpp.o: /home/xkrato61/pcg/PCG-proj2/Step1/main.cpp
CMakeFiles/nbody1.dir/Step1/main.cpp.o: CMakeFiles/nbody1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xkrato61/pcg/PCG-proj2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nbody1.dir/Step1/main.cpp.o"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nbody1.dir/Step1/main.cpp.o -MF CMakeFiles/nbody1.dir/Step1/main.cpp.o.d -o CMakeFiles/nbody1.dir/Step1/main.cpp.o -c /home/xkrato61/pcg/PCG-proj2/Step1/main.cpp

CMakeFiles/nbody1.dir/Step1/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nbody1.dir/Step1/main.cpp.i"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xkrato61/pcg/PCG-proj2/Step1/main.cpp > CMakeFiles/nbody1.dir/Step1/main.cpp.i

CMakeFiles/nbody1.dir/Step1/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nbody1.dir/Step1/main.cpp.s"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xkrato61/pcg/PCG-proj2/Step1/main.cpp -o CMakeFiles/nbody1.dir/Step1/main.cpp.s

CMakeFiles/nbody1.dir/Step1/nbody.cpp.o: CMakeFiles/nbody1.dir/flags.make
CMakeFiles/nbody1.dir/Step1/nbody.cpp.o: /home/xkrato61/pcg/PCG-proj2/Step1/nbody.cpp
CMakeFiles/nbody1.dir/Step1/nbody.cpp.o: CMakeFiles/nbody1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xkrato61/pcg/PCG-proj2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nbody1.dir/Step1/nbody.cpp.o"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nbody1.dir/Step1/nbody.cpp.o -MF CMakeFiles/nbody1.dir/Step1/nbody.cpp.o.d -o CMakeFiles/nbody1.dir/Step1/nbody.cpp.o -c /home/xkrato61/pcg/PCG-proj2/Step1/nbody.cpp

CMakeFiles/nbody1.dir/Step1/nbody.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nbody1.dir/Step1/nbody.cpp.i"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xkrato61/pcg/PCG-proj2/Step1/nbody.cpp > CMakeFiles/nbody1.dir/Step1/nbody.cpp.i

CMakeFiles/nbody1.dir/Step1/nbody.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nbody1.dir/Step1/nbody.cpp.s"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xkrato61/pcg/PCG-proj2/Step1/nbody.cpp -o CMakeFiles/nbody1.dir/Step1/nbody.cpp.s

CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o: CMakeFiles/nbody1.dir/flags.make
CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o: /home/xkrato61/pcg/PCG-proj2/Commons/h5Helper.cpp
CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o: CMakeFiles/nbody1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xkrato61/pcg/PCG-proj2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o -MF CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o.d -o CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o -c /home/xkrato61/pcg/PCG-proj2/Commons/h5Helper.cpp

CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.i"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xkrato61/pcg/PCG-proj2/Commons/h5Helper.cpp > CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.i

CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.s"
	/apps/all/NVHPC/24.3-CUDA-12.3.0/Linux_x86_64/24.3/compilers/bin/nvc++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xkrato61/pcg/PCG-proj2/Commons/h5Helper.cpp -o CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.s

# Object files for target nbody1
nbody1_OBJECTS = \
"CMakeFiles/nbody1.dir/Step1/main.cpp.o" \
"CMakeFiles/nbody1.dir/Step1/nbody.cpp.o" \
"CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o"

# External object files for target nbody1
nbody1_EXTERNAL_OBJECTS =

nbody1: CMakeFiles/nbody1.dir/Step1/main.cpp.o
nbody1: CMakeFiles/nbody1.dir/Step1/nbody.cpp.o
nbody1: CMakeFiles/nbody1.dir/Commons/h5Helper.cpp.o
nbody1: CMakeFiles/nbody1.dir/build.make
nbody1: /apps/all/HDF5/1.14.3-NVHPC-24.3-CUDA-12.3.0/lib/libhdf5.so
nbody1: /usr/lib64/libpthread.so
nbody1: /apps/all/Szip/2.1.1-GCCcore-12.2.0/lib/libsz.so
nbody1: /apps/all/zlib/1.2.12-GCCcore-12.2.0/lib/libz.so
nbody1: /usr/lib64/libdl.so
nbody1: /usr/lib64/libm.so
nbody1: CMakeFiles/nbody1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xkrato61/pcg/PCG-proj2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable nbody1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nbody1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nbody1.dir/build: nbody1
.PHONY : CMakeFiles/nbody1.dir/build

CMakeFiles/nbody1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nbody1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nbody1.dir/clean

CMakeFiles/nbody1.dir/depend:
	cd /home/xkrato61/pcg/PCG-proj2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xkrato61/pcg/PCG-proj2 /home/xkrato61/pcg/PCG-proj2 /home/xkrato61/pcg/PCG-proj2/build /home/xkrato61/pcg/PCG-proj2/build /home/xkrato61/pcg/PCG-proj2/build/CMakeFiles/nbody1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nbody1.dir/depend

