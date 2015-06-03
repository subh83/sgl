#ifndef _SGL_STL_CONTAINER_UTILS_H
#define _SGL_STL_CONTAINER_UTILS_H

#include <boost/any.hpp>

// For properties in a container
template <class T>
class type_wrapper {
public:
    // constructors
    type_wrapper () :  ptr (new T) { }
    // template <class W> type_wrapper (const W& val) : ptr (new T (val)) { } // all type conversions of T inherited
    // value access
    T& operator()(void) const { return (*ptr); } // return reference
    // Note: Default copy constructor and assignment operator will copy the pointer
    //       as necessitated by relocation of objects when the container resizes
private:
    T* ptr;
};

template <class container>
class stl_container_wrapper : public container {
public:
    // overwrite copy constructor, assignment operator and destructor
    
    
    ~stl_container_wrapper () {
        for (auto it=begin(); it!=end(); ++it)
            delete it->ptr;
    }
};

/* USE:
   typedef  stl_container_wrapper< std::unordered_map <std::string, type_wrapper< int > > >  myMap;
   myMap m;
   m["first"]() = 1;
   for (auto it=
*/

#endif
