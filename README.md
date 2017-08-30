# jsInterpreter

git clone https://github.com/756445638/jsInterpreter

cd jsInterpreter 

depends: flex bison make gcc (on fedora execute "dnf(or yum) -y install flex bison make gcc",on ubuntu execute "apt-get -y install flex bison make gcc")

make

examples:

	./jsinterpreter example/hello.js

	./jsinterpreter example/closure.js

	./jsinterpreter example/recursive.js

	./jsinterpreter example/bubblesort.js

	./jsinterpreter example/gc_test.js

