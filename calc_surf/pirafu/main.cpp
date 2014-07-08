//
//  main.cpp
//  pirafu
//
//  Created by Ryohei Fushimi on 7/1/14.
//  Copyright (c) 2014 dsj. All rights reserved.
//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
using namespace cv;

const int DIM_VECTOR = 128;  // 128次元ベクトル

/**
 * SURF情報をファイルに出力
 * @param[in]   filename            SURFを保存するファイル名
 * @param[in]   imageKeypoints      SURFキーポイント情報
 * @param[in]   imageDescriptors    SURF特徴ベクトル情報
 * @return なし
 */
void writeSURF(const char* filename, vector<KeyPoint> imageKeypoints, cv::Mat imageDescriptors) {
    fstream fout;
    fout.open(filename, ios::out);
    if (!fout.is_open()) {
        cerr << "cannot open file: " << filename << endl;
        return;
    }

    // 1行目はキーポイント数と特徴量の次元数を書き込む
    fout << imageKeypoints.size() << ' ' << DIM_VECTOR << endl;

    // 2行目からキーポイント情報と特徴ベクトルを書き込む
    for (int i = 0; i < imageKeypoints.size(); i++) {
        KeyPoint point = imageKeypoints.at(i);
        float* descriptor = (float*) imageDescriptors.row(i).data;
        // キーポイント情報（X座標, Y座標, サイズ, ラプラシアン）を書き込む
        fout << point.pt.x << ' ' << point.pt.y << ' ' << point.size << ' ';
        // 特徴ベクトルを書き込む
        for (int j = 0; j < DIM_VECTOR; j++) {
            fout << descriptor[j] << ' ';
        }
        fout << endl;
    }

    fout.close();
}

int main(int argc, char** argv) {
    
    for (int j = 0; j < 1; j ++){
        for (int i = 1; i <= 440; i++){
            char imageFile[100];
            char surfFile[100];
            const char* dirname = j ? "チャーハン": "能年玲奈";

            sprintf(imageFile, "/Users/ryohei/gitrepos/pirafu/resized-bing/%s/%d.jpg", dirname, i);
            sprintf(surfFile, "/Users/ryohei/gitrepos/pirafu/surf-bing/%s/%d.surf", dirname, i);
            
            // SURF抽出用に画像をグレースケールで読み込む
            IplImage* grayImage = cvLoadImage(imageFile, CV_LOAD_IMAGE_GRAYSCALE);
            
            if (!grayImage) {
                cerr << "cannot find image file: " << imageFile << endl;
                return -1;
            }
            
            // キーポイント描画用にカラーでも読み込む
            IplImage* colorImage = cvLoadImage(imageFile, CV_LOAD_IMAGE_COLOR);
            if (!colorImage) {
                cerr << "cannot find image file: " << imageFile << endl;
                return -1;
            }
            
            std::vector<KeyPoint> keypoints;
            cv::Mat descriptors;
            
            cv::SurfDescriptorExtractor extractor;
            
            cv::SURF calcSURF(500);
            calcSURF.detect(grayImage, keypoints);
            calcSURF.compute(grayImage, keypoints, descriptors);
            
            // SURFをファイルに出力
            writeSURF(surfFile, keypoints, descriptors);

            cvReleaseImage(&grayImage);
        }
    }

//    vector<KeyPoint>::iterator it = keypoints.begin();
//    // 画像にキーポイントを描画
//    while (it != keypoints.end()) {
//        KeyPoint point = *it;
//        CvPoint center;  // キーポイントの中心座標
//        int radius;      // キーポイントの半径
//        center.x = cvRound(point.pt.x);
//        center.y = cvRound(point.pt.y);
//        radius = cvRound(point.size * 1.2 / 9.0 * 2.0);
//        cvCircle(colorImage, center, radius, cvScalar(0,255,255), 1, 8, 0);
//        ++it;
//    }
//
//    cvNamedWindow("SURF");
//    cvShowImage("SURF", colorImage);
//    cvWaitKey(0);
//
//    // 後始末
//    cvReleaseImage(&grayImage);
//    cvReleaseImage(&colorImage);
//    cvClearSeq(imageKeypoints);
//    cvClearSeq(imageDescriptors);
//    cvReleaseMemStorage(&storage);

    cvDestroyAllWindows();

    return 0;
}