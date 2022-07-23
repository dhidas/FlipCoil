#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <epicsString.h>


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
    for (long ib = NExtra; ib < N + NExtra; ++ib) {
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




static long tscansave(aSubRecord *prec) {

  std::cout << "hello dhidas" << std::endl;
  std::string fff(((epicsOldString*)(prec->a))[0], sizeof(epicsOldString));
  std::cout << "fff " << fff << std::endl;
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


    // B input is data waveform
    long ib = 0;
    double *b = (double*) prec->b;

    // C is counter, D is Rf
    double const Counter  = ((double*) prec->c)[0];
    double const Aper     = ((double*) prec->d)[0];
    long   const N        = ((long*) prec->e)[0];
    double const TrigTime = ((double*) prec->f)[0];
    //double const V        = ((double*) prec->g)[0];
    std::string Range(((epicsOldString*)(prec->g))[0], sizeof(epicsOldString));
    double const X        = ((double*) prec->h)[0];
    double const Xo       = ((double*) prec->i)[0];
    double const Y        = ((double*) prec->j)[0];
    double const Yo       = ((double*) prec->k)[0];
    double const R        = ((double*) prec->l)[0];
    double const Ro       = ((double*) prec->m)[0];
    double const W        = ((double*) prec->n)[0];
    long   const NTurns   = ((long*) prec->o)[0];
    std::string Comments(((epicsOldString*)(prec->u))[0], sizeof(epicsOldString));


    // A input is filename
    std::string filename(((epicsOldString*)(prec->a))[0], sizeof(epicsOldString));
    if (filename.size() == 0) {
      return 1;
    }
    char filename2[500];
    if (Counter >= 0) {
      sprintf(filename2, "%s_%04d.txt", ((epicsOldString*)(prec->a))[0], (int) Counter);
    } else {
      sprintf(filename2, "%s.txt", ((epicsOldString*)(prec->a))[0]);
    }
    std::ofstream fo(filename2);


    std::cout << "# filename:   " << filename2 << std::endl;
    std::cout << "# Time:       " << ttime << std::endl;
    std::cout << "# nob:        " << prec->nob << std::endl;
    std::cout << "# Counter:    " << Counter << std::endl;
    std::cout << "# Aperture:   " << Aper << std::endl;
    std::cout << "# NPoints:    " << N << std::endl;
    std::cout << "# TrigTime:   " << TrigTime << std::endl;
    std::cout << "# Range:      " << Range << std::endl;
    std::cout << "# X Position: " << X << std::endl;
    std::cout << "# X Yaw:      " << Xo << std::endl;
    std::cout << "# Y Position: " << Y << std::endl;
    std::cout << "# Y Tilt:     " << Yo << std::endl;
    std::cout << "# R Position: " << R << std::endl;
    std::cout << "# R Offset:   " << Ro << std::endl;
    std::cout << "# Coil Width: " << W << std::endl;
    std::cout << "# NTurns:     " << NTurns << std::endl;
    std::cout << "# Comments:   " << Comments << std::endl;

    fo << "# filename:   " << filename2 << std::endl;
    fo << "# Time:       " << ttime << std::endl;
    fo << "# nob:        " << prec->nob << std::endl;
    fo << "# Counter:    " << Counter << std::endl;
    fo << "# Aperture:   " << Aper << std::endl;
    fo << "# NPoints:    " << N << std::endl;
    fo << "# TrigTime:   " << TrigTime << std::endl;
    fo << "# Range:      " << Range << std::endl;
    fo << "# X Position: " << X << std::endl;
    fo << "# X Yaw:      " << Xo << std::endl;
    fo << "# Y Position: " << Y << std::endl;
    fo << "# Y Tilt:     " << Yo << std::endl;
    fo << "# R Position: " << R << std::endl;
    fo << "# R Offset:   " << Ro << std::endl;
    fo << "# Coil Width: " << W << std::endl;
    fo << "# NTurns:     " << NTurns << std::endl;
    fo << "# Comments:   " << Comments << std::endl;

    for (long ib = 0; ib < N; ++ib) {
      fo << b[ib] << std::endl;
      if (ib < 10) std::cout << (double) b[ib] << std::endl;
    }

    if (Counter >= 0) {
      ((double*) prec->vala)[0] = Counter + 1;
    } else {
      ((double*) prec->vala)[0] = Counter;
    }

    // Close file
    fo.close();

  } catch (...) {
    return 1;
  }

  return 0; /* process output links */
}










epicsRegisterFunction(rscansave);
epicsRegisterFunction(tscansave);

