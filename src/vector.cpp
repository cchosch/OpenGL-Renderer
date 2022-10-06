#include <iostream>
#include <cmath>

class Vector3{
public:

    double x;
    double y;
    double z;


    void normalize(){
        double len = this->length();
        this->x = this->x/len;
        this->y = this->y/len;
        this->z = this->z/len;
    };

    double length(){
        return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));
    }

    std::string outVec(){
        return "Vector3("+std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z)+")";
    }

    Vector3(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    };

};
