#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

static long my_asub_routine(aSubRecord *prec) {
    long i, *a;
    double sum=0;
    a = (long *)prec->a;
    for (i=0; i<prec->noa; i++) {
        sum += a[i];
    }
    return 0; /* process output links */
}

epicsRegisterFunction(my_asub_routine);

