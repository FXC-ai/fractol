#include <stdio.h>
#include <math.h>

int main()
{
    
    double nb_iter = 1;
    double max_iter = 500;
    double result;


    while (nb_iter < max_iter)
    {
        result = 1-(log(nb_iter) / log(max_iter));
        printf("%f : %f\n",nb_iter, ceil(result*255));
        nb_iter++;
    }
    


    return 0;
}
