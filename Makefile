CXX = g++
CXXFLAG = -std=c++20 -fmodules-ts -Wall -g
EXEC = a4
OBJECTS = main.o cell.o grid.o textdisplay.o todolist.o

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}
main.o: main.cc grid.h state.h todolist.h
cell.o: cell.cc cell.h
grid.o: grid.cc grid.h
textdisplay.o: textdisplay.cc textdisplay.h
todolist.o: todolist.cc todolist.h
PHONY:clean
clean:
	rm ${OBJECTS} ${EXEC}
