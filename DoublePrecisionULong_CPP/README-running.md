Before running the program, you should build/compile it, via
* the easiest way to compile, the green hammer-shaped "build" button in C-Lion
* you can also use "Build->Rebuild Project", if you want to see the warnings for every file
* if you are familiar with cmake (or clang) you can use those tools on the command-line

Once you've built/compiled the program, you can run it
* from within C-Lion, with the triangular green "play" button

* from within C-Lion, for debugging, with the green bug button by the play button

* from the command-line, via

      cmake-build-debug/DoublePrecisionULong_CPP

* from the command-line, with valgrind, via

      valgrind cmake-build-debug/DoublePrecisionULong_CPP

* from the command-line, with valgrind, and providing the input "0 0", via

      echo 0 0 | valgrind cmake-build-debug/DoublePrecisionULong_CPP

* from the command-line, with valgrind and input, and command-line arguments
  (arguments to valgrind, such as "--leak-check=full", are given after valgrind;
  arguments to the program on "doctest" within the program, e.g., "-nr" to Not Run tests,
  are given after the program name), via

      echo 0 0 | valgrind --leak-check=full cmake-build-debug/DoublePrecisionULong_CPP  -nr
