#ifndef _SGL_OBJ_BASE_H
#define _SGL_OBJ_BASE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "../sgl_utils/stl_utils.h"
#include "../sgl_utils/gl_transformation_util.h"
#include "../sgl_utils/simple_lock.h"

// ==========================================================
// Property maps

class OPropertiesMap : public std::unordered_map <std::string, sgl_any> { }; // object properties

class LPropertiesMap : public OPropertiesMap { // link properties
public:
    LPropertiesMap () { }
    LPropertiesMap (const OPropertiesMap& op) : OPropertiesMap (op) { } // OP to LP conversion
};

class CPropertiesMap : public LPropertiesMap { // computed properties
public:
    CPropertiesMap () { }
    CPropertiesMap (const OPropertiesMap& op) : LPropertiesMap(op) { } // OP to CP conversion
};

// ==========================================================

#define declare_ModifiesMemberUsedInDrawing   ActivateSimpleLock<sglLockStates,LOCK_RECURSIVE> sgl_obj_fun_lock (sglDrawLock, SGL_MEM_LOCK);

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
        declare_ModifiesMemberUsedInDrawing;
        // --
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
        declare_ModifiesMemberUsedInDrawing;
        // --
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
        declare_ModifiesMemberUsedInDrawing;
        // --
        // de-register child
        childObjects_p.erase (child_obj_p);
        // de-register parent
        child_obj_p->parentObjects_p.erase (this);
        // remove object if not shared
        if ( !(child_obj_p->shared) ||   // Explicitly unshared
                    child_obj_p->parentObjects_p.size()==0 )  // no other parent
            delete child_obj_p;
    }
    
    // +++++++++++++++++++++++++
    // constructor:
    
    sglObjectBase () : shared(false) { }
    
    // -------------------------
    // copy constructor and assignment operator
    // ^^ if creating a copy, need to mark each and every child as shared
    
    sglObjectBase (const sglObjectBase& other) : 
                    shared(other.shared), parentObjects_p(other.parentObjects_p), childObjects_p(other.childObjects_p) {
        declare_ModifiesMemberUsedInDrawing;
        // --
        for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it) {
            it->first->parentObjects_p.insert (this);
            it->first->shared = true;
        }
    }
    
    // +++++++++++++++++++++++++
    // Transformations
    std::vector <sglTransformation*> transformations_p;
    
    // -------------------------
    // Adding/removing transformations:
    
    template <class transType> // objType must be derived from sglObjectBase
    transType* addTransformation (const transType& trans) {
        declare_ModifiesMemberUsedInDrawing;
        // --
        transType* new_trans = new transType (trans);
        transformations_p.push_back (new_trans);
        return (new_trans);
    }
    
    void removeTransformation (sglTransformation* trans_p) {
        declare_ModifiesMemberUsedInDrawing;
        // --
        auto found_it = std::find (transformations_p.begin(), transformations_p.end(), trans_p);
        if (found_it != transformations_p.end()) {
            delete (*found_it);
            transformations_p.erase (found_it);
        }
    }
    
    void removeTransformation (int index = -1) {
        declare_ModifiesMemberUsedInDrawing;
        // --
        if (index<0 || index>=transformations_p.size())
            index = transformations_p.size() - 1;
        delete (transformations_p[index]);
        transformations_p.erase (transformations_p.begin() + index);
    }
    
    // +++++++++++++++++++++++++
    // This will be overwritten in 'sglObject':
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) { }
    
    // +++++++++++++++++++++++++
    // virtual destructor
    
    virtual ~sglObjectBase () {
        declare_ModifiesMemberUsedInDrawing;
        // --
        for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it) {
            auto found_it = it->first->parentObjects_p.find(this);
            if ( !(it->first->shared) ||   // Explicitly unshared
                    (it->first->parentObjects_p.size()==1 && found_it!=it->first->parentObjects_p.end()) )
                delete (it->first);
            else if (found_it!=it->first->parentObjects_p.end())
                it->first->parentObjects_p.erase (this);
        }
    }
    
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

// object properties
#define declare_OP(type,name,default) \
    type& name (void) { declare_ModifiesMemberUsedInDrawing; if (this_OP.find(#name)==this_OP.end()) this_OP[#name] = default; return (sgl_any_cast (SINGLE_ARG(type &), this_OP[#name])); } \
    type& name (OPropertiesMap& xxx_OP) { declare_ModifiesMemberUsedInDrawing; if (xxx_OP.find(#name)==xxx_OP.end()) xxx_OP[#name] = default; return ( sgl_any_cast (SINGLE_ARG(type &), xxx_OP[#name]) ); } \
    const type& name (OPropertiesMap& xxx_OP, const type& alt_val) { declare_ModifiesMemberUsedInDrawing; if (xxx_OP.find(#name)==xxx_OP.end()) return (alt_val); else return ( sgl_any_cast (SINGLE_ARG(type &), xxx_OP[#name]) ); }

// Link properties (to be declared in a parent)
#define declare_LP(type,name,default) \
    type& name (sglObjectBase* cp) { declare_ModifiesMemberUsedInDrawing; if (childObjects_p.find(cp)==childObjects_p.end()) addChild(cp); LPropertiesMap& tmp = childObjects_p[cp]; if (tmp.find(#name)==tmp.end()) tmp[#name] = default; return (sgl_any_cast (SINGLE_ARG(type &), tmp[#name])); } \
    type& name (LPropertiesMap& xxx_LP) { declare_ModifiesMemberUsedInDrawing; if (xxx_LP.find(#name)==xxx_LP.end()) xxx_LP[#name] = default; return ( sgl_any_cast (SINGLE_ARG(type &), xxx_LP[#name]) ); } \
    const type& name (LPropertiesMap& xxx_LP, const type& alt_val) { declare_ModifiesMemberUsedInDrawing; if (xxx_LP.find(#name)==xxx_LP.end()) return (alt_val); else return ( sgl_any_cast (SINGLE_ARG(type &), xxx_LP[#name]) ); }

// --------------------------------------------

#define sgl_draw_function_head      ActivateSimpleLock<sglLockStates,LOCK_RECURSIVE> sgl_obj_fun_lock (sglDrawLock, SGL_DRAW_LOCK); \
                                    computeProperties (parent_CP, parent_child_LP);
                            // ...
#define sgl_draw_end    

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
    
    // link (to children) properties
    declare_LP (bool, visible, true);
    
    // non-heritable object properties
    // none.
    
    // -------------------------
    // Constructors for setting default properties
    sglObject (std::vector<double> c=sglMake3vec (0.0, 0.0, 0.0), double a=1.0) {
        color() = c;
        alpha() = a;
    }
    
    // -------------------------
    // Mix parents' and self properties
    
    void computeProperties (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        // this_CP = this_OP; // set defaults
        for (auto it=this_OP.begin(); it!=this_OP.end(); ++it)
            this_CP[it->first] = it->second; 
        // make this a privte member? (to be use by 'draw' only)
        visible(this_CP) = visible()  &  visible(parent_CP, true)  &  visible(parent_child_LP, true);
        color(this_CP) = color();
        alpha(this_CP) = alpha()  *  alpha(parent_CP, 1.0)  *  alpha(parent_child_LP, 1.0);
        // --
        // Can use more complex criteria set by user-defined parameters in properties, e.g., color_combine_mode = xor, and, or
    }
    
    // +++++++++++++++++++++++++
    // -------------------------
    // drawing (to be over-written)
    virtual void draw (CPropertiesMap&  parent_CP,  LPropertiesMap&  parent_child_LP) {
        sgl_draw_function_head; // computes 'this_CP'
        // --
        if (visible(this_CP)) {
            // Apply transformations
            for (int a=transformations_p.size()-1; a>=0; --a)
                transformations_p[a]->apply();
            // Draw self -- Some OpenGL drawing calls.
            // Draw children as desired
            for (auto it=childObjects_p.begin(); it!=childObjects_p.end(); ++it)
                it->first->draw (this_CP, it->second);
            // Remove transformations
            for (int a=0; a<transformations_p.size(); ++a)
                transformations_p[a]->remove();
        }
    }
    
};

#endif
