#ifndef _VECFIELD_H_
#define _VECFIELD_H_

#include <fstream>
#include <locale>
#include <vector>
#include "vector3d.h"
#include "curve.h"

/**
 * \file   vecfield.h
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  A VecField osztály deklarációja.
 */

class Curve;

/**
 * \brief VecField osztály
 *
 * Van egy vector<Arrow> adattagja. Egy Arrow -ban tárolja a vektormezõ egy pontját.
 * A kirajzolás gyorsítása végett az Arrow from és to értéke a kirajzolni kívánt vonal
 * kezdõ és végpontja. De meg lehetne úgy is valósítani, hogy a from érték legyen az értelmezési
 * tartomány egy pontja, a to pedig az ott felvett érték.
 */
class VecField {
private:
    std::vector<Arrow> field;
public:
    static double arrowLength;
    VecField(const std::vector<Arrow>& places);
    void CalculateB(const Curve& curve);
    void Draw();

    void saveFile();
};

template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};

#endif // _VECFIELD_H_
