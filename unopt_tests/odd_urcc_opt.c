#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
/* func decls end */

  /* Ast::Scope prog: 5 symbols, 1 children */
  char str[26] = "input a number, e.g. 255\n";
  char str1[3] = "%d";
  char str2[4] = "odd";
  char str3[5] = "even";
  char str4[10] = "%d is %s\n";

int main (int var_argc, char **var_argv){
    /* Ast::Block main body: 16 symbols, 26 children */
    int var_retval;
    int var_argc_addr;
    char **var_argv_addr;
    int var_i;
    int var_parity;
    char *var_answer;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_call1;
    int var_0;
    int var_rem;
    int var_1;
    int var_cmp;
    int var_2;
    char *var_3;
    int var_call2;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_retval = 0;
    var_argc_addr = var_argc;
    var_argv_addr = var_argv;
    var_call = printf((& str[0]));
    var_call1 = __isoc99_scanf((& str1[0]), (& var_i));
    var_0 = var_i;
    var_rem = (var_0 % 2);
    var_parity = var_rem;
    var_1 = var_parity;
    var_cmp = (var_1 == 0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    goto lbl_L1;
    lbl_if_end:;
    var_answer = (& str2[0]);
    goto lbl_L2;
    lbl_L1:;
    var_answer = (& str3[0]);
    goto lbl_L2;
    lbl_L2:;
    var_2 = var_i;
    var_3 = var_answer;
    var_call2 = printf((& str4[0]), var_2, var_3);
    return 0;
}
