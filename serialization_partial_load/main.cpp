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
#include "simple_log_archive.hpp"
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

int main(int argc, char *argv[])
{
    // make the schedule
    bus_schedule schedule;
    bus_schedule another_schedule;

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

    // make a  routes
    bus_route route0;
    route0.append(bs0);
    route0.append(bs1);
    route0.append(bs2);

    // add trips to schedule
    schedule.append("bob", 6, 24, &route0);
    schedule.append("bob", 9, 57, &route0);
    schedule.append("alice", 11, 02, &route0);

    // make aother routes
    bus_route route1;
    route1.append(bs3);
    route1.append(bs2);
    route1.append(bs1);

    // add trips to schedule
    another_schedule.append("ted", 7, 17, &route1);
    another_schedule.append("ted", 9, 38, &route1);
    another_schedule.append("alice", 11, 47, &route1);

    // use string stream to capture serialization result
    std::string original_schedule_string;
    {
        std::stringstream ss;
        simple_log_archive slog(ss);
        slog << schedule;
        original_schedule_string = ss.str();
    }

    // write out all data
    {
        std::ofstream ofs("tmp.db");
        boost::archive::text_oarchive oa(ofs);
        oa << schedule;
        oa << another_schedule;
    }

    // read the first data object to program
    // use string stream to capture serialization result
    std::string restored_schedule_string;
    {
        std::ifstream ifs("tmp.db");
        boost::archive::text_iarchive ia(ifs);
        bus_schedule tmp_schedule;
        ia >> tmp_schedule;

        std::stringstream ss;
        simple_log_archive slog(ss);
        slog << tmp_schedule;
        restored_schedule_string = ss.str();
    }

    if(original_schedule_string.compare(restored_schedule_string) !=0)
        std::cout << "save and restore strings are different." << std::endl;
    else
        std::cout << "save and restore strings are equal." << std::endl;

    delete bs0;
    delete bs1;
    delete bs2;
    delete bs3;
    return 0;
}
