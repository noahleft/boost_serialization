
prog: *.cpp
	g++ main.cpp -o prog -I/usr/local/opt/openssl@1.1/include -lcrypto

test: *.cpp
	g++ test.cpp -o test -I/usr/local/opt/openssl@1.1/include -lcrypto
	./test

clean:
	rm -f prog
	rm -f test



