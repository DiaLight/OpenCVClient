//
// Created by dialight on 29.11.16.
//

#ifndef OPENCVCLIENT_PATRIANGLEDETECT_HPP
#define OPENCVCLIENT_PATRIANGLEDETECT_HPP

#include <highgui.h>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <iostream>
#include <opencv/Types.hpp>

using namespace cv;
using namespace std;

struct patriangle_t {
    Line4i lines[3];
    Point2i fst_pos;
    Point2i cur_pos;
    bool checked;
    patriangle_t(const Line4i &l1, const Line4i &l2, const Line4i &l3) : lines{l1, l2, l3} {}
};
typedef struct patriangle_t PATriangle;

class PATriangleDetect {

    Mat gray;

    int area = 15; // 15

    vector<Vec4i> tmp;
public:

    Mat loop(Mat &frame);

    void findTriangles(const vector<Line4i> &lines, int width, vector<PATriangle> &triangles);

    void show(Mat &frame, vector<PATriangle> &triangles) {

//        CvFont *font = new CvFont;
//        cvInitFont(font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, 8);
        auto text = "Triangle has been detected!";

        int i = 0;
        int j = 0;
        for(auto trp = triangles.begin(); trp != triangles.end(); ) {
            auto &tr = *trp;

            stringstream ss;
            ss << "New Triangle: #" << j++ << "    It's first position: " << tr.fst_pos.x << " " << tr.fst_pos.y;
            cv::putText(frame, ss.str(), cvPoint(150, 50 * ((int) triangles.size() + 1)), FONT_HERSHEY_COMPLEX_SMALL, 0.8, CV_RGB(0, 255, 0), 1, LINE_AA);

            if (checkCloseBorderline(tr.cur_pos, frame.cols)) {
                trp = triangles.erase(trp);
            } else {
                ++trp;
            }
            // вывод сообщения на экран о прохождении треугольника через линию
            if (tr.checked) {
                cv::putText(frame, text, cvPoint(50, 50 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.8, CV_RGB(0, 255, 0), 1, LINE_AA);
            }
        }

        // обводка треугольников в массиве, и проверка прохождения треугольника через линию
        for (i = 0; i < triangles.size(); i++) {
            PATriangle &tr = triangles[i];
            if (abs(frame.cols / 2 - tr.cur_pos.x) <= frame.cols / 25 && !tr.checked) {
                stringstream ss;
                ss << "NEW TRIANGLE #" << i << "    ITS POSITION " << tr.cur_pos.x << " " << tr.cur_pos.y;
                cv::putText(frame, ss.str(), cvPoint(150, 50 * i), FONT_HERSHEY_COMPLEX_SMALL, 0.8, CV_RGB(0, 255, 0), 1, LINE_AA);
//                cv::putText(frame, text, cvPoint(150, 50 * i), FONT_HERSHEY_COMPLEX_SMALL, 0.8, CV_RGB(0, 255, 0), 1, LINE_AA);
                tr.checked = true;
            }
            for (j = 0; j < 3; j++) {
                Line4i &line1 = tr.lines[j];
                cv::line(frame, line1.p1, line1.p2, CV_RGB(255, 0, 0), 3, CV_AA);
            }
            cv::circle(frame, tr.cur_pos, 2, CV_RGB(255, 255, 0), 1, LINE_AA);
        }

        cv::line(frame, Point2i(frame.cols / 2, 0), Point2i(frame.cols / 2, frame.rows), CV_RGB(0, 255, 0), 1, LINE_AA);
    }

    void manSmooth(Mat &img) {
        //Сглаживание
        float kernel[9];
        kernel[0] = 0.1;
        kernel[1] = 0.1;
        kernel[2] = 0.1;

        kernel[3] = 0.1;
        kernel[4] = 0.1;
        kernel[5] = 0.1;

        kernel[6] = 0.1;
        kernel[7] = 0.1;
        kernel[8] = 0.1;

        Mat kernel_matrix = Mat(3, 3, CV_32F, kernel, sizeof(float));
        cv::filter2D(img, img, img.depth(), kernel_matrix, cvPoint(-1, -1));
    }
    void filterImage(Mat &img) {
        // Обработка изображения
        cv::blur(img, img, Size(3,3));
//    CvMat kernel_matrix = cvMat(3, 3, CV_32FC1, kernel);
//    cvFilter2D(img, img, &kernel_matrix, cvPoint(-1, -1));

        //Увеличение четкости


        //Увеличение яркости
        // kernel[0]=-0.1; kernel[1]=0.2; kernel[2]=-0.1;

        // kernel[3]=0.2; kernel[4]=3; kernel[5]=0.2;

        // kernel[6]=-0.1; kernel[7]=0.2; kernel[8]=-0.1;

        // kernel_matrix=cvMat(3,3,CV_32FC1,kernel);
        // //cvFilter2D(img, img, &kernel_matrix, cvPoint(-1,-1));

        // kernel[0]=-0.1; kernel[1]=-0.1; kernel[2]=-0.1;

        // kernel[3]=-0.1; kernel[4]=2; kernel[5]=-0.1;

        // kernel[6]=-0.1; kernel[7]=-0.1; kernel[8]=-0.1;

        //kernel_matrix=cvMat(3,3,CV_32FC1,kernel);
        //cvFilter2D(img, img, &kernel_matrix, cvPoint(-1,-1));
    }

    void showTriangles(Mat &frame, vector<PATriangle> const& triangles);

private:
    Point2i posTriangle(Line4i *t);
    bool triangleCompare(Point2i p, Point2i q, int area);

    /* используется для отсеивания треугольников,
     * которые находятся слишком близко к границам экрана
     */
    bool checkCloseBorderline(Point2i pos, int width) {
        return width * 3 / 4 <= pos.x || width / 4 >= pos.x;
    }

};


#endif //OPENCVCLIENT_PATRIANGLEDETECT_HPP
