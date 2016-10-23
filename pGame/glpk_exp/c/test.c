#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void){
	glp_prob *lp;
	int ia[100], ja[100];
	double ar[100], a, x, y, z;

	lp = glp_create_prob();
	glp_set_prob_name(lp, "test");
	glp_set_obj_dir(lp, GLP_MAX);
    
    //add rows
    glp_add_rows(lp, 3);
    glp_set_row_name(lp, 1, "row1");
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 100);
    
    glp_set_row_name(lp, 2, "row2");
    glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 111);
    
    glp_set_row_name(lp, 3, "row3");
    glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 48);
    
    //add cols
    glp_add_cols(lp, 3);
    
    glp_set_col_name(lp, 1, "col1");
    glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(lp, 1, 5.0);
    
    glp_set_col_name(lp, 2, "col2");
    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(lp, 2, 10.0);
    
    glp_set_col_name(lp, 2, "col3");
    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(lp, 2, 15.0);
    
    ia[1] = 1, ja[1] = 1, ar[1] = 0.3;
    ia[2] = 1, ja[2] = 2, ar[2] = 1.0;
    ia[3] = 1, ja[3] = 3, ar[3] = 17.0;
    
    ia[4] = 2, ja[4] = 1, ar[4] = 12.0;
    ia[5] = 2, ja[5] = 2, ar[5] = 3.0;
    ia[6] = 2, ja[6] = 3, ar[6] = 1.0;
    
    ia[7] = 3, ja[7] = 1, ar[7] = 1.0;
    ia[8] = 3, ja[8] = 2, ar[8] = 1.0;
    ia[9] = 3, ja[9] = 3, ar[9] = 1.0;
    
    glp_load_matrix(lp, 9, ia, ja, ar);
    
    glp_simplex(lp, NULL);
    //results
    a = glp_get_obj_val(lp);
    x = glp_get_col_prim(lp, 1);
    y = glp_get_col_prim(lp, 2);
    z = glp_get_col_prim(lp, 3);
    
    printf("a = %g; x = %g; y = %g; z = %g\n", a, x, y, z);
	
  
    //cleanup
    glp_delete_prob(lp);
    glp_free_env();

	return 0;
}
