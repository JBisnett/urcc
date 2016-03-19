#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
/* func decls end */

  /* Ast::Scope prog: 1 symbols, 1 children */
  char str[7] = "hello\n";

int main (){
    /* Ast::Block main body: 8 symbols, 19 children */
    int var_retval;
    int var_i;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_call;
    int var_1;
    int var_inc;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_retval = 0;
    var_i = 0;
    goto lbl_for_cond;
    lbl_for_cond:;
    var_0 = var_i;
    var_cmp = (var_0 < 10);
    if (var_cmp) goto lbl_for_body; else goto lbl_for_end;
    lbl_for_body:;
    var_call = printf((& str[0]));
    goto lbl_for_inc;
    lbl_for_inc:;
    var_1 = var_i;
    var_inc = (var_1 + 1);
    var_i = var_inc;
    goto lbl_for_cond;
    lbl_for_end:;
    return 0;
}
