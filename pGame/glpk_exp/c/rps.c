#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void){
	glp_prob *lp;
	int ia[1000], ja[1000];
	double ar[1000], u, r, p, s;

	lp = glp_create_prob();
	glp_set_prob_name(lp, "rps");
	glp_set_obj_dir(lp, GLP_MAX);

	glp_add_rows(lp, 4);
	glp_set_row_name(lp, 1, "rock row");
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 0.0);

	glp_set_row_name(lp, 2, "paper row");
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 0.0);

	glp_set_row_name(lp, 3, "scissors row");
	glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 0.0);

	glp_set_row_name(lp, 4, "all row");
	glp_set_row_bnds(lp, 4, GLP_UP, 0.0, 1.0);

	glp_add_cols(lp, 4);
	glp_set_col_name(lp, 1, "u");
  	glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
 	glp_set_obj_coef(lp, 1, 1.0);

 	glp_set_col_name(lp, 2, "r");
  	glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
 	glp_set_obj_coef(lp, 2, 0.0);

 	glp_set_col_name(lp, 3, "p");
  	glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);
 	glp_set_obj_coef(lp, 3, 0.0);

 	glp_set_col_name(lp, 4, "s");
  	glp_set_col_bnds(lp, 4, GLP_LO, 0.0, 0.0);
 	glp_set_obj_coef(lp, 4, 0.0);

 	ia[1] = 1, ja[1] = 1, ar[1] = 1.0;
 	ia[2] = 1, ja[2] = 2, ar[2] = 0.0;
 	ia[3] = 1, ja[3] = 3, ar[3] = -1.0;
 	ia[4] = 1, ja[4] = 4, ar[4] = 1.0;

 	ia[5] = 2, ja[5] = 1, ar[5] = 1.0;
 	ia[6] = 2, ja[6] = 2, ar[6] = 1.0;
 	ia[7] = 2, ja[7] = 3, ar[7] = 0.0;
 	ia[8] = 2, ja[8] = 4, ar[8] = -1.0;

    ia[9] = 3, ja[9] = 1, ar[9] = 1.0;
 	ia[10] = 3, ja[10] = 2, ar[10] = -1.0;
 	ia[11] = 3, ja[11] = 3, ar[11] = 1.0;
 	ia[12] = 3, ja[12] = 4, ar[12] = 0.0;

 	ia[13] = 4, ja[13] = 1, ar[9] = 0.0;
 	ia[14] = 4, ja[14] = 2, ar[10] = 1.0;
 	ia[15] = 4, ja[15] = 3, ar[11] = 1.0;
 	ia[16] = 4, ja[16] = 4, ar[12] = 1.0;

  	glp_load_matrix(lp, 16, ia, ja, ar);

  	glp_simplex(lp, NULL);
  	u = glp_get_col_prim(lp, 1);
  	r = glp_get_col_prim(lp, 2);
  	p = glp_get_col_prim(lp, 3);
  	s = glp_get_col_prim(lp, 4);

  printf("u = %g; r = %g; p = %g\n; s = %g\n", u, r, p, s);
  
  //cleanup
  glp_delete_prob(lp);
  glp_free_env();



	return 0;
}