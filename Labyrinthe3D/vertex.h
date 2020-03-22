#ifndef VERTEX_H
#define VERTEX_H


class Vertex
{
public:
    Vertex();
    Vertex(double x, double y, double z);

    // GETTERS
    double getX(){return x_;};
    double getY(){return y_;};
    double getZ(){return z_;};

    // SETTERS
    void setX(double x){x_ = x;};
    void setY(double y){y_ = y;};
    void setZ(double z){z_ = z;};

    Vertex xContrary(){return Vertex(-x_,y_,z_);};

private:
    double x_;
    double y_;
    double z_;
};

#endif // VERTEX_H
