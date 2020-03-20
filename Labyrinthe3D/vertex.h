#ifndef VERTEX_H
#define VERTEX_H


class Vertex
{
public:
    Vertex(double x, double y, double z);
    double getX(){return x_;};
    double getY(){return y_;};
    double getZ(){return z_;};
    Vertex xContrary(){return Vertex(-x_,y_,z_);};

private:
    double x_;
    double y_;
    double z_;
};

#endif // VERTEX_H
