# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\code\cpp\gameGngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\code\cpp\gameGngine\build

# Utility rule file for test_game_copy_target.

# Include any custom commands dependencies for this target.
include test/CMakeFiles/test_game_copy_target.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_game_copy_target.dir/progress.make

test/CMakeFiles/test_game_copy_target: test/copy_assets

test/copy_assets: test/always_rebuild
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\code\cpp\gameGngine\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating copy_assets"
	cd /d D:\code\cpp\gameGngine\build\test && "C:\Program Files\CMake\bin\cmake.exe" -E copy_directory D:/code/cpp/gameGngine/assets D:/code/cpp/gameGngine/build/test/assets

test/always_rebuild:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\code\cpp\gameGngine\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating always_rebuild"
	cd /d D:\code\cpp\gameGngine\build\test && cmake -E echo "copy files"

test_game_copy_target: test/CMakeFiles/test_game_copy_target
test_game_copy_target: test/always_rebuild
test_game_copy_target: test/copy_assets
test_game_copy_target: test/CMakeFiles/test_game_copy_target.dir/build.make
.PHONY : test_game_copy_target

# Rule to build all files generated by this target.
test/CMakeFiles/test_game_copy_target.dir/build: test_game_copy_target
.PHONY : test/CMakeFiles/test_game_copy_target.dir/build

test/CMakeFiles/test_game_copy_target.dir/clean:
	cd /d D:\code\cpp\gameGngine\build\test && $(CMAKE_COMMAND) -P CMakeFiles\test_game_copy_target.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/test_game_copy_target.dir/clean

test/CMakeFiles/test_game_copy_target.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\cpp\gameGngine D:\code\cpp\gameGngine\test D:\code\cpp\gameGngine\build D:\code\cpp\gameGngine\build\test D:\code\cpp\gameGngine\build\test\CMakeFiles\test_game_copy_target.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_game_copy_target.dir/depend
