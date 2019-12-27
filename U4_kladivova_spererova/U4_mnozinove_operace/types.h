#ifndef TYPES_H
#define TYPES_H

//Position of point and line
typedef enum {

    LeftHp = 0,
    RightHp = 1,
    Colinear = 2

} TPointLinePosition;

//Position of point and polygon
typedef enum {

    Inner,
    Outer,
    On

} TPointPolygonPosition;

//Boolean operations
typedef enum {

    Union,
    Intersect,
    DifferenceAB,
    DifferenceBA

} TBooleanOperation;

//Position of point and line
typedef enum {

    Parallel,
    Identical,
    NonIntersected,
    Intersected

} T2LinePosition;
#endif // TYPES_H
