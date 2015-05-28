#ifndef _SGL_CONSTRUCTORS_H
#define _SGL_CONSTRUCTORS_H

#include <vector>

std::vector<double> sglMakeColor (double r, double g, double b) {
    std::vector<double> ret(3);
    ret[0] = r; ret[1] = g; ret[2] = b;
    return (ret);
}

std::vector<double> sglMakeColor (double r, double g, double b, double a) {
    std::vector<double> ret(4);
    ret[0] = r; ret[1] = g; ret[2] = b; ret[3] = a;
    return (ret);
}

#endif
