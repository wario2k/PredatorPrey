init:
	mkdir -p out/

build:
	make init
	g++ *.cpp

run:
	make build
	out/simulation

graph: 
	python out/graph.py out/simulation.csv out/out.png