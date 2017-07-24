#ifndef _ARROW_H_
#define _ARROW_H_

#include "vector3d.h"

/**
 * \file   arrow.h
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  Az Arrow osztály deklarációja.
 */

/**
 * \brief Arrow osztály
 *
 * Két Vector3d típusú vektort tárol.
 */
class Arrow {
private:
    Vector3d from;
    Vector3d to;
public:
    Arrow();
    Arrow(const Vector3d &a, const Vector3d &b);
    Vector3d getFrom() const;
    Vector3d getTo() const;
    void setFrom(const Vector3d& vec);
    void setTo(const Vector3d& vec);
    double getTheta();
    double getPhi();
};

#endif // _ARROW_H_
