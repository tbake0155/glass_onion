#include "coordinates.h"

#ifndef SEGMENT_H
#define SEGMENT_H

class segment
{
    public:
        segment(){}
        segment(coordinates origin, coordinates termination);
        ~segment(){}
        void set_origin(coordinates Origin){origin=Origin;}
        coordinates get_origin(){return origin;}
        void set_termination(coordinates terminal){termination=terminal;}
        coordinates get_termination(){return termination;}

    private:
        coordinates origin;
        coordinates termination;
};

#endif // SEGMENT_H
