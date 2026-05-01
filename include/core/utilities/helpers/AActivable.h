#ifndef A_ACTIVABLE_H
#define A_ACTIVABLE_H

namespace Core {
    class AActivable {
    public:
        virtual ~AActivable() = default;

        virtual void enable();
        virtual void disable();
        virtual void toggle();

        [[nodiscard]] virtual bool isActive() const;

    protected:
        bool active = false;
    };

}

#endif //A_ACTIVABLE_H