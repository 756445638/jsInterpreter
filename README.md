# jsInterpreter

git clone https://github.com/756445638/jsInterpreter
cd jsInterpreter 
depends: flex bison make gcc (on fedora excute "dnf -y install flex bison make gcc")
make clean && make

examples:
./jsinterpreter example/hello.js

./jsinterpreter example/closure.js

./jsinterpreter example/recursive.js

./jsinterpreter example/bubblesort.js

./jsinterpreter example/gc_test.js

