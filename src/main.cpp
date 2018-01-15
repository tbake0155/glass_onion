#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
#include <list>
#include "crack.h"

using namespace std;

int main()
{
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Global Variables
    //
    default_random_engine random_engine(time(NULL));
    uniform_int_distribution<int> origin_dist(3,6);                   //initial cracks
    uniform_int_distribution<int> shatter_dist(0,101);                //event probability
    uniform_real_distribution<double> radian_dist(0,6.28318530718);   //from 0pi to 2pi
    normal_distribution<double> crack_dist(3.0, 1.0);                 //crack length
    bool control_freak=false;      // will end end simulation when all cracks have terminated
    double largest_value=0.0;      // largest x or y value in gnuplot graph
    list<crack> glass_onion;       // list of cracks
    list<crack>::iterator glass_onion_itr;

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Alert User Simulation will begin
    //
    cout<<"\nGlass Shattering Simulation started..."<<endl;

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Simulation Pre-Loop Initialization
    //
    //create initial cracks
    crack * crack_ptr;
    for(int i=0;i<origin_dist(random_engine);i++)
    {
        crack_ptr = new crack(); //create random number of cracks from the origin
        glass_onion.push_back(*crack_ptr);
        delete crack_ptr;
    }

    //create initial crack segments
    glass_onion_itr=glass_onion.begin();
    while(glass_onion_itr!=glass_onion.end())
    {
        glass_onion_itr->first_segment(crack_dist(random_engine),radian_dist(random_engine));
        glass_onion_itr++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Simulation Loop
    //
    while(control_freak==false)
    {
        control_freak=true;
        list<crack>new_cracks;

        glass_onion_itr=glass_onion.begin();
        while(glass_onion_itr!=glass_onion.end())
        {
            if(glass_onion_itr->get_terminator()==false)
            {
                control_freak=false;
                //simulation loop variables
                double length=crack_dist(random_engine);
                double radians=radian_dist(random_engine);
                int lottery=shatter_dist(random_engine);

                if(lottery<10)
                {
                    glass_onion_itr->add_segment(length,-1.0);
                }
                else if(lottery<35)
                {
                    glass_onion_itr->add_segment(length,radians);
                }
                else if(lottery<67)
                {
                    double length2=crack_dist(random_engine);
                    double radians2=radian_dist(random_engine);
                    coordinates origin=glass_onion_itr->get_segments().back().get_origin();
                    glass_onion_itr->add_segment(length,radians);
                    crack * new_crack=new crack();
                    new_crack->add_segment(length2, radians2, origin);
                    new_cracks.push_back(*new_crack);
                }
                else if(lottery<=101)
                {
                    glass_onion_itr->set_terminator(true);
                }
            }
            glass_onion_itr++;
        }
        glass_onion.sort();
        new_cracks.sort();
        glass_onion.merge(new_cracks);
        new_cracks.clear();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Alert User Simulation has ended and gnu plot is being called
    //
    cout<<"Number of cracks: "<<glass_onion.size()<<endl<<endl;
    cout<<"Gnuplot is generating a shatter plot..."<<endl;
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Plot crack simulation
    //
    //determine largest x or y value
    glass_onion_itr=glass_onion.begin();
    while(glass_onion_itr!=glass_onion.end())
    {
        if(glass_onion_itr->get_segments().back().get_termination().getX() > largest_value)
        {
            largest_value=glass_onion_itr->get_segments().back().get_termination().getX();
        }
        if(glass_onion_itr->get_segments().back().get_termination().getY() > largest_value)
        {
            largest_value=glass_onion_itr->get_segments().back().get_termination().getY();
        }
        glass_onion_itr++;
    }

    //File stream for crack data
    fstream gnu_origin;
    gnu_origin.open("gnu_origin.txt", ios::out);
    gnu_origin<<0.0<<" "<<0.0<<endl;
    gnu_origin.flush();
    gnu_origin.close();

    fstream gnu_crack;
    gnu_crack.open("gnu_cracks.txt", ios::out);
    glass_onion_itr=glass_onion.begin();
    while(glass_onion_itr!=glass_onion.end())
    {
        glass_onion_itr->print_segments(gnu_crack);
        glass_onion_itr++;
    }
    gnu_crack<<flush;
    gnu_crack.close();

    //File stream for gnu plot command file
    fstream gnu_command;
    gnu_command.open("gnu_command.txt", ios::out);
    gnu_command<<"set terminal png size 1920, 1080"<<endl;
    gnu_command<<"set output '"<<"shatter_plot.png"<<endl;
    gnu_command<<"set xrange [-"<<largest_value+10.0<<":"<<largest_value+10.0<<"]"<<endl;
    gnu_command<<"set yrange [-"<<largest_value+10.0<<":"<<largest_value+10.0<<"]"<<endl;
    gnu_command<<"plot \"gnu_cracks.txt\" with lines, \"gnu_origin.txt\" with points pointtype 7 pointsize 2"<<endl;
    gnu_command<<" quit"<<endl;
    gnu_command<<flush;
    gnu_command.close();

    //system call to gnuplot.exe in local directory
    system("gnuplot gnu_command.txt");

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    //Alert User Simulation has completed
    //
    cout<<"\nThe Simulation is Complete!!!"<<endl;
    cout<<"Output file is 'shatter_plot.png'"<<endl;

    return 0;
}
