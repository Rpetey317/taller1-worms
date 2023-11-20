#ifndef __POINT_H__
#define __POINT_H__

/*
 * Simple wrapper class for a 2d integer point
 */
class Point {
public:
    int x;
    int y;

    /*
     *Create a point with given coords
     */
    Point(int x, int y);

    /*
     *Create a point with <0, 0> as coords
     */
    Point();

    /*
     * Copy constructor
     */
    Point(Point const& other);

    /*
     * Return point above (-1 in y coord)
     */
    Point above();

    /*
     * Return point below (+1 in y coord)
     */
    Point below();

    /*
     * Return point to the right (+1 in x coord)
     */
    Point right();

    /*
     * Return point to the left (-1 in x coord)
     */
    Point left();

    /*
     * Addition operator (coord by coord)
     */
    Point operator+(Point const& other);

    /*
     * Substraction operator (coord by coord)
     */
    Point operator-(Point const& other);

    /*
     * Copy assigner
     */
    Point& operator=(const Point& other);

    /*
     * Print to std::cout as "x y\n"
     */
    void print();
};

#endif  // !__POINT_H__
