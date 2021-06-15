
all: hello.gz prog prog_nolib

hello.gz:
	echo 'hello world' > hello
	bzip2 hello

prog: *.cpp
	g++ main.cpp -o prog -lboost_iostreams

prog_nolib: *.cpp
	g++ main.cpp bzip2.cpp -o prog_nolib -lbz2

clean:
	rm -f prog*
	rm -f hello hello.bz2



