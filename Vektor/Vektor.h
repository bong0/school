/* 
 * File:   Vektor.h
 * Author: bongo
 *
 * Created on August 30, 2011, 8:26 AM
 */
#include <iostream>

#ifndef VEKTOR_H
#define	VEKTOR_H
class Vektor {
    private:
        double x;
        double y;
        double z;
        
    protected:
    public:
        Vektor();
        Vektor(double x, double y, double z);
        ~Vektor();
        std::string show();
        double Betrag();
        Vektor vadd(Vektor v1);
        double getX();
        double getY();
        double getZ();
        void setX(double x);
        void setY(double y);
        void setZ(double z);
        Vektor operator+(Vektor v1);
        double operator+(double f);
};
#endif	/* VEKTOR_H */

