// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2007
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

///////////////////////////////////////////////////////////////////////////////
//
//   Filename:   set.cc
//
//   Description:
//
//
//   Mod#   Date      Name           Description
//   ----   ----      ----           -----------
//   000    04-15-05  Halley Gotway
//
///////////////////////////////////////////////////////////////////////////////

using namespace std;

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

#include "set.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Code for class FcstObsSet
//
///////////////////////////////////////////////////////////////////////////////

FcstObsSet::FcstObsSet() {
   clear();
}

///////////////////////////////////////////////////////////////////////////////

FcstObsSet::~FcstObsSet() { }

///////////////////////////////////////////////////////////////////////////////

FcstObsSet::FcstObsSet(const FcstObsSet &S) {
   int j;

   clear();

   n_fcst = S.n_fcst;
   n_obs = S.n_obs;

   for(j=0; j<n_fcst; j++) {
      fcst_number[j] = S.fcst_number[j];
   }

   for(j=0; j<n_obs; j++) {
      obs_number[j] = S.obs_number[j];
   }
}

///////////////////////////////////////////////////////////////////////////////

FcstObsSet & FcstObsSet::operator=(const FcstObsSet &S) {
   int j;

   if( this == &S ) return(*this);

   clear();

   n_fcst = S.n_fcst;
   n_obs = S.n_obs;

   for(j=0; j<n_fcst; j++){
      fcst_number[j] = S.fcst_number[j];
   }

   for(j=0; j<n_obs; j++) {
      obs_number[j] = S.obs_number[j];
   }

   return(*this);
}

///////////////////////////////////////////////////////////////////////////////

int FcstObsSet::has_fcst(int k) const {
   int j;

   for(j=0; j<n_fcst; j++) {
      if( fcst_number[j] == k ) return(1);
   }

   return(0);
}

///////////////////////////////////////////////////////////////////////////////

int FcstObsSet::has_obs(int k) const {
   int j;

   for(j=0; j<n_obs; j++) {
      if( obs_number[j] == k ) return(1);
   }

   return(0);
}

///////////////////////////////////////////////////////////////////////////////

void FcstObsSet::add_pair(int fcst, int obs) {

   if( fcst >= 0 )  add_fcst(fcst);
   if( obs  >= 0 )  add_obs(obs);

   return;
}

///////////////////////////////////////////////////////////////////////////////

void FcstObsSet::add_fcst(int k) {

   if( has_fcst(k) ) return;

   if( n_fcst >= max_fcst_numbers ) {
      cerr << "\n\nERROR: FcstObsSet::add_fcst(int) -> "
	   << "too many fcst numbers!\n\n" << flush;

      exit(1);
   }

   fcst_number[n_fcst++] = k;

   return;
}

///////////////////////////////////////////////////////////////////////////////

void FcstObsSet::add_obs(int k) {

   if( has_obs(k) ) return;

   if( n_obs >= max_obs_numbers ) {
      cerr << "\n\nERROR: FcstObsSet::add_obs(int) -> "
	   << "too many obs numbers!\n\n" << flush;

      exit(1);
   }

   obs_number[n_obs++] = k;

   return;
}

///////////////////////////////////////////////////////////////////////////////

void FcstObsSet::clear() {
   int j;

   n_fcst = n_obs = 0;

   for(j=0; j<max_fcst_numbers; j++) {
      fcst_number[j] = 0;
   }

   for(j=0; j<max_obs_numbers; j++) {
      obs_number[j] = 0;
   }

   return;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Code for class FcstObsSet_collection
//
///////////////////////////////////////////////////////////////////////////////

SetCollection::SetCollection() {

   n_sets = 0;
}

///////////////////////////////////////////////////////////////////////////////

SetCollection::~SetCollection() { }

///////////////////////////////////////////////////////////////////////////////

SetCollection::SetCollection(const SetCollection &a) {
   int j;

   clear();

   n_sets = a.n_sets;

   for(j=0; j<n_sets; j++) {
      set[j] = a.set[j];
   }
}

///////////////////////////////////////////////////////////////////////////////

SetCollection & SetCollection::operator=(const SetCollection &a) {
   int j;

   if( this == &a ) return(*this);

   clear();

   n_sets = a.n_sets;

   for(j=0; j<n_sets; j++) {
      set[j] = a.set[j];
   }

   return(*this);
}

///////////////////////////////////////////////////////////////////////////////

void SetCollection::add_pair(int fcst, int obs) {
   int j;

   if( n_sets >= max_fcst_obs_sets ) {
      cerr << "\n\nERROR: SetCollection::add_pair(int, int) -> "
           << "too many sets!\n\n" << flush;

      exit(1);
   }

   set[n_sets].clear();

   set[n_sets].add_pair(fcst, obs);

   n_sets++;

   do {
      j = merge();
   } while( j > 0 );

   return;
}

///////////////////////////////////////////////////////////////////////////////

int SetCollection::merge() {
   int j, k;
   int jm, km;
   int need_merge;

   if( n_sets <= 1 ) return(0);

   need_merge = 0;

   for(j=0; j<(n_sets - 1); j++) {
      for(k=(j + 1); k<n_sets; k++) {

         if( !need_merge && fcst_obs_sets_overlap(set[j], set[k]) ) {
            need_merge = 1;

            jm = j;
            km = k;
         }
      }
   }

   if( need_merge ) {
      merge_two(jm, km);
   }

   return(need_merge);
}

///////////////////////////////////////////////////////////////////////////////

void SetCollection::merge_two(int index1, int index2) {
   int j;
   int imin, imax;
   FcstObsSet a;

   imin = (index1 < index2) ? index1 : index2;
   imax = (index1 > index2) ? index1 : index2;

   a = union_fcst_obs_sets(set[imin], set[imax]);

   for(j=imax; j<(n_sets - 1); j++) {
      set[j] = set[j + 1];
   }

   n_sets--;

   for(j=imin; j<(n_sets - 1); j++) {
      set[j] = set[j + 1];
   }

   n_sets--;

   set[n_sets] = a;

   n_sets++;

   for(j=n_sets; j<max_fcst_obs_sets; j++) {
      set[j].clear();
   }

   return;
}

///////////////////////////////////////////////////////////////////////////////

int SetCollection::fcst_set_number(int fcst_number) const {
   int j;

   for(j=0; j<n_sets; j++) {
      if( set[j].has_fcst(fcst_number) ) return(j);
   }

   return(-1);
}

///////////////////////////////////////////////////////////////////////////////

int SetCollection::obs_set_number(int obs_number) const {
   int j;

   for(j=0; j<n_sets; j++) {
      if( set[j].has_obs(obs_number) ) return(j);
   }

   return(-1);
}

///////////////////////////////////////////////////////////////////////////////

int SetCollection::is_fcst_matched(int fcst_number) const {
   int matched, j;

   matched = 0;

   //
   // Find the set number containing this fcst object
   //
   j = fcst_set_number(fcst_number);

   //
   // Check to see if the set contains obs objects
   //
   if(j != -1) {
      if(set[j].n_obs > 0) matched = 1;
   }

   return(matched);
}

///////////////////////////////////////////////////////////////////////////////

int SetCollection::is_obs_matched(int obs_number) const {
   int matched, j;

   matched = 0;

   //
   // Find the set number containing this obs object
   //
   j = obs_set_number(obs_number);

   //
   // Check to see if the set contains fcst objects
   //
   if(j != -1) {
      if(set[j].n_fcst > 0) matched = 1;
   }

   return(matched);
}

///////////////////////////////////////////////////////////////////////////////
//
// Eliminate any sets with either n_fcst or n_obs = 0
//
///////////////////////////////////////////////////////////////////////////////

void SetCollection::clear_empty_sets() {
   int i, j;
   
   for(i=0; i<n_sets; i++) {
   
      if(set[i].n_fcst == 0 || set[i].n_obs == 0) {
      
         for(j=i; j+1<n_sets; j++) set[j] = set[j+1];
	 
	 n_sets--;
	 i--;
      }
   } // end for i
   
   return;
}

///////////////////////////////////////////////////////////////////////////////

void SetCollection::clear() {
   int j;

   n_sets = 0;

   for(j=0; j<max_fcst_obs_sets; j++) {
      set[j].clear();
   }

   return;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Code for misc functions
//
///////////////////////////////////////////////////////////////////////////////

int fcst_obs_sets_overlap(const FcstObsSet &a, const FcstObsSet &b) {
   int j;

   //
   //  check fcst's
   //
   for(j=0; j<(a.n_fcst); j++) {
      if( b.has_fcst(a.fcst_number[j]) ) return(1);
   }

   //
   //  check obs's
   //
   for(j=0; j<(a.n_obs); j++) {
      if( b.has_obs(a.obs_number[j]) ) return(1);
   }

   //
   //
   //

   return(0);
}

///////////////////////////////////////////////////////////////////////////////

FcstObsSet union_fcst_obs_sets(const FcstObsSet &a, const FcstObsSet &b) {
   int j;
   FcstObsSet c;

   for(j=0; j<(a.n_fcst); j++) {
       c.add_fcst(a.fcst_number[j]);
   }

   for(j=0; j<(b.n_fcst); j++) {
      c.add_fcst(b.fcst_number[j]);
   }

   for(j=0; j<(a.n_obs); j++) {
      c.add_obs(a.obs_number[j]);
   }

   for(j=0; j<(b.n_obs); j++) {
      c.add_obs(b.obs_number[j]);
   }

   return(c);
}

///////////////////////////////////////////////////////////////////////////////

ostream & operator<<(ostream &out, const FcstObsSet &set) {
   int j;

   //
   //  write the fcst's
   //
   out.setf(ios::fixed);

   out << "n_fcst = ";

   out.width(2);  out << (set.n_fcst);

   out << " ... ";

   for(j=0; j<(set.n_fcst); j++) {
      out.width(3);   out << (set.fcst_number[j]) << " ";
   }

   out << "\n";

   //
   //  write the obs's
   //
   out.setf(ios::fixed);

   out << "n_obs = ";

   out.width(2);  out << (set.n_obs);

   out << " ... ";

   for(j=0; j<(set.n_obs); j++) {
      out.width(3);   out << (set.obs_number[j]) << " ";
   }

   out << "\n\n";

   //
   //
   //

   return(out);
}

///////////////////////////////////////////////////////////////////////////////

ostream & operator<<(ostream &out, const SetCollection &c) {
   int j;

   for(j=0; j<(c.n_sets); j++) {
      out << j << "\n";
      out << (c.set[j]);
   }

   return(out);
}

///////////////////////////////////////////////////////////////////////////////
