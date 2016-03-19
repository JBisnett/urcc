#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
void recursedigit (int var_n);
/* func decls end */

  /* Ast::Scope prog: 9 symbols, 2 children */
  char str[2] = "0";
  char str1[2] = "1";
  char str2[19] = "Give me a number: ";
  char str3[3] = "%d";
  char str4[28] = "I need a positive integer.\n";
  char str5[31] = "The binary representation of: ";
  char str6[4] = "%d\n";
  char str7[5] = "is: ";
  char str8[3] = "\n\n";

void recursedigit (int var_n){
    /* Ast::Block recursedigit body: 19 symbols, 45 children */
    int var_n_addr;
    int var_on;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_1;
    int var_2;
    int var_div;
    int var_mul;
    int var_sub;
    int var_cmp1;
    int var_3;
    int var_div4;
    int var_4;
    int var_cmp5;
    int var_call;
    int var_5;
    int var_cmp8;
    int var_call10;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_n_addr = var_n;
    var_0 = var_n_addr;
    var_cmp = (0 == var_0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    goto lbl_if_end11;
    lbl_if_end:;
    var_on = 0;
    var_1 = var_n_addr;
    var_2 = var_n_addr;
    var_div = (var_2 / 2);
    var_mul = (var_div * 2);
    var_sub = (var_1 - var_mul);
    var_cmp1 = (0 != var_sub);
    if (var_cmp1) goto lbl_if_then2; else goto lbl_if_end_if_end3_crit_edge;
    lbl_if_end_if_end3_crit_edge:;
    goto lbl_if_end3;
    lbl_if_then2:;
    var_on = 1;
    goto lbl_if_end3;
    lbl_if_end3:;
    var_3 = var_n_addr;
    var_div4 = (var_3 / 2);
    recursedigit(var_div4);
    var_4 = var_on;
    var_cmp5 = (0 == var_4);
    if (var_cmp5) goto lbl_if_then6; else goto lbl_if_end3_if_end7_crit_edge;
    lbl_if_end3_if_end7_crit_edge:;
    goto lbl_if_end7;
    lbl_if_then6:;
    var_call = printf((& str[0]));
    goto lbl_if_end7;
    lbl_if_end7:;
    var_5 = var_on;
    var_cmp8 = (1 == var_5);
    if (var_cmp8) goto lbl_if_then9; else goto lbl_if_end7_if_end11_crit_edge;
    lbl_if_end7_if_end11_crit_edge:;
    goto lbl_if_end11;
    lbl_if_then9:;
    var_call10 = printf((& str1[0]));
    goto lbl_if_end11;
    lbl_if_end11:;
    return;
}
int main (){
    /* Ast::Block main body: 17 symbols, 32 children */
    int var_retval;
    int var_a;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_call;
    int var_call1;
    int var_1;
    int var_cmp2;
    int var_call3;
    int var_call4;
    int var_2;
    int var_call5;
    int var_call6;
    int var_3;
    int var_call7;
    int var_4;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_retval = 0;
    var_a = 0;
    goto lbl_while_cond;
    lbl_while_cond:;
    var_0 = var_a;
    var_cmp = (0 >= var_0);
    if (var_cmp) goto lbl_while_body; else goto lbl_while_end;
    lbl_while_body:;
    var_call = printf((& str2[0]));
    var_call1 = __isoc99_scanf((& str3[0]), (& var_a));
    var_1 = var_a;
    var_cmp2 = (0 >= var_1);
    if (var_cmp2) goto lbl_if_then; else goto lbl_while_body_if_end_crit_edge;
    lbl_while_body_if_end_crit_edge:;
    goto lbl_if_end;
    lbl_if_then:;
    var_call3 = printf((& str4[0]));
    goto lbl_if_end;
    lbl_if_end:;
    goto lbl_while_cond;
    lbl_while_end:;
    var_call4 = printf((& str5[0]));
    var_2 = var_a;
    var_call5 = printf((& str6[0]), var_2);
    var_call6 = printf((& str7[0]));
    var_3 = var_a;
    recursedigit(var_3);
    var_call7 = printf((& str8[0]));
    var_4 = var_retval;
    return var_4;
}
