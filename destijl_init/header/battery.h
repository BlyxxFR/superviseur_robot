//
// Created by barrech on 04/05/18.
//

#ifndef SUPERVISEUR_ROBOT_BATTERY_H
#define SUPERVISEUR_ROBOT_BATTERY_H

#define BATTERY_LEVEL_UNKNOWN -1

#ifdef __cplusplus
extern "C" {
#endif

class Battery{
    private :
        int _level;
    public :
        Battery();
        void set_level(int level);
        int level();
        ~Battery(void);
};

#ifdef __cplusplus
}
#endif

#endif //SUPERVISEUR_ROBOT_BATTERY_H
