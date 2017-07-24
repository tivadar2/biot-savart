#include "curve.h"

/**
 * \file   curve.cpp
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  A Curve osztály függényeinek implementációja.
 *
 */

/** \brief Üres konstruktor
 */
Curve::Curve()
{

}

/** \brief Értékadó konstruktor
 *
 * \details az áramerősség 1.0 értékű az egész vezetőben
 *
 * \param cur a curve-nek ad értéket
 */
Curve::Curve(const std::vector<Arrow>& cur)
{
    curve = cur;
    current.push_back(1.0);
    with_current = false;
}

/** \brief Beolvasó konstruktor
 *
 * \details Fájlból beolvassa a Curve -t
 *
 * \param path a beolvasandó fájl elérési útvonala
 */
Curve::Curve(const char * path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
    file.open(path);
    }
    catch(std::ifstream::failure)
    {
        std::cerr << "Hiba, nem letezik ilyen Curve file!" << std::endl;
    }
    file >> (*this);
    file.close();
}

/** \brief Curve beolvasó
 *
 * \details Fájlból beolvassa a Curve -t
 *
 * \param path a beolvasandó fájl elérési útvonala
 */
void Curve::Load(const char * path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
    }
    catch(std::ifstream::failure)
    {
        std::cerr << "Hiba, nem letezik ilyen Curve file!" << std::endl;
    }
    file >> (*this);
    file.close();
}

/** \brief Kirajzoló függvény
 */
void Curve::Draw()
{
    glPushMatrix();
	glLineWidth(1.5f);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_LINES);
	/* Kicsiny darabokat összekötő egyenes kirajzolása */
	for(unsigned int i = 0;i < curve.size();i++)
    {
        glVertex3d(curve[i].getFrom().getX(),
                   curve[i].getFrom().getY(),
                   curve[i].getFrom().getZ());
        glVertex3d(curve[i].getTo().getX(),
                   curve[i].getTo().getY(),
                   curve[i].getTo().getZ());
    }
	glEnd();
	glPopMatrix();
}

/** \brief Beolvasó operátor
 *
 * \details Streamból beolvassa a Curve -t
 * Formátum: első sor: $kis vonaldarabok száma/sorok száma$ $"with_current"/"without_current"$
 * if(without_current)$ current értéke $
 * Többi sor: $x$ $y$ $z$ a vezető x, y, z koordinátái
 */
std::istream& operator>>(std::istream& in, Curve& c)
{
    int n;
    std::string flag;
    in >> n >> flag;
    c.curve.reserve(n);
    if(flag == "with_current")
    {
        c.with_current = true;
        c.current.reserve(n);
        double fromX, fromY, fromZ, toX, toY, toZ, curr;
        for(int i = 0;i < n;i++)
        {
            in >> fromX >> fromY >> fromZ;
            in >> toX >> toY >> toZ;
            in >> curr;
            c.curve.push_back(Arrow(Vector3d(fromX, fromY, fromZ),
                                    Vector3d(toX, toY, toZ)));
            c.current.push_back(curr);
        }
    }
    else if(flag == "without_current")
    {
        c.with_current = false;
        double curr;
        in >> curr;
        c.current.push_back(curr);
        double fromX, fromY, fromZ, toX, toY, toZ;
        for(int i = 0;i < n;i++)
        {
            in >> fromX >> fromY >> fromZ;
            in >> toX >> toY >> toZ;
            c.curve.push_back(Arrow(Vector3d(fromX, fromY, fromZ),
                                    Vector3d(toX, toY, toZ)));
        }
    }
    return in;
}

/** \brief Kiíró operátor
 *
 * \details Streambe írja a Curve -t
 * Formátum: első sor: $kis vonaldarabok száma/sorok száma$ $"with_current"/"without_current"$
 * if(without_current)$ current értéke $
 * Többi sor: $x$ $y$ $z$ a vezető x, y, z koordinátái
 */
std::ostream& operator<<(std::ostream& out, Curve& c)
{
    out << c.curve.size() << " ";
    if(c.with_current)
    {
        out << "with_current";
        for(unsigned int i = 0;i < c.curve.size();i++)
        {
            out << std::endl;
            out << c.curve[i].getFrom().getX() << " ";
            out << c.curve[i].getFrom().getY() << " ";
            out << c.curve[i].getFrom().getZ() << "\t";
            out << c.curve[i].getTo().getX() << " ";
            out << c.curve[i].getTo().getY() << " ";
            out << c.curve[i].getTo().getZ() << "\t";
            out << c.current[i];
        }
    }
    else
    {
        out << "without_current" << " " << c.current[0];
        for(unsigned int i = 0;i < c.curve.size();i++)
        {
            out << std::endl;
            out << c.curve[i].getFrom().getX() << " ";
            out << c.curve[i].getFrom().getY() << " ";
            out << c.curve[i].getFrom().getZ() << "\t";
            out << c.curve[i].getTo().getX() << " ";
            out << c.curve[i].getTo().getY() << " ";
            out << c.curve[i].getTo().getZ();
        }
    }
    return out;
}
