PGP2DIR = P-GP2
INCDIR= $(PGP2DIR)/include/
LIBDIR= $(PGP2DIR)/lib/
GP2_PROGRAMS = GP2_Programs
GP2_FILES = GP2_Files
GP2_OBJECTS = depth_start init_individual local_edge_crossover local_node_crossover mutate_edge mutate_node remove_depth neutral_cap
OBJECTS := evaluate.c function_set.c genetic_operators.c individual_util.c ea.c rand_util.c
CC=gcc

CFLAGS = -I$(INCDIR) -L $(LIBDIR) -O2 -lgp2 -lm -g -fsplit-stack

symreg:	$(OBJECTS) symbolic_regression_experiment.c
		rm -f -r $(GP2_FILES);	mkdir $(GP2_FILES);
		$(foreach var,$(GP2_OBJECTS),mkdir $(GP2_FILES)/$(var);	echo '$(var) compile'; $(PGP2DIR)/bin/gp2 -l $(PGP2DIR) -m $(var) -o $(GP2_FILES)/$(var) $(GP2_PROGRAMS)/$(var).gp2; )
		$(CC) symbolic_regression_experiment.c $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(GP2_FILES)/$(var)/*.c) $(CFLAGS) -o symreg

symreg-clean:
		rm -f symreg

symreg_nc:	$(OBJECTS) symbolic_regression_no_crossover.c
		rm -f -r $(GP2_FILES);	mkdir $(GP2_FILES);
		$(foreach var,$(GP2_OBJECTS),mkdir $(GP2_FILES)/$(var);	echo '$(var) compile'; $(PGP2DIR)/bin/gp2 -l $(PGP2DIR) -m $(var) -o $(GP2_FILES)/$(var) $(GP2_PROGRAMS)/$(var).gp2; )
		$(CC) symbolic_regression_no_crossover.c $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(GP2_FILES)/$(var)/*.c) $(CFLAGS) -o symreg_nc

symreg-clean_nc:
		rm -f symreg_nc

symreg_sp:	$(OBJECTS) symbolic_regression_small_pop.c
		rm -f -r $(GP2_FILES);	mkdir $(GP2_FILES);
		$(foreach var,$(GP2_OBJECTS),mkdir $(GP2_FILES)/$(var);	echo '$(var) compile'; $(PGP2DIR)/bin/gp2 -l $(PGP2DIR) -m $(var) -o $(GP2_FILES)/$(var) $(GP2_PROGRAMS)/$(var).gp2; )
		$(CC) symbolic_regression_small_pop.c $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(GP2_FILES)/$(var)/*.c) $(CFLAGS) -o symreg_sp

symreg-clean_sp:
		rm -f symreg_sp
