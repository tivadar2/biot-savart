#include "arrow.h"

/**
 * \file   arrow.cpp
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  Az Arrow osztály függényeinek implementációja.
 */


/** \brief Alap konstruktor, minden értéket 0-ra állít.
 */
Arrow::Arrow()
{
    from = Vector3d();
    to = Vector3d();
}

/** \brief Értékadó konstruktor
 *
 * \param a a from értékét inicializálja
 * \param b a to értékét inicializálja
 */
Arrow::Arrow(const Vector3d &a, const Vector3d &b)
{
    from = a;
    to = b;
}

/** \brief A from tagváltozó gettere.
 *
 * \return Vector3d típusú from tagváltozó
 */
Vector3d Arrow::getFrom() const
{
    return from;
}

/** \brief A to tagváltozó gettere.
 *
 * \return Vector3d típusú to tagváltozó
 */
Vector3d Arrow::getTo() const
{
    return to;
}

/** \brief A from tagváltozó settere.
 *
 * \param vec from-nak ad értéket
 */
void Arrow::setFrom(const Vector3d& vec)
{
    from = vec;
}

/** \brief A to tagváltozó settere.
 *
 * \param vec to-nak ad értéket
 */
void Arrow::setTo(const Vector3d& vec)
{
    to = vec;
}

/** \brief A nyíl gömbi koordinátarendszer-beli theta szögét adja vissza radiánban.
 *
 * \return A nyíl gömbi koordinátarendszer-beli theta szögét adja vissza radiánban.
 */
double Arrow::getTheta()
{
    return (to - from).getTheta();
}

/** \brief A nyíl gömbi koordinátarendszer-beli phi szögét adja vissza radiánban.
 *
 * \return A nyíl gömbi koordinátarendszer-beli phi szögét adja vissza radiánban.
 */
double Arrow::getPhi()
{
    Vector3d tmp = to - from;
    return tmp.getPhi();
}
