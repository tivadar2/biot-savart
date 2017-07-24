#ifndef _CURVE_H_
#define _CURVE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/gl.h>
#include "arrow.h"
#include "vector3d.h"
#include "vecfield.h"

/**
 * \file   curve.h
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  A Curve osztály deklarációja.
 */

/**
 * \brief Curve osztály
 *
 * Egy vector<Arrow>-ban tárolja a vezeték kis egyenes darabjait. Minden darabhoz lehet
 * rendelni egy áramerősséget a current vectorban.
 * A with_current kapcsoló arra lenne jó, ha a vezetőben különböző erősségű
 * áramok folynának, akkor minden kis darabban folyhatna akár más-más áram.
 * De ez a funkció nem lett implementálva.
 */
class Curve {
    friend class VecField;
private:
    std::vector<Arrow> curve;
    std::vector<double> current;
    bool with_current;
public:
    Curve();
    Curve(const std::vector<Arrow>& cur);
    Curve(const char * path);
    void Load(const char * path);
    void Draw();
    friend std::istream& operator>>(std::istream& in, Curve& c);
    friend std::ostream& operator<<(std::ostream& out, Curve& c);
};

#endif // _CURVE_H_
