# CMake generated Testfile for 
# Source directory: /home/alex/solyuway/workspace/tasks/lab05
# Build directory: /home/alex/solyuway/workspace/tasks/lab05/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BankingTests "/home/alex/solyuway/workspace/tasks/lab05/build/banking_tests")
set_tests_properties(BankingTests PROPERTIES  _BACKTRACE_TRIPLES "/home/alex/solyuway/workspace/tasks/lab05/CMakeLists.txt;67;add_test;/home/alex/solyuway/workspace/tasks/lab05/CMakeLists.txt;0;")
subdirs("third-party/gtest")
