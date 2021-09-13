#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "fixedpoint.h"

// You can remove this once all of the functions are fully implemented
static Fixedpoint DUMMY;

// MS 1
Fixedpoint fixedpoint_create(uint64_t whole) {
  // TODO: implement - done
  
  // make fixedpoint struct and store
  Fixedpoint fp;

  fp.whole = whole;

  // check for tags
  ((whole << 8) == 1) ? (fp.validNeg=1) : (fp.validNonneg=1);
  fp.hasFrac = 0;
  
  return fp;
}

// MS 1
Fixedpoint fixedpoint_create2(uint64_t whole, uint64_t frac) {
  // TODO: implement - done
  
  Fixedpoint fp;

  fp.whole = whole;

  fp.frac = frac;
  fp.hasFrac = 1;

  ((whole << 8) == 1) ? (fp.validNeg=1) : (fp.validNonneg=1);

  return fp;
}

//me
Fixedpoint fixedpoint_create_from_hex(const char *hex) {
  // TODO: implement
  // can use strtoul and sprintf
  // check for error - invalid hex digits in input (anything not 0-9, a-f, A-F)
  // should only return valid nonneg, valid neg, or error
  assert(0);
  return DUMMY;
}

// MS 1
uint64_t fixedpoint_whole_part(Fixedpoint val) {
  // TODO: implement - done
  return val.whole;
}

// MS 1
uint64_t fixedpoint_frac_part(Fixedpoint val) {
  // TODO: implement
  if (val.hasFrac == 1) {
    return val.frac;
  } else {
    return 0;
  }
}

//me
Fixedpoint fixedpoint_add(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  // check for overflow
  // for overflow of fractional parts, carry/borrow to the whole part

  if(left.hasFrac || right.hasFrac) {
    uint64_t wholeSum;
    uint64_t fracSum;
    Fixedpoint fp = fixedpoint_create2(wholeSum, fracSum);
    return fp;
  } else {
    uint64_t wholeSum;
    Fixedpoint fp = fixedpoint_create(wholeSum);
    return fp;
  }
}

//me
Fixedpoint fixedpoint_sub(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  // for overflow of fractional parts, carry/borrow to the whole part
  assert(0);
  return DUMMY;
}

//me
Fixedpoint fixedpoint_negate(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_halve(Fixedpoint val) {
  // TODO: implement
  // check for underflow - least significant bit of orig value lost
  assert(0);
  return DUMMY;
}

Fixedpoint fixedpoint_double(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return DUMMY;
}

int fixedpoint_compare(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  assert(0);
  return 0;
}

// MS 1
int fixedpoint_is_zero(Fixedpoint val) {
  // TODO: implement - done
  if(val.hasFrac == 0) {
    return val.whole == 0;
  } else {
    return val.whole == 0 && val.frac == 0;
  }
}

//me
int fixedpoint_is_err(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

//me
int fixedpoint_is_neg(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

//me
int fixedpoint_is_overflow_neg(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

//me
int fixedpoint_is_overflow_pos(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_underflow_neg(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_underflow_pos(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

int fixedpoint_is_valid(Fixedpoint val) {
  // TODO: implement
  assert(0);
  return 0;
}

char *fixedpoint_format_as_hex(Fixedpoint val) {
  // TODO: implement
  // translate fraction directly but must drop trailing zeros when converting to hex
  assert(0);
  char *s = malloc(20);
  strcpy(s, "<invalid>");
  return s;
}
