//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_IPTRIANGLEDETECT2_HPP
#define OPENCVCLIENT_IPTRIANGLEDETECT2_HPP

#include <opencv/Types.hpp>

class IPTriangleDetect2 {

    Mat gray;
public:

    void find(Mat &mat, vector<Triangle12i> &triangles);

};


#endif //OPENCVCLIENT_IPTRIANGLEDETECT2_HPP
