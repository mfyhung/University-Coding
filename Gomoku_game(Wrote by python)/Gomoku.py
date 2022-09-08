#CSCI3180 Principles of Programming Languages
#
#--- Declaration --
#
# I declare that the assignment here submitted is original except for source
# material explicitly acknowledged. I also acknowledge that I am aware of
# University policy and regulations on honesty in academic work, and of the
# disciplinary guidelines and procedures applicable to breaches of such policy
# and regulations, as contained in the website
# http://www.cuhk.edu.hk/policy/academichonesty/
#
# Assignment 2
# Name : Hung Fan Yan
# Student ID : 1155083147
# Email Addr : 1155083147@link.cuhk.edu.hk
import random
import abc

class Gomoku(object):
    turn = 1
    gameboard = [[" " for x in range(9)] for y in range(9)]
    playerO = "player1"
    playerX = "player2"
    user_choice1 = None
    user_choice2 = None

    def begin(self):
        # The main function of the program to call out the function and get the beginning walue
        print ("Please choose player 1 (O):")
        print ("1. Human")
        print ("2. Computer")

        while True:
            self.user_choice1 = raw_input("Your choice is: ")
            if self.user_choice1 == "1" or self.user_choice1 == "2":
                break
            else:
                print("You can only input 1 or 2, Please input again")
        # End of the loop

        if self.user_choice1 == '1':
            print ("Player O is Human.\n")
        else:
            print("Player O is Computer.\n")

        print ("Please choose player 2 (X): ")
        print ("1. Human")
        print ("2. Computer")

        while True:
            self.user_choice2 = raw_input("Your choice is: ")
            if self.user_choice2 == "1" or self.user_choice2 == "2":
                break
            else:
                print("You can only input 1 or 2, Please input again")
        # end of the loop
        if self.user_choice2 == '1':
            print ("Player X is Human.\n")
        else:
            print("Player X is Computer.\n")
    def startGame(self):
        self.begin()
        self.createPlayer("O", 1)
        self.createPlayer("X", 2)
        while True:
            if self.turn % 2 == 1:
                self.playerO.nextMove()
            else:
                self.playerX.nextMove()
            self.printGameBoard()
            self.turn = self.turn + 1
            self.checkWin()
            self.checkTie()
    def createPlayer(self, symbol, playerNum):
        if playerNum == 1:
            if self.user_choice1 == '1':
                self.playerO = Human(symbol, self.gameboard)
            else:
                self.playerO = Computer(symbol, self.gameboard)
        else:
            if self.user_choice2 == '1':
                self.playerX = Human(symbol, self.gameboard)
            else:
                self.playerX = Computer(symbol, self.gameboard)
    def printGameBoard(self):
        i = -1
        while i < 9:
            j = 0
            if i == -1:
                print ("  |"),
                while j < 9:
                    if j == 8:
                        print j + 1, ("|")
                        print ("---------------------------------------")
                    else:
                        print j + 1, ("|"),

                    j += 1
            else:
                print i+1, ("|"),
                while j < 9:
                    if j == 8:
                        print self.gameboard[i][j], ("|")
                        print ("---------------------------------------")
                    else:
                        print self.gameboard[i][j], ("|"),
                    j += 1
            i += 1
    def checkWin(self):
        i = 0
        while i < 9:
            j = 0
            while j < 9:
                # check the col
                if i <= 4:
                    if (self.gameboard[i][j] == self.gameboard[i + 1][j]):
                        if(self.gameboard[i + 1][j] == self.gameboard[i + 2][j]):
                            if(self.gameboard[i + 2][j] == self.gameboard[i+3][j]):
                                if(self.gameboard[i+3][j] == self.gameboard[i+4][j]):
                                    if self.gameboard[i][j] == 'O':
                                        print("Game ends. Player O wins")
                                        quit()
                                    elif self.gameboard[i][j] == 'X':
                                        print("Game ends. Player X wins")
                                        quit()
                # check the row
                if j <= 4:
                    if (self.gameboard[i][j] == self.gameboard[i][j + 1]):
                        if(self.gameboard[i][j+1] == self.gameboard[i][j+2]):
                            if(self.gameboard[i][j+2] == self.gameboard[i][j+3]):
                                if(self.gameboard[i][j+3] == self.gameboard[i][j+4]):
                                    if self.gameboard[i][j] == 'O':
                                        print("Game ends. Player O wins")
                                        quit()
                                    elif self.gameboard[i][j] == 'X':
                                        print("Game ends. Player X wins")
                                        quit()
                # check the \
                if i<=4 and j <= 4:
                    if (self.gameboard[i][j] == self.gameboard[i + 1][j+1]):
                        if(self.gameboard[i + 1][j+1] == self.gameboard[i + 2][j+2]):
                            if(self.gameboard[i + 2][j+2] == self.gameboard[i+3][j+3]):
                                if(self.gameboard[i+3][j+3] == self.gameboard[i+4][j+4]):
                                    if self.gameboard[i][j] == 'O':
                                        print("Game ends. Player O wins")
                                        quit()
                                    elif self.gameboard[i][j] == 'X':
                                        print("Game ends. Player X wins")
                                        quit()
                # check the /
                if i>=4 and j<=4:
                    if (self.gameboard[i][j] == self.gameboard[i - 1][j+1]):
                        if(self.gameboard[i - 1][j+1] == self.gameboard[i - 2][j+2]):
                            if(self.gameboard[i - 2][j+2] == self.gameboard[i-3][j+3]):
                                if(self.gameboard[i-3][j+3] == self.gameboard[i-4][j+4]):
                                    if self.gameboard[i][j] == 'O':
                                        print("Game ends. Player O wins")
                                        quit()
                                    elif self.gameboard[i][j] == 'X':
                                        print("Game ends. Player X wins")
                                        quit()
                j += 1
            i += 1
    def checkTie(self):
        i = 0
        counter = 0
        while i < 9:
            j = 0
            while j < 9:
                if self.gameboard[i][j] == ' ':
                    counter = counter + 1
                j = j + 1
            i = i + 1
        if counter == 0:
            print("The game is Tie!")
            quit()

class Player(Gomoku):
    def __init__(self, symbol, gameboard):
        self.symbol = symbol
        self.gameboard2 = gameboard
    __metaclass__ = abc.ABCMeta
    @abc.abstractmethod
    def nextMove(self):
        return

class Human(Player):
    def __init__(self, symbol, gameboard):
        super(Human, self).__init__(symbol, gameboard)
        self.symbol = symbol
        self.gameboard2 = gameboard

    def nextMove(self):
        while True:
            print("Player"), self.symbol, ("'s turn!")
            print("Type the row and col to put the disc: ")
            x, y = map(int, raw_input().split())
            if (x <= 9 and x>=1) and (y<= 9 and y>= 1) and (self.gameboard2[x-1][y-1] == ' '):
                break
            print("Invalid input!")
        self.gameboard[x-1][y-1] = self.symbol

class Computer(Player):
    def __init__(self, symbol, gameboard):
        super(Computer, self).__init__(symbol, gameboard)
        self.symbol = symbol
        self.gameboard2 = gameboard

    def nextMove(self):
        while True:
            x = random.randint(1, 9)
            y = random.randint(1, 9)
            if (x <= 9 and x>=1) and (y<= 9 and y>= 1) and (self.gameboard2[x-1][y-1] == ' '):
                break
        print("Player"), self.symbol, ("'s turn!")
        print("The Computer move: "), x, (" "),y
        self.gameboard[x-1][y-1] = self.symbol

the_try = Gomoku()
the_try.startGame()