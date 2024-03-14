/**
 * @brief Ephemerides for orbital simulation
 * @author Marc S. Ressl
 * 
 * @copyright Copyright (c) 2022-2023
 */

#ifndef EPHEMERIDES_H
#define EPHEMERIDES_H

#include "raylib.h"
#include "raymath.h"

struct EphemeridesBody
{
    const char *name; // Name
    float mass;		  // [kg]
    float radius;	  // [m]
    Color color;	  // Raylib color
    Vector3 position; // [m]
    Vector3 velocity; // [m/s]
};

/**
 * @brief Solay system ephermerides for 2022-01-01T00:00:00Z
 * 
 * @cite https://ssd.jpl.nasa.gov/horizons/app.html#/
*/
EphemeridesBody solarSystem[] = {
    {
        "Sol",
        1988500E24F,
        695700E3F,
        GOLD,
        {-1.283674643550172E+09F, 2.589397504295033E+07F, 5.007104996950605E+08F},
        {-5.809369653802155E-00F, 2.513455442031695E-01F, -1.461959576560110E+01F},
    },
    {
        "Mercurio",
        0.3302E24F,
        2440E3F,
        GRAY,
        {5.242617205495467E+10F, -5.398976570474024E+09F, -5.596063357617276E+09F},
        {-3.931719860392732E+03F, 4.493726800433638E+03F, 5.056613955108243E+04F},
    },
    {
        "Venus",
        4.8685E24F,
        6051.84E3F,
        BEIGE,
        {-1.143612889654620E+10F, 2.081921801192194E+09F, 1.076180391552140E+11F},
        {-3.498958532524220E+04F, 1.971012081662609E+03F, -3.509011592387367E+03F},
    },
    {
        "Tierra",
        5.97219E24F,
        6371.01E3F,
        BLUE,
        {-2.741147560901964E+10F, 1.907499306293577E+07F, 1.452697499646169E+11F},
        {-2.981801522121922E+04F, 1.781036907294364E00F, -5.415519940416356E+03F},
    },
    {
        "Marte",
        0.64171E24F,
        3389.92E3F,
        RED,
        {-1.309510737126251E+11F, -7.714450109843910E+08F, -1.893127398896606E+11F},
        {2.090994471204196E+04F, -7.557181497936503E02F, -1.160503586188451E+04F},
    },
    {
        "Jupiter",
        1898.18722E24F,
        69911E3F,
        BEIGE,
        {6.955554713494443E+11F, -1.444959769995748E+10F, -2.679620040967891E+11F},
        {4.539612624165795E+03F, -1.547160200183022E+02F, 1.280513202430234E+04F},
    },
    {
        "Saturno",
        568.34E24F,
        58232E3F,
        LIGHTGRAY,
        {1.039929189378534E+12F, -2.303100000185490E+10F, -1.056650101932204E+12F},
        {6.345150006906061E+03F, -3.704447055166629E+02F, 6.756117358248296E+03F},
    },
    {
        "Urano",
        86.813E24F,
        25362E3F,
        SKYBLUE,
        {2.152570437700128E+12F, -2.039611192913723E+10F, 2.016888245555490E+12F},
        {-4.705853565766252E+03F, 7.821724397220797E+01F, 4.652144641704226E+03F},
    },
    {
        "Neptuno",
        102.409E24F,
        24624E3F,
        DARKBLUE,
        {4.431790029686977E+12F, -8.954348456482631E+10F, -6.114486878028781E+11F},
        {7.066237951457524E+02F, -1.271365751559108E+02F, 5.417076605926207E+03F},
    },
};

#define SOLARSYSTEM_BODYNUM (sizeof(solarSystem) / sizeof(EphemeridesBody))

/**
 * Alpha Centauri system ephermerides for 2022-01-01T00:00:00Z
 * 
 * @cite https://ssd.jpl.nasa.gov/horizons/app.html#/
*/
EphemeridesBody alphaCentauriSystem[] = {
    {
        "Alfa Centauri A",
        2167000E24F,
        834840.F,
        YELLOW,
        {7.76412948E+11F, 0, 0},
        {0, 0, 7.120E+03F},
    },
    {
        "Alfa Centauri B",
        1789000E24F,
        626130.F,
        GOLD,
        {-9.20026904E+11F, 0, 0},
        {0, 0, -8.430E03F},
    },
};

#define ALPHACENTAURISYSTEM_BODYNUM (sizeof(alphaCentauriSystem) / sizeof(EphemeridesBody))

#endif
