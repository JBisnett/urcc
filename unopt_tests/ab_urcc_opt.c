#include <stdio.h>
#include <stdlib.h>

/* func decls begin */
/* func decls end */

  /* Ast::Scope prog: 1 symbols, 1 children */
  char str[10] = "19 s=%2d\n";

int main (){
    /* Ast::Block main body: 9 symbols, 11 children */
    int var_x;
    int var_y;
    int var_z;
    int var_reg2mem_alloca_point;
    int var_0;
    int var_1;
    int var_add;
    int var_2;
    int var_call;

    lbl_entry:;
    var_reg2mem_alloca_point = 0;
    var_y = 0;
    var_x = 1;
    var_0 = var_x;
    var_1 = var_y;
    var_add = (var_0 + var_1);
    var_z = var_add;
    var_2 = var_z;
    var_call = printf((& str[0]), var_2);
    return 0;
}
