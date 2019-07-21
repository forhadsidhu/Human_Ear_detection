


#include "core\core.hpp"
#include "highgui\highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/legacy/legacy.hpp"


#include <stdio.h>
#include <stdlib.h>
#include<cstdlib>
#include <iostream>
#include<direct.h>
#include<fstream>
#include <cstdio>
#include <vector>
#include<string.h>
#include<stdio.h>
#include<cmath>
#include<stdio.h>
#include<math.h>
#include <string>
#include<fstream>
#include "conio.h"

using namespace cv;
using namespace std;


#define PI 3.14159265
cv::Mat RGBtoHSV(const cv::Mat RGBMat);

double angleofTriangle(cv::Point a,cv::Point b,cv::Point c);
Point center,ref;

int returnLargestContourIndex(vector<vector<Point> > contours);

int main(int argc,const char** argv){
	

	


	     //cout<<"YES"<<endl;

	     int imgNum=74;
	     Mat  image=imread("F:\\Code\\Ear_detection\\test\\e6.jpg", CV_LOAD_IMAGE_UNCHANGED);


		 namedWindow("Mainimage",CV_WINDOW_NORMAL);
		 resizeWindow("Mainimage",100,100);
		 imshow("Mainimage",image);

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
		 
	          namedWindow("mask",CV_WINDOW_NORMAL);
		     resizeWindow("mask",200,200);
		     imshow("mask",mask);
		 
		 ///----------------------------------------------------------------

			



		
		

		


		       Mat segmented;
		      image.copyTo(segmented,mask);
  ///-----------------------------------------------------------------
		 
		     namedWindow("Segmented",CV_WINDOW_NORMAL);
		     resizeWindow("Segmented",200,200);
		    imshow("Segmented",segmented);

 ///----------------------------------------------------------------
		

	 

		 
		  Mat canny;
		  
	    Canny(segmented,canny,100,100,3);

		  namedWindow("Edges_oka",CV_WINDOW_NORMAL);
		   resizeWindow("Edges_oka",200,200);
		   imshow("Edges_oka",canny);



		   Mat can;
		   Canny(segmented,can,60,75,3);


		   int val=1;
		   int val1=16;


		 
		  
		   // allocate memories related to the number of rows
          int** arr = new int*[can.rows];

		// allocate memories related to the number of columns of each row
		for(int i = 0; i < can.rows; i++)
		{
			arr[i] = new int[can.cols];
		}


		  

		 //  int arr[350][350];


		

		   for(int i=0;i<can.rows ;i++)
		   {

			    for(int j=0;j<can.cols;j++)
				{
			               if(can.at<unsigned char>(i,j)>0)
						   {
							   arr[i][j]=16;

						   }
						   else{
							   arr[i][j]=-1;
						   }

				}


		   }
		   

		  
		   // Variables to store the final output 
    int maxSum = -100000, finalLeft, finalRight, finalTop, finalBottom; 
  
    int left, right, i; 
    int temp[500], sum, start, finish; 

	cout<<"Yes"<<endl;

  
    // Set the left column 
    for (left = 0; left < can.cols; ++left) 
    { 
        // Initialize all elements of temp as 0 
        memset(temp, 0, sizeof(temp)); 
  
        // Set the right column for the left column set by outer loop 
        for (right = left; right < can.cols; ++right) 
        { 

			

           // Calculate sum between current left and right for every row 'i' 
            for (i = 0; i < can.rows; ++i) 
                temp[i] += arr[i][right]; 
			     

  
            // Find the maximum sum subarray in temp[]. The kadane()  
            // function also sets values of start and finish.  So 'sum' is  
            // sum of rectangle between (start, left) and (finish, right)  
            //  which is the maximum sum with boundary columns strictly as 
            //  left and right. 

			////----------------------------------------------------------------Kadani----------------------------------
           // sum = kadane(temp, &start, &finish, ROW); 


   // initialize sum, maxSum and 
    int sum = 0, maxSum1 =-100000, i; 
  
    // Just some initial value to check for all negative values case 
    int finish = -1; 
	int n=can.rows;

  
    // local variable 
    int local_start = 0; 
  
    for (i = 0; i < n; ++i) 
    { 
        sum += temp[i]; 
        if (sum < 0) 
        { 
            sum = 0; 
            local_start = i+1; 
        } 
        else if (sum > maxSum1) 
        { 
            maxSum1 = sum; 
            start = local_start; 
            finish = i; 
        } 
    } 
  
     // There is at-least one non-negative number 
   // if (finish != -1) 
    //    return maxSum; 
  
	if(finish==-1){
    // Special Case: When all numbers in arr[] are negative 
    maxSum1 = temp[0]; 
    start = finish = 0; 
  
    // Find the maximum element in array 
    for (i = 1; i < n; i++) 
    { 
        if (temp[i] > maxSum1) 
        { 
            maxSum1 = temp[i]; 
            start = finish = i; 
        } 
    } 
	}
  



			///--------------------------------------------------------------------Kadani-------------------------------
            // Compare sum with maximum sum so far. If sum is more, then  
            // update maxSum and other output values 
            if (maxSum1 > maxSum) 
            { 
                maxSum = maxSum1; 
                finalLeft = left; 
                finalRight = right; 
                finalTop = start; 
                finalBottom = finish; 
            } 
        } 
    } 



	cout<<can.rows<<" "<<can.cols<<endl;

	cout<<finalTop<<" "<<finalLeft<<" "<<finalBottom<<" "<<finalRight<<endl;




		     



						// de-allocate memories related to the number of columns of each row
					// (YOU FORGOT THIS IN YOUR ORIGINAL CODE!!!)
					for(i = 0; i < can.rows; i++)
					{
						delete arr[i];
					}

					delete[] arr;




		   ///-----------------------special done----------------------------------------------



	    for(int i=0;i<can.rows;i++)
		{

			 for(int j=0;j<can.cols;j++)
			 {
				  if((i<finalTop || i>finalBottom)||(j<finalLeft || j>finalRight))
				  {
					  can.at<unsigned char>(i,j)=0;
				  }

			 }



		}

		


		
		  namedWindow("can",CV_WINDOW_NORMAL);
		   resizeWindow("can",200,200);
		 imshow("can",can);

		 Rect croppedRectangle = Rect(finalLeft,finalTop,finalRight-finalLeft,finalBottom-finalTop);
			  Mat can2= can(croppedRectangle);


			  
		      Mat cropped;
	          GaussianBlur( can2, cropped, Size( 3, 3 ), 0, 0 );

			


		// Mat can1;
		// can.copyTo(can1);

		 ///-----------------------------------------------------------------------------

		           
		      namedWindow("Cropped",CV_WINDOW_NORMAL);
		  
		         imshow("Cropped",cropped);





		 ///-----------------------------------Cropping Shes----------------------------------------------------



/*

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
	/*
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
	/*
		  Mat closed;
		 Mat element= getStructuringElement(MORPH_ELLIPSE,Size(5,10));
		 morphologyEx(dilated,closed,CV_MOP_CLOSE,element);

		  ///-----------------------------------------------------------------
		 
		 namedWindow("Closed",CV_WINDOW_NORMAL);
		 resizeWindow("Closed",200,200);
		 imshow("Closed",closed);
		 
		 ///----------------------------------------------------------------

		  
		 Mat distanceMat=Mat(closed.rows,closed.cols,CV_8UC1);
		 distanceTransform(closed,distanceMat,CV_DIST_L2,3);

		  ///-----------------------------------------------------------------
		 
		 namedWindow("distance_transform",CV_WINDOW_NORMAL);
		 resizeWindow("distance_transform",200,200);
		 imshow("distance_transform",distanceMat);
		 
		 ///----------------------------------------------------------------
		  
		 cv::normalize(distanceMat,distanceMat,0,1.,cv::NORM_MINMAX);

		  ///-----------------------------------------------------------------
		 
		 namedWindow("norm",CV_WINDOW_NORMAL);
		 resizeWindow("norm",200,200);
		 imshow("norm",distanceMat);
		
		
		 ///----------------------------------------------------------------

		 cv::threshold(distanceMat,distanceMat,.5,1.,CV_THRESH_BINARY);

		  ///-----------------------------------------------------------------
		 
		 namedWindow("Thresh",CV_WINDOW_NORMAL);
		 resizeWindow("Thresh",200,200);
		 imshow("Thresh",distanceMat);
		 
		 ///----------------------------------------------------------------
		 
		 Mat again_dilated=Mat(closed.rows,closed.cols,CV_8UC1);
		 Mat element4=getStructuringElement(MORPH_ELLIPSE,Size(10,25));
		 morphologyEx(distanceMat,again_dilated,CV_MOP_DILATE,element4);

		  ///-----------------------------------------------------------------
		
		 namedWindow("again_dilated",CV_WINDOW_NORMAL);
		 resizeWindow("again_dilated",200,200);
		 imshow("again_dilated",again_dilated);
		
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
		 
		 namedWindow("ellipsemask",CV_WINDOW_NORMAL);
		 resizeWindow("ellipsemask",100,100);
		 imshow("ellipsemask",ellipseMask);
		 
		 ///----------------------------------------------------------------
		 
		 blur(image,image,Size(3,3));
		  
		 /*
		 namedWindow("blur",CV_WINDOW_NORMAL);
		 resizeWindow("blur",70,70);
		 imshow("blur",image);
		 */
		 ///----------------------------------------------------------------
		 /*
		  Canny(image,canny,60,75,3);
		   ///-----------------------------------------------------------------
		  
		 namedWindow("canny",CV_WINDOW_NORMAL);
		 resizeWindow("canny",70,70);
		 imshow("canny",canny);
		 
		 ///----------------------------------------------------------------

		 
		      Mat gaus;
	          GaussianBlur( canny, gaus, Size( 3, 3 ), 0, 0 );


			 


           Mat cropped;
 		  gaus.copyTo(cropped,ellipseMask);

			  

		 

///-----------------------------------------------------------------

		  
		 namedWindow("cropped",CV_WINDOW_NORMAL);
		 resizeWindow("cropped",100,100);
		 imshow("cropped",cropped);
		 
		 
///----------------------------------------------------------------------------------------------------------------------------
		  
		 cv::Mat rot_mat= cv::getRotationMatrix2D(minEllipse.center,minEllipse.angle,1);
		 cv::Mat rotated;
		 cv::warpAffine(cropped,rotated,rot_mat,image.size(),cv::INTER_CUBIC);
///-----------------------------------------------------------------
	
		 namedWindow("rotated",CV_WINDOW_NORMAL);
		 resizeWindow("rotated",200,200);
		 imshow("rotated",rotated);
		 
///-------------------------------------------------------------------------------------

		 getRectSubPix(rotated,minEllipse.size,minEllipse.center,cropped);
		 center=Point(cropped.cols/2,cropped.rows/2);
		 ref=Point(cropped.cols/2.0);
		 circle(cropped,center,1,Scalar(0,0,255),2);

	///---------------------------------------------------------------------------------
		
		 namedWindow("Cropped",CV_WINDOW_NORMAL);
		 resizeWindow("Cropped",200,200);
		 imshow("Cropped",cropped);

		 cout<<"YES"<<endl;
		 





		 int upper[21];
		 int lower[21];



		 std::fill(upper,upper+20,0);
		 std::fill(lower,lower+20,0);

//----------------------------Curve fitting-----------------------------------------------//

		 /*
		 vector<int>x;
		 vector<int>y;



		 for(int i=0;i<cropped.rows;i++)
		 {
			   for(int j=cropped.cols-1;j>=0;j--)
			   {

				    if(cropped.at<unsigned char>(i,j)>50){

						x.push_back(i);
						y.push_back(j);
						break;

					}

			   }



		 }


		long long x2=0,x3=0,x4=0,xy=0,xxy=0,x1=0,y1=0;

		for(int i=0;i<x.size();i++)
		{
          x2+=x[i]*x[i];
		  x3+=x[i]*x[i]*x[i];
		  x4+=x[i]*x[i]*x[i]*x[i];
		  xy+=x[i]*y[i];
		  xxy+=x[i]*x[i]*y[i];
		  x1+=x[i];
		  y1+=y[i];

		}

		///Jacobi iteration method...................

	long long a0=0,b0=0,c0=0;
	
	long long n=x.size();


	for(int i=0;i<12;i++)
	{

		  
		 long long  a1=(y1-b0*x1-n*c0)/x2;
		 long long  b1=(xy-a0*x3-c0*x1)/x2;
		 long long  c1=(xxy-a0*x4-b0*x3)/x2;
	
		   if(a0==a1 && b0==b1 && c0==c1)
		   {
			     break;
		   }

		   a0=a1;
		   b0=b1;
		   c0=c1;



	}

	
	*/

///--------------------------------------------------End of curve fitting---------------------------------//


        // getRectSubPix(rotated,minEllipse.size,minEllipse.center,cropped);
		 center=Point(cropped.cols/2,cropped.rows/2);
		 ref=Point(cropped.cols/2.0);
		// circle(cropped,center,1,Scalar(0,0,255),2);
         


          int upper[21];
		 int lower[21];



		 std::fill(upper,upper+20,0);
		 std::fill(lower,lower+20,0);


		  int count=-1;
		  int pointr[500];
		  int pointc[500];


		  for(int r=(cropped.rows)/2;r>0;r-=5)
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


					  if(n==1 &&!flag){
						  claster++;
						  flag=1;
						  n=0;
					  }

				 }
				 
				   // cout<<"YES"<<endl;
					  int index=(cropped.rows-(2*r))/10;
					  upper[index]=claster;
					  line(cropped,Point(0,r),Point(cropped.cols,r),Scalar(255,0,0),1);
					  

		  }


		  cout<<"rows:"<<cropped.rows<<endl;


//------------------------------------------------------------------------------------
		
		  namedWindow("Line",CV_WINDOW_NORMAL);
		               resizeWindow("Line",100,200);
		            imshow("Line",cropped);
					
///-----------------------------------------------------------------------

					int index=0;

					for(int r=(cropped.rows/2)+5;r<cropped.rows;r+=5)
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

					  

					   mkdir("data/database");
					   char s[100]="data/database/";
					   sprintf(s,"%s%d",s,imgNum);
					   mkdir(s);
					  
					   char pointsPerLine[100];
					   char st[200]="/point_per_Line.txt";
					   sprintf(pointsPerLine,"%s%s",s,st);

						   ofstream outfile;
					   outfile.open(pointsPerLine,std::ios_base::out);

					   if(outfile.is_open())
					   {
						    outfile<<imgNum<<".\n";
							outfile<<"   ";

							 for(int i=0;i<20;i++)
							   if(upper[i])outfile<<upper[i]<<" ";

							 outfile<<"\n ";
							 for(int i=0;i<20;i++)
								  if(lower[i])outfile<<lower[i]<<" ";

							 outfile<<"\n\n";

							 outfile.close();



					   }
					   else cout<<"Unable to open file";



					   char MaxdistancesFileName[100];
					   sprintf(MaxdistancesFileName,"%s/Max_Height.txt",s);
					   ofstream  Maxdistancefile;
					   Maxdistancefile.open(MaxdistancesFileName,std::ios_base::out);

					   if(Maxdistancefile.is_open())
					   { 
						   
						    Maxdistancefile<<cropped.size().height;

							Maxdistancefile.close();

					   }
					   else{
						    cout<<"Unable to open file"<<endl;
					   }


					   //-------------------------------------------------------

					   /*
					   char outeredgecurve[100];
					   sprintf(outeredgecurve,"%s/outer_edge.txt",s);
					   ofstream  outeredgecurvefile;
					   outeredgecurvefile.open(outeredgecurve,std::ios_base::out);

					   if(outeredgecurvefile.is_open())
					   { 
						   
						    outeredgecurvefile<<a0<<","<<b0<<","<<c0;

							outeredgecurvefile.close();

					   }
					   else{
						    cout<<"Unable to open file"<<endl;
					   }



					   */


					   ///-----------------------------------------------------------------
                
					   
				char distancesFileName[100];
				sprintf(distancesFileName,"%s/distances.txt",s);

				ofstream distancefile;
				distancefile.open(distancesFileName,std::ios_base::out);


				char angleFileName[100];
				sprintf(angleFileName,"%s/angles.txt",s);
				ofstream anglefile;
				anglefile.open(angleFileName,std::ios_base::out);


				double distSum=0,angleSum=0,distAvg,angleAvg;

				double *dist=0;

				   dist=new double[count];

				double *angle=0;
				    angle=new double[count];


					if(distancefile.is_open() && anglefile.is_open())
					{

						   for(int i=0;i<count;i++)
						   {

							   double dis=((center.x-pointc[i])*(center.x-pointc[i])+(center.y-pointr[i])*(center.y-pointr[i]));

							   dis=sqrtf(dis);
							    distancefile<<dis<<" ";

								distSum+=dis;
								dist[i]=dis;

								double angl=angleofTriangle(center,ref,Point(pointc[i],pointr[i]));
								anglefile<<angl<<" ";

								angleSum+=angl;
								angle[i]=angl;




						   }


						   distancefile<<"\n";
						   anglefile<<"\n";

						   distAvg=distSum/count;
						   angleAvg=angleSum/count;

						   cout<<"Avg:"<<distAvg<<", "<<angleAvg<<endl;

						   distancefile.close();
						   anglefile.close();



					}
					else{
						 cout<<"Unable to open file"<<endl;
						
					     
					}



			char sdFileName[100];
			sprintf(sdFileName,"%s/sd.txt",s);
			ofstream sdfile;
			sdfile.open(sdFileName,std::ios_base::out);

			double distVarianceSum=0,distVariance;
			double angleVarianceSum=0,angleVariance;

			     if(sdfile.is_open())
				 {

					  for(int i=0;i<count;i++)
					  {
						  distVarianceSum+=(distAvg-dist[i])*(distAvg-dist[i]);
						  angleVarianceSum+=(angleAvg-angle[i])*(angleAvg-angle[i]);

					  }

					  double x1=abs(distVarianceSum/count);

					  distVariance=sqrtf(x1);

					  double y1=abs(angleVarianceSum/count);

					  angleVariance=sqrtf(y1);

					  sdfile<<distVariance<<","<<angleVariance<<";"<<endl;

					  sdfile.close();

				 }
				 else{
					 cout<<"Unable to open file"<<endl;
				 }

						


		for(int i=1;i<=46;i++){			

				 char ts[500]="data/database/";
				 sprintf(ts,"%s%d",ts,i);

				 char testFileName[100];
				 sprintf(testFileName,"%s/sd.txt",ts);


				 ifstream testfile(testFileName);
				// testfile.open(testFileName,std::ios_base::in);



                
				  std::string line;
				 std::string ls="",first="",second="";
				 if(testfile.is_open()){


					  while(std::getline(testfile,line)){

						  
						   cout<<"YEs"<<endl;
						   cout<<line<<endl;

						  for(int j=0;j<line.size();j++)
						  {

							 
							     char c=line[j];
								 if(c==',')
								 {
									   first=ls;
									   ls="";
									   continue;
								 }
								 if(c==';')
								 {
									  second=ls;
									  ls="";
								 }
								 ls+=c;

							   
						  }

						// cout<<"First->"<<first<<"Second->"<<second<<endl;

					  }
					 

					

					


					double fdistSd=atof(first.c_str());
					double fangleSd=atof(second.c_str());

				//  cout<<"First->"<<first<<"Second->"<<second<<endl;


					int idistSd=(int)fdistSd;
					int iangleSd=(int)fangleSd;
					int idistVar=(int)distVariance;
					int iangleVar=(int)angleVariance;

				/*	
					while(idistSd>10)
					{
						idistSd/=10;

					}
					while(iangleSd>10)
					{
						iangleSd/=10;

					}
					while(idistVar>10)
					{
						idistVar/=10;

					}
					while(iangleVar>10)
					{
						iangleVar/=10;

					}
					
					*/
            
					cout<<"Sd of Query image "<<idistSd<<":"<<iangleSd<<"\n";


					if((idistSd==idistVar) && (iangleSd==iangleVar)){
						 cout<<"This Image is found in image no:"<<i<<endl;
						 testfile.close();
						 break;

					}

					testfile.close();

				 }
				 else{
					    cout<<"YES found"<<endl;
					    cout<<"-------------------End----------------"<<endl;



				 }
				 

		}


		
              
  waitKey(0);
  return 0;


  
}  
   

double angleofTriangle(cv::Point a,cv::Point b,cv::Point c)
{
          
	       double  C=std::sqrtf((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
		   double  A=std::sqrtf((b.x-c.x)*(b.x-c.x)+(b.y-c.y)*(b.y-c.y));
		   double  B=std::sqrtf((c.x-a.x)*(c.x-a.x)+(c.y-a.y)*(c.y-a.y));

		   double cos_a=(B*B+C*C-A*A)/(2*B*C);
		   double theta=acos(cos_a);
		   double angleInDegree=(theta*180)/PI;

		  
		   

		   return angleInDegree;




}

int returnLargestContourIndex(vector<vector<Point> > contours)
 {
     unsigned int max_contour_size = 0;
     int max_contour_idx = -1;
     for(unsigned int i = 0; i < contours.size(); ++i)
     {
         if(contours[i].size() > max_contour_size)
         {
             max_contour_size = static_cast<int>(contours[i].size());
             max_contour_idx = i;
         }
     }
     return max_contour_idx;
 }