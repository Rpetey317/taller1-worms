#ifndef __Vect2D_H__
#define __Vect2D_H__

/*
 * Simple wrapper class for a 2d integer Vect2D
 */
class Vect2D {
public:
    int x;
    int y;

    /*
     *Create a Vect2D with given coords
     */
    Vect2D(int x, int y);

    /*
     *Create a Vect2D with <0, 0> as coords
     */
    Vect2D();

    /*
     * Copy constructor
     */
    Vect2D(Vect2D const& other);

    /*
     * Return Vect2D above (-1 in y coord)
     */
    Vect2D above();

    /*
     * Return Vect2D below (+1 in y coord)
     */
    Vect2D below();

    /*
     * Return Vect2D to the right (+1 in x coord)
     */
    Vect2D right();

    /*
     * Return Vect2D to the left (-1 in x coord)
     */
    Vect2D left();

    /*
     * Addition operator (coord by coord)
     */
    Vect2D operator+(Vect2D const& other);

    /*
     * Substraction operator (coord by coord)
     */
    Vect2D operator-(Vect2D const& other);

    /*
     * Copy assigner
     */
    Vect2D& operator=(const Vect2D& other);

    /*
     * Print to std::cout as "x y\n"
     */
    void print();
};

#endif  // !__Vect2D_H__
