#pragma once
#include <iostream>

class Vector3D
{

public:
    double x;
    double y;
    double z;


    // Constructeur par défaut
    Vector3D();

    // Constructeur avec des valeurs initiales
    Vector3D(double xVal, double yVal, double zVal);

    // Méthode pour additionner deux vecteurs
    Vector3D operator+(const Vector3D& autre) const;
    void operator+=(const Vector3D& autre);

    // Méthode pour soustraire un vecteur d'un autre
    Vector3D operator-(const Vector3D& autre) const;
    void operator-=(const Vector3D& autre);

    // Méthode pour multiplier le vecteur par un scalaire
    Vector3D operator*(double scalaire) const;
    void operator*=(double scalaire);

    // Méthode pour diviser le vecteur par un scalaire
    Vector3D operator/(double scalaire) const;
    void operator/=(double scalaire);

    // Méthode pour afficher le vecteur
    void afficher() const;

    // Méthode pour calculer la norme du vecteur
    double norme() const;

    // Méthode pour calculer le produit scalaire avec un autre vecteur
    double produitScalaire(const Vector3D& autre) const;

    // Méthode pour calculer le produit vectoriel avec un autre vecteur
    Vector3D produitVectoriel(const Vector3D& autre) const;

    // Méthode pour ajouter un vecteur redimensioné
    Vector3D addScaledVector(const Vector3D& autre, double scale);
};

