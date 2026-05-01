#ifndef I_LIFE_CYCLE_H
#define I_LIFE_CYCLE_H

class ILifeCycle {
public:
    virtual ~ILifeCycle() = default;
    virtual void initialize() = 0;
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate() = 0;
    virtual void lateUpdate() = 0;
};

#endif //I_LIFE_CYCLE_H