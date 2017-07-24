#include "vecfield.h"

/**
 * \file   vecfield.cpp
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  Az VecField osztály függényeinek implementációja.
 */

/** \brief Konstruktor ami a private tagnak ad értéket.
 * \details A field tagváltozót inicalizálja ez a konstruktor a paraméteren keresztül.
 *
 * \param places A field tagváltozónak átadott érték.
 */
VecField::VecField(const std::vector<Arrow>& places)
{
    field = places;
}

/** \brief Kiszámolja a bemeneti Curve vektormezőjét
 * \details Az adott Curve -re Biot-Savart törvénnyel kiszámolja a vektormezőt.
 * Az Arrow::from értékek az adottak és ezekből számlja ki az indukciót, majd az
 * indukcióvektor hozzáadja a from-hoz és egyenlővé teszi a to-val.
 * Az áramerősséget az egész Curve -nél ugyanannyinak veszi.
 * Az indukciót már itt logaritmikusan tároljuk el a szemléletesebb kijelzés miatt.
 *
 * \param wire Erre a Curve -re kiszámolja a field from pontjaiban a mágneses indukcióvektort.
 */
void VecField::CalculateB(const Curve& wire)
{
    Vector3d dl, r, l, r_;
    //double I = wire.current[0];
    double I = 1.0;
    double r_abs;
    for(unsigned int i = 0;i < field.size();i++)
    {
        r = field[i].getFrom();
        Vector3d B; /* (0.0, 0.0, 0.0) értékű */
        for(unsigned int j = 0;j < wire.curve.size();j++)
        {
            l = (wire.curve[j].getFrom() + wire.curve[j].getTo())/2;
            r_ = r - l; /* A vonaldarabkától a kiszámolandó pontig mutató vektor */
            r_abs = r_.abs();
            if(r_abs == 0)  /* Ha a Curve egy pontján akarnánk kiszámolni az indukciót */
                continue;
            dl = wire.curve[j].getTo() - wire.curve[j].getFrom(); /* Kicsiny dl vektor */
            B += (CrossProduct(dl, r_) * I)/(r_abs*r_abs*r_abs*4*M_PI); /* Összeadja a dl hosszúságú darabok járandóságát */
        }
        /* Az indukciót logaritmikusan ábrázoljuk. */
        field[i].setTo(r+(B.log())*arrowLength);
        //field[i].setTo(r+B);
    }

}

/** \brief Kirajzolja a vektormezőt
 * \details Ábrázolás: az értelmezési taromány egy pontjából a hozzá tartozó értékhez nyílat rajzol.
 *
 */
void VecField::Draw()
{
    /* Vonal kirajzolása */
    glPushMatrix();
    glLineWidth(1.5f);
    glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_LINES);
	for(unsigned int i = 0;i < field.size();i++)
    {
        glVertex3d(field[i].getFrom().getX(),
                   field[i].getFrom().getY(),
                   field[i].getFrom().getZ());
        glVertex3d(field[i].getTo().getX(),
                   field[i].getTo().getY(),
                   field[i].getTo().getZ());
    }
	glEnd();
	glPopMatrix();

    /* A nyíl tetejének kirajzolása (egy négyzet alapú gúla) */
    for(unsigned int i = 0;i < field.size();i++)
    {
        glColor3f(0.0f, 0.5f,1.0f);
        glPushMatrix();
        glTranslated(field[i].getTo().getX(),
                       field[i].getTo().getY(),
                       field[i].getTo().getZ());
        glRotatef(field[i].getTheta()*180/M_PI, sin(field[i].getPhi()), 0.0, -cos(field[i].getPhi()));

        /* A gúla  oldalai */
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0.1, 0.0);
        glVertex3f(0.05, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.05);
        glVertex3f(-0.05, 0.0, 0.0);
        glVertex3f(0.0, 0.0, -0.05);
        glVertex3f(0.05, 0.0, 0.0);
        glEnd();

        glColor3f(1.0f, 0.0f,0.0f);
        /* A gúla alapja */
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, 0);
        glVertex3f(0.05, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.05);
        glVertex3f(-0.05, 0.0, 0.0);
        glVertex3f(0.0, 0.0, -0.05);
        glVertex3f(0.05, 0.0, 0.0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

}

void VecField::saveFile()
{
    std::fstream file;
    file.open("B.txt", std::fstream::out);
    file.imbue(std::locale(file.getloc(), new punct_facet<char, ','>));
    for(int i = 0;i < field.size();i++)
    {
        //file << field[i].getFrom().getZ() << " ";
        file << (field[i].getTo() - field[i].getFrom()).getZ() << " ";
    }
    file.close();

}
