#include <iostream>

class Vecteur3D {

private:
    double x;
    double y;
    double z;

public:

    // Constructeur par défaut
    Vecteur3D() : x(0.0), y(0.0), z(0.0) {}

    // Constructeur avec des valeurs initiales
    Vecteur3D(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}

    // Méthode pour afficher le vecteur
    void afficher() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    // Méthode pour calculer la norme du vecteur
    double norme() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Méthode pour additionner deux vecteurs
    Vecteur3D operator+(const Vecteur3D& autre) const {
        return Vecteur3D(x + autre.x, y + autre.y, z + autre.z);
    }

    // Méthode pour soustraire un vecteur d'un autre
    Vecteur3D operator-(const Vecteur3D& autre) const {
        return Vecteur3D(x - autre.x, y - autre.y, z - autre.z);
    }

    // Méthode pour multiplier le vecteur par un scalaire
    Vecteur3D operator*(double scalaire) const {
        return Vecteur3D(x * scalaire, y * scalaire, z * scalaire);
    }

    // Méthode pour calculer le produit scalaire avec un autre vecteur
    double produitScalaire(const Vecteur3D& autre) const {
        return x * autre.x + y * autre.y + z * autre.z;
    }

    // Méthode pour calculer le produit vectoriel avec un autre vecteur
    Vecteur3D produitVectoriel(const Vecteur3D& autre) const {
        return Vecteur3D(y * autre.z - z * autre.y, z * autre.x - x * autre.z, x * autre.y - y * autre.x);
    }
};