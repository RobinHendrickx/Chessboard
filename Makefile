EXE = chess
OBJ = ChessMain.o ChessBoard.o Piece.o Pawn.o Bishop.o Castle.o Queen.o King.o Knight.o
DEP = $(OBJ:%.o=%.d)
CXX = g++
CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(EXE)

.PHONY: clean





