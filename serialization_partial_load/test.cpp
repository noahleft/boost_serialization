#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <iostream>
#include <sstream>

BOOST_AUTO_TEST_CASE( string_compare )
{
    std::stringstream ss;
    ss << "Hello," << "World!";
    
    std::stringstream ss2;
    ss2 << "Hello," << "World!";
    
    std::stringstream ss3;
    ss3 << "Hi," << "World!";
    
    BOOST_CHECK(ss.str().compare(ss2.str())==0);
    BOOST_CHECK(ss.str().compare(ss3.str())!=0);
}
