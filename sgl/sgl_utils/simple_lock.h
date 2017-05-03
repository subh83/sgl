#ifndef _SGL_SIMPLE_LOCK_H
#define _SGL_SIMPLE_LOCK_H

#include <thread>
#include <chrono>

template <class ThreadIDType>
ThreadIDType  get_default_thread_id (void) { return (ThreadIDType()); }

template <>
std::thread::id  get_default_thread_id<std::thread::id> (void) { return (std::this_thread::get_id()); }

// --------------------------------------------------------------

typedef bool  LOCK_MONO;
void lock_state_capture (LOCK_MONO& locked) { locked = true; }
void lock_state_release (LOCK_MONO& locked) { locked = false; }

typedef unsigned int  LOCK_RECURSIVE;
void lock_state_capture (LOCK_RECURSIVE& locked) { ++locked; }
void lock_state_release (LOCK_RECURSIVE& locked) { --locked; }

// =============================================================

template <class LockStateType=LOCK_MONO, class ThreadIDType=std::thread::id>
class SimpleLock {

private:
    ThreadIDType lock_owner_id;
    LockStateType locked;
    
public:
    typedef ThreadIDType  IDtype;
    SimpleLock() : locked (0) { }
    
    // -------------------
    
    bool is_locked (ThreadIDType requestor_id = get_default_thread_id<ThreadIDType>()) {
        return (locked  &&  lock_owner_id == requestor_id);
    }
    
    bool try_lock (ThreadIDType requestor_id = get_default_thread_id<ThreadIDType>()) {
        if (!locked) {
            // try to set lock
            lock_state_capture (locked);
            if (!locked) // another thread unlocked it in the mean time
                return (false);
            // TODO: Avoid the case where locked==true, but lock_owner_id does not represent any existing thread
            lock_owner_id = requestor_id;
            // check if successfully set lock
            if (locked  &&  lock_owner_id == requestor_id)
                return (true);
        }
        else if (lock_owner_id == requestor_id) { // already locked
            lock_state_capture (locked);
            return (true);
        }
            
        return (false);
    }
    
    void lock ( ThreadIDType requestor_id = get_default_thread_id<ThreadIDType>(), 
                    std::chrono::duration<long int, std::micro> pause_before_retry = std::chrono::microseconds(1) ) {
        while (!try_lock(requestor_id))
            std::this_thread::sleep_for (pause_before_retry);
    }
    
    void unlock (ThreadIDType requestor_id = get_default_thread_id<ThreadIDType>()) {
        if (locked  &&  lock_owner_id == requestor_id)
            lock_state_release (locked);
    }
};

// --------------------------------------------------------------

template <class LockStateType=LOCK_MONO, class ThreadIDType=std::thread::id>
class ActivateSimpleLock {

public:
    typedef SimpleLock<LockStateType, ThreadIDType>  LockType;
    
    ActivateSimpleLock (LockType l, ThreadIDType requestor_id = get_default_thread_id<ThreadIDType>()) 
            : this_lock(l), lock_owner_id(requestor_id)  { this_lock.lock (requestor_id); }
    
    ~ActivateSimpleLock() { this_lock.unlock (lock_owner_id); }

private:
    LockType this_lock;
    ThreadIDType lock_owner_id;
};

#endif
