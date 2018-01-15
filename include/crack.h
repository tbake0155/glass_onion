#include "segment.h"
#include <list>
#include <random>
#include <iostream>

#ifndef CRACK_H
#define CRACK_H

class crack
{
    public:
        crack(){terminator=false;}
        ~crack(){}
        bool get_terminator() { return terminator; }
        void set_terminator(bool val) { terminator = val; }
        std::list<segment> get_segments(){return segments;}
        void print_segments(std::ostream &out);
        void add_segment(double length, double radians);
        void add_segment(double length, double radians, coordinates origin);
        void first_segment(double length, double radians);
        bool operator<(const crack& other)const;

    private:
        bool terminator;
        double last_angle;
        std::list<segment> segments;
};

#endif // CRACK_H
