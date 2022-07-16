#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <epicsString.h>


#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

static long rscansave(aSubRecord *prec) {

  try {
    // Local time now
    time_t now = time(0);
    tm *t = localtime(&now);
    char ttime[200];
    sprintf(ttime, "%04d-%02d-%02d %02d:%02d:%02d\n",
        t->tm_year+1900,
        t->tm_mon,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
        );


    // A input is filename
    std::string filename(((epicsOldString*)(prec->a))[0], sizeof(epicsOldString));
    if (filename.size() == 0) {
      return 1;
    }
    std::ofstream fo(filename.c_str());

    // B input is data waveform
    long ib = 0;
    double *b = (double*) prec->b;

    // C is R0, D is Rf
    double const R0       = ((double*) prec->c)[0];
    double const Rf       = ((double*) prec->d)[0];
    long   const N        = ((long*) prec->e)[0];
    long   const NExtra   = ((long*) prec->f)[0];
    double const V        = ((double*) prec->g)[0];
    double const X        = ((double*) prec->h)[0];
    double const Xo       = ((double*) prec->i)[0];
    double const Y        = ((double*) prec->j)[0];
    double const Yo       = ((double*) prec->k)[0];
    double const W        = ((double*) prec->l)[0];
    long   const NTurns   = ((long*) prec->m)[0];
    std::string Comments(((epicsOldString*)(prec->u))[0], sizeof(epicsOldString));

    std::cout << "# filename:   " << filename << std::endl;
    std::cout << "# Time:       " << ttime << std::endl;
    std::cout << "# nob:        " << prec->nob << std::endl;
    std::cout << "# RFirst:     " << R0 << std::endl;
    std::cout << "# RLast:      " << Rf << std::endl;
    std::cout << "# NPoints:    " << N << std::endl;
    std::cout << "# NExtra:     " << NExtra << std::endl;
    std::cout << "# Velocity:   " << V << std::endl;
    std::cout << "# X Position: " << X << std::endl;
    std::cout << "# X Yaw:      " << Xo << std::endl;
    std::cout << "# Y Position: " << Y << std::endl;
    std::cout << "# Y Tilt:     " << Yo << std::endl;
    std::cout << "# Coil Width: " << W << std::endl;
    std::cout << "# NTurns:     " << NTurns << std::endl;
    std::cout << "# Comments:   " << Comments << std::endl;

    fo << "# filename:   " << filename << std::endl;
    fo << "# Time:       " << ttime << std::endl;
    fo << "# nob:        " << prec->nob << std::endl;
    fo << "# RFirst:     " << R0 << std::endl;
    fo << "# RLast:      " << Rf << std::endl;
    fo << "# NPoints:    " << N << std::endl;
    fo << "# NExtra:     " << NExtra << std::endl;
    fo << "# Velocity:   " << V << std::endl;
    fo << "# X Position: " << X << std::endl;
    fo << "# X Yaw:      " << Xo << std::endl;
    fo << "# Y Position: " << Y << std::endl;
    fo << "# Y Tilt:     " << Yo << std::endl;
    fo << "# Coil Width: " << W << std::endl;
    fo << "# NTurns:     " << NTurns << std::endl;
    fo << "# Comments:   " << Comments << std::endl;

    double sum = 0;
    double tsum = 0;
    for (long ib = NExtra; ib < prec->nob - NExtra; ++ib) {
      fo << ((double*) prec->b)[ib] << std::endl;
      if (ib < 10) std::cout << ((double*) prec->b)[ib] << std::endl;

      sum += ((double*) prec->b)[ib];
      tsum += (((double*) prec->b)[ib] + ((double*) prec->b)[ib+1]) / 2;
    }

    // Integral = sum (V dt / (2 NTurns width))


    // Close file
    fo.close();

  } catch (...) {
    return 1;
  }
  return 0; /* process output links */
}


static long setup_triggers(aSubRecord *prec) {

  try {
  } catch (...) {
    return 1;
  }

  return 0;
}



epicsRegisterFunction(rscansave);
epicsRegisterFunction(setup_triggers);

