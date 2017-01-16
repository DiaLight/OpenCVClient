//
// Created by dialight on 17.12.16.
//

#ifndef OPENCVCLIENT_CVUTILS_HPP
#define OPENCVCLIENT_CVUTILS_HPP

#include <Properties.hpp>
#include "opencv/Types.hpp"
#include <limits>

#define DEFAULT_THRESHOlD 16

namespace CvUtils {

    bool pointsCompare(Point2i const& p1, Point2i const& p2, int threshold = DEFAULT_THRESHOlD);
    bool linesCompare(Line4i const& l1, Line4i const& l2, int threshold = DEFAULT_THRESHOlD);

    void filterPoints(const vector<Point2i> &src, vector<Point2i> &dst, int threshold = DEFAULT_THRESHOlD);
    void filterLines(const vector<Line4i> &src, vector<Line4i> &dst, int threshold = DEFAULT_THRESHOlD);

    /**
     * Метод для определения смежности 2-х линий. Используется для нахождения треугольников.
     * @param l1 первая сторона потенциального треугольника
     * @param l2 вторая сторона потенциального тругольника
     * @param threshold погрешность в сравнении точек
     * @return Если првые 2 стороны смежны, то 3-ю недостающую сторону треугольника. Иначе, пустую линию.
     */
    Line4i testTriangle(const Line4i &l1, const Line4i &l2, int threshold = DEFAULT_THRESHOlD);

    void filterContoursBySize(vector<vector<Point>> const &in, vector<vector<Point>> &out, int def_min_size = 20, int def_max_size = 200);

    void contoursToLines(vector<vector<Point>> const &in, vector<vector<Line4i>> &out);

}


#endif //OPENCVCLIENT_CVUTILS_HPP
