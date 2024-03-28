#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace cv; // namespace opencv
using namespace std;

#define WIDTH_VIDEO_SIZE 900
#define HEIGHT_VIDEO_SIZE 650

int array_lower_red[3] = {117,150,60};
int array_upper_red[3] = {179,255,255};

//int array_lower_red[3] = {};
//int array_lower_red[3] = {};

//int array_lower_red[3] = {};
//int array_lower_red[3] = {};

int main(int argc, char **argv)
{
    VideoCapture cap(0); // ouverture du flux camera webcam

    if (!cap.isOpened()) // si pas ouverture renvoi erreur
    {
        cout << "Ouverture du flux impossible" << endl;
        return -1;
    }

    while (true)
    {
        Mat main_img;
        Mat resize_img;
        Mat cpy_img_input;

        Mat hsv_img;

        Mat red_mask_img;

        bool img_is_read;
        img_is_read = cap.read(main_img); // lire une nouvelle image de la video

        // casser la boucle while en cas de deconnection d'une image
        if (img_is_read == false)
        {
            cout << "Camera video déconnecté" << endl;
            cin.get(); // Attente d'un appui de touche
            break;
        }

        // Redimentionnement de l'image principal
        resize(main_img, resize_img, Size(WIDTH_VIDEO_SIZE, HEIGHT_VIDEO_SIZE));

        // Création d'une copy pour desiner les contours.
        cpy_img_input = resize_img.clone();

        // Convertion de l'image RGB en HSV (Hue,Saturation,Value)
        cvtColor(resize_img, hsv_img, COLOR_RGB2HSV);

        //Création du masque de couleur rouge pour l'image HSV
        inRange(hsv_img,Scalar(array_lower_red[0],array_lower_red[1],array_lower_red[2]),Scalar(array_upper_red[0],array_upper_red[1],array_upper_red[2]),red_mask_img);

        


        //Nettoyage de l'image
        //morphological opening (remove small objects from the foreground)
        erode(red_mask_img, red_mask_img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( red_mask_img, red_mask_img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

        //morphological closing (fill small holes in the foreground)
        dilate( red_mask_img, red_mask_img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
        erode(red_mask_img, red_mask_img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //Création du contour pour mask rouge
        findContours(red_mask_img,/*return contour*/,RETR_TREE,CHAIN_APPROX_SIMPLE)


        imshow("Main_Frame",resize_img); // Affichage du flux au choix
        imshow("HSV",hsv_img);
        imshow("Red_Detection",red_mask_img);
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;
}