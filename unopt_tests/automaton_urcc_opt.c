#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
int getnextdigit ();
void state_0 ();
void state_2 ();
void state_1 ();
void state_3 ();
/* func decls end */

  /* Ast::Scope prog: 9 symbols, 6 children */
  char str[32] = "Give me a number (-1 to quit): ";
  char str1[3] = "%d";
  char str2[39] = "I need a number that's either 0 or 1.\n";
  char str3[36] = "You gave me an even number of 0's.\n";
  char str4[36] = "You gave me an even number of 1's.\n";
  char str5[32] = "I therefore accept this input.\n";
  char str6[35] = "You gave me an odd number of 1's.\n";
  char str7[32] = "I therefore reject this input.\n";
  char str8[35] = "You gave me an odd number of 0's.\n";

int getnextdigit (){
    /* Ast::Block getnextdigit body: 10 symbols, 25 children */
    int var_n;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_call1;
    int var_0;
    int var_cmp;
    int var_1;
    int var_cmp2;
    int var_call3;
    int var_2;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    goto lbl_while_body;
    lbl_while_body:;
    var_call = printf((& str[0]));
    var_call1 = __isoc99_scanf((& str1[0]), (& var_n));
    var_0 = var_n;
    var_cmp = (-1 <= var_0);
    if (var_cmp) goto lbl_land_lhs_true; else goto lbl_while_body_if_end_crit_edge;
    lbl_while_body_if_end_crit_edge:;
    goto lbl_if_end;
    lbl_land_lhs_true:;
    var_1 = var_n;
    var_cmp2 = (1 >= var_1);
    if (var_cmp2) goto lbl_if_then; else goto lbl_land_lhs_true_if_end_crit_edge;
    lbl_land_lhs_true_if_end_crit_edge:;
    goto lbl_if_end;
    lbl_if_then:;
    goto lbl_while_end;
    lbl_if_end:;
    var_call3 = printf((& str2[0]));
    goto lbl_while_body;
    lbl_while_end:;
    var_2 = var_n;
    return var_2;
}
void state_0 (){
    /* Ast::Block state_0 body: 12 symbols, 32 children */
    int var_a;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_0;
    int var_cmp;
    int var_call1;
    int var_call2;
    int var_call3;
    int var_1;
    int var_cmp4;
    int var_2;
    int var_cmp7;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_call = getnextdigit();
    var_a = var_call;
    var_0 = var_a;
    var_cmp = (-1 == var_0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_call1 = printf((& str3[0]));
    var_call2 = printf((& str4[0]));
    var_call3 = printf((& str5[0]));
    goto lbl_if_end9;
    lbl_if_end:;
    var_1 = var_a;
    var_cmp4 = (0 == var_1);
    if (var_cmp4) goto lbl_if_then5; else goto lbl_if_end_if_end6_crit_edge;
    lbl_if_end_if_end6_crit_edge:;
    goto lbl_if_end6;
    lbl_if_then5:;
    state_2();
    goto lbl_if_end6;
    lbl_if_end6:;
    var_2 = var_a;
    var_cmp7 = (1 == var_2);
    if (var_cmp7) goto lbl_if_then8; else goto lbl_if_end6_if_end9_crit_edge;
    lbl_if_end6_if_end9_crit_edge:;
    goto lbl_if_end9;
    lbl_if_then8:;
    state_1();
    goto lbl_if_end9;
    lbl_if_end9:;
    return;
}
void state_2 (){
    /* Ast::Block state_2 body: 12 symbols, 32 children */
    int var_a;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_0;
    int var_cmp;
    int var_call1;
    int var_call2;
    int var_call3;
    int var_1;
    int var_cmp4;
    int var_2;
    int var_cmp7;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_call = getnextdigit();
    var_a = var_call;
    var_0 = var_a;
    var_cmp = (-1 == var_0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_call1 = printf((& str8[0]));
    var_call2 = printf((& str4[0]));
    var_call3 = printf((& str7[0]));
    goto lbl_if_end9;
    lbl_if_end:;
    var_1 = var_a;
    var_cmp4 = (0 == var_1);
    if (var_cmp4) goto lbl_if_then5; else goto lbl_if_end_if_end6_crit_edge;
    lbl_if_end_if_end6_crit_edge:;
    goto lbl_if_end6;
    lbl_if_then5:;
    state_0();
    goto lbl_if_end6;
    lbl_if_end6:;
    var_2 = var_a;
    var_cmp7 = (1 == var_2);
    if (var_cmp7) goto lbl_if_then8; else goto lbl_if_end6_if_end9_crit_edge;
    lbl_if_end6_if_end9_crit_edge:;
    goto lbl_if_end9;
    lbl_if_then8:;
    state_3();
    goto lbl_if_end9;
    lbl_if_end9:;
    return;
}
void state_1 (){
    /* Ast::Block state_1 body: 12 symbols, 32 children */
    int var_a;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_0;
    int var_cmp;
    int var_call1;
    int var_call2;
    int var_call3;
    int var_1;
    int var_cmp4;
    int var_2;
    int var_cmp7;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_call = getnextdigit();
    var_a = var_call;
    var_0 = var_a;
    var_cmp = (-1 == var_0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_call1 = printf((& str3[0]));
    var_call2 = printf((& str6[0]));
    var_call3 = printf((& str7[0]));
    goto lbl_if_end9;
    lbl_if_end:;
    var_1 = var_a;
    var_cmp4 = (0 == var_1);
    if (var_cmp4) goto lbl_if_then5; else goto lbl_if_end_if_end6_crit_edge;
    lbl_if_end_if_end6_crit_edge:;
    goto lbl_if_end6;
    lbl_if_then5:;
    state_3();
    goto lbl_if_end6;
    lbl_if_end6:;
    var_2 = var_a;
    var_cmp7 = (1 == var_2);
    if (var_cmp7) goto lbl_if_then8; else goto lbl_if_end6_if_end9_crit_edge;
    lbl_if_end6_if_end9_crit_edge:;
    goto lbl_if_end9;
    lbl_if_then8:;
    state_0();
    goto lbl_if_end9;
    lbl_if_end9:;
    return;
}
void state_3 (){
    /* Ast::Block state_3 body: 12 symbols, 32 children */
    int var_a;
    int var_reg2mem_alloca_point;
    int var_call;
    int var_0;
    int var_cmp;
    int var_call1;
    int var_call2;
    int var_call3;
    int var_1;
    int var_cmp4;
    int var_2;
    int var_cmp7;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_call = getnextdigit();
    var_a = var_call;
    var_0 = var_a;
    var_cmp = (-1 == var_0);
    if (var_cmp) goto lbl_if_then; else goto lbl_if_end;
    lbl_if_then:;
    var_call1 = printf((& str8[0]));
    var_call2 = printf((& str6[0]));
    var_call3 = printf((& str7[0]));
    goto lbl_if_end9;
    lbl_if_end:;
    var_1 = var_a;
    var_cmp4 = (0 == var_1);
    if (var_cmp4) goto lbl_if_then5; else goto lbl_if_end_if_end6_crit_edge;
    lbl_if_end_if_end6_crit_edge:;
    goto lbl_if_end6;
    lbl_if_then5:;
    state_1();
    goto lbl_if_end6;
    lbl_if_end6:;
    var_2 = var_a;
    var_cmp7 = (1 == var_2);
    if (var_cmp7) goto lbl_if_then8; else goto lbl_if_end6_if_end9_crit_edge;
    lbl_if_end6_if_end9_crit_edge:;
    goto lbl_if_end9;
    lbl_if_then8:;
    state_2();
    goto lbl_if_end9;
    lbl_if_end9:;
    return;
}
int main (){
    /* Ast::Block main body: 1 symbols, 4 children */
    int var_reg2mem_alloca_point;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    state_0();
    return 0;
}
