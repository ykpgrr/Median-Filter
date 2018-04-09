//
//  main.cpp
//  Median_Filter
//  Created by Yakup Gorur on 4/3/18.
//  Copyright © 2018 Yakup Gorur. All rights reserved.
//  Digital Signal Processing Design and Application 2017-2018 Spring
//  Homework 5
//  Lecturer: Prof. Dr. Bilge Gunsel, Research Assistant Yağmur Sabucu

// !!! Please ensure that the image folder path is true.


#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std; //namespace for  C++ standard library
using namespace cv;  //namespace for  OpenCV library

//**************************-User Defined Settings-****************************
//image folder path
string image_folder_path = "/Users/yakup/Software Developer/DigSignalProcess/HW5/";

//To make debug: It shows all outputs in the operations
bool debug = false;

//***********************************--End--***********************************

void MedianFilter(const Mat& input, Mat& output, int N);
int FindMedium(int Array [], int N);

int main(int argc, const char * argv[]) {
    
    //Reading the "noisy_foto.jpg" image file into noisy Mat Object
    Mat noisy = imread(image_folder_path + "noisy_foto.jpg");
    
    //Check the Is the file opened or not?
    if (noisy.empty()){
        std::cerr<<"can't open image: <noisy_foto.jpg>"<<std::endl;
        return - 1;
    }
    
    //Debug: Show the noisy image file
    if(debug){ imshow("noisy image file", noisy); waitKey();}
    
    Mat noisy_gray(noisy.size(), CV_8UC1); //Noisy_Gray Mat object 8 bits
    //Convert Gray
    //Convert to noisy image to 8bits gray level image.
    cvtColor(noisy, noisy_gray, COLOR_BGR2GRAY);
    
    //Debug: Show the gray level image
    if(debug){ imshow("Gray Level Image File", noisy_gray); waitKey();}
    
    //Write the gray level image as noisy_gray.jpg
    imwrite(image_folder_path + "noisy_gray.jpg", noisy_gray);
    
//Median Filter with 7*7 Kernel
    Mat median1_gray(noisy_gray.size(), CV_8UC1); //Create median1_gray Mat Object
    //Take Median Filter with 7*7 Kernel
    MedianFilter(noisy_gray, median1_gray, 7);
    //Write the median1_gray image
    imwrite(image_folder_path + "median1_gray.jpg", median1_gray);
    
    //Debug: Show the median1_gray  image
    if(debug){ imshow("median1_gray Image", median1_gray); waitKey();}
    /*
//Median Filter with 27*27 Kernel
    Mat median2_gray(noisy_gray.size(), CV_8UC1); //Create median2_gray Mat Object
    //Take Median Filter with 27*27 Kernel
    MedianFilter(noisy_gray, median2_gray, 27);
    //Write the median1_gray image
    imwrite(image_folder_path + "median2_gray.jpg", median2_gray);
    
    //Debug: Show the median1_gray  image
    if(debug){ imshow("median2_gray Image", median2_gray); waitKey();}
    */
    
//To make test, the original opencv function.
//TEST, 7*7 kernel Test
    Mat opencv_median1_gray(noisy_gray.size(), CV_8UC1);
    medianBlur(noisy_gray, opencv_median1_gray, 7);
    
    //Write the opencv_median1_gray.jpg image
    imwrite(image_folder_path + "opencv_median1_gray.jpg", opencv_median1_gray);
    //Debug: Show the opencv_median1_gray.jpg  image
    if(debug){ imshow("opencv_median1_gray Image", opencv_median1_gray); waitKey();}
    
    
//TEST, 27*27 Kernel Test
    Mat opencv_median2_gray(noisy_gray.size(), CV_8UC1);
    medianBlur(noisy_gray, opencv_median2_gray, 27);
    
    //Write the opencv_median2_gray image
    imwrite(image_folder_path + "opencv_median2_gray.jpg", opencv_median2_gray);
    //Debug: Show the opencv_median2_gray  image
    if(debug){ imshow("opencv_median2_gray Image", opencv_median2_gray); waitKey();}
    
    return 0;
}


//     MEDIAN FILTER
//     image  - input image
//     output - output image
//     N      - width and Height of the image
void MedianFilter(const Mat& input, Mat& output, int N){
    
    //Padding. Adding border
    Mat input_padding;
    int padding_size = (N-1/2);
    copyMakeBorder( input, input_padding, padding_size , padding_size, padding_size, padding_size, BORDER_REFLECT);
    
    //Move window through all elements of the image
    for (int column_index = 0; column_index < input.cols; column_index++){
        
        for (int row_index= 0; row_index < input.rows ; row_index++){
            
            int window [N*N]; // window array N*N: filter lenght
            
            int window_left_bound = column_index - ((N-1) / 2 ); //left boundary of window
            int window_right_bound = column_index + ((N-1) / 2 ); //right boundary of window
            
            int window_up_bound = row_index - ((N-1) / 2 ); //up boundary of window
            int window_down_bound = row_index +((N-1) / 2 ); //down boundary of window
            
            //Taking the window[N*N]
            int i = 0;
            for(int window_column = window_left_bound; window_column <= window_right_bound; window_column++)
                for(int window_row = window_up_bound; window_row <= window_down_bound; window_row++, i++){
                    window[i] = (int)input_padding.at<uchar>(window_row + padding_size/2, window_column + padding_size/2);
                }
            
            //Assign The Medium of elements in Window
            output.at<uchar>(row_index, column_index) =  FindMedium(window, N*N);
            
        }
    }
}

//     Finding Medium
//     Array  - input Array
//     Lenght - Lenght of Input Array
//     ->Returning the medium integer value.
int FindMedium(int Array [], int Lenght){
    
    //   Order elements (only half of them) because the other half does not important for median value.
    for (int j = 0; j <= (Lenght-1)/2; ++j)
    {
        //   Find position of minimum element in each iteration
        int minumum_point = j;
        for (int index = j + 1; index < Lenght; ++index){
            if (Array[index] < Array[minumum_point])
                minumum_point = index;
        }
        //   Put found minimum element in its place
        const int temp = Array[j];
        Array[j] = Array[minumum_point];
        Array[minumum_point] = temp;
    }
    return Array [(Lenght-1)/2]; //return the mediaan value
}









