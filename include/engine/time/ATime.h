#ifndef A_TIME_H
#define A_TIME_H

class ATime {
public:
    virtual ~ATime() = default;
    virtual void tick() = 0;
    float getDeltaTime();

protected:
    float deltaTime = 0.0f;
    float lastTick = 0.0f;
};

#endif //A_TIME_H