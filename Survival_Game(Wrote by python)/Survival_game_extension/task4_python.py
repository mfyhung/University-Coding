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

class SurvivalGame(object):
    D = 10 #dimension of board
    O = 2 #number of obstacles
    n = None
    teleportObjects = []

    def printBoard(self):
        printObject = [["  " for x in range(10)] for y in range(10)]
        i = 0
        while i < self.n:
            pos = self.teleportObjects[i].getPos()
            printObject[pos.getX()][pos.getY()] = self.teleportObjects[i].getName()
            i += 1

        j = self.n
        while j < self.n + 2:
            pos = self.teleportObjects[j].getPos()
            printObject[pos.getX()][pos.getY()] = "O" + str(j - self.n)
            j += 1

        i = -1
        while i < 10:
            j = 0
            if i == -1:
                print ("  | "),
                while j < 10:
                    if j == 9:
                        print j, ("|")
                        print ("-----------------------------------------------------")
                    else:
                        print j, ("| "),

                    j += 1
            else:
                print i, ("|"),
                while j < 10:
                    if j == 9:
                        print printObject[i][j], ("|")
                        print ("-----------------------------------------------------")
                    else:
                        print printObject[i][j], ("|"),
                    j += 1
            i += 1

    def positionOccupied(self, randx, randy):
        for o in self.teleportObjects:
            if isinstance(o, Player):
                pos = o.getPos()
                if (pos.getX() == randx) and (pos.getY() == randy):
                    return True
                else:
                    pos = o.getPos()
                    if (pos.getX() == randx) and (pos.getY() == randy):
                        return True
        return False

    def getPlayer(self, randx, randy):
        for o in self.teleportObjects:
            if isinstance(o, Player):
                pos = o.getPos()
                if (pos.getX() == randx) and (pos.getY() == randy):
                    return o

    def init(self):
        print("Welcome to Kafustrok. Light blesses you. \nInput number of players: (a even number)")
        while 1:
            self.n = input()
            if self.n % 2 == 0:
                break
            else:
                print("You can only input a even number! \nInput number of players: (a even number)")
        self.teleportObjects = [None] * (self.n + self.O)
        for i in range(0, self.n / 2):
            self.teleportObjects[i] = Human(0, 0, i, self)
            self.teleportObjects[i + self.n / 2] = Chark(0, 0, i, self)
        for i in range(0, self.O):
            self.teleportObjects[i + self.n] = Obstacle(0, 0, i, self)

    def gameStart(self):
        turn = 0
        numOfAlicePlayers = self.n
        while numOfAlicePlayers > 1:
            if turn == 0:
                for obj in self.teleportObjects:
                    if isinstance(obj, Human):
                        obj.teleport()
                    elif isinstance(obj, Chark):
                        obj.teleport()
                    elif isinstance(obj, Obstacle):
                        obj.teleport()
                print("Everything gets teleported..")
            self.printBoard()
            t = self.teleportObjects[turn]
            if (t.health > 0):
                t.askForMove()
                print("\n")
            turn = (turn + 1) % self.n
            numOfAlicePlayers = 0
            y = 0
            humancount = 0
            charkcount = 0
            while y < self.n:
                if self.teleportObjects[y].health > 0:
                    numOfAlicePlayers += 1
                y += 1
            for i in range(0,(self.n)/2,1):
                if self.teleportObjects[i].health > 0:
                    humancount += 1
            for i in range((self.n)/2, self.n,1):
                if self.teleportObjects[i].health > 0:
                    charkcount +=1
            if charkcount == 0 or humancount == 0:
                if humancount > 0:
                    print("Human win!")
                else:
                    print("Chark win!")
                break
        print("Game over.")
        self.printBoard()


class Pos(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, another):
        return abs(self.x - another.x) + abs(self.y - another.y)

    def distance(self, x1, y1):
        return abs(self.x - x1) + abs(self.y - y1)

    def setPos(self, x, y):
        self.x = x
        self.y = y

    def getX(self):
        return self.x

    def getY(self):
        return self.y


class Wand(object):
    WAND_RANGE = 5
    WAND_INIT_HEAL = 10

    def __init__(self, owner):
        self.range = self.WAND_RANGE
        self.effect = self.WAND_INIT_HEAL
        self.owner = owner

    def enhance(self):
        self.effect += 5

    def action(self, posx, posy):
        print("You are using wand healing "), posx,  posy, (".")
        if self.owner.pos.distance(posx, posy) <= self.range:
            player = self.owner.game.getPlayer(posx, posy)

            if player is not None:
                if isinstance(self.owner, Human):
                    if isinstance(player, Human):
                        player.increaseHealth(self.effect)
                elif isinstance(self.owner, Chark) and isinstance(player, Chark):
                    player.increaseHealth(self.effect)
                else:
                    print("You cannot heal the other race")

            else:
                print("Our of reach.")

    def getEffect(self):
        return self.effect

    def getRange(self):
        return self.range


class Weapon(object):
    __metaclass__ = abc.ABCMeta

    def __init__(self, range, damage, owner):
        self.range = range
        self.effect = damage
        self.owner = owner

    @abc.abstractmethod
    def action(self, posx, posy):
        return

    @abc.abstractmethod
    def enhance(self):
        return

    def getEffect(self):
        return self.effect

    def getRange(self):
        return self.range


class Axe(Weapon):
    AXE_RANGE = 1
    AXE_INIT_DAMAGE = 40

    def __init__(self, owner):
        super(Axe, self).__init__(self.AXE_RANGE, self.AXE_INIT_DAMAGE, owner)
        pass

    def enhance(self):
        self.effect += 10

    def action(self, posx, posy):
        print("You are using axe attacking "), posx,  posy, (".")
        if self.owner.pos.distance(posx, posy) <= self.range:
            player = self.owner.game.getPlayer(posx, posy)

            if player is not None:
                if isinstance(player, Human):
                    player.decreaseHealth(self.effect)
                else:
                    print("You cannot attack the same race!")

            else:
                print("Our of reach.")


class Rifle(Weapon):
    RIFLE_RANGE = 4
    RIFLE_INIT_DAMAGE = 10
    AMMO_LIMIT = 6
    AMMO_RECHARGE = 3

    def __init__(self, owner):
        super(Rifle, self). __init__(self.RIFLE_RANGE, self.RIFLE_INIT_DAMAGE, owner)
        self.ammo = self.AMMO_LIMIT

    def enhance(self):
        if self.AMMO_LIMIT <= (self.ammo + self.AMMO_RECHARGE):
            self.ammo = self.AMMO_LIMIT
        else:
            self.ammo = self.ammo + self.AMMO_RECHARGE

    def action(self, posx, posy):
        print("You are using rifle attacking "), posx, posy, (".")
        print("Type how many ammos you want to use.")
        ammoToUse = input()
        if ammoToUse > self.ammo:
            print("You don't have that ammos.")
            return
        if self.owner.pos.distance(posx, posy) <= self.range:
            player = self.owner.game.getPlayer(posx, posy)
            if player is not None:
                if isinstance(player, Chark):
                    player.decreaseHealth(self.effect * ammoToUse)
                    self.ammo -= ammoToUse
                else:
                    print("You cannot attack the same race!")
            else:
                print("Out of reach.")

    def getAmmo(self):
        return self.ammo


class Player(object):
#    equipment = Weapon()

    def __init__(self, healthCap, mob, posx, posy, index, game):
        self.MOBILITY = mob
        self.health = healthCap
        self.healthCap = healthCap
        self.pos = Pos(posx, posy)
        self.index = index
        self.game = game

    def getPos(self):
        return self.pos

    def teleport(self):
        randx = random.randint(0, 9)
        randy = random.randint(0, 9)
        while self.game.positionOccupied(randx, randy):
            randx = random.randint(0, 9)
            randy = random.randint(0, 9)
        self.pos.setPos(randx, randy)

    def increaseHealth(self, h):
        if self.health <= 0:
            button = True
        else:
            button = False
        self.health += h
        if self.health >= 0:
            if button == True:
                self.myString = self.myString[:1] + str(self.index)
        if self.health >= 80:
            self.health = self.healthCap

    def decreaseHealth(self, h):
        self.health -= h
        if self.health <= 0:
            self.myString = "C" + self.myString[:1]

    def getName(self):
        return self.myString

    def askForMove(self):
        # print general information
        print("Your health is "), self.health, (". Your position is "), self.pos.getX(), self.pos.getY(),\
            (". Your mobility is "), self.MOBILITY, (".")
        print("You now have following options: ")
        print("1. Move")
        print("2. Attack")
        print("3. End tne turn")
        a = input()
        if a == 1:
            print("Specify your target position (Input 'x y').")
            posx, posy = map(int, raw_input().split())
            if self.pos.distance(posx, posy) > self.MOBILITY:
                print("Beyond your reach. Staying still.")
            elif self.game.positionOccupied(posx, posy):
                print("Position occupied. Cannot move there.")
            else:
                self.pos.setPos(posx, posy)
                self.game.printBoard()
                print("You can now \n1.attack\n2.End the turn")
                k = input()
                if k == 1:
                    print("Input position to attack. (Input 'x y')")
                    attx, atty = map(int, raw_input().split())
                    self.equipment.action(attx, atty)
        elif a == 2:
            print("Input position to attack.")
            attx, atty = map(int, raw_input().split())
            self.equipment.action(attx, atty)

        elif a == 3:
            return

    def askForMovehealer(self):
        # print general information
        print("Your health is "), self.health, (". Your position is "), self.pos.getX(), self.pos.getY(),\
            (". Your mobility is "), self.MOBILITY, (".")
        print("You now have following options: ")
        print("1. Move")
        print("2. Heal")
        print("3. End tne turn")
        a = input()
        if a == 1:
            print("Specify your target position (Input 'x y').")
            posx, posy = map(int, raw_input().split())
            if self.pos.distance(posx, posy) > self.MOBILITY:
                print("Beyond your reach. Staying still.")
            elif self.game.positionOccupied(posx, posy):
                print("Position occupied. Cannot move there.")
            else:
                self.pos.setPos(posx, posy)
                self.game.printBoard()
                print("You can now \n1.Heal\n2.End the turn")
                k = input()
                if k == 1:
                    print("Input position to Heal. (Input 'x y')")
                    attx, atty = map(int, raw_input().split())
                    self.equipment.action(attx, atty)
        elif a == 2:
            print("Input position to Heal.")
            attx, atty = map(int, raw_input().split())
            self.equipment.action(attx, atty)

        elif a == 3:
            return

class Human(Player):
    def __init__(self, posx, posy, index, game):
        super(Human, self).__init__(80, 2, posx, posy, index, game)
        self.index = index
        self.myString = 'H' + str(index)
        if index == (self.game.n/2) -1:
            self.equipment = Wand(self)
        else:
            self.equipment = Rifle(self)

    def teleport(self):
        super(Human, self).teleport()
        self.equipment.enhance()

    def distance(self, posx, posy):
        pass

    def askForMove(self):
        if self.index == (self.game.n/2) -1:
            print("You are a human "), self.myString, (" using Wand. (Range "), self.equipment.getRange(), \
                (", Heal per shot: "), self.equipment.getEffect(), (")")
            super(Human, self).askForMovehealer()
        else:
            print("You are a human "), self.myString, (" using Rifle. (Range "), self.equipment.getRange(), \
                (", Ammo #: "), self.equipment.getAmmo(), (", Damage per shot: "), self.equipment.getEffect(), (")")
            super(Human, self).askForMove()


class Chark(Player):
    def __init__(self, posx, posy, index, game):
        super(Chark, self).__init__(100, 4, posx, posy, index, game)
        self.index = index
        self.myString = "C" + str(index)
        if index == self.game.n/2 - 1:
            self.equipment = Wand(self)
        else:
            self.equipment = Axe(self)

    def teleport(self):
        super(Chark, self).teleport()
        self.equipment.enhance()

    def askForMove(self):
        if self.index == self.game.n/2 - 1:
            print("You are a Chark "), self.myString, (" using Wand. (Range "), self.equipment.getRange(), \
                (", Heal per shot: "), self.equipment.getEffect(), (")")
            super(Chark, self).askForMovehealer()
        else:
            print("You are a Chark "), self.myString, (" using Axe. (Range "), self.equipment.getRange(), \
                (", Damage: "), self.equipment.getEffect(), (")")
            super(Chark, self).askForMove()


class Obstacle(object):
    def __init__(self, posx, posy, index, game):
        self.pos = Pos(posx, posy)
        self.index = index
        self.game = game

    def getPos(self):
        return self.pos

    def teleport(self):
        randx = random.randint(0, 9)
        randy = 10 - randx - 1
        while self.game.positionOccupied(randx, randy):
            randx = random.randint(0, 9)
            randy = 10 - randx - 1
        self.pos.setPos(randx, randy)


game = SurvivalGame()
game.init()
game.gameStart()