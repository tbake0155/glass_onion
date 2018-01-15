#include "crack.h"
#include <math.h>
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void crack::print_segments(std::ostream &out)
{
    std::list<segment>::iterator segment_itr;

    segment_itr=segments.begin();
    while(segment_itr!=segments.end())
    {
        out<<segment_itr->get_origin().getX()<<" "<<segment_itr->get_origin().getY()<<std::endl;
        out<<segment_itr->get_termination().getX()<<" "<<segment_itr->get_termination().getY()<<std::endl;
        out<<std::endl;
        segment_itr++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void crack::first_segment(double length, double radians)
{
    coordinates origin;

    double terminal_x=origin.getX() + length*cos(radians);
    double terminal_y=origin.getY() + length*sin(radians);

    coordinates termination(terminal_x, terminal_y);

    segment * segment_ptr=new segment(origin, termination);
    segments.push_back(*segment_ptr);
    delete segment_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void crack::add_segment(double length, double radians)
{
    if(radians==-1.0)
    {
        radians=last_angle;
    }
    else
    {
        last_angle=radians;
    }

    coordinates origin=segments.back().get_termination();

    double terminal_x=origin.getX() + length*cos(radians);
    double terminal_y=origin.getY() + length*sin(radians);

    coordinates termination(terminal_x, terminal_y);

    segment * segment_ptr=new segment(origin, termination);
    segments.push_back(*segment_ptr);
    delete segment_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void crack::add_segment(double length, double radians, coordinates origin)
{
    if(radians==-1.0)
    {
        radians=last_angle;
    }
    else
    {
        last_angle=radians;
    }

    double terminal_x=origin.getX() + length*cos(radians);
    double terminal_y=origin.getY() + length*sin(radians);

    coordinates termination(terminal_x, terminal_y);

    segment * segment_ptr=new segment(origin, termination);
    segments.push_back(*segment_ptr);
    delete segment_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
bool crack::operator<(const crack& other)const
{
    if(this->last_angle < other.last_angle)
    {
        return true;
    }
    return false;

}
