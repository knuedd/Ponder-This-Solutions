all: gen_candidates split_solution_par

gen_candidates: gen_candidates.cpp check.h
	g++ -O6 gen_candidates.cpp -o gen_candidates -lgmpxx -lgmp

split_solution_par: split_solution_par.cpp check.h
	g++ -O6 -fopenmp split_solution_par.cpp -o split_solution_par -lgmpxx -lgmp
