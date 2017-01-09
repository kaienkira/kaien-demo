#ifndef TEST_PHYSX_PTR_H
#define TEST_PHYSX_PTR_H

#include <brickred/class_util.h>

template <class T>
class PhysxPtr {
public:
    explicit PhysxPtr(T *p = 0) : px_(p) {}
    ~PhysxPtr() { if (px_ != 0) px_->release(); }

    T *operator->() const { return px_; }
    T &operator*() const { return *px_; }
    T *get() const { return px_; }

    void swap(PhysxPtr &b)
    {
        T *tmp = b.px_;
        b.px_ = px_;
        px_ = tmp;
    }

    void reset(T *p = 0)
    {
        PhysxPtr<T>(p).swap(*this);
    }

    BRICKRED_SAFE_BOOL_TYPE(PhysxPtr)
    operator SafeBoolType() const
    {
        return px_ != 0 ? &PhysxPtr::SafeBoolTypeNotNull : 0;
    }

    T *release()
    {
        T *p = px_;
        px_ = 0;

        return p;
    }

private:
    BRICKRED_NONCOPYABLE(PhysxPtr)

    T *px_;
};

#endif
