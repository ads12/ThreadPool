# ThreadPool
C++ 11/14 implementation of simple Threadpool library with unit tests using Code block Unit test library.

**Prerequisites:**
- g++ compiler with C++11/14 support
- MinGW package for Windows execution
- Code Block unit test library framework at link <br />
http://wiki.codeblocks.org/index.php/UnitTesting#Unit_Test_frameworks

**Compilation/Execution**<br />
_Linux Platform_:<br />
g++ -Wall -fexceptions -g -std=c++14  -c ./main.cpp -o ./main.o <br />
g++ -o test.out main.o <br />

_Windows Platform_:<br />
g++.exe -Wall -fexceptions -g -std=c++14  -c main.cpp -o main.o<br />
g++.exe  -o Test.exe main.o <br />

**Sample Output** <br />
Thread ID : 2 inserted vector element   Vector size::1 <br />
Thread ID : 4 inserted vector element   Vector size::2 <br />
Thread ID : 6 inserted vector element   Vector size::3 <br />
Thread ID : 8 inserted vector element   Vector size::4 <br />
Thread ID : 10 inserted vector element  Vector size::5 <br />
Thread ID : 9 removed vector element    Vector size::4 <br />
Thread ID : 3 removed vector element    Vector size::3 <br />
Thread ID : 5 removed vector element    Vector size::2 <br />
Thread ID : 11 removed vector element   Vector size::1 <br />
Thread ID : 7 removed vector element    Vector size::0 <br />
thread joined <br />
Process returned 0 (0x0)   execution time : 0.169 s <br />
Press any key to continue. <br />

**Running Unit tests** <br />

_Linux Platform:_ <br />
g++ -Wall -std=c++14 -fexceptions -std=c++14 -g -std=c++14 -I../../UnitTest++/UnitTest++ -I../../UnitTest++/UnitTest++ -c test_main.cpp -o test_main.o <br />
g++ -o Test1.out test_main.o   ../../UnitTest++/Deliv/Release/libUnitTest++.a <br />

_Windows Platform_ <br />
g++.exe -Wall -std=c++14 -fexceptions -std=c++14 -g -std=c++14 -I..\..\UnitTest++\UnitTest++ -I..\..\UnitTest++\UnitTest++ -c test_main.cpp -o test_main.o <br />
g++.exe  -o Test1.exe test_main.o   ..\..\UnitTest++\Deliv\Release\libUnitTest++.a <br />

**Sample Output** <br />
Success: 3 tests passed. <br />
Test time: 0.03 seconds. <br />

Process returned 0 (0x0)   execution time : 0.085 s <br />
Press any key to continue. <br />
