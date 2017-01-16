//
// Created by dialight on 06.12.16.
//

#include "utils/DrawUtils.hpp"

RNG rng(12345);

void ::DrawUtils::showPoints(Mat &frame, vector<Point2i> const &points) {
    for(auto const& p : points) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        cv::circle(frame, p, 5,  color, 2, LineTypes::LINE_AA);
    }
}

void ::DrawUtils::showLines(Mat &frame, vector<Line4i> const &lines) {
    for(auto const& l : lines) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        cv::line(frame, l.p1, l.p2, color, 3, LineTypes::LINE_AA);
    }
}

void ::DrawUtils::showPointContours(Mat &frame, vector<vector<Point2i>> const &contours) {
    int i = 0;
    for(auto const& contour : contours) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

        Point2i center;
        auto second = contour.end() - 1;
        for(auto first = contour.begin(); first != contour.end(); ++first) {
            cv::line(frame, *first, *second, color, 2);
            center += *first;
            second = first;
        }

        auto points = contour.size();
        center.x /= points;
        center.y /= points;
//            cv::rectangle(frame, rect, color, 1);

        stringstream ss;
        ss << "(" << i << "): " << contour.size();
        cv::putText(frame, ss.str(), center + Point2i(-10, -5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, color, 1, LineTypes::LINE_AA);
        i++;
    }
//        for(int i = 0; i < contours.size(); i++) {
//            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
//            drawContours(frame, contours, i, color, 2, 8, hierarchy, 0, Point());
//        }
}

void ::DrawUtils::showLineContours(Mat &frame, vector<vector<Line4i>> const &contours) {
    int i = 0;
    for(auto const& contour : contours) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        Point2i center;
        for(auto l : contour) {
            cv::line(frame, l.p1, l.p2, color, 2);
            center += l.p1;
            center += l.p2;
        }
        auto points = contour.size() * 2;
        center.x /= points;
        center.y /= points;
//            cv::rectangle(frame, rect, color, 1);

        stringstream ss;
        ss << "(" << i << ")" << contour.size();
        cv::putText(frame, ss.str(), center + Point2i(-10, -5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, color, 1, LineTypes::LINE_AA);
        i++;
    }
//        for(int i = 0; i < contours.size(); i++) {
//            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
//            drawContours(frame, contours, i, color, 2, 8, hierarchy, 0, Point());
//        }
}

void ::DrawUtils::showTriangle(Mat &frame, Triangle12i const &tr) {
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
    showTriangle(frame, tr, color);
}
void ::DrawUtils::showTriangle(Mat &frame, Triangle12i const &tr, Scalar &color) {
    cv::line(frame, tr.l1.p1, tr.l1.p2, color, 3, LineTypes::LINE_AA);
    cv::line(frame, tr.l2.p1, tr.l2.p2, color, 3, LineTypes::LINE_AA);
    cv::line(frame, tr.l3.p1, tr.l3.p2, color, 3, LineTypes::LINE_AA);
}

void ::DrawUtils::showTriangles(Mat &frame, vector<Triangle12i> const &triangles) {
    for(auto const& tr : triangles) {
        showTriangle(frame, tr);
    }
}
