//
// Created by barrech on 04/05/18.
//

#ifndef SUPERVISEUR_ROBOT_PERIODIC_THREADS_H
#define SUPERVISEUR_ROBOT_PERIODIC_THREADS_H

#ifdef __cplusplus
extern "C" {
#endif

struct periodic_info {
    int timer_fd;
    unsigned long long wakeups_missed;
};

class PeriodicThreads {
    private :

    public :
        PeriodicThreads();
        int make_periodic(unsigned int period, struct periodic_info *info);
        void wait_period(struct periodic_info *info);
        ~PeriodicThreads(void);
};

#ifdef __cplusplus
}
#endif

#endif //SUPERVISEUR_ROBOT_PERIODIC_THREADS_H
