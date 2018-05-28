//
// Created by barrech on 04/05/18.
//

#ifndef SUPERVISEUR_ROBOT_CAMERA_H
#define SUPERVISEUR_ROBOT_CAMERA_H


#ifdef __cplusplus
extern "C" {
#endif

class TheCamera{
    private :
        pthread_t _threadVideoID;
        pthread_t _threadPositionID;
        Camera _rpiCam;
        Image _imgVideo;
        Arene _monArene;
        Position _positionRobots[20];
        Jpg _compress;
        static void * _threadVideo(void * arg);
        static void * _threadComputePosition(void * arg);
    public :
        TheCamera();

        void openCamera();
        void closeCamera();

        void startComputingPosition();
        void stopComputingPosition();

        void detectArena();
        void arenaConfirm();
        void arenaInfirm();

        ~TheCamera(void);
};

#ifdef __cplusplus
}
#endif

#endif //SUPERVISEUR_ROBOT_CAMERA_H
