#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
int square (int var_x);
int complex_abs_squared (int var_real, int var_imag);
int check_for_bail (int var_real, int var_imag);
int absval (int var_x);
int checkpixel (int var_x, int var_y);
/* func decls end */

  /* Ast::Scope prog: 3 symbols, 6 children */
  char str[2] = "X";
  char str1[2] = " ";
  char str2[2] = "\n";

int square (int var_x){
    /* Ast::Block square body: 7 symbols, 9 children */
    int var_x_addr;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_1;
    int var_mul;
    int var_add;
    int var_div;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_x_addr = var_x;
    var_0 = var_x_addr;
    var_1 = var_x_addr;
    var_mul = (var_0 * var_1);
    var_add = (var_mul + 500);
    var_div = (var_add / 1000);
    return var_div;
}
int complex_abs_squared (int var_real, int var_imag){
    /* Ast::Block complex_abs_squared body: 8 symbols, 10 children */
    int var_real_addr;
    int var_imag_addr;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_call;
    int var_1;
    int var_call1;
    int var_add;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_real_addr = var_real;
    var_imag_addr = var_imag;
    var_0 = var_real_addr;
    var_call = square(var_0);
    var_1 = var_imag_addr;
    var_call1 = square(var_1);
    var_add = (var_call + var_call1);
    return var_add;
}
int check_for_bail (int var_real, int var_imag){
    /* Ast::Block check_for_bail body: 13 symbols, 33 children */
    int var_retval;
    int var_real_addr;
    int var_imag_addr;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_1;
    int var_cmp1;
    int var_2;
    int var_3;
    int var_call;
    int var_cmp2;
    int var_4;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_real_addr = var_real;
    var_imag_addr = var_imag;
    var_0 = var_real_addr;
    var_cmp = (var_0 >= 4000);
    if (var_cmp) goto lbl_entry_if_then_crit_edge; else goto lbl_lor_lhs_false;
    lbl_entry_if_then_crit_edge:;
    goto lbl_if_then;
    lbl_lor_lhs_false:;
    var_1 = var_imag_addr;
    var_cmp1 = (var_1 >= 4000);
    if (var_cmp1) goto lbl_lor_lhs_false_if_then_crit_edge; else goto lbl_if_end;
    lbl_lor_lhs_false_if_then_crit_edge:;
    goto lbl_if_then;
    lbl_if_then:;
    var_retval = 0;
    goto lbl_return;
    lbl_if_end:;
    var_2 = var_real_addr;
    var_3 = var_imag_addr;
    var_call = complex_abs_squared(var_2, var_3);
    var_cmp2 = (1600 >= var_call);
    if (var_cmp2) goto lbl_if_then3; else goto lbl_if_end4;
    lbl_if_then3:;
    var_retval = 0;
    goto lbl_return;
    lbl_if_end4:;
    var_retval = 1;
    goto lbl_return;
    lbl_return:;
    var_4 = var_retval;
    return var_4;
}
int absval (int var_x){
    /* Ast::Block absval body: 9 symbols, 18 children */
    int var_retval;
    int var_x_addr;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_1;
    int var_mul;
    int var_2;
    int var_3;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_x_addr = var_x;
    var_0 = var_x_addr;
    var_cmp = (var_0 < 0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_1 = var_x_addr;
    var_mul = (-1 * var_1);
    var_retval = var_mul;
    goto lbl_return;
    lbl_if_end:;
    var_2 = var_x_addr;
    var_retval = var_2;
    goto lbl_return;
    lbl_return:;
    var_3 = var_retval;
    return var_3;
}
int checkpixel (int var_x, int var_y){
    /* Ast::Block checkpixel body: 36 symbols, 54 children */
    int var_retval;
    int var_x_addr;
    int var_y_addr;
    int var_real;
    int var_imag;
    int var_temp;
    int var_iter;
    int var_bail;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_1;
    int var_call;
    int var_2;
    int var_call1;
    int var_sub;
    int var_3;
    int var_add;
    int var_4;
    int var_mul;
    int var_5;
    int var_mul2;
    int var_add3;
    int var_div;
    int var_6;
    int var_add4;
    int var_7;
    int var_8;
    int var_call5;
    int var_9;
    int var_call6;
    int var_add7;
    int var_cmp8;
    int var_10;
    int var_add9;
    int var_11;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_x_addr = var_x;
    var_y_addr = var_y;
    var_real = 0;
    var_imag = 0;
    var_iter = 0;
    var_bail = 16000;
    goto lbl_while_cond;
    lbl_while_cond:;
    var_0 = var_iter;
    var_cmp = (var_0 < 255);
    if (var_cmp) goto lbl_while_body; else goto lbl_while_end;
    lbl_while_body:;
    var_1 = var_real;
    var_call = square(var_1);
    var_2 = var_imag;
    var_call1 = square(var_2);
    var_sub = (var_call - var_call1);
    var_3 = var_x_addr;
    var_add = (var_sub + var_3);
    var_temp = var_add;
    var_4 = var_real;
    var_mul = (2 * var_4);
    var_5 = var_imag;
    var_mul2 = (var_mul * var_5);
    var_add3 = (var_mul2 + 500);
    var_div = (var_add3 / 1000);
    var_6 = var_y_addr;
    var_add4 = (var_div + var_6);
    var_imag = var_add4;
    var_7 = var_temp;
    var_real = var_7;
    var_8 = var_real;
    var_call5 = absval(var_8);
    var_9 = var_imag;
    var_call6 = absval(var_9);
    var_add7 = (var_call5 + var_call6);
    var_cmp8 = (var_add7 >= 5000);
    if (var_cmp8) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_retval = 0;
    goto lbl_return;
    lbl_if_end:;
    var_10 = var_iter;
    var_add9 = (var_10 + 1);
    var_iter = var_add9;
    goto lbl_while_cond;
    lbl_while_end:;
    var_retval = 1;
    goto lbl_return;
    lbl_return:;
    var_11 = var_retval;
    return var_11;
}
int main (){
    /* Ast::Block main body: 24 symbols, 52 children */
    int var_retval;
    int var_x;
    int var_y;
    int var_on;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_cmp;
    int var_1;
    int var_cmp2;
    int var_2;
    int var_3;
    int var_call;
    int var_4;
    int var_cmp4;
    int var_call5;
    int var_5;
    int var_cmp6;
    int var_call8;
    int var_6;
    int var_add;
    int var_call10;
    int var_7;
    int var_sub;
    int var_8;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_retval = 0;
    var_y = 950;
    goto lbl_while_cond;
    lbl_while_cond:;
    var_0 = var_y;
    var_cmp = (var_0 >= -950);
    if (var_cmp) goto lbl_while_body; else goto lbl_while_end11;
    lbl_while_body:;
    var_x = -2100;
    goto lbl_while_cond1;
    lbl_while_cond1:;
    var_1 = var_x;
    var_cmp2 = (var_1 < 1000);
    if (var_cmp2) goto lbl_while_body3; else goto lbl_while_end;
    lbl_while_body3:;
    var_2 = var_x;
    var_3 = var_y;
    var_call = checkpixel(var_2, var_3);
    var_on = var_call;
    var_4 = var_on;
    var_cmp4 = (1 == var_4);
    if (var_cmp4) goto lbl_if_then; else goto lbl_while_body3_if_end_crit_edge;
    lbl_while_body3_if_end_crit_edge:;
    goto lbl_if_end;
    lbl_if_then:;
    var_call5 = printf((& str[0]));
    goto lbl_if_end;
    lbl_if_end:;
    var_5 = var_on;
    var_cmp6 = (0 == var_5);
    if (var_cmp6) goto lbl_if_then7; else goto lbl_if_end_if_end9_crit_edge;
    lbl_if_end_if_end9_crit_edge:;
    goto lbl_if_end9;
    lbl_if_then7:;
    var_call8 = printf((& str1[0]));
    goto lbl_if_end9;
    lbl_if_end9:;
    var_6 = var_x;
    var_add = (var_6 + 40);
    var_x = var_add;
    goto lbl_while_cond1;
    lbl_while_end:;
    var_call10 = printf((& str2[0]));
    var_7 = var_y;
    var_sub = (var_7 - 50);
    var_y = var_sub;
    goto lbl_while_cond;
    lbl_while_end11:;
    var_8 = var_retval;
    return var_8;
}
