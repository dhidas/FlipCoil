#include <stdlib.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <epicsString.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>


std::string get_s_from_wf (unsigned int n, epicsOldString* wf) {
  std::ostringstream dnamess;
  for (unsigned int i = 0; i < n; ++i) {
    std::string s(wf[i], sizeof(epicsOldString));
    int num;
    try {
      num = stoi(s);
      dnamess << char(num);
    } catch (...) {
      break;
    }
  }
  std::string dname = dnamess.str();

  return dname;
}

static long rscansave(aSubRecord *prec) {

  try {
    // Local time now
    time_t now = time(0);
    tm *t = localtime(&now);
    char ttime[200];
    sprintf(ttime, "%04d-%02d-%02d %02d:%02d:%02d",
        t->tm_year+1900,
        t->tm_mon,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
        );


    // A input is filename
    std::string dname = get_s_from_wf(prec->noa, (epicsOldString*) prec->a);
    std::string fname = get_s_from_wf(prec->nob, (epicsOldString*) prec->b);

    // B input is data waveform
    double *c = (double*) prec->c;

    // Inputs
    double const Counter  = ((double*) prec->d)[0];
    double const Aper     = ((double*) prec->e)[0];
    double const R0       = ((double*) prec->f)[0];
    double const Rf       = ((double*) prec->g)[0];
    double const Ro       = ((double*) prec->h)[0];
    long   const N        = ((long*) prec->i)[0];
    long   const NExtra   = ((long*) prec->j)[0];
    double const V        = ((double*) prec->k)[0];
    double const X        = ((double*) prec->l)[0];
    double const Xo       = ((double*) prec->m)[0];
    double const Y        = ((double*) prec->n)[0];
    double const Yo       = ((double*) prec->o)[0];
    double const W        = ((double*) prec->p)[0];
    long   const NTurns   = ((long*) prec->q)[0];
    std::string Comments = get_s_from_wf(prec->nou, (epicsOldString*) prec->u);
    std::replace(Comments.begin(), Comments.end(), '\n', ' ');
    std::replace(Comments.begin(), Comments.end(), '\r', ' ');

    char filename2[8000];
    if (Counter >= 0) {
      sprintf(filename2, "%s/%s_x%+06.3f_y%+06.3f_%04d.txt", dname.c_str(), fname.c_str(), X, Y, (int) Counter);
    } else {
      sprintf(filename2, "%s/%s_x%+06.3f_y%+06.3f.txt", dname.c_str(), fname.c_str(), X, Y);
    }
    std::ofstream fo(filename2);

    std::cout << "# filename:   " << filename2 << std::endl;
    std::cout << "# Time:       " << ttime << std::endl;
    std::cout << "# noc:        " << prec->noc << std::endl;
    std::cout << "# Counter:    " << Counter << std::endl;
    std::cout << "# Aper:       " << Aper << std::endl;
    std::cout << "# RFirst:     " << R0 << std::endl;
    std::cout << "# RLast:      " << Rf << std::endl;
    std::cout << "# ROffset:    " << Ro << std::endl;
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

    fo << "# filename:   " << filename2 << std::endl;
    fo << "# Time:       " << ttime << std::endl;
    fo << "# noc:        " << prec->noc << std::endl;
    fo << "# Counter:    " << Counter << std::endl;
    fo << "# Aper:       " << Aper << std::endl;
    fo << "# RFirst:     " << R0 << std::endl;
    fo << "# RLast:      " << Rf << std::endl;
    fo << "# ROffset:    " << Ro << std::endl;
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

    fo << std::scientific << std::setw(9) << std::showpos;
    for (long ic = NExtra; ic < N + NExtra; ++ic) {
      double const R = (Rf - R0) / (N - 1) * (ic - NExtra) + R0;
      fo << std::setw(6) << R << " " << std::setw(9) << ((double*) prec->c)[ic] << std::endl;
      if (ic < 10) std::cout << ((double*) prec->c)[ic] << std::endl;

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


static long xscansave(aSubRecord *prec) {

  try {
    // Local time now
    time_t now = time(0);
    tm *t = localtime(&now);
    char ttime[200];
    sprintf(ttime, "%04d-%02d-%02d %02d:%02d:%02d",
        t->tm_year+1900,
        t->tm_mon,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
        );


    // A input is filename
    std::string dname = get_s_from_wf(prec->noa, (epicsOldString*) prec->a);
    std::string fname = get_s_from_wf(prec->nob, (epicsOldString*) prec->b);

    // B input is data waveform
    double *c = (double*) prec->c;

    // Inputs
    double const Counter  = ((double*) prec->d)[0];
    double const Aper     = ((double*) prec->e)[0];
    double const X0       = ((double*) prec->f)[0];
    double const Xf       = ((double*) prec->g)[0];
    double const Xo       = ((double*) prec->h)[0];
    long   const N        = ((long*) prec->i)[0];
    long   const NExtra   = ((long*) prec->j)[0];
    double const V        = ((double*) prec->k)[0];
    double const R        = ((double*) prec->l)[0];
    double const Ro       = ((double*) prec->m)[0];
    double const Y        = ((double*) prec->n)[0];
    double const Yo       = ((double*) prec->o)[0];
    double const W        = ((double*) prec->p)[0];
    long   const NTurns   = ((long*) prec->q)[0];
    std::string Comments = get_s_from_wf(prec->nou, (epicsOldString*) prec->u);
    std::replace(Comments.begin(), Comments.end(), '\n', ' ');
    std::replace(Comments.begin(), Comments.end(), '\r', ' ');

    char filename2[8000];
    if (Counter >= 0) {
      sprintf(filename2, "%s/%s_r%+07.3f_y%+06.3f_%04d.txt", dname.c_str(), fname.c_str(), R, Y, (int) Counter);
    } else {
      sprintf(filename2, "%s/%s_r%+07.3f_y%+06.3f.txt", dname.c_str(), fname.c_str(), R, Y);
    }
    std::ofstream fo(filename2);

    std::cout << "# filename:   " << filename2 << std::endl;
    std::cout << "# Time:       " << ttime << std::endl;
    std::cout << "# noc:        " << prec->noc << std::endl;
    std::cout << "# Counter:    " << Counter << std::endl;
    std::cout << "# Aper:       " << Aper << std::endl;
    std::cout << "# XFirst:     " << X0 << std::endl;
    std::cout << "# XLast:      " << Xf << std::endl;
    std::cout << "# XOffset:    " << Xo << std::endl;
    std::cout << "# NPoints:    " << N << std::endl;
    std::cout << "# NExtra:     " << NExtra << std::endl;
    std::cout << "# Velocity:   " << V << std::endl;
    std::cout << "# R Position: " << R << std::endl;
    std::cout << "# R Offser:   " << Ro << std::endl;
    std::cout << "# Y Position: " << Y << std::endl;
    std::cout << "# Y Tilt:     " << Yo << std::endl;
    std::cout << "# Coil Width: " << W << std::endl;
    std::cout << "# NTurns:     " << NTurns << std::endl;
    std::cout << "# Comments:   " << Comments << std::endl;

    fo << "# filename:   " << filename2 << std::endl;
    fo << "# Time:       " << ttime << std::endl;
    fo << "# noc:        " << prec->noc << std::endl;
    fo << "# Counter:    " << Counter << std::endl;
    fo << "# Aper:       " << Aper << std::endl;
    fo << "# XFirst:     " << X0 << std::endl;
    fo << "# XLast:      " << Xf << std::endl;
    fo << "# XOffset:    " << Xo << std::endl;
    fo << "# NPoints:    " << N << std::endl;
    fo << "# NExtra:     " << NExtra << std::endl;
    fo << "# Velocity:   " << V << std::endl;
    fo << "# R Position: " << R << std::endl;
    fo << "# R Offset:   " << Ro << std::endl;
    fo << "# Y Position: " << Y << std::endl;
    fo << "# Y Tilt:     " << Yo << std::endl;
    fo << "# Coil Width: " << W << std::endl;
    fo << "# NTurns:     " << NTurns << std::endl;
    fo << "# Comments:   " << Comments << std::endl;

    fo << std::scientific << std::showpos;
    for (long ic = NExtra; ic < N + NExtra; ++ic) {
      double const X = (Xf - X0) / (N - 1) * (ic - NExtra) + X0;
      fo << std::setw(6) << X << " " << std::setw(9) << ((double*) prec->c)[ic] << std::endl;
      if (ic < 10) std::cout << ((double*) prec->c)[ic] << std::endl;

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




static long tscansave(aSubRecord *prec) {

    std::cout << "a" << std::endl;

  try {
    // Local time now
    time_t now = time(0);
    tm *t = localtime(&now);
    char ttime[200];
    sprintf(ttime, "%04d-%02d-%02d %02d:%02d:%02d",
        t->tm_year+1900,
        t->tm_mon,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
        );

    std::string dname = get_s_from_wf(prec->noa, (epicsOldString*) prec->a);
    std::string fname = get_s_from_wf(prec->nob, (epicsOldString*) prec->b);
    std::string range = get_s_from_wf(prec->noh, (epicsOldString*) prec->h);

    // B input is data waveform
    long ic = 0;
    double *c = (double*) prec->c;

    // Inputs
    double const Counter  = ((double*) prec->d)[0];
    double const Aper     = ((double*) prec->e)[0];
    long   const N        = ((long*) prec->f)[0];
    double const TrigTime = ((double*) prec->g)[0];
    std::string Range(((epicsOldString*)(prec->h))[0], sizeof(epicsOldString));
    double const X        = ((double*) prec->i)[0];
    double const Xo       = ((double*) prec->j)[0];
    double const Y        = ((double*) prec->k)[0];
    double const Yo       = ((double*) prec->l)[0];
    double const R        = ((double*) prec->m)[0];
    double const Ro       = ((double*) prec->n)[0];
    double const W        = ((double*) prec->o)[0];
    long   const NTurns   = ((long*) prec->p)[0];
    std::string Comments = get_s_from_wf(prec->nou, (epicsOldString*) prec->u);
    std::replace(Comments.begin(), Comments.end(), '\n', ' ');
    std::replace(Comments.begin(), Comments.end(), '\r', ' ');


    char filename2[8000];
    if (Counter >= 0) {
      sprintf(filename2, "%s/%s_%04d.txt", dname.c_str(), fname.c_str(), (int) Counter);
    } else {
      sprintf(filename2, "%s/%s.txt", dname.c_str(), fname.c_str());
    }
    std::ofstream fo(filename2);

    std::cout << "# filename:   " << filename2 << std::endl;
    std::cout << "# Time:       " << ttime << std::endl;
    std::cout << "# noc:        " << prec->noc << std::endl;
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
    fo << "# noc:        " << prec->noc << std::endl;
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

    for (long ic = 0; ic < N; ++ic) {
      fo << c[ic] << std::endl;
      if (ic < 10) std::cout << (double) c[ic] << std::endl;
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
epicsRegisterFunction(xscansave);
epicsRegisterFunction(tscansave);

