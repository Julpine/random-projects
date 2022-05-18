# makefile for: main_multi.c
NAME = guessWords
SOURCE = main_multi.c

MPICC2 = /usr/bin/mpirun
MPICC = /usr/lib64/openmpi/bin/mpicc
MPIRUN = /usr/lib64/openmpi/bin/mpirun

build: $(SOURCE)
	$(MPICC) $(SOURCE) -o $(NAME)
	@echo 'Compiling finished. $(NAME)* created'

run:
	@echo 'Running $(NAME) with 1 core'
	$(MPIRUN) -np 0 ./$(NAME)

run2:
	@echo 'Running $(NAME) with 2 cores'
	$(MPIRUN) -np 2 ./$(NAME)

run3:
	@echo 'Running $(NAME) with 3 cores'
	$(MPIRUN) -np 3 ./$(NAME)
run4:
	@echo 'Running $(NAME) with 4 cores'
	$(MPIRUN) -np 4 ./$(NAME)

run5:
	@echo 'Running $(NAME) with 5 cores'
	$(MPIRUN) -np 5 ./$(NAME)

run6:
	@echo 'Running $(NAME) with 6 cores'
	$(MPIRUN) -np 6 ./$(NAME)

run7:
	@echo 'Running $(NAME) with 7 cores'
	$(MPIRUN) -np 7 ./$(NAME)

run8:
	@echo 'Running $(NAME) with 8 cores'
	$(MPIRUN) -np 8 ./$(NAME)

em:
	vim makefile
