//
// Created by dialight on 26.02.17.
//

#ifndef OPENCVCLIENT_IPTDMANUAL_HPP
#define OPENCVCLIENT_IPTDMANUAL_HPP

#include <opencv/Types.hpp>

class IPTDManual {

    cv::Mat gray;
public:
    void loop(cv::Mat &frame);
};


#endif //OPENCVCLIENT_IPTDMANUAL_HPP
