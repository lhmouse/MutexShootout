// Written by Mark Waterman, and placed in the public domain.
// The author hereby disclaims copyright to this source code.

#pragma once

#if _WIN32

#include <Windows.h>

namespace shootout {

template <DWORD SpinCount = 4000>
class cs_mutex
{
public:
    cs_mutex()
    {
        ::InitializeCriticalSectionAndSpinCount(&cs_, SpinCount);
    }

    ~cs_mutex()
    {
        ::DeleteCriticalSection(&cs_);
    }

    cs_mutex(const cs_mutex&) = delete;
    cs_mutex& operator=(const cs_mutex&) = delete;

    void lock()
    {
        EnterCriticalSection(&cs_);
    }

    void unlock()
    {
        LeaveCriticalSection(&cs_);
        
    }

private:
    CRITICAL_SECTION cs_;
};



class srw_mutex
{
public:
    srw_mutex()
    {
        ::InitializeSRWLock(&srw_);
    }

    ~srw_mutex()
    {
    }

    srw_mutex(const srw_mutex&) = delete;
    srw_mutex& operator=(const srw_mutex&) = delete;

    void lock()
    {
        AcquireSRWLockExclusive(&srw_);
    }

    void unlock()
    {
        ReleaseSRWLockExclusive(&srw_);
    }

private:
    SRWLOCK srw_;
};


}

#endif // _WIN32

#if HAS_MCFGTHREAD

#include <mcfgthread/mutex.h>

namespace shootout {

class mcf_mutex
{
public:
    constexpr mcf_mutex()
        : mtx_()
    {
    }

    ~mcf_mutex()
    {
    }

    mcf_mutex(const mcf_mutex&) = delete;
    mcf_mutex& operator=(const mcf_mutex&) = delete;

    void lock()
    {
        ::_MCF_mutex_lock(&mtx_, nullptr);  // infinite timeout
    }

    void unlock()
    {
        ::_MCF_mutex_unlock(&mtx_);
    }

private:
    ::_MCF_mutex mtx_;
};

class mcf_mutex_noinline
{
public:
    constexpr mcf_mutex_noinline()
        : mtx_()
    {
    }

    ~mcf_mutex_noinline()
    {
    }

    mcf_mutex_noinline(const mcf_mutex_noinline&) = delete;
    mcf_mutex_noinline& operator=(const mcf_mutex_noinline&) = delete;

    void lock()
    {
        ::_MCF_mutex_lock_slow(&mtx_, nullptr);  // infinite timeout
    }

    void unlock()
    {
        ::_MCF_mutex_unlock_slow(&mtx_);
    }

private:
    ::_MCF_mutex mtx_;
};

} // namespace shootout

#endif // HAS_MCFGTHREAD
