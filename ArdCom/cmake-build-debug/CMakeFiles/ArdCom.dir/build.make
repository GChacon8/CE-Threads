# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Gits\CE-Threads\ArdCom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Gits\CE-Threads\ArdCom\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ArdCom.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ArdCom.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ArdCom.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ArdCom.dir/flags.make

CMakeFiles/ArdCom.dir/main.c.obj: CMakeFiles/ArdCom.dir/flags.make
CMakeFiles/ArdCom.dir/main.c.obj: D:/Gits/CE-Threads/ArdCom/main.c
CMakeFiles/ArdCom.dir/main.c.obj: CMakeFiles/ArdCom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Gits\CE-Threads\ArdCom\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ArdCom.dir/main.c.obj"
	"D:\CLion 2024.2.2\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArdCom.dir/main.c.obj -MF CMakeFiles\ArdCom.dir\main.c.obj.d -o CMakeFiles\ArdCom.dir\main.c.obj -c D:\Gits\CE-Threads\ArdCom\main.c

CMakeFiles/ArdCom.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArdCom.dir/main.c.i"
	"D:\CLion 2024.2.2\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Gits\CE-Threads\ArdCom\main.c > CMakeFiles\ArdCom.dir\main.c.i

CMakeFiles/ArdCom.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArdCom.dir/main.c.s"
	"D:\CLion 2024.2.2\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Gits\CE-Threads\ArdCom\main.c -o CMakeFiles\ArdCom.dir\main.c.s

CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj: CMakeFiles/ArdCom.dir/flags.make
CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj: D:/Gits/CE-Threads/ArdCom/Libs/serial_com.c
CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj: CMakeFiles/ArdCom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Gits\CE-Threads\ArdCom\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj"
	"D:\CLion 2024.2.2\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj -MF CMakeFiles\ArdCom.dir\Libs\serial_com.c.obj.d -o CMakeFiles\ArdCom.dir\Libs\serial_com.c.obj -c D:\Gits\CE-Threads\ArdCom\Libs\serial_com.c

CMakeFiles/ArdCom.dir/Libs/serial_com.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArdCom.dir/Libs/serial_com.c.i"
	"D:\CLion 2024.2.2\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Gits\CE-Threads\ArdCom\Libs\serial_com.c > CMakeFiles\ArdCom.dir\Libs\serial_com.c.i

CMakeFiles/ArdCom.dir/Libs/serial_com.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArdCom.dir/Libs/serial_com.c.s"
	"D:\CLion 2024.2.2\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Gits\CE-Threads\ArdCom\Libs\serial_com.c -o CMakeFiles\ArdCom.dir\Libs\serial_com.c.s

# Object files for target ArdCom
ArdCom_OBJECTS = \
"CMakeFiles/ArdCom.dir/main.c.obj" \
"CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj"

# External object files for target ArdCom
ArdCom_EXTERNAL_OBJECTS =

ArdCom.exe: CMakeFiles/ArdCom.dir/main.c.obj
ArdCom.exe: CMakeFiles/ArdCom.dir/Libs/serial_com.c.obj
ArdCom.exe: CMakeFiles/ArdCom.dir/build.make
ArdCom.exe: CMakeFiles/ArdCom.dir/linkLibs.rsp
ArdCom.exe: CMakeFiles/ArdCom.dir/objects1.rsp
ArdCom.exe: CMakeFiles/ArdCom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Gits\CE-Threads\ArdCom\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ArdCom.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ArdCom.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ArdCom.dir/build: ArdCom.exe
.PHONY : CMakeFiles/ArdCom.dir/build

CMakeFiles/ArdCom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ArdCom.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ArdCom.dir/clean

CMakeFiles/ArdCom.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Gits\CE-Threads\ArdCom D:\Gits\CE-Threads\ArdCom D:\Gits\CE-Threads\ArdCom\cmake-build-debug D:\Gits\CE-Threads\ArdCom\cmake-build-debug D:\Gits\CE-Threads\ArdCom\cmake-build-debug\CMakeFiles\ArdCom.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ArdCom.dir/depend

