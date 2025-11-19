#ifndef PFE_STRUCTS
#include <MPU6500_WE.h>
// Struct for combining accepted flex ranges for each letter
struct LetterFlexRange{
  int flexMin1;
  int flexMax1;

  int flexMin2;
  int flexMax2;

  int flexMin3;
  int flexMax3;

  int flexMin4;
  int flexMax4;

  int flexMin5;
  int flexMax5;
};

// Struct for combining accepted flex ranges for each letter
struct LetterXYZRange{
  xyzFloat minimumRange;
  xyzFloat maximumRange;
};

#define PFE_STRUCTS

#endif