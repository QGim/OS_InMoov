#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

 //Read the file
 Mat image = imread("456498.jpg");
 //Name of the window
 String windowsName = "test_img_quentin";

 //Check image error
 if(image.empty())
 {
    cout<<"Impossible d'ouvrir l'image"<<endl;
    cin.get(); //Press any key
    return -1;
 }
 
 //Create a window
 namedWindow(windowsName);
 
 //Show the image in the window
 imshow(windowsName,image);
 
 //Wait for any key in the window
 waitKey(0);
 
 //Distroy window
 destroyWindow(windowsName);
 
 return 0;
}
