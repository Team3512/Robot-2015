#include "../Robot.hpp"
#include <Timer.h>

void Robot::AutoNoop() {
    while (IsAutonomous()) {
        Wait(0.01);
    }
}
