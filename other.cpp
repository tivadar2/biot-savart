#include "other.h"

/**
 * \file   other.cpp
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  Egyéb függvények pl. Curve -t és VecField -et generáló függvények definíciója.
 */

Curve GenerateSolenoid(int N, double l, double r, int resolution)
{
    if(resolution <= 0)
        throw std::invalid_argument("Nem lehet 0 vagy annal kisebb a resolution Soleniod!");
    std::vector<Arrow> sol;
    sol.reserve(resolution);
    double dt = (double)1/resolution, omega = N*2*M_PI, h = l/resolution;
    /* A kis vonalak kezdõ és végpontjának kiszámítása */
    for(int t = -resolution/2; t < resolution/2;t++)
    {
        sol.push_back(Arrow(Vector3d(r*cos(omega*t*dt), r*sin(omega*t*dt), h*t),
                            Vector3d(r*cos(omega*(t+1)*dt), r*sin(omega*(t+1)*dt), h*(t+1))));
    }
    return Curve(sol);
}

Curve GenerateLine(double l, int resolution)
{
    if(resolution <= 0)
        throw std::invalid_argument("Nem lehet 0 vagy annal kisebb resolutionu Line!");
    std::vector<Arrow> lin;
    lin.reserve(resolution);
    double h = l/resolution;
    /* A kis vonalak kezdõ és végpontjának kiszámítása */
    for(int t = -resolution/2; t < resolution/2;t++)
    {
        lin.push_back(Arrow(Vector3d(0, h*t, 0),
                            Vector3d(0, h*(t+1), 0)));
    }
    return Curve(lin);
}

Curve GenerateToroid(double R, double r, int N, int resolution)
{
    if(resolution <= 0)
        throw std::invalid_argument("Nem lehet 0 vagy annal kisebb resolutionu Toroid!");
    if(N <= 0)
        throw std::invalid_argument("Nem lehet 0 vagy annal kisebb tekercsszamu Toroid!");
    std::vector<Arrow> tor;
    tor.reserve(resolution);
    double u = 2.0*M_PI/resolution, v = N*2.0*M_PI/resolution;
    /* A kis vonalak kezdõ és végpontjának kiszámítása */
    for(int t = 0; t < resolution;t++)
    {
        tor.push_back(Arrow(Vector3d((R + r*cos(v*t))*cos(u*t), r*sin(v*t), (R + r*cos(v*t))*sin(u*t)),
                            Vector3d((R + r*cos(v*(t+1)))*cos(u*(t+1)), r*sin(v*(t+1)), (R + r*cos(v*(t+1)))*sin(u*(t+1)))));
    }
    return Curve(tor);
}

VecField GenerateCompleteVecField(double d, int N, double x, double y, double z)
{
    if(N <= 0)
        throw std::invalid_argument("Nem lehet 0 vagy annal kevesebb pontu a VecField!");
    std::vector<Arrow> hely;
    hely.reserve(N*N*N);
    /* A vektormezõ értelmezési tartományának feltöltése */
    for(int i = -N/2;i < N/2;i++)
    {
        for(int j = -N/2;j < N/2;j++)
        {
            for(int k = -N/2;k < N/2;k++)
            {
                hely.push_back(Arrow(Vector3d(d*i + x, d*j + y, d*k + z), Vector3d()));
            }
        }
    }
    return hely;
}

VecField GeneratePlaneVecField(double d, int N, double x, double y, double z)
{
    if(N <= 0)
        throw std::invalid_argument("Nem lehet 0 vagy annal kevesebb pontu a VecField!");
    std::vector<Arrow> hely;
    hely.reserve(N*N);
    /* A vektormezõ értelmezési tartományának feltöltése */
    for(int i = -N/2;i < N/2;i++)
    {
        for(int k = -N/2;k < N/2;k++)
        {
            hely.push_back(Arrow(Vector3d(d*i + x, y, d*k + z), Vector3d()));
        }
    }
    return hely;
}
