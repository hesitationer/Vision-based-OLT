/*****************************************************************************
*	Implemetation of the saliency detction method described in paper
*	"Minimum Barrier Salient Object Detection at 80 FPS", Jianming Zhang, 
*	Stan Sclaroff, Zhe Lin, Xiaohui Shen, Brian Price, Radomir Mech, ICCV, 
*       2015
*	
*	Copyright (C) 2015 Jianming Zhang
*	If you have problems about this software on saliency detction method, please contact: 
*       jimmie33@gmail.com
*	
*	This is a C++ implementation on Linux of MBSPlusKF (modified on the above cited paper) 
*	of the method described in:

*   "Vision-based Real-Time Aerial Object Localization and Tracking for UAV Sensing System",
*	Yuanwei Wu, Yao Sui, Guanghui Wang, TCSVT under view, 2016.

*	If you have problems about this software MBSPlusKF, please contact: 
*       wuyuanwei2010 at gmail.com
*	
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*******************************************************************************/

#ifndef BMS_H
#define BMS_H

#ifdef IMDEBUG
#include <imdebug.h>
#endif
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>


static cv::RNG MBS_RNG;

class MBS
{
public:
	MBS (const cv::Mat& src);
	MBS (const cv::Mat& src, cv::Mat& mDst, cv::Mat& state);
	cv::Mat getSaliencyMap();
	void computeSaliency(bool use_MBSPlus = false);
	cv::Mat getMBSMap() const { return mMBSMap; }
private:
	cv::Mat mSaliencyMap;
	cv::Mat mMBSMap;
	int mAttMapCount;
	cv::Mat mBorderPriorMap;
	cv::Mat mSrc;
	cv::Mat mDst;
	cv::Mat KF_state;
	std::vector<cv::Mat> mFeatureMaps;
	void whitenFeatMap(float reg);
	void computeBorderPriorMap(float reg, float marginRatio);
};

cv::Mat computeCWS(const cv::Mat src, float reg, float marginRatio);
cv::Mat fastMBS(const std::vector<cv::Mat> featureMaps);
cv::Mat fastMBSPlus(const std::vector<cv::Mat> featureMaps, cv::Mat& mDst, cv::Mat& KF_state);
int findFrameMargin(const cv::Mat& img, bool reverse);
bool removeFrame(const cv::Mat& inImg, cv::Mat& outImg, cv::Rect &roi);

#endif
