# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing"

# Include any dependencies generated for this target.
include CMakeFiles/tutorial03_matrices.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tutorial03_matrices.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tutorial03_matrices.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tutorial03_matrices.dir/flags.make

CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o: CMakeFiles/tutorial03_matrices.dir/flags.make
CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o: /Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/tutorial03_matrices/tutorial03.cpp
CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o: CMakeFiles/tutorial03_matrices.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o -MF CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o.d -o CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o -c "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial03_matrices/tutorial03.cpp"

CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial03_matrices/tutorial03.cpp" > CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.i

CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial03_matrices/tutorial03.cpp" -o CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.s

CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o: CMakeFiles/tutorial03_matrices.dir/flags.make
CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o: /Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/common/shader.cpp
CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o: CMakeFiles/tutorial03_matrices.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o -MF CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o.d -o CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o -c "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/common/shader.cpp"

CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/common/shader.cpp" > CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.i

CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/common/shader.cpp" -o CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.s

# Object files for target tutorial03_matrices
tutorial03_matrices_OBJECTS = \
"CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o" \
"CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o"

# External object files for target tutorial03_matrices
tutorial03_matrices_EXTERNAL_OBJECTS =

tutorial03_matrices: CMakeFiles/tutorial03_matrices.dir/tutorial03_matrices/tutorial03.cpp.o
tutorial03_matrices: CMakeFiles/tutorial03_matrices.dir/common/shader.cpp.o
tutorial03_matrices: CMakeFiles/tutorial03_matrices.dir/build.make
tutorial03_matrices: external/glfw-3.1.2/src/libglfw3.a
tutorial03_matrices: external/libGLEW_1130.a
tutorial03_matrices: CMakeFiles/tutorial03_matrices.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable tutorial03_matrices"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorial03_matrices.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E copy /Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/tutorial09_vbo_indexing/./tutorial03_matrices /Users/gongkaiwen/Desktop/研究生/第一学期/ece\ 6122/ogl-master\ 2/tutorial03_matrices/

# Rule to build all files generated by this target.
CMakeFiles/tutorial03_matrices.dir/build: tutorial03_matrices
.PHONY : CMakeFiles/tutorial03_matrices.dir/build

CMakeFiles/tutorial03_matrices.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tutorial03_matrices.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tutorial03_matrices.dir/clean

CMakeFiles/tutorial03_matrices.dir/depend:
	cd "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2" "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2" "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing" "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing" "/Users/gongkaiwen/Desktop/研究生/第一学期/ece 6122/ogl-master 2/tutorial09_vbo_indexing/CMakeFiles/tutorial03_matrices.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/tutorial03_matrices.dir/depend

