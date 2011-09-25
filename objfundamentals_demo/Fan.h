/* 
 * File:   Fan.h
 * Author: bongo
 *
 * Created on September 7, 2011, 6:11 PM
 */

#ifndef FAN_H
#define	FAN_H

class Fan {
public:
    Fan();
    Fan(std::string fan_model, long rotation_speed, bool hooligan);
    Fan(const Fan& orig); /* Copy-Konstuktor:
                           * erstellt neues Objekt von einem
                           * existierenden
                           */
    void print();
    virtual ~Fan();
private:
    std::string fan_model;
    long rotation_speed;
    bool hooligan;
};

#endif	/* FAN_H */

