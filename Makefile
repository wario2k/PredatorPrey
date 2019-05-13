init:
	mkdir -p out/

build:
	make init
	g++ *.cpp -o out/simulation

run:
	make build
	out/simulation

graph: 
	python graph.py out/simulation.csv out/out.png