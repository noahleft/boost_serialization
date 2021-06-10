
all: hello.gz prog

hello.gz:
	echo 'hello world' > hello
	bzip2 hello

prog: *.cpp
	g++ main.cpp -o prog -lboost_iostreams

clean:
	rm -f prog
	rm -f hello hello.bz2



