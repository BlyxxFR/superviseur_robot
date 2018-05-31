//
// Created by barrech on 04/05/18.
//

#include "../header/periodicThreads.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
     * \fn Constructeur de classe
     * \brief Constructeur de l'objet PeriodicThreads.
     */
PeriodicThreads::PeriodicThreads() {

}


/**
     * \fn static int make_periodic(int unsigned period, struct periodic_info *info)
     * \brief Rend un thread périodique
     * \param period période
     * \param *info sur la période
     */

int PeriodicThreads::make_periodic(int unsigned period, struct periodic_info *info) {
    int ret;
    unsigned int ns;
    unsigned int sec;
    int fd;
    struct itimerspec itval;

    /* Create the timer */
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    info->wakeups_missed = 0;
    info->timer_fd = fd;
    if (fd == -1)
        return fd;

    /* Make the timer periodic */
    sec = period / 1000000;
    ns = (period - (sec * 1000000)) * 1000;
    itval.it_interval.tv_sec = sec;
    itval.it_interval.tv_nsec = ns;
    itval.it_value.tv_sec = sec;
    itval.it_value.tv_nsec = ns;
    ret = timerfd_settime(fd, 0, &itval, NULL);
    return ret;
}

/**
     * \fn static void wait_period(struct periodic_info *info)
     * \brief Attend la prochaine période.
     * \param *info sur la période
     */

void PeriodicThreads::wait_period(struct periodic_info *info) {
    unsigned long long missed;
    int ret;

    /* Wait for the next timer event. If we have missed any the
       number is written to "missed" */
    ret = read(info->timer_fd, &missed, sizeof(missed));
    if (ret == -1) {
        perror("read timer");
        return;
    }

    info->wakeups_missed += missed;
}


/**
     * \fn Destructeur de classe
     * \brief Destructeur de l'objet PeriodicThreads.
     */
PeriodicThreads::~PeriodicThreads(void) {}

#ifdef __cplusplus
}
#endif