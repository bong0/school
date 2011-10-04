/* 
 * File:   KennlinienAblage.h
 * Author: bongo
 *
 * Created on September 22, 2011, 10:38 AM
 */

//#ifndef KENNLINIENABLAGE_H
//#define	KENNLINIENABLAGE_H
#pragma once

class KennlinienAblage {
public:
    KennlinienAblage(int anzahl);
    KennlinienAblage(int anzahl, float parr[][2]);
    KennlinienAblage(const KennlinienAblage& orig); // der copy-Konstruktor
    KennlinienAblage& operator=(const KennlinienAblage& orig); // der überladene = Operator
    float getI(float u);
    float getU(float i);
    bool setData();
    int binSearch(int lb, int rb, float key, int search_line);
    void show();
    virtual ~KennlinienAblage();
private:
    void init(int anzahl, float parr[][2]);
    float (*parr)[2];
    int anzahl;
};

//#endif	/* KENNLINIENABLAGE_H */

