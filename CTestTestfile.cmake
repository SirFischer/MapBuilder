# CMake generated Testfile for 
# Source directory: /home/mfischer/Marek/Work/DeepVertic/Tools/MapBuilder
# Build directory: /home/mfischer/Marek/Work/DeepVertic/Tools/MapBuilder
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RunMapBuilder "/home/mfischer/Marek/Work/DeepVertic/Tools/MapBuilder/MapBuilder")
set_tests_properties(RunMapBuilder PROPERTIES  WORKING_DIRECTORY "/home/mfischer/Marek/Work/DeepVertic/Tools/MapBuilder" _BACKTRACE_TRIPLES "/home/mfischer/Marek/Work/DeepVertic/Tools/MapBuilder/CMakeLists.txt;125;add_test;/home/mfischer/Marek/Work/DeepVertic/Tools/MapBuilder/CMakeLists.txt;0;")
subdirs("mfGUI")
