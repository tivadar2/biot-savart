#include "vector3d.h"

/**
 * \file   vector3d.cpp
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  A Vector3d osztály függényeinek implementációja.
 */

/** \brief Értékadó konstruktor
 *
 * \param vec x, y, z értékét feltölti
 */
Vector3d::Vector3d(const Vector3d& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

/** \brief Értékadó konstruktor
 *
 * \param a x-nek adja értékét
 * \param b y-nek adja értékét
 * \param c z-nek adja értékét
 */
Vector3d::Vector3d(double a, double b, double c)
{
    x = a;
    y = b;
    z = c;
}

/** \brief Az x settere
 *
 * \param in x-nek adja értékét
 */
void Vector3d::setX(double in)
{
    x = in;
}

/** \brief Az y settere
 *
 * \param in y-nek adja értékét
 */
void Vector3d::setY(double in)
{
    y = in;
}

/** \brief Az z settere
 *
 * \param in z-nek adja értékét
 */
void Vector3d::setZ(double in)
{
    z = in;
}

/** \brief Az x gettere
 *
 * \return x értékét adja vissza
 */
double Vector3d::getX() const
{
    return x;
}

/** \brief Az y gettere
 *
 * \return y értékét adja vissza
 */
double Vector3d::getY() const
{
    return y;
}

/** \brief Az z gettere
 *
 * \return z értékét adja vissza
 */
double Vector3d::getZ() const
{
    return z;
}

/** \brief A gömbi koordinátarendszer-beli theta-t adja vissza.
 *
 * \return A gömbi koordinátarendszer-beli theta-t adja vissza
 */
double Vector3d::getTheta() const
{
    return atan2(sqrt(x*x + z*z), y);
}

/** \brief A gömbi koordinátarendszer-beli phi-t adja vissza.
 *
 * \return A gömbi koordinátarendszer-beli phi-t adja vissza
 */
double Vector3d::getPhi() const
{
    return atan2(z, x);
}

/** \brief A vektor abszolútértékét adja vissza.
 *
 * \return A vektor abszolútértékét adja vissza
 */
double Vector3d::abs() const
{
    return sqrt(x*x + y*y + z*z);
}

/** \brief A vektor hosszát logaritmikusan csökkenti.
 *
 * \return A logaritmikusan csökkentett hosszú Vector3d -t adja vissza.
 */
Vector3d Vector3d::log() const
{
    Vector3d res(x, y, z);
    double tmp = res.abs();
    double szorzo = (1.0 - exp(-tmp/20));
    res = res * szorzo;
    return res/tmp*4;
}

/** \brief Két Vector3d keresztszorzatát számolja ki.
 *
 * \param a Elsõ vektor
 * \param b Második vektor
 *
 * \return Két Vector3d keresztszorzatát adja vissza.
 */
Vector3d CrossProduct(const Vector3d& a, const Vector3d& b)
{
    Vector3d res;
    res.x = a.y*b.z - a.z*b.y;
    res.y = a.z*b.x - a.x*b.z;
    res.z = a.x*b.y - a.y*b.x;
    return res;
}

/** \brief Két Vector3d összeadására alkalmas operátor
 */
Vector3d Vector3d::operator+(const Vector3d& vec)
{
    Vector3d res(*this);
    res.x += vec.x;
    res.y += vec.y;
    res.z += vec.z;
    return res;
}

/** \brief Két Vector3d kivonására alkalmas operátor
 */
Vector3d Vector3d::operator-(const Vector3d& vec)
{
    Vector3d res(*this);
    res.x -= vec.x;
    res.y -= vec.y;
    res.z -= vec.z;
    return res;
}

/** \brief this-hez hozzáad egy másik Vector3d -t.
 */
const Vector3d& Vector3d::operator+=(const Vector3d& vec)
{
    *this = *this + vec;
    return *this;
}

/** \brief this-bõl kivon egy másik Vector3d -t.
 */
const Vector3d& Vector3d::operator-=(const Vector3d& vec)
{
    *this = *this - vec;
    return *this;
}

/** \brief Egy Vector3d és egy double-t összeszoroz (csak a vektor nagysága változik)
 * iránya ellentettjére változik, ha negatív az a.
 */
Vector3d Vector3d::operator*(double a)
{
    Vector3d res(*this);
    res.x *= a;
    res.y *= a;
    res.z *= a;
    return res;
}

/** \brief Egy Vector3d -t eloszt egy double-el (csak a vektor nagysága változik)
 * iránya ellentettjére változik, ha negatív az a.
 */
Vector3d Vector3d::operator/(double a)
{
    Vector3d res(*this);
    res.x /= a;
    res.y /= a;
    res.z /= a;
    return res;
}
