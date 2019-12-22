#ifndef SORTBYANGLE_H
#define SORTBYANGLE_H
#include "algorithms.h"

class sortByAngle
{
public:

    bool operator()(Angle &t, Angle &t1)
    {
        //Tolerance
        double eps = 10e-12;

        // If difference between two angles is very small, sort according to distance
        if(fabs(t.a-t1.a) <eps)
        {
            if(t.d < t1.d)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        else if(t.a < t1.a)
        {
            return 1;
        }

        else
        {
            return 0;
        }
    }
};

#endif // SORTBYANGLE_H
