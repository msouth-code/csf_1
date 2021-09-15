Lauren Diaz & Miayunique South

Contributions:
For MS1, we contributed equally by pair programming over zoom

For MS2, we split up the functions as follows:
  Lauren: 
    fixedpoint_create_from_hex
    fixedpoint_negate
    fixedpoint_add
    fixedpoint_sub 
    fixedpoint_is_err
    fixedpoint_is_neg
    fixedpoint_is_overflow_neg
    fixedpoint_is_overflow_pos
   Miayunique:
    fixedpoint_halve
    fixedpoint_double
    fixedpoint_compare
    fixedpoint_is_underflow_neg
    fixedpoint_is_underflow_pos
    fixedpoint_is_valid
    fixedpoint_format_as_hex
   We then worked together to come up with the test cases and debug the program.
   
   
  When debugging, our main complications came from our implementation of fixedpoint_create_from_hex. We spent quite some time debugging since our whole, frac, wholehex, and frachex variables weren't copying properly. We spent some time cleaning up our strtoul and strcpy usages and were able to solve them. Our other issues came from the following functions: format_as_hex, negate, add, sub, overflow_pos, and err. 
