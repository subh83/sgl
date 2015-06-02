#ifndef _SGL_STL_UTILS_H
#define _SGL_STL_UTILS_H

#include <vector>

std::vector<double> sglMake3vec (const double& r, const double& g, const double& b) {
    std::vector<double> ret(3);
    ret[0] = r; ret[1] = g; ret[2] = b;
    return (ret);
}

std::vector<double>
operator+ (const std::vector<double>& l, const std::vector<double>& r) {
    std::vector<double> ret = l;
    for (int a=0; a<l.size(); ++a)
        ret[a] += r[a];
    return (ret);
}

std::vector<double>
operator* (double l, const std::vector<double>& r) {
    std::vector<double> ret = r;
    for (int a=0; a<r.size(); ++a)
        ret[a] *= l;
    return (ret);
}

// ------------------------------------

/*template <class key_type, class value_type>
class vector_map : public std::vector < std::pair<key_type, value_type> >
{
public:
    value_type& operator[] (const key_type& k) {
        for (int a=0; a<size(); ++a)
            if (operator[](a).first == k)
                return (operator[](a).second);
    }
}; */


#endif
