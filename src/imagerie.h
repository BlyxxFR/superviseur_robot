/**
 * \file      imagerie.h
 * \author    L.Senaneuch
 * \version   1.0
 * \date      06/06/2017
 * \brief     Fonctions de traitement d'image utilisable pour la d�tection du robot.
 *
 * \details   Ce fichier utilise la libraire openCV2 pour faciliter le traitement d'image dans le projet Destijl.
 *            Il permet de faciliter la d�tection de l'ar�ne et la d�tection du robot.
 *			  /!\ Attention Bien que celui-ci soit un .cpp la structure du code n'est pas sous forme d'objet.
 */


#ifndef IMAGERIE_H
#define IMAGERIE_H
#include <raspicam/raspicam_cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <math.h>

#define WIDTH 640 //1280 1024 640
#define HEIGHT 480 // 960 768 480

using namespace std;
using namespace cv;
using namespace raspicam;

typedef Mat Image;
typedef RaspiCam_Cv Camera;
typedef Rect Arene;
typedef vector<unsigned char> Jpg;
struct  position {
    Point center;
    Point direction;
    float angle;
};


 /**
 * \brief      D�tecte la position d'un robot.
 * \details    D�tecte la position de triangles blanc sur une image /a imgInput pass� en param�tre d'entrer.
 *             
 * \param    *imgInput       Pointeur sur l'image sur laquelle chercher la position du des robots.
 * \param    *posTriangle    Pointeur sur un tableau de position ou seront stock� les positions des triangles d�tect�s.
 * \param    *monArene		 Pointeur de type Ar�ne si n�cessaire d'affiner la recherche (optionnel) 
 * \return    Le nombre de triangle d�tect�.
 */
int detectPosition(Image *imgInput, position *posTriangle, Arene * monArene = NULL);


 
 /**
 * \brief      Capture une image avec la camera pass� en entr�e.
 * \details    La camera doit pr�alablement �t� ouverte via \a openCamera(...)
 *             
 * \param    *Camera       Pointeur sur la camera pass� en entr�e.
 * \param    *monImage 	   Pointeur sur une image captur�. 
 * \return    Retourne -1 si une erreur survient.
 */
void getImg(RaspiCam_Cv *Camera, Image * monImage);




 /**
 * \brief      D�tecte une ar�ne dans une image fournis en param�tre.
 *             
 * \param    *monImage       Pointeur sur l'image d'entr�e
 * \param    *rectangle 	 Pointeur sur les coordonn�es du rectangles trouv�. 
 * \return    Retourne -1 si aucune ar�ne n'est d�tect�. Sinon retourne 0
 */
int detectArena(Image *monImage, Arene *rectangle);


 /**
 * \brief      Ferme la camera pass� en param�tre
 *             
 * \param    *Camera       Pointeur sur la camera � ferm�
 */
void closeCam(Camera *Camera);


 /**
 * \brief      Dessine le plus petit rectangle contenant l'ar�ne
 
 * \param    *imgInput       Pointeur sur l'image d'entr�e.
 * \param    *imgOutput      Pointeur sur l'image de sortie (image d'entr�e + ar�ne marqu�)
 * \param    *monArene		 Pointeur de type Ar�ne contenant les information � dessin� 
 */
void drawArena(Image *imgInput, Image *imgOutput, Arene *monArene);


 /**
 * \brief      D�tecte la position d'un robot.
 * \details    D�tecte la position de triangles blanc sur une image /a imgInput pass� en param�tre d'entrer.
 *             
 * \param    *imgInput      	Pointeur sur l'image � sauvegarder en m�moire sous format jpg.
 * \param    *imageCompress		Pointeur sur une image .jpg pr�te � �tre envoyer � l'Interaface graphique.
 */
void imgCompress(Image *imgInput, Jpg *imageCompress);

 
 
 /**
 * \brief      Ouvre une camera.
 * \details    Met � jour le file descriptor pass� en param�tre pour correspondre � la camera ouverte
 *             
 * \param    *Camera      	Pointeur d'un file descriptor d'une camera ouverte
 * \return retourne 0 si la camera a �t� ouverte correctement et -1 si une erreur survient.
 */
int openCamera(RaspiCam_Cv  *Camera);



 
 /**
 * \brief      Dessine sur une image en entr�e la position d'un robot et sa direction.
 * \details    Sauvegarde l'image des coordonn�es pass� par positionRobot superpos� � l'image d'entr�e sur imgOutput.
 *             
 * \param      *imgInput	      	Pointeur sur l'image d'entr�e
 * \param      *imgOutput    		Pointeur sur l'image de sortie ( image d'entr�e + dessin de la position)
 * \param      *positionRobot   	Pointeur sur la structure position d'un robot.
 */
void drawPosition(Image *imgInput, Image *imgOutput, position *positionRobot);



#endif // IMAGERIE_H
