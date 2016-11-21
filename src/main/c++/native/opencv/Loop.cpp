//
// Created by dialight on 06.11.16.
//

#include <opencv/Loop.hpp>
#include <utils/MacroEnumString.hpp>

Loop::Loop(PropertiesClient *propc, Tool *tool) : tool(tool), propc(propc) {

}

#define MethodsMacro(m) \
    m(RAW, "Без оработки") \
    m(LINES, "Lines") \
    m(CONTOURS, "Contours") \
    m(BLUR_TEST, "Тест блюра") \
    m(KENNY_TEST, "Тест метода кенни") \
    m(THRESHOLD_TEST, "тест порогового преобразования") \
    m(ADAPTIVE_THRESHOLD_TEST, "тест адаптивного порогового преобразования")
ENUM_STRING(MethodsMacro, Methods, MethodsVector)

Mat Loop::loop(Mat frame) {
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    switch(propc->getSelect("method", &MethodsVector, Methods::CONTOURS)) {
        case Methods::RAW: break;
        case Methods::LINES:
            tool->gaussianBlur(gray, 7, 1.5);
            tool->canny(gray, 30, 60);
            tool->houghLines(gray, frame);
            return frame;
        case Methods::CONTOURS:
            tool->gaussianBlur(gray, 7, 1.5);
            tool->adaptiveThreshold(gray);
//            tool->canny(gray, 60, 80);
            tool->findContours2(gray, frame);
            return frame;
        case Methods::BLUR_TEST: //тест блюра
            tool->gaussianBlur(gray, 7, 1.5);
            return gray;
        case Methods::KENNY_TEST: //тест метода Кенни на блюре
            tool->gaussianBlur(gray, 7, 1.5);
            tool->canny(gray, 30, 60); //обводит резкие линии(детектор границ Кенни)
            return gray;
        case Methods::THRESHOLD_TEST: //тест порогового преобразования на блюре
            tool->gaussianBlur(gray, 3, 0.0);
            tool->threshold(gray);
            return gray;
        case Methods::ADAPTIVE_THRESHOLD_TEST: //тест адаптивного порогового преобразования на блюре
            tool->gaussianBlur(gray, 3, 0.0);
            tool->adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            return gray;
        default:break;
    }
    return frame;
}
