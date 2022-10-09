#define _USE_MATH_DEFINES
#include <cmath>
#include <map>
#include <vector>
#include <string>


#include <iostream>

/**
* 
* (x / a) ^ n + (y / b) ^ n = 1
*/

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef SUPER_ELLIPS_H
    #define SUPER_ELLIPS_H

class SuperEllipse
{

public:
    static std::vector<float*> execute(std::map<std::string, float> params)
    {
        // [x, y]
        std::vector<float*> coords;

        float a = 1.0f;
        float b = 1.0f;
        float n = 400.0f;
        float precision = 0.1f;

        if (params.find("a") != params.end())
        {
            a = params["a"];
        }

        if (params.find("b") != params.end())
        {
            b = params["b"];
        }

        if (params.find("n") != params.end())
        {
            n = params["n"];
        }

        if (params.find("PRECISION") != params.end())
        {
            precision = params["PRECISION"];
        }

        float x = 0;
        float y = 0;

        for (float fi = 0; fi < M_PI / 2; fi += precision)
        {
            x = a * powf(cos(fi), 2 / n);
            y = b * powf(sin(fi), 2 / n);

            float* _coords = new float[2];
            _coords[0] = x;
            _coords[1] = y;

            coords.push_back(_coords);
        }

        return coords;
    }
};

#endif // !SUPER_ELLIPS_H


