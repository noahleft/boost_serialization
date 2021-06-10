#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

int main() 
{
    using namespace std;
    using namespace boost::iostreams;

    ifstream file("hello.bz2", ios_base::in | ios_base::binary);
    boost::iostreams::filtering_streambuf<input> in;
    in.push(bzip2_decompressor());
    in.push(file);
    boost::iostreams::copy(in, cout);
}