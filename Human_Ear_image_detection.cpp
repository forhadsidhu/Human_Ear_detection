

#include "core\core.hpp"
#include "highgui\highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/legacy/legacy.hpp"





#include <iostream>
#include<direct.h>
#include<fstream>
#include <cstdio>
#include <vector>
#include<string.h>

using namespace cv;
using namespace std;



cv::Mat RGBtoHSV(const cv::Mat RGBMat);

double angleofTriangle(cv::Point a,cv::Point b,cv::Point c);
Point center,ref;


int main(int argc,const char** argv){




	     Mat  image=imread("F:\\Code\\Ear_Image_Detection\\ear8.jpg", CV_LOAD_IMAGE_COLOR);

		 Mat hsv=Mat::zeros(image.rows,image.cols,CV_32FC3);

		 cvtColor(image,hsv,CV_BGR2HSV);

        ///-----------------------------------------------------------------
		 namedWindow("HSV",CV_WINDOW_NORMAL);
		 resizeWindow("HSV",200,200);
		 imshow("HSV",hsv);
		 ///----------------------------------------------------------------
		 //  onek gula skin niya tader hue,saturation & standard deviation ber korey min & max range ber krci....
		 ///  min=avg-sd    max=avg+sd;


		 int hueLower=0;
		 int hueUpper=33;
		 int satLower=50;
		 int satUpper=255;
		 int vLower=50;
		 int vUpper=255;

		 Scalar Lower=Scalar(hueLower,satLower,vLower);
		 Scalar Upper=Scalar(hueUpper,satUpper,vUpper);

		 Mat mask;
		 inRange(hsv,Lower,Upper,mask);


		 ///-----------------------------------------------------------------
		 /*
	          namedWindow("mask",CV_WINDOW_NORMAL);
		     resizeWindow("mask",200,200);
		 imshow("mask",mask);
		 */
		 ///----------------------------------------------------------------

		


		 Mat segmented;
		 image.copyTo(segmented,mask);
		  ///-----------------------------------------------------------------
		 /*
		     namedWindow("Segmented",CV_WINDOW_NORMAL);
		   resizeWindow("Segmented",200,200);
		 imshow("Segmented",segmented);
		 */
		 ///----------------------------------------------------------------
		  
		 Mat canny;
		 Canny(segmented,canny,30,30,3);


		   Mat first_closed;
		 Mat first_element= getStructuringElement(MORPH_ELLIPSE,Size(5,10));
		 morphologyEx(canny,first_closed,CV_MOP_CLOSE,first_element);


		  ///-----------------------------------------------------------------
		 /*
		    namedWindow("first_close",CV_WINDOW_NORMAL);
		   resizeWindow("first_closed",200,200);
		 imshow("first_closed",first_closed);
		 */
		 ///----------------------------------------------------------------
		  Mat dilated=Mat(first_closed.rows,first_closed.cols,CV_8UC1);
		 Mat element3=getStructuringElement(MORPH_ELLIPSE,Size(10,25));
		 morphologyEx(first_closed,dilated,CV_MOP_DILATE,element3);

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("dilated",CV_WINDOW_NORMAL);
		 resizeWindow("dilated",200,200);
		 imshow("dilated",dilated);
		 */
		 ///----------------------------------------------------------------
		  Mat closed;
		 Mat element= getStructuringElement(MORPH_ELLIPSE,Size(5,10));
		 morphologyEx(dilated,closed,CV_MOP_CLOSE,element);

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("Closed",CV_WINDOW_NORMAL);
		 resizeWindow("Closed",200,200);
		 imshow("Closed",closed);
		 */
		 ///----------------------------------------------------------------

		  
		 Mat distanceMat=Mat(closed.rows,closed.cols,CV_8UC1);
		 distanceTransform(closed,distanceMat,CV_DIST_L2,3);

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("distance_transform",CV_WINDOW_NORMAL);
		 resizeWindow("distance_transform",100,100);
		 imshow("distance_transform",distanceMat);
		 */
		 ///----------------------------------------------------------------
		  
		 cv::normalize(distanceMat,distanceMat,0,1.,cv::NORM_MINMAX);

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("norm",CV_WINDOW_NORMAL);
		 resizeWindow("norm",200,200);
		 imshow("norm",distanceMat);
		 */
		 ///----------------------------------------------------------------

		 cv::threshold(distanceMat,distanceMat,.5,1.,CV_THRESH_BINARY);

		 cout<<"YES"<<endl;

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("Thresh",CV_WINDOW_NORMAL);
		 resizeWindow("Thresh",200,200);
		 imshow("Thresh",distanceMat);
		 */
		 ///----------------------------------------------------------------
		 
		 Mat again_dilated=Mat(closed.rows,closed.cols,CV_8UC1);
		 Mat element4=getStructuringElement(MORPH_ELLIPSE,Size(10,25));
		 morphologyEx(distanceMat,again_dilated,CV_MOP_DILATE,element4);

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("again_dilated",CV_WINDOW_NORMAL);
		 resizeWindow("again_dilated",200,200);
		 imshow("again_dilated",again_dilated);
		 */
		 ///----------------------------------------------------------------
		 

		
		 Mat converted;

		 double minVal;
		 double maxVal;
		 Point minLoc;
		 Point maxLoc;
		 minMaxLoc(again_dilated,&minVal,&maxVal,&minLoc,&maxLoc);
		 again_dilated-=minVal;

		 again_dilated.convertTo(converted,CV_8UC1,255.0/(maxVal-minVal));

		 vector<vector<Point>> contours;

		 findContours(converted,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
		 double largest_area=0;
		 int largest_index=0;

		 for(int i=0;i<contours.size();i++)
		 {
			  double area=contourArea(contours[i],false);

			  if(area>largest_area)
			  {

				   largest_area=area;
				   largest_index=i;
			  }

		 }

		
		 RotatedRect minEllipse =fitEllipse(contours[largest_index]);

		 Mat ellipseMask= Mat::zeros(image.rows,image.cols,CV_8UC1);
		 ellipse(ellipseMask,minEllipse,Scalar(255),CV_FILLED,2);

		  ///-----------------------------------------------------------------
		 /*
		 namedWindow("ellipsemask",CV_WINDOW_NORMAL);
		 resizeWindow("ellipsemask",100,100);
		 imshow("ellipsemask",ellipseMask);
		 */
		 ///----------------------------------------------------------------
		 
		 blur(image,image,Size(3,3));
		  
		 /*
		 namedWindow("blur",CV_WINDOW_NORMAL);
		 resizeWindow("blur",70,70);
		 imshow("blur",image);
		 */
		 ///----------------------------------------------------------------

		  Canny(image,canny,25,45,3);
		   ///-----------------------------------------------------------------
		  /*
		 namedWindow("canny",CV_WINDOW_NORMAL);
		 resizeWindow("canny",70,70);
		 imshow("canny",canny);
		 */
		 ///----------------------------------------------------------------


		      Mat gaus;
	          GaussianBlur( canny, gaus, Size( 3, 3 ), 0, 0 );


		  Mat cropped;
		  gaus.copyTo(cropped,ellipseMask);

		 

///-----------------------------------------------------------------

		  /*
		 namedWindow("cropped",CV_WINDOW_NORMAL);
		 resizeWindow("cropped",100,100);
		 imshow("cropped",cropped);]
		 */
///----------------------------------------------------------------------------------------------------------------------------
		  
		 cv::Mat rot_mat= cv::getRotationMatrix2D(minEllipse.center,minEllipse.angle,1);
		 cv::Mat rotated;
		 cv::warpAffine(cropped,rotated,rot_mat,image.size(),cv::INTER_CUBIC);
///-----------------------------------------------------------------
	/*
		 namedWindow("rotated",CV_WINDOW_NORMAL);
		 resizeWindow("rotated",200,200);
		 imshow("rotated",rotated);
		 */
///-------------------------------------------------------------------------------------
		 getRectSubPix(rotated,minEllipse.size,minEllipse.center,cropped);
		 center=Point(cropped.cols/2,cropped.rows/2);
		 ref=Point(cropped.cols/2.0);
		 circle(cropped,center,1,Scalar(0,0,255),2);

	///---------------------------------------------------------------------------------
		
		 namedWindow("Nafiza",CV_WINDOW_NORMAL);
		 resizeWindow("Nafiza",200,200);
		 imshow("Nafiza",cropped);

		
		 





		 int upper[21];
		 int lower[21];



		 std::fill(upper,upper+20,0);
		 std::fill(lower,lower+20,0);


		  int count=-1;
		  int pointr[700];
		  int pointc[700];


		  for(int r=(cropped.rows)/2;r>0;r-=5)
		  {
			   
			     int n=0;
				 int claster=0;
				 bool flag=0;

				 for(int c=0;c<cropped.cols;++c)
				 {


					  if(cropped.at<unsigned char>(r,c)>10){
					   n++;
					   count++;
					   pointr[count]=r;
					   pointc[count]=c;
					  }
					  else{
						    n=0;
							flag=0;

					  }


					  if(n==1 &&!flag){
						  claster++;
						  flag=1;
						  n=0;
					  }

				 }
				 
				    cout<<"YES"<<endl;
					  int index=(cropped.rows-(2*r))/10;
					  upper[index]=claster;
					  line(cropped,Point(0,r),Point(cropped.cols,r),Scalar(255,0,0),1);
					  

		  }


		  cout<<"rows:"<<cropped.rows<<endl;


//------------------------------------------------------------------------------------
					   namedWindow("Line",CV_WINDOW_NORMAL);
		               resizeWindow("Line",200,200);
		            imshow("Line",cropped);
///-----------------------------------------------------------------------

					int index=0;

					for(int r=cropped.rows/2+5;r<cropped.rows;r+=5)
					{

						  int n=0;
						  int claster=0;
						  bool flag=0;

						  for(int c=0;c<cropped.cols;++c)
						  {
							  if(cropped.at<unsigned char>(r,c)>50){
								   n++;
								   count++;
								   pointr[count]=r;
								   pointc[count]=c;

							  }
							  else{
								   n=0;
								   flag=0;
							  }

							  if(n==1&&!flag)
							  {
								   claster++;
								   flag=1;
								   n=0;

							  }

						  }///second loop

						  lower[index]=claster;
						  line(cropped,Point(0,r),Point(cropped.cols,r),Scalar(255,0,0),1);
						  index++;



					}

//------------------------------------------------------------------------------------
					   namedWindow("Line",CV_WINDOW_NORMAL);
		               resizeWindow("Line",200,200);
		            imshow("Line",cropped);
///-----------------------------------------------------------------------


  
  waitKey(0);
  return 0;


  
}  
