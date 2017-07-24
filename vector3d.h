#ifndef _VECTOR3D_h_
#define _VECTOR3D_h_

#include <cmath>

/**
 * \file   vector3d.h
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  A Vector3d osztály deklarációja.
 */


/**
 * \brief Vector3d osztály
 *
 * 3 double tagváltozója van, melyek egy 3d-s vektort reprezentálnak Descartes-koordinátákkal.
 * A vektorokat összeadhatjuk, kivonhatjuk, számmal oszthatjuk, szorozhatjuk, vehetjük az
 * abszolútértékét a hosszát logaritmikusan csökkenthetjük és mint helyvektornak meghatározhatjuk
 * a gömbi koordinátarendszer-beli theta és phi szöget. (abs(), getTheta(), getPhi())
 */
class Vector3d {
private:
    double x, y, z;
public:
    Vector3d(const Vector3d& vec);
    Vector3d(double a = 0.0, double b = 0.0, double c = 0.0);
    void setX(double in);
    void setY(double in);
    void setZ(double in);
    double getX() const;
    double getY() const;
    double getZ() const;
    double getTheta() const;
    double getPhi() const;

    double abs() const;
    Vector3d log() const;
    friend Vector3d CrossProduct(const Vector3d& a, const Vector3d& b);

    Vector3d operator+(const Vector3d& vec);
    Vector3d operator-(const Vector3d& vec);
    const Vector3d& operator+=(const Vector3d& vec);
    const Vector3d& operator-=(const Vector3d& vec);
    Vector3d operator*(double a);
    Vector3d operator/(double a);
};

#endif // _VECTOR3D_h_
