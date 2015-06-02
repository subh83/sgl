#ifndef _SGL_OBJ_BASE_H
#define _SGL_OBJ_BASE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../sgl_utils/stl_utils.h"

// ==========================================================

class OPropertiesMap : public std::unordered_map <std::string, sgl_any> { }; // object properties
class LPropertiesMap : public OPropertiesMap { }; // link properties
class CPropertiesMap : public LPropertiesMap { }; // computed properties

// Class without properties. Only for maintaining parent-child relationship
class sglObjectBase
{
public:
    static CPropertiesMap empty_CP;
    static OPropertiesMap empty_OP;
    static LPropertiesMap empty_LP;
    
    // +++++++++++++++++++++++++
    // Children and Parents
    bool shared;
    
    // Prent-child relations and link properties
    std::unordered_set <sglObjectBase*> parentObjects_p;
    std::unordered_map <sglObjectBase*, LPropertiesMap> childObjects_p; // Linl Properties (LP) map
    
    // -------------------------
    // Adding/removing Children:
    
    // unshared child

    template <class objType> // objType must be derived from sglObjectBase
    objType* addChild (const objType& child,  LPropertiesMap parent_child_LP=empty_LP) {
        // make copy (call copy constructor)
        objType* new_child = new objType (child);
        new_child->shared = false;
        // register parent
        new_child->parentObjects_p.insert (this);
        // register child
        childObjects_p.insert ( std::make_pair(new_child, parent_child_LP) ); // type casting
        // return pointer
        return (new_child);
    }
    
    // shared child

    template <class objType> // objType must be derived from sglObjectBase
    objType* addChild (objType* child_p, LPropertiesMap parent_child_LP=empty_LP) {
        child_p->shared = true;
        // register parent
        child_p->parentObjects_p.insert (this);
        // register child
        childObjects_p.insert ( std::make_pair(child_p, parent_child_LP) ); // type casting
        // return pointer
        return (child_p);
    }
    
    // remove a child

    void removeChild (sglObjectBase* child_obj_p) {
        // de-register child
        childObjects_p.erase (child_obj_p);
        // de-register parent
        child_obj_p->parentObjects_p.erase (this);
        // remove object if not shared
        if ( !(child_obj_p->shared) ||   // Explicitly unshared
                    child_obj_p->parentObjects_p.size()==0 )  // no other parent
            delete child_obj_p;
    }
    
    // -------------------------
    // constructor:
    
    sglObjectBase () : shared(false) { }
    
    // -------------------------
    // copy constructor and assignment operator
    // ^^ if creating a copy, need to mark each and every child as shared
    
    sglObjectBase (const sglObjectBase& other) : 
                    shared(other.shared), parentObjects_p(other.parentObjects_p), childObjects_p(other.childObjects_p) {
        for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it) {
            it->first->parentObjects_p.insert (this);
            it->first->shared = true;
        }
    }
    
    // -------------------------
    // Destructor
    
    ~sglObjectBase () {
        for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it) {
            auto found_it = it->first->parentObjects_p.find(this);
            if ( !(it->first->shared) ||   // Explicitly unshared
                    (it->first->parentObjects_p.size()==1 && found_it!=it->first->parentObjects_p.end()) )
                delete (it->first);
            else if (found_it!=it->first->parentObjects_p.end())
                it->first->parentObjects_p.erase (this);
        }
    }
    
    // -------------------------
    // This will be overwritten in 'sglObject'
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) { }
    
private:
    sglObjectBase& operator=(const sglObjectBase& other) { } // prevent call to assignment operator
};

// ------------------------
// Define empty objects
CPropertiesMap  sglObjectBase::empty_CP  =  CPropertiesMap();
OPropertiesMap  sglObjectBase::empty_OP  =  OPropertiesMap();
LPropertiesMap  sglObjectBase::empty_LP  =  LPropertiesMap();

// ==========================================================

// Macro for defining functions:
//    - type& name (void);
//    - type& name (PropertiesMap&);
//    - type& name (PropertiesMap&, type&);

// object properties
#define declare_OP(type,name,default) \
    type& name (void) { if (this_OP.find(#name)==this_OP.end()) this_OP[#name] = default; return (sgl_any_cast (type &, this_OP[#name])); } \
    type& name (OPropertiesMap& xxx_OP) { if (xxx_OP.find(#name)==xxx_OP.end()) xxx_OP[#name] = default; return ( sgl_any_cast (type &, xxx_OP[#name]) ); } \
    const type& name (OPropertiesMap& xxx_OP, const type& alt_val) { if (xxx_OP.find(#name)==xxx_OP.end()) return (alt_val); else return ( sgl_any_cast (type &, xxx_OP[#name]) ); }

// Link properties (to be declared in a parent)
#define declare_LP(type,name,default) \
    type& name (sglObjectBase* cp) { if (childObjects_p.find(cp)==childObjects_p.end()) addChild(cp); LPropertiesMap& tmp = childObjects_p[cp]; if (tmp.find(#name)==tmp.end()) tmp[#name] = default; return (sgl_any_cast (type &, tmp[#name])); } \
    type& name (LPropertiesMap& xxx_LP) { if (xxx_LP.find(#name)==xxx_LP.end()) xxx_LP[#name] = default; return ( sgl_any_cast (type &, xxx_LP[#name]) ); } \
    const type& name (LPropertiesMap& xxx_LP, const type& alt_val) { if (xxx_LP.find(#name)==xxx_LP.end()) return (alt_val); else return ( sgl_any_cast (type &, xxx_LP[#name]) ); }

// --------------------------------------------

// Base object handling properties
class sglObject : public sglObjectBase
{
public:
    // +++++++++++++++++++++++++
    
    // object properties (OP):
    // Defined in sglObjectBase:  typedef std::unordered_map <std::string, boost::any>   PropertiesMap;
    OPropertiesMap  this_OP;    // will contain all native object properties (OP)
    CPropertiesMap  this_CP;  // temporary variable (can be private)
    
    // object (self) properties
    declare_OP (bool, visible, true);
    declare_OP (std::vector<double>, color, sglMake3vec (0.0, 0.0, 0.0));
    declare_OP (double, alpha, 1.0);
    // --
    declare_OP (std::vector<double>, translation, sglMake3vec (0.0, 0.0, 0.0));
    declare_OP (double, scale, 1.0);
    
    // link (to children) properties
    declare_LP (bool, visible, true);
    
    // non-object properties
    // Add properties that do not need to be passed on to children.
    
    // -------------------------
    // Constructors for setting default properties
    sglObject (std::vector<double> c=sglMake3vec (0.0, 0.0, 0.0), double a=1.0) {
        //visible() = true;
        color() = c;
        alpha() = a;
        // --
        //translation() = sglMake3vec (0.0, 0.0, 0.0);
        //scale() = 1.0;
    }
    
    // -------------------------
    // Mix parents' and self properties
    
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        // make this a privte member? (to be use by 'draw' only)
        visible(this_CP) = visible()  &  visible(parent_CP, true)  &  visible(parent_child_LP, true);
        color(this_CP) = color();
        alpha(this_CP) = alpha()  *  alpha(parent_CP, 1.0)  *  alpha(parent_child_LP, 1.0);
        // --
        translation(this_CP) = translation(parent_CP, sglMake3vec (0.0, 0.0, 0.0)) + translation();
        scale(this_CP) = scale() * scale(parent_CP, 1.0);
        // Can use more complex criteria set by user-defined parameters in properties, e.g., color_combine_mode = xor, and, or
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // Drawing functions
    
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        computeProperties (parent_CP, parent_child_LP); // computes 'this_CP'
        // --
        if (visible(this_CP)) {
            // Draw self.
            // Some OpenGL drawing calls.
            // Draw children as desired
            /* for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it)
                it->first->draw (this_CP, it->second); */
        }
    }
};

#endif
