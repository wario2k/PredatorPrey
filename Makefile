init:
	mkdir -p out/

build:
	make init
	g++ \
	roadrunner.cpp \
	cell.cpp \
	controller.cpp \
	organismcreator.cpp \
	coyote.cpp \
	grid.cpp \
	main.cpp \
	organism.cpp \
	organismimpl.cpp \
	-o out/simulation

run:
	make build
	out/simulation

graph: 
	python out/graph.py out/simulation.csv out/out.png