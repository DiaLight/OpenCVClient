//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_IPTRIANGLEDETECT2_HPP
#define OPENCVCLIENT_IPTRIANGLEDETECT2_HPP

#include <opencv/Types.hpp>
#include <IntelEdison.hpp>

class IPTDContours {

    Mat gray;
    Triangle12i last;
    RNG rng;
    Scalar color;
    IntelEdison edison;
public:

    void find(Mat &mat, vector<Triangle12i> &triangles);

    void loop(Mat &mat);
};


#endif //OPENCVCLIENT_IPTRIANGLEDETECT2_HPP
