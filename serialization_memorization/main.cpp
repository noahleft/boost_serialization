/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//
// demo_log.cpp
//
// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cstdio>

#include "demo_gps.hpp"

typedef struct bus_stop_list {
    bus_stop_list *next;
    bus_stop *data;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & next;
        ar & data;
    }
} bus_stop_list_t;

int main(int argc, char *argv[])
{
    // fill in the data
    // make a few stops
    bus_stop *bs0 = new bus_stop_corner(
        gps_position(34, 135, 52.560f),
        gps_position(134, 22, 78.30f),
        "24th Street", "10th Avenue"
    );
    bus_stop *bs1 = new bus_stop_corner(
        gps_position(35, 137, 23.456f),
        gps_position(133, 35, 54.12f),
        "State street", "Cathedral Vista Lane"
    );
    bus_stop *bs2 = new bus_stop_destination(
        gps_position(35, 136, 15.456f),
        gps_position(133, 32, 15.300f),
        "White House"
    );
    bus_stop *bs3 = new bus_stop_destination(
        gps_position(35, 134, 48.789f),
        gps_position(133, 32, 16.230f),
        "Lincoln Memorial"
    );

    bus_stop_list_t* head = NULL;
    bus_stop_list_t* bsptr;
    // make bus stop list for bs0
    bsptr = new bus_stop_list_t();
    bsptr->data = bs0;
    bsptr->next = head;
    head = bsptr;
    // make bus stop list for bs1
    bsptr = new bus_stop_list_t();
    bsptr->data = bs1;
    bsptr->next = head;
    head = bsptr;
    // make bus stop list for bs2
    bsptr = new bus_stop_list_t();
    bsptr->data = bs2;
    bsptr->next = head;
    head = bsptr;
    // make bus stop list for bs3
    bsptr = new bus_stop_list_t();
    bsptr->data = bs3;
    bsptr->next = head;
    head = bsptr;
    // .... consider if we have millions of elements
    // the call stack would overflow during serializing it

    for(bsptr=head; bsptr; bsptr=bsptr->next)
    {
        std::cout<<*(bsptr->data)<<std::endl;
    }

    delete bs0;
    delete bs1;
    delete bs2;
    delete bs3;
    while(head) {
        bsptr = head->next;
        delete head;
        head = bsptr;
    }
    return 0;
}
