MAIN=../../main
NRUNS=10

define run_analysis
	echo "nTubes,tubeH,nColors,seed,$(2)-nMoves,$(2)-mem_b,$(2)-t_ns" > $(2).csv
	$(MAIN) cli $(NRUNS) 2 4 1 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 3 4 1 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 4 4 2 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 5 4 3 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 6 4 3 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 7 4 4 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 8 4 4 0 $(1) >> $(2).csv
endef

define run_analysis_ids
	echo "nTubes,tubeH,nColors,seed,$(2)-nMoves,$(2)-mem_b,$(2)-t_ns" > $(2).csv
	$(MAIN) cli $(NRUNS) 2 4 1 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 3 4 1 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 4 4 2 0 $(1) >> $(2).csv
	$(MAIN) cli $(NRUNS) 5 4 3 0 $(1) >> $(2).csv
	echo ",,,,,," >> $(2).csv
	echo ",,,,,," >> $(2).csv
	echo ",,,,,," >> $(2).csv
endef

all: discard-dfs-math.csv

discard-dfs-math.csv: discard-dfs.csv
	head -n 1 discard-dfs.csv > discard-dfs-math.csv
	cat discard-dfs.csv | tail -n +2 | awk -F , -v OFS=, '{print $$1,$$2,$$3,$$4,$$20/$$5,$$6/1000000,$$7/$$10,$$20/$$8,$$9/1000000,$$10/1000000,($$11==""?"-":$$20/$$11),($$12==""?"-":$$12/1000000),($$13==""?"-":$$13/$$10),$$20/$$14,$$15/1000000,$$16/$$10,$$20/$$17,$$18/1000000,$$19/$$10,$$20,$$21/1000000,$$22/$$10,$$20/$$23,$$24/1000000,$$25/$$10}' >> discard-dfs-math.csv

discard-dfs.csv: dfs.csv bfs.csv iterative-deepening.csv dfs-greedy-admissible.csv greedy-admissible.csv astar-admissible.csv astar-nonadmissible.csv #dfs-greedy-fh.csv dfs-fh.csv astar-fh.csv
	csvcut -c 5,6,7 bfs.csv                     > bfs-cut.csv
	csvcut -c 5,6,7 iterative-deepening.csv     > iterative-deepening-cut.csv
	csvcut -c 5,6,7 dfs-greedy-admissible.csv   > dfs-greedy-admissible-cut.csv
	csvcut -c 5,6,7 greedy-admissible.csv       > greedy-admissible-cut.csv
	csvcut -c 5,6,7 astar-admissible.csv        > astar-admissible-cut.csv
	csvcut -c 5,6,7 astar-nonadmissible.csv     > astar-nonadmissible-cut.csv
#	csvcut -c 5,6,7 dfs-greedy-fh.csv           > dfs-greedy-fh-cut.csv
#	csvcut -c 5,6,7 dfs-fh.csv                  > dfs-fh-cut.csv
#	csvcut -c 5,6,7 astar-fh.csv                > astar-fh-cut.csv
	paste -d , dfs.csv bfs-cut.csv iterative-deepening-cut.csv dfs-greedy-admissible-cut.csv greedy-admissible-cut.csv astar-admissible-cut.csv astar-nonadmissible-cut.csv > discard-dfs.csv
	sed -i 's/-//g' discard-dfs.csv
	sed -i 's/_//g' discard-dfs.csv
	rm bfs-cut.csv
	rm iterative-deepening-cut.csv
	rm dfs-greedy-admissible-cut.csv
	rm greedy-admissible-cut.csv
	rm astar-admissible-cut.csv
	rm astar-nonadmissible-cut.csv
#	rm dfs-greedy-fh-cut.csv
#	rm dfs-fh-cut.csv
#	rm astar-fh-cut.csv

dfs.csv:
	$(call run_analysis,dfs,dfs)

bfs.csv:
	$(call run_analysis,bfs,bfs)

iterative-deepening.csv:
	$(call run_analysis_ids,iterative-deepening,iterative-deepening)

dfs-greedy-admissible.csv:
	$(call run_analysis,informed admissible dfs-greedy,dfs-greedy-admissible)

greedy-admissible.csv:
	$(call run_analysis,informed admissible greedy,greedy-admissible)

astar-admissible.csv:
	$(call run_analysis,informed admissible astar,astar-admissible)

astar-nonadmissible.csv:
	$(call run_analysis,informed nonadmissible 1.1 astar,astar-nonadmissible)

# dfs-greedy-fh.csv:
# 	$(call run_analysis,informed finite-horizon-heuristics 3 admissible finite-horizon dfs-greedy,dfs-greedy-fh)

# dfs-fh.csv:
# 	$(call run_analysis,informed finite-horizon-heuristics 3 admissible finite-horizon greedy,dfs-fh)

# astar-fh.csv:
# 	$(call run_analysis,informed finite-horizon-heuristics 3 admissible finite-horizon astar,astar-fh)
