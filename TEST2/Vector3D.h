#pragma once
#include <iostream>
#include <string>

class Vector3D
{

public:
    double x;
    double y;
    double z;


    // Constructeur par d�faut
    Vector3D();

    // Constructeur avec des valeurs initiales
    Vector3D(double xVal, double yVal, double zVal);

    Vector3D& operator=(const Vector3D& autre);

    // M�thode pour additionner deux vecteurs
    Vector3D operator+(const Vector3D& autre) const;
    void operator+=(const Vector3D& autre);

    // M�thode pour soustraire un vecteur d'un autre
    Vector3D operator-(const Vector3D& autre) const;
    void operator-=(const Vector3D& autre);

    // M�thode pour multiplier le vecteur par un scalaire
    Vector3D operator*(double scalaire) const;
    void operator*=(double scalaire);

    double operator*(const Vector3D& other) const;

    // M�thode pour diviser le vecteur par un scalaire
    Vector3D operator/(double scalaire) const;
    void operator/=(double scalaire);

    

    // M�thode pour afficher le vecteur
    void afficher() const;

    // M�thode pour calculer la norme du vecteur
    double norme() const;

    // M�thode pour calculer le produit scalaire avec un autre vecteur
    double produitScalaire(const Vector3D& autre) const;

    // M�thode pour calculer le produit vectoriel avec un autre vecteur
    Vector3D produitVectoriel(const Vector3D& autre) const;

    // M�thode pour ajouter un vecteur redimension�
    Vector3D addScaledVector(const Vector3D& autre, double scale);

    // Calcul de la magnitude du vecteur
    double magnitude() const;

    //To string
    std::string ToStr();

    //Normalize vector
    void normalize();

    friend bool operator==(const Vector3D& l, const Vector3D& r) {
        return l.x == r.x && l.y == r.y && l.z == r.z;
    }
};

