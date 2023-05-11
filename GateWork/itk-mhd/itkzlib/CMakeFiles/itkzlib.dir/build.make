# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /volatile/Applications/Gate/GateWork

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /volatile/Applications/Gate/GateWork

# Include any dependencies generated for this target.
include itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.make

# Include the progress variables for this target.
include itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/progress.make

# Include the compile flags for this target's objects.
include itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.o: source/externals/itk-mhd/itkzlib/adler32.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.o -MF CMakeFiles/itkzlib.dir/adler32.o.d -o CMakeFiles/itkzlib.dir/adler32.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/adler32.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/adler32.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/adler32.c > CMakeFiles/itkzlib.dir/adler32.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/adler32.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/adler32.c -o CMakeFiles/itkzlib.dir/adler32.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.o: source/externals/itk-mhd/itkzlib/compress.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.o -MF CMakeFiles/itkzlib.dir/compress.o.d -o CMakeFiles/itkzlib.dir/compress.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/compress.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/compress.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/compress.c > CMakeFiles/itkzlib.dir/compress.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/compress.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/compress.c -o CMakeFiles/itkzlib.dir/compress.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.o: source/externals/itk-mhd/itkzlib/crc32.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.o -MF CMakeFiles/itkzlib.dir/crc32.o.d -o CMakeFiles/itkzlib.dir/crc32.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/crc32.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/crc32.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/crc32.c > CMakeFiles/itkzlib.dir/crc32.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/crc32.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/crc32.c -o CMakeFiles/itkzlib.dir/crc32.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.o: source/externals/itk-mhd/itkzlib/deflate.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.o -MF CMakeFiles/itkzlib.dir/deflate.o.d -o CMakeFiles/itkzlib.dir/deflate.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/deflate.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/deflate.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/deflate.c > CMakeFiles/itkzlib.dir/deflate.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/deflate.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/deflate.c -o CMakeFiles/itkzlib.dir/deflate.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.o: source/externals/itk-mhd/itkzlib/gzio.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.o -MF CMakeFiles/itkzlib.dir/gzio.o.d -o CMakeFiles/itkzlib.dir/gzio.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/gzio.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/gzio.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/gzio.c > CMakeFiles/itkzlib.dir/gzio.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/gzio.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/gzio.c -o CMakeFiles/itkzlib.dir/gzio.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.o: source/externals/itk-mhd/itkzlib/inffast.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.o -MF CMakeFiles/itkzlib.dir/inffast.o.d -o CMakeFiles/itkzlib.dir/inffast.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inffast.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/inffast.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inffast.c > CMakeFiles/itkzlib.dir/inffast.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/inffast.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inffast.c -o CMakeFiles/itkzlib.dir/inffast.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.o: source/externals/itk-mhd/itkzlib/inflate.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.o -MF CMakeFiles/itkzlib.dir/inflate.o.d -o CMakeFiles/itkzlib.dir/inflate.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inflate.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/inflate.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inflate.c > CMakeFiles/itkzlib.dir/inflate.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/inflate.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inflate.c -o CMakeFiles/itkzlib.dir/inflate.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.o: source/externals/itk-mhd/itkzlib/inftrees.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.o -MF CMakeFiles/itkzlib.dir/inftrees.o.d -o CMakeFiles/itkzlib.dir/inftrees.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inftrees.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/inftrees.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inftrees.c > CMakeFiles/itkzlib.dir/inftrees.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/inftrees.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/inftrees.c -o CMakeFiles/itkzlib.dir/inftrees.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.o: source/externals/itk-mhd/itkzlib/trees.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.o -MF CMakeFiles/itkzlib.dir/trees.o.d -o CMakeFiles/itkzlib.dir/trees.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/trees.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/trees.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/trees.c > CMakeFiles/itkzlib.dir/trees.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/trees.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/trees.c -o CMakeFiles/itkzlib.dir/trees.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.o: source/externals/itk-mhd/itkzlib/uncompr.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.o -MF CMakeFiles/itkzlib.dir/uncompr.o.d -o CMakeFiles/itkzlib.dir/uncompr.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/uncompr.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/uncompr.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/uncompr.c > CMakeFiles/itkzlib.dir/uncompr.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/uncompr.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/uncompr.c -o CMakeFiles/itkzlib.dir/uncompr.s

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/flags.make
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.o: source/externals/itk-mhd/itkzlib/zutil.c
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.o: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.o"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.o -MF CMakeFiles/itkzlib.dir/zutil.o.d -o CMakeFiles/itkzlib.dir/zutil.o -c /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/zutil.c

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/itkzlib.dir/zutil.i"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/zutil.c > CMakeFiles/itkzlib.dir/zutil.i

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/itkzlib.dir/zutil.s"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib/zutil.c -o CMakeFiles/itkzlib.dir/zutil.s

# Object files for target itkzlib
itkzlib_OBJECTS = \
"CMakeFiles/itkzlib.dir/adler32.o" \
"CMakeFiles/itkzlib.dir/compress.o" \
"CMakeFiles/itkzlib.dir/crc32.o" \
"CMakeFiles/itkzlib.dir/deflate.o" \
"CMakeFiles/itkzlib.dir/gzio.o" \
"CMakeFiles/itkzlib.dir/inffast.o" \
"CMakeFiles/itkzlib.dir/inflate.o" \
"CMakeFiles/itkzlib.dir/inftrees.o" \
"CMakeFiles/itkzlib.dir/trees.o" \
"CMakeFiles/itkzlib.dir/uncompr.o" \
"CMakeFiles/itkzlib.dir/zutil.o"

# External object files for target itkzlib
itkzlib_EXTERNAL_OBJECTS =

itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/adler32.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/compress.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/crc32.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/deflate.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/gzio.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inffast.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inflate.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/inftrees.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/trees.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/uncompr.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/zutil.o
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/build.make
itk-mhd/itkzlib/libitkzlib.a: itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/volatile/Applications/Gate/GateWork/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C static library libitkzlib.a"
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && $(CMAKE_COMMAND) -P CMakeFiles/itkzlib.dir/cmake_clean_target.cmake
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/itkzlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/build: itk-mhd/itkzlib/libitkzlib.a
.PHONY : itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/build

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/clean:
	cd /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib && $(CMAKE_COMMAND) -P CMakeFiles/itkzlib.dir/cmake_clean.cmake
.PHONY : itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/clean

itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/depend:
	cd /volatile/Applications/Gate/GateWork && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /volatile/Applications/Gate/GateWork /volatile/Applications/Gate/GateWork/source/externals/itk-mhd/itkzlib /volatile/Applications/Gate/GateWork /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib /volatile/Applications/Gate/GateWork/itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : itk-mhd/itkzlib/CMakeFiles/itkzlib.dir/depend

