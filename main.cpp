#include <vector>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <fstream>

#include "vecfield.h"
#include "vector3d.h"
#include "arrow.h"
#include "curve.h"
#include "other.h"

/** @file */
/**
 * \file   main.cpp
 * \Author Pongó Tivadar
 * \date   2015 Május
 * \brief  A demóprogram forráskódja.
 *
 */

  /** \mainpage Biot_savart
 *
 * Programozta: Pongó Tivadar (IWOZY3)
 *
 * A program különböző vezető elrendezések mágneses indukció terét tudja kiszámolni Biot-Savart törvénnyel.
 * A demó 3 vezető elrendezés (szolenoid, toroid, egyenes) terét mutatja be két féle
 * vektormező (sík, térbeli) esetén.
 *
 * A program OpenGL-t használ megjelenítésre SDL kerettel. Az SDL segít a platform
 * független esemény- és ablakkezelésben. Az OpenGL miatt az x, y, z koordináták
 * közül az y a függőleges x, z pedig a vízszintes síkban mozgók.
 *
 * \section Használat
 * Először is ha egy vezető terét akarjuk kirajzoltatni, akkor egy Curve típusú objektumot kell létrehoznunk.
 * ennek a feltöltése legegyszerűbben a Curve(const std::vector<Arrow>& cur) konstruktor segítségével
 * valósítható meg. Tehát egy vector<Arrow>-ba tesszük a vezetőt alkotó vonalakat.
 *
 * Következő egy VecField definiálása, azaz megadni, hogy melyik pontokban számolja ki az
 * indukciót a program. Ezt a VecField(const std::vector<Arrow>& places) konstruktorral
 * lehet megtenni. Itt az átadott vector<Arrow> from tagváltozójában legyenek a kiszámoltatni
 * kívánt helyek, a to tagváltozót a CalculateB(const Curve& curve) függvény felül fogja
 * írni.
 *
 * \section Osztályok
 * \li \c Vector3d
 * \li \c Arrow
 * \li \c Curve
 * \li \c VecField
 *
 */

double VecField::arrowLength = 0.2;

int main(int argc, char *argv[])
{
    /* Melyik vezetőt, milyen vektormezővel jelenítse meg */
    int whichCurve, whichVecField;
    /* Vektormező középpontjának koordinátái */
    double fieldX = 0.0, fieldY = 0.0, fieldZ = 0.0, d_field = 0.5;
    std::vector<Curve> curves;
    curves.push_back(GenerateSolenoid(1, 0.0, 0.5, 100));
    curves.push_back(GenerateToroid(2.0, 0.5, 50, 1000));
    curves.push_back(GenerateLine(10.0, 100));

/*
    {
        int N = 100;
        double l = 10.0;
        int resolution = 50;
        double r = 1.0;
        std::vector<Arrow> sol;
        sol.reserve(N*resolution);
        double dt = (double)1/resolution, omega = 2*M_PI, h = l/resolution;
        for(int i = -N/2;i < N/2;i++)
        {
            for(int t = 0; t < resolution;t++)
            {
                sol.push_back(Arrow(Vector3d(r*cos(omega*t*dt), r*sin(omega*t*dt), i*l/N),
                                    Vector3d(r*cos(omega*(t+1)*dt), r*sin(omega*(t+1)*dt), i*l/N)));
            }
        }
        curves.push_back(Curve(sol));
    }
*/



    /* Le van-e nyomva az egérgomb */
    bool clicked = false;
    int lastX, lastY;
    /* A nézőpont szögei */
    double phi = M_PI_4, theta = M_PI_4;
    /* Kamera távolsága */
    double cam_dist = 5;

    /* SDL beállítások */
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);
    SDL_WarpMouse(800/2, 600/2);
    SDL_WM_SetCaption("Biot-Savart", "Biot-Savart");

    /* OpenGL beállítások */
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (double)800/600, .1, 100);
    glMatrixMode(GL_MODELVIEW);

    std::vector<VecField> mezok;
    mezok.push_back(GenerateCompleteVecField(0.5, 10, 0.0, 0.0, 0.0));
    mezok.push_back(GeneratePlaneVecField(0.5, 10, 0.0, 0.0, 0.0));

    {
        double d = 0.5;
        int N = 20;
        std::vector<Arrow> hely;
        hely.reserve(N);
        for(int k = -20;k <= 20;k++)
        {
            hely.push_back(Arrow(Vector3d(0.0, 0.0, 0.0 + k*d), Vector3d()));
        }
        mezok.push_back(VecField(hely));
    }
    mezok[2].CalculateB(curves[0]);
    //mezok[2].saveFile();
    mezok[0].CalculateB(curves[0]);
    whichCurve =  whichVecField = mezok.size()*curves.size()*10000;

    /* Eseménykezelő */
    while (SDL_WaitEvent(&event) && event.type!=SDL_QUIT)
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_LEFT:
			    whichCurve--;
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
			case SDLK_RIGHT:
			    whichCurve++;
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_UP:
			    whichVecField++;
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
			case SDLK_DOWN:
			    whichVecField--;
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_w:
                fieldY += 0.5;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_s:
                fieldY -= 0.5;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_a:
                fieldZ -= 0.5;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_d:
                fieldZ += 0.5;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_q:
                fieldX -= 0.5;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_e:
                fieldX += 0.5;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_PLUS:
            case SDLK_KP_PLUS:
                d_field += 0.05;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_MINUS:
            case SDLK_KP_MINUS:
                d_field -= 0.05;
                if(whichVecField%mezok.size() == 0)
                {
                    mezok[0] = GenerateCompleteVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
                else if(whichVecField%mezok.size() == 1)
                {
                    mezok[1] = GeneratePlaneVecField(d_field, 10, fieldX, fieldY, fieldZ);
                }
			    mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_r:
                VecField::arrowLength += 0.05;
                mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            case SDLK_f:
                VecField::arrowLength -= 0.05;
                mezok[whichVecField%mezok.size()].CalculateB(curves[whichCurve%curves.size()]);
				break;
            default:
                break;
			}
            break;
        case SDL_MOUSEBUTTONDOWN:
            clicked = true;
            lastX = event.button.x;
            lastY = event.button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            phi += double(lastX - event.button.x)/100;
            theta += double(lastY - event.button.y)/100;
            lastX = event.button.x;
            lastY = event.button.y;
            clicked = false;

            switch(event.button.button)
            {
                case SDL_BUTTON_WHEELUP:
                    cam_dist--;
                    break;
                case SDL_BUTTON_WHEELDOWN:
                    cam_dist++;
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            if(clicked)
            {
               phi -= double(lastX - event.button.x)/100;
                theta += double(lastY - event.button.y)/100;
                lastX = event.button.x;
                lastY = event.button.y;
            }
            break;

        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(cam_dist*sin(theta)*cos(phi), cam_dist*cos(theta), cam_dist*sin(theta)*sin(phi),
                  0,0, 0,  0.0,1.0f , 0.0);

        /* Kirajzolja a vezetőt */
        curves[whichCurve%curves.size()].Draw();
        /* Kirajzolja a vektormezőt */
        mezok[whichVecField%mezok.size()].Draw();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
