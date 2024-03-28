#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


using namespace cv; //namespace opencv
using namespace std;


#define WIDTH_VIDEO_SIZE 900
#define HEIGHT_VIDEO_SIZE 650

int main(int argc, char**argv)
{

    //declation variable de control  ==> Hue,Saturation,Value
    int Low_Hue = 170;
    int High_Hue = 179;

    int Low_Sat = 150;
    int High_Sat = 255;

    int Low_Value = 60;
    int High_Value = 255;

    //declaration variable gestion des point ligne de reference
    int LastX = -1; 
    int LastY = -1;

    VideoCapture cap(0); //ouverture du flux camera webcam

    if(!cap.isOpened()) //si pas ouverture renvoi erreur
    {
        cout<<"Ouverture du flux impossible"<<endl;
        return -1;
    }



    namedWindow("Control",WINDOW_AUTOSIZE); //creation de la fenetre principal

    createTrackbar("LowHue", "Control", &Low_Hue, 179); //Hue (0 - 179)
    createTrackbar("HighHue", "Control", &High_Hue, 179);

    createTrackbar("LowSat", "Control", &Low_Sat, 255); //Saturation (0 - 255)
    createTrackbar("HighSat", "Control", &High_Sat, 255);

    createTrackbar("LowValue", "Control", &Low_Value, 255); //Value (0 - 255)
    createTrackbar("HighValue", "Control", &High_Value, 255);

     //Capture a temporary image from the camera
    Mat imgTmp;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;

    while (true)
    {
        Mat image_Original;
        Mat image_Original_resized;


        Mat image_Thresholded;
        Mat image_Thresholded_resized;

        Mat image_HSV;

        bool Is_Success = cap.read(image_Original); // lecture de la video

        if (!Is_Success) //if aucun succes casser la boucle
        {
            cout << "Aucune lecture possible du flux video" << endl;
            break;
        }
        

        cvtColor(image_Original, image_HSV, COLOR_RGB2HSV); //Convert the captured frame from BGR to HSV
 
    
        inRange(image_HSV, Scalar(Low_Hue, Low_Sat, Low_Value), Scalar(High_Hue, High_Sat, High_Value), image_Thresholded); //Threshold the image
      
        //morphological opening (remove small objects from the foreground)
        erode(image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

        //morphological closing (fill small holes in the foreground)
        dilate( image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
        erode(image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


          //Calculate the moments of the thresholded image
        Moments oMoments = moments(image_Thresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
        if (dArea > 10000)
        {
            //calculate the position of the ball
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;        
        
            if (LastX >= 0 && LastY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                line(imgLines, Point(posX, posY), Point(LastX, LastY), Scalar(0,0,255), 2);
            }
            LastX = posX;
            LastY = posY;
        }
        resize(image_Thresholded,image_Thresholded_resized,Size(WIDTH_VIDEO_SIZE, HEIGHT_VIDEO_SIZE),INTER_LINEAR);
        imshow("Thresholded Image", image_Thresholded_resized); //show the thresholded image

        image_Original = image_Original + imgLines;
        resize(image_Original,image_Original_resized,Size(WIDTH_VIDEO_SIZE, HEIGHT_VIDEO_SIZE),INTER_LINEAR);

        imshow("Original", image_Original_resized); //show the original image
    
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break; 
        }

    }
    cap.release();
    destroyAllWindows();
    return 0;
}