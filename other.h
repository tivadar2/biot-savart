#ifndef _OTHER_H_
#define _OTHER_H_

#include <iostream>
#include <stdexcept>
#include "curve.h"

/**
 * \file   other.h
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  Egyéb függvények pl. Curve -t és VecField -et generáló függvények deklarációja.
 */

/** \brief Generál egy szolenoid alakú Curve -t
 * \details A demóban GenerateSolenoid(20, 10.0, 1.0, 800) a használt paraméterek.
 *
 * \param N A szolenoid menetszáma.
 * \param l A szolenoid hossza.
 * \param r A szolenoid sugara.
 * \param resolution A szolenoidot kitevõ kis egyenes vonalak darabszáma.
 *
 * \return Egy Curve típusu objektummal tér vissza, amiben a megadott paraméterek szerinti
 * szolenoid adatai vannak.
 */
Curve GenerateSolenoid(int N, double l, double r, int resolution);

/** \brief Generál egy egyenes Curve -t
 * \details A demóban GenerateLine(100.0, 100) a használt paraméterek.
 *
 * \param l Az egyenes hossza.
 * \param resolution Az egyenest kitevõ kis egyenes vonalak darabszáma.
 *
 * \return Egy Curve típusu objektummal tér vissza, amiben a megadott paraméterek szerinti
 * egyenes adatai vannak.
 */
Curve GenerateLine(double l, int resolution);

/** \brief Generál egy toroid alakú Curve -t
 * \details A demóban GenerateToroid(2.0, 0.5, 50, 1000) a használt paraméterek.
 *
 * \param R A toroid nagy sugara
 * \param r A toroid kis sugara.
 * \param N A toroid menetszáma.
 * \param resolution A toroidot kitevõ kis egyenes vonalak darabszáma.
 *
 * \return Egy Curve típusu objektummal tér vissza, amiben a megadott paraméterek szerinti
 * toroid adatai vannak.
 */
Curve GenerateToroid(double R, double r, int N, int resolution);

/** \brief Generál egy sík VecField -t
 * \details A demóban GeneratePlaneVecField(0.5, 10, 0.0, 0.0, 0.0) a használt alapparaméterek.
 * Csak a VecField from tagját tölti fel a to tagot nullázza.
 *
 * \param d A vektormezõ pontjai közti távolság.
 * \param N A vektormezõ egy dimenziójára jutó pontok száma.
 * Pl. 10 azt jelenti itt, hogy 10*10-es ponthalmaznak számolja ki a vektormezõjét.
 * \param x A vektormezõ pontjainak közepének az x koordinátája.
 * \param y A vektormezõ pontjainak közepének az y koordinátája.
 * \param z A vektormezõ pontjainak közepének az z koordinátája.
 *
 * \return Egy VecField típusu objektummal tér vissza, amiben a megadott paraméterek szerinti
 * vektormezõ adatai vannak.
 */
VecField GeneratePlaneVecField(double d, int N, double x, double y, double z);

/** \brief Generál egy térbeli VecField -t
 * \details A demóban GenerateCompleteVecField(0.5, 10, 0.0, 0.0, 0.0) a használt alapparaméterek.
 * Csak a VecField from tagját tölti fel a to tagot nullázza.
 *
 * \param d A vektormezõ pontjai közti távolság.
 * \param N A vektormezõ egy dimenziójára jutó pontok száma.
 * Pl. 10 azt jelenti itt, hogy 10*10*10-es ponthalmaznak számolja ki a vektormezõjét.
 * \param x A vektormezõ pontjainak közepének az x koordinátája.
 * \param y A vektormezõ pontjainak közepének az y koordinátája.
 * \param z A vektormezõ pontjainak közepének az z koordinátája.
 *
 * \return Egy VecField típusu objektummal tér vissza, amiben a megadott paraméterek szerinti
 * vektormezõ adatai vannak.
 */
VecField GenerateCompleteVecField(double d, int N, double x, double y, double z);

#endif // _OTHER_H_
