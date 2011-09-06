/* 
 * File:   konto.h
 * Author: bongo
 *
 * Created on August 16, 2011, 9:46 AM
 */
#define uint unsigned int
#ifndef KONTO_H
#define KONTO_H
class Konto {
    private: // Datenkapselung (default)
        uint ktonr;
        double ktostand;
        std::string inhaber;
        std::string pin;
        void setPIN(std::string pin);
        bool isAuthorized;

    protected: // Zugriff f. Methoden d. Klasse u. Methoden abgel. Klassen

    public:
        Konto();
        Konto(uint _ktonr, double _ktostand, std::string inhaber, std::string pin="1234");
        uint getKontoNr();
        void setKontoNr(uint _ktonr);
        bool einzahlen(double betrag);
        bool abheben(double betrag);
        double getKontoStand();
        std::string getKontoInhaber();
        bool pinIsValid(std::string hashedPIN);
        ~Konto();
};
#endif