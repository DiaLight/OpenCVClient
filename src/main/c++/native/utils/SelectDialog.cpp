//
// Created by dialight on 09.03.17.
//

#include <utils/SelectDialog.hpp>

using namespace cv;

static Scalar red(0, 0, 255);

static void static_mouseHandler(int event, int x, int y, int flags, void *param) {
    ((SelectDialog *) param)->mouseHandler(event, x, y, flags);
}

bool SelectDialog::getBBFromUser(Mat &frame, Rect &rect) {
    img0 = frame.clone();
    bb = &rect;
    bool correctBB = false;
//    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, 8);

    setMouseCallback(windowName, static_mouseHandler, this);
    putText(img0, "Draw a bounding box and press Enter", Point(0, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(255, 255, 0));
    imshow(windowName, img0);

    while (!correctBB) {
        char key = (char) waitKey(0);

        if (tolower(key) == 'q') {
            return false;
        }

        if (((key == '\n') || (key == '\r') || (key == '\r\n')) && (bb->x != -1) && (bb->y != -1)) {
            correctBB = true;
        }
    }

    if (rect.width < 0) {
        rect.x += rect.width;
        rect.width = -rect.width;
    }

    if (rect.height < 0) {
        rect.y += rect.height;
        rect.height = -rect.height;
    }

    setMouseCallback(windowName, NULL, NULL);

    return true;
}

SelectDialog::SelectDialog(const std::string &windowName) : windowName(windowName) {

}

void SelectDialog::loop(Mat &frame, tld::TLD &tld) {
    Mat gray;
    cvtColor(frame, gray, CV_BGR2GRAY);
    if(showCall) {
        showCall = false;
        Rect box(-1, -1, -1, -1);
        if (getBBFromUser(frame, box)) {
            tld.selectObject(gray, &box);
        }
    }
}

void SelectDialog::show() {
    showCall = true;
}

void SelectDialog::mouseHandler(int event, int x, int y, int flags) {
    /* user press left button */
    if (event == CV_EVENT_LBUTTONDOWN && !drag) {
        point = cvPoint(x, y);
        drag = true;
    }

    /* user drag the mouse */
    if (event == CV_EVENT_MOUSEMOVE && drag) {
        img1 = img0.clone();

        rectangle(img1, point, Point(x, y), red, 1, 8, 0);

        imshow(windowName, img1);
    }

    /* user release left button */
    if (event == CV_EVENT_LBUTTONUP && drag) {
        *bb = cvRect(point.x, point.y, x - point.x, y - point.y);
        drag = false;
    }
}
