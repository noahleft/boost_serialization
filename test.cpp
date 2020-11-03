#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include <openssl/md5.h>
#include <string>
#include <iostream>

std::string convert_md5(unsigned char* md5) {
    std::string retString = "";
    char buf[3];
    for(int i=0; i<MD5_DIGEST_LENGTH; i++) {
        snprintf(buf, 2, "%02x", md5[i]);
        retString+=buf;
    }
    return retString;
}

BOOST_AUTO_TEST_CASE( md5 )
{
    unsigned char result[MD5_DIGEST_LENGTH];
    unsigned char candidate[] = "";
    size_t len = 0;
    MD5(candidate, len, result);

    unsigned char result2[MD5_DIGEST_LENGTH];
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, candidate, len);
    MD5_Final(result2, &context);
    BOOST_CHECK(convert_md5(result) == convert_md5(result2));
}