#ifndef VERTEX_H
#define VERTEX_H


class Vertex
{
public:
    Vertex();
    Vertex(float x, float y, float z);

    // GETTERS
    float getX(){return x_;};
    float getY(){return y_;};
    float getZ(){return z_;};

    // SETTERS
    void setX(float x){x_ = x;};
    void setY(float y){y_ = y;};
    void setZ(float z){z_ = z;};

    Vertex xContrary(){return Vertex(-x_,y_,z_);};

private:
    float x_;
    float y_;
    float z_;
};

#endif // VERTEX_H
