#ifndef _SGL_STL_UTILS_H
#define _SGL_STL_UTILS_H

#include <vector>

#define MIN(x,y) (((x)<(y))?(x):(y))
#define MAX(x,y) (((x)<(y))?(y):(x))

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


// --------------------------------

template <class T>
class wrapped_array {
public:
    T* data;
    int size;
    
    // constructor & destructor
    wrapped_array (std::vector<T> invec = std::vector<T>()) {
        size = invec.size();
        data = new T[size];
        for (int a=0; a<size; ++a) data[a] = invec[a];
    }
    
    ~wrapped_array () { delete[] data; }
    
    // access value
    T* operator()(void) { return data; }
    
    // deep copy
    wrapped_array (const wrapped_array& other) {
        size = other.size;
        data = new T[size];
        for (int a=0; a<size; ++a) data[a] = other.data[a];
    }
    
    void operator=(const wrapped_array& source) {
        if (&source != this) {
            size = source.size;
            data = new T[size];
            for (int a=0; a<size; ++a) data[a] = source.data[a];
        }
    }
};

template <class T>
wrapped_array<T> vector2array (std::vector<T> invec) {
    return (wrapped_array<T>(invec));
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
