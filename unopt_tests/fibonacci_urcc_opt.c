#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
void initialize_array ();
int fib (int var_val);
/* func decls end */

  /* Ast::Scope prog: 3 symbols, 3 children */
  int array[32];
  char str[53] = "The first few digits of the Fibonacci sequence are:\n";
  char str1[4] = "%d\n";

void initialize_array (){
    /* Ast::Block initialize_array body: 11 symbols, 21 children */
    int var_idx;
    int var_bound;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_1;
    int var_cmp;
    int var_2;
    long long var_idxprom;
    int *var_arrayidx;
    int var_3;
    int var_add;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_bound = 32;
    var_idx = 0;
    goto lbl_while_cond;
    lbl_while_cond:;
    var_0 = var_idx;
    var_1 = var_bound;
    var_cmp = (var_0 < var_1);
    if (var_cmp) goto lbl_while_body; else goto lbl_while_end;
    lbl_while_body:;
    var_2 = var_idx;
    var_idxprom = var_2;
    var_arrayidx = (& array[var_idxprom]);
    *var_arrayidx = -1;
    var_3 = var_idx;
    var_add = (var_3 + 1);
    var_idx = var_add;
    goto lbl_while_cond;
    lbl_while_end:;
    return;
}
int fib (int var_val){
    /* Ast::Block fib body: 25 symbols, 41 children */
    int var_retval;
    int var_val_addr;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_1;
    long long var_idxprom;
    int *var_arrayidx;
    int var_2;
    int var_cmp1;
    int var_3;
    int var_sub;
    int var_call;
    int var_4;
    int var_sub3;
    int var_call4;
    int var_add;
    int var_5;
    long long var_idxprom5;
    int *var_arrayidx6;
    int var_6;
    long long var_idxprom8;
    int *var_arrayidx9;
    int var_7;
    int var_8;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_val_addr = var_val;
    var_0 = var_val_addr;
    var_cmp = (var_0 < 2);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_retval = 1;
    goto lbl_return;
    lbl_if_end:;
    var_1 = var_val_addr;
    var_idxprom = var_1;
    var_arrayidx = (& array[var_idxprom]);
    var_2 = *var_arrayidx;
    var_cmp1 = (var_2 == -1);
    if (var_cmp1) goto lbl_if_then2; else goto lbl_if_end_if_end7_crit_edge;
    lbl_if_end_if_end7_crit_edge:;
    goto lbl_if_end7;
    lbl_if_then2:;
    var_3 = var_val_addr;
    var_sub = (var_3 - 1);
    var_call = fib(var_sub);
    var_4 = var_val_addr;
    var_sub3 = (var_4 - 2);
    var_call4 = fib(var_sub3);
    var_add = (var_call + var_call4);
    var_5 = var_val_addr;
    var_idxprom5 = var_5;
    var_arrayidx6 = (& array[var_idxprom5]);
    *var_arrayidx6 = var_add;
    goto lbl_if_end7;
    lbl_if_end7:;
    var_6 = var_val_addr;
    var_idxprom8 = var_6;
    var_arrayidx9 = (& array[var_idxprom8]);
    var_7 = *var_arrayidx9;
    var_retval = var_7;
    goto lbl_return;
    lbl_return:;
    var_8 = var_retval;
    return var_8;
}
int main (){
    /* Ast::Block main body: 14 symbols, 24 children */
    int var_retval;
    int var_idx;
    int var_bound;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_0;
    int var_1;
    int var_cmp;
    int var_2;
    int var_call1;
    int var_call2;
    int var_3;
    int var_add;
    int var_4;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_retval = 0;
    var_bound = 32;
    initialize_array();
    var_idx = 0;
    var_call = printf((& str[0]));
    goto lbl_while_cond;
    lbl_while_cond:;
    var_0 = var_idx;
    var_1 = var_bound;
    var_cmp = (var_0 < var_1);
    if (var_cmp) goto lbl_while_body; else goto lbl_while_end;
    lbl_while_body:;
    var_2 = var_idx;
    var_call1 = fib(var_2);
    var_call2 = printf((& str1[0]), var_call1);
    var_3 = var_idx;
    var_add = (var_3 + 1);
    var_idx = var_add;
    goto lbl_while_cond;
    lbl_while_end:;
    var_4 = var_retval;
    return var_4;
}
