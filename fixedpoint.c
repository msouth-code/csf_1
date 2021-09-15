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

int is_valid_hex(const char *hex) {
  int dot = 0;
  int	wc = 0;
  int fc = 0;
  for(int i = 0; i < strlen(hex); i++) {
	  if(hex[i] == '.') { dot = 1; }
	  (dot == 1) ? fc++:wc++;
	  // 48 - 57, 65 - 70, 97 - 102
	  if(hex[i] < 48 || (hex[i] > 57 && hex[i] < 65) || (hex[i] > 70 && hex[i] < 97) || hex[i] > 102) {
		  return 0;
	  }  
  }
  if(wc > 16 || fc > 16) {
	  return 0;
  }
  return 1;
}

void cpysubstr(const char *str, char* res, int start, int end) {
	int count = 0;
	for(int i = start; i < end; i++) {
		res[count] = str[i];
	}
}

//me
Fixedpoint fixedpoint_create_from_hex(const char *hex) {
  // TODO: implement
  // can use strtoul and sprintf
  // check for error - invalid hex digits in input (anything not 0-9, a-f, A-F)
  if(is_valid_hex(hex) == 0) {
	  Fixedpoint fp = fixedpoint_create(0);
	  fp.error = 1;
	  return fp;
  }
  int neg;
  int dec;

  char* wholehex;
  char* frachex;

  // x
  // -x
  // x.y
  // -x.y
  char* dot = strchr(hex, '.');
  int dotpos = dot - hex; // location of dot in string
  if(hex[0] == '-') { 
	  neg = 1;
	  cpysubstr(hex, wholehex, 1, dotpos);
  } else { cpysubstr(hex, wholehex, 0, dotpos); }
  if(dot != NULL) { 
	  dec = 1; 
	  cpysubstr(hex, frachex, dotpos, strlen(hex) - 1);
  }

  // hex to bin
  char* ptr;
  Fixedpoint fp;
  uint64_t whole = strtoul(wholehex, &ptr, 2);
  if(dec == 1) { 
	  uint64_t frac = strtoul(frachex, &ptr, 2); 
	  fp = fixedpoint_create2(whole, frac);
	  fp.hasFrac = 1;
  } else { fp = fixedpoint_create(whole); }

  if(neg == 1) {
	  fp.validNeg = 1;
  } else {
	  fp.validNonneg = 1;
  }

  // should only return valid nonneg, valid neg, or error
  return fp;
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
  int pos_over;
  int neg_over;

  int neg;
  int frac;

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
  int pos_over;
  int neg_over;

  int neg;
  int frac;

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
  Fixedpoint half;
  int underflow;

  uint64_t whole = val.whole >> 1;
  //check for underflow
  uint64_t wmsk = (1 << 2) - 1;
  uint64_t lsbs = val.whole & wmsk;
  if(lsbs == 01) {
	  underflow = 1;
  } 
  uint64_t frac;
  if(val.hasFrac == 1) {
	  frac = val.frac >> 1;
	  //check for underflow
	  uint64_t fmsk = (1 << 2) - 1;
	  uint64_t flsbs = val.frac & fmsk;
	  if(flsbs == 01) {
		  underflow = 1;
	  }
	  half.frac = frac;
  }
  half.whole = whole;
  if(val.validNeg == 1) {
	  half.validNeg = 1;
	  if(underflow == 1) {
		  half.negunderfl = 1;
	  }
  } else {
	  half.validNonneg = 1;
	  if(underflow == 1) {
		  half.posunderfl = 1;
	  }
  }
  return half;
}

Fixedpoint fixedpoint_double(Fixedpoint val) {
  // TODO: implement
  Fixedpoint doubled;

  doubled.whole = val.whole<<1;
  if(val.hasFrac) {
	  doubled.frac = val.frac << 1;
  }
  return doubled;
}

int fixedpoint_compare(Fixedpoint left, Fixedpoint right) {
  // TODO: implement
  if(left.whole == right.whole) {
    if(left.frac == right.frac) {
      return 0;
    } else if(left.frac < right.frac) { // left is less
      return -1;
    } else {
    return 1;
    }
  }

  if(left.whole < right.whole) { //left is less
    return -1;
  } else {
    return 1;
  }
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
  return val.negunderfl;
}

int fixedpoint_is_underflow_pos(Fixedpoint val) {
  // TODO: implement
  return val.posunderfl;
}

int fixedpoint_is_valid(Fixedpoint val) {
  // TODO: implement
  if(val.error == 1 || val.posoverfl == 1 ||
  val.negoverfl == 1 || val.posunderfl == 1 ||
  val.negunderfl == 1) {
    return 0;
  }
  return 1;
}


char *fixedpoint_format_as_hex(Fixedpoint val) {
  // TODO: implement
  // translate fraction directly but must drop trailing zeros when converting to hex
  char *s = malloc(40);
  if(val.validNeg == 1) {
	  s[0] = '-';
  }

  int wholehex = 0;
  int rem;
  int i = 1;
  int binwhole = val.whole;
  while(binwhole != 0) {
	  rem = binwhole % 10;
	  wholehex = wholehex + rem * i;
	  i *= 2;
	  binwhole /= 10;
  }

  char *w = malloc(20);
  sprintf(w, "%i", wholehex);
  strcat(s, w);
  free(w);

  if(val.hasFrac) {
	  int frachex = 0;
	  int remf;
	  int f = 1;
	  int binfrac = val.frac;
	  while(binfrac != 0) {
		  remf = binfrac % 10;
		  frachex = frachex + remf * f;
		  f *= 2;
		  binfrac /= 10;
	  }
	  char dot[1] = ".";
	  strcat(s, dot);
	  char *ef = malloc(20);
	  sprintf(ef, "%i", frachex);
	  strcat(s, ef);
	  free(ef);
  }

  return s;
}
