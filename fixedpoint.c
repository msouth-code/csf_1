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

Fixedpoint add_magnitude(Fixedpoint left, Fixedpoint right, Fixedpoint sum) {
	return sum;
}



//me
Fixedpoint fixedpoint_add(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  // check for overflow
  // for overflow of fractional parts, carry/borrow to the whole part
  uint64_t pos_over;
  uint64_t neg_over;

  uint64_t neg;
  uint64_t frac;

  uint64_t sum_whole;
  uint64_t sum_frac;
  if(left.validNeg == 1 && right.validNonneg == 1) {
	  // left neg right pos
	  sum_whole = right.whole - left.whole;
	  neg = 1;
	  if(left.hasFrac || right.hasFrac) {
		  sum_frac = right.frac - left.frac;
		  frac = 1;
		  // check for neg overflow of frac
		  if(sum_frac > right.frac) {
			  sum_whole--;
			  neg_over = 1;
		  }
	  }
	  // check for neg overflow of whole
	  if(sum_whole > right.whole) {
		  neg_over = 1;
	  }
  } else if(right.validNeg == 1 && left.validNonneg == 1) {
	  // right neg left pos
	  sum_whole = left.whole - right.whole;
	  neg = 1;
	  if(left.hasFrac || right.hasFrac) {
		  sum_frac = left.frac - right.frac;
		  frac = 1;
		  // check for neg overflow of frac
		  if(sum_frac > left.frac) {
			  sum_whole--;
			  neg_over = 1;
		  }
	  }
	  // check for neg overflow of whole
	  if(sum_whole > left.whole) {
		  neg_over = 1;
	  }
  } else {
	  sum_whole = left.whole + right.whole;
	  neg = left.validNeg;
	  if(left.hasFrac || right.hasFrac) {
		  sum_frac = left.frac + right.frac;
		  frac = 1;
		  if(sum_frac < left.frac) {
			  sum_whole++;
			  pos_over = 1;
		  }
	  }
	  if(sum_whole < left.whole) {
		  pos_over = 1;
	  }
  }
  Fixedpoint fp = fixedpoint_create2(sum_whole, sum_frac);
  if(neg == 1) { fp.validNeg = 1; }
  else { fp.validNonneg = 1; }
  fp.posoverfl = pos_over;
  fp.negoverfl = neg_over;
  fp.hasFrac = frac;
  return fp;
}

//me
Fixedpoint fixedpoint_sub(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  // for overflow of fractional parts, carry/borrow to the whole part
  uint64_t pos_over;
  uint64_t neg_over;

  uint64_t neg;
  uint64_t frac;

  uint64_t diff_whole;
  uint64_t diff_frac;
  if((left.validNeg == 1 && right.validNonneg == 1) || (right.validNeg == 1 && left.validNonneg == 1)) {
	  // left neg right pos --- -l - r => r + l
	  // right neg left pos --- l - -r => l + r
	  diff_whole = left.whole + right.whole;
	  if(left.hasFrac || right.hasFrac) {
		  diff_frac = left.frac + right.frac;
		  frac = 1;
		  if(diff_frac < left.frac) {
			  diff_whole++;
			  pos_over = 1;
		  }
	  }
	  if(diff_whole < left.whole) {
		  pos_over = 1;
	  }
  } else if (left.validNonneg == 1 && right.validNonneg == 1) { // both positive
	  diff_whole = left.whole - right.whole;
	  if(left.hasFrac || right.hasFrac) {
		  diff_frac = left.frac - right.frac;
		  frac = 1;
		  if(diff_frac > left.frac) {
			  diff_whole--;
			  neg_over = 1;
		  }
	  }
	  if(diff_whole > left.whole) {
		  neg_over = 1;
	  }
  } else { // both negative
	  // - l - - r => -l + r => r - l
	  diff_whole = right.whole - left.whole;
	  if(left.hasFrac || right.hasFrac) {
		  diff_frac = right.frac - left.frac;
		  frac = 1;
		  if(diff_frac > right.frac) {
			  diff_whole --;
			  neg_over = 1;
		  }
	  }
	  if(diff_whole > left.whole) {
		  neg_over = 1;
	  }
  }
  Fixedpoint fp = fixedpoint_create2(diff_whole, diff_frac);
  if(neg == 1) { fp.validNeg = 1; }
  else { fp.validNonneg = 1; }
  fp.posoverfl = pos_over;
  fp.negoverfl = neg_over;
  fp.hasFrac = frac;
  return fp;

}

//me
Fixedpoint fixedpoint_negate(Fixedpoint val) {
  // TODO: implement
  val.validNeg = 1;
  val.validNonneg = 0;
  return val;
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
  return val.error == 1;
}

//me
int fixedpoint_is_neg(Fixedpoint val) {
  // TODO: implement
  return val.validNeg == 1;
}

//me
int fixedpoint_is_overflow_neg(Fixedpoint val) {
  // TODO: implement
  return val.negoverfl;
}

//me
int fixedpoint_is_overflow_pos(Fixedpoint val) {
  // TODO: implement
  return val.posoverfl;
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
