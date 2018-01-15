#ifndef COORDINATES_H
#define COORDINATES_H


class coordinates
{
    public:
        coordinates();
        coordinates(double x, double y);
        ~coordinates();
        double getX() { return x; }
        void setX(double val) { x = val; }
        double getY() { return y; }
        void setY(double val) { y = val; }
    private:
        double x;
        double y;
};

#endif // COORDINATES_H
