class FifteenPuzzle {
public:
    FifteenPuzzle(unsigned s);
    bool move(char dir);
    void print() const;
    bool isSolved() const;
    int getSteps() const;
private:
    int board[4][4];
    int r, c, steps;
};
