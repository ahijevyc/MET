// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2007
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*



////////////////////////////////////////////////////////////////////////


#ifndef  __VX_PPM_H__
#define  __VX_PPM_H__


////////////////////////////////////////////////////////////////////////


#include "vx_pxm_base.h"
#include "vx_color.h"


////////////////////////////////////////////////////////////////////////


class Ppm : public PxmBase {

   private:

      void assign(const Ppm &);

      void init_from_scratch();

   public:

      Ppm();
      Ppm(const char *);
      virtual ~Ppm();
      Ppm(const Ppm &);
      Ppm & operator=(const Ppm &);

         //
         //  from base class
         //

      int  read(const char *);

      int write(const char *) const;

      void clear();


      void set_size_rc(int NR, int NC);
      void set_size_xy(int NX, int NY);

      Color getrc(int row, int col) const;
      Color getxy(int   x, int   y) const;

      void putrc(const Color &, int row, int col);
      void putxy(const Color &, int   x, int   y);


      void rotate(int);

      void autocrop();

      void gamma(double);

      void reverse_video();

      void all_black();

      void all_white();

      void dump(ostream &, int depth = 0) const;

         //
         //  not from base class
         //

      void make_gray();

};


////////////////////////////////////////////////////////////////////////


#endif   //  __VX_PPM_H__


////////////////////////////////////////////////////////////////////////


