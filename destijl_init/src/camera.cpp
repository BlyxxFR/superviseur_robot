//
// Created by barrech on 04/05/18.
//

#include "../header/functions.h"
#include "../header/periodicThreads.h"
#include "../header/camera.h"
#include <pthread.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
     * \fn Constructeur de classe
     * \brief Constructeur de l'objet Battery.
     */
TheCamera::TheCamera() {
    memset(&this->_threadVideoID, '\0', sizeof(pthread_t));
    memset(&this->_threadPositionID, '\0', sizeof(pthread_t));
}

/**
     * \fn void openTheCamera()
     * \brief Démarre la caméra.
     */

void TheCamera::openCamera() {
    if (!this->_threadVideoID || pthread_kill(this->_threadVideoID, 0) != 0) {
        pthread_create(&this->_threadVideoID, NULL, this->_threadVideo, this);
    }
}

/**
     * \fn void closeTheCamera()
     * \brief Ferme la caméra.
     */

void TheCamera::closeCamera() {
    if (this->_threadVideoID && pthread_kill(this->_threadVideoID, 0) == 0) {
        if (this->_threadPositionID && pthread_kill(this->_threadPositionID, 0) == 0) {
            pthread_cancel(this->_threadPositionID);
        }
        close_camera(&this->_rpiCam);
        memset(&this->_threadVideoID, '\0', sizeof(pthread_t));
    }
}

/**
     * \fn void detectArena()
     * \brief Détecte l'arène
     */

void TheCamera::detectArena() {
    if (!this->_threadVideoID || pthread_kill(this->_threadVideoID, 0) == 0) {
        detect_arena(&this->_imgVideo, &this->_monArene);
    }
}

/**
     * \fn void arenaConfirm()
     * \brief Confirme l'arène
     */

void TheCamera::arenaConfirm() {
    draw_arena(&this->_imgVideo, &this->_imgVideo, &this->_monArene);
}

/**
     * \fn void arenaInfirm()
     * \brief Refuse l'arène
     */

void TheCamera::arenaInfirm() {
    Arene *p = &this->_monArene;
    p = NULL;
}

/**
     * \fn void startComputingPosition()
     * \brief Arrête de calculer la position du robot
     */

void TheCamera::startComputingPosition() {
    if (!this->_threadPositionID || pthread_kill(this->_threadPositionID, 0) != 0) {
        pthread_create(&this->_threadPositionID, NULL, this->_threadComputePosition, this);
    }
}

/**
     * \fn void stopComputingPosition()
     * \brief Arrête de calculer la position du robot
     */

void TheCamera::stopComputingPosition() {
    if (this->_threadPositionID && pthread_kill(this->_threadPositionID, 0) == 0) {
        pthread_cancel(this->_threadPositionID);
        memset(&this->_threadPositionID, '\0', sizeof(pthread_t));
    }
}

/**
     * \fn void _threadVideo()
     * \brief Thread qui enregistre la vidéo
     */

void *TheCamera::_threadVideo(void *arg) {
    PeriodicThreads periodicThreads;
    struct periodic_info info;
    periodicThreads.make_periodic(100000, &info);

    TheCamera * This = (TheCamera *)arg;
    open_camera(&This->_rpiCam);
    while (1) {
        get_image(&This->_rpiCam, &This->_imgVideo);
        compress_image(&This->_imgVideo, &This->_compress);
        send_message_to_monitor(HEADER_STM_IMAGE, &This->_compress);
        periodicThreads.wait_period(&info);
    }
    return NULL;
}

/**
     * \fn void _threadComputePosition()
     * \brief Thread qui calcule la position du robot
     */

void *TheCamera::_threadComputePosition(void *arg) {
    PeriodicThreads periodicThreads;
    struct periodic_info info;
    periodicThreads.make_periodic(100000, &info);

    TheCamera * This = (TheCamera *)arg;
    if (!This->_threadVideoID || pthread_kill(This->_threadVideoID, 0) == 0) {
        while (1) {
            if (detect_arena(&This->_imgVideo, &This->_monArene) == 0) {
                detect_position(&This->_imgVideo, This->_positionRobots, &This->_monArene);
            } else {
                detect_position(&This->_imgVideo, This->_positionRobots);
            }
            draw_position(&This->_imgVideo, &This->_imgVideo, &This->_positionRobots[0]);
            send_message_to_monitor(HEADER_STM_POS, &This->_positionRobots);
            periodicThreads.wait_period(&info);
        }
    }
    return NULL;
}


/**
     * \fn Destructeur de classe
     * \brief Destructeur de l'objet TheCamera.
     */
TheCamera::~TheCamera(void) {}

#ifdef __cplusplus
}
#endif
