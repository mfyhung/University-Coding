=pod
∗ CSCI3180 Principles of Programming Languages ∗
∗ --- Declaration --∗ ∗ I declare that the assignment here submitted is original except for source
∗ material explicitly acknowledged. I also acknowledge that I am aware of
∗ University policy and regulations on honesty in academic work, and of the
∗ disciplinary guidelines and procedures applicable to breaches of such policy
∗ and regulations, as contained in the website
∗ http://www.cuhk.edu.hk/policy/academichonesty/
∗ Assignment 3
∗ Name : Hung Fan Yan
∗ Student ID : 1155083147
∗ Email Addr : 1155083147@link.cuhk.edu.hk
=cut

use strict;
use warnings;

package Game;
use MannerDeckStudent;
use Player;

sub new {
	my $class = shift @_;
	my @player_object = ();#the player object array
	my $player_object_ref = \@player_object; #make a reference in order to pass to another function.
	my @stack = (); #the stack array
	my $stackref = \@stack;#stack reference
	my $deck = MannerDeckStudent->new(); #initalize the deck object to get the card to the players.
	my $players_name = 0; #get the players name from the main function and initalize to the object array
	my $counter = 0;# for count the game turns
	my $userremain;# for count the user remain
	my $object = bless{"player_object_ref"=>$player_object_ref, "deck"=>$deck, "players_name"=>$players_name,"stackref"=>$stackref,"counter"=>$counter,"userremain"=>$userremain},$class;
	return $object;
}

sub set_players {
	my $self = shift @_;
	$self->{players_name} = shift @_; #get the reference of the name from the main function.
	return 1;
}

sub getReturn {
	my $self = shift @_;
	my $new_ele = shift @_; #get the new element from the start function.
	my $count = (scalar @{$self->{stackref}}) - 1;
	if ($new_ele eq "J"){#the situation when the card is J, if the stack is 0, then it remain there, if it is not it get all the cards from the stack
			if ($count == 0){
				return 0;
			}
			else{
			return $count;
		}
	}
	for my $b(0..$count-1){
		if ((@{$self->{stackref}}[$b]) eq $new_ele){ #if the new element is not equal to J, check is it have the same element in the stack and return the times the stack array should be pop.
					return $count - $b;
				}
	}
	return 0;
}

sub showCards {
	my $self = shift @_;
	return @{$self->{stackref}};
}

sub start_game {
	my $self = shift @_;
	($self->{deck})->shuffle();#shuffle the deck 1 times
	if (52 % (scalar @{$self->{players_name}}) != 0){# checking, if the player numbers is not equal to 2 4 or 13 it will print out the warning and return.
		print "Error: cards' number 52 can not be divided by players number ",(scalar @{$self->{players_name}}),"!";
		return 1;
	}
	my @ret = ($self->{deck})->AveDealCards(scalar @{$self->{players_name}});# get the array of the different player deck
	for ($a = 0 ; $a < (scalar @{$self->{players_name}}); $a = $a +1){#give the above array to the object user
		my $defobj = Player->new(@{$self->{players_name}}[$a], $ret[$a]);
		push @{$self->{player_object_ref}}, $defobj;
	}
	print "There ",(scalar @{$self->{players_name}})," players in the game:\n";
	print join " ",@{$self->{players_name}},"\n\n";
	print "Game Begin!\n\n";
	while (1){# it will keep loop until only one player left
		for ($a = 0;$a < scalar (@{$self->{player_object_ref}}); $a = $a +1){# it will loop for the number of player times
			print join ' ',"Player",(@{$self->{player_object_ref}}[$a])->{name},"has",((@{$self->{player_object_ref}}[$a])->numCards()),"cards before deal.\n";
			print "===== Before player's deal====\n";
			print join ' ',$self->showCards();
			print "\n===================================\n";
			my $deal = (@{$self->{player_object_ref}}[$a])->dealCards();#get the deal card from the user and push it to the stack array
			push @{$self->{stackref}},$deal;
		if ($self->getReturn($deal)!= 0){
			for my $c(0..$self->getReturn($deal)){#get the card back when there are the same card in the stack of it or it deal a J
					my $recard = pop (@{$self->{stackref}});
					(@{$self->{player_object_ref}}[$a])->getCards($recard);
				}
			}
			print join ' ',(@{$self->{player_object_ref}}[$a])->{name},"==> card",$deal;
			print "\n===== After player's deal====\n";
			print join " ",$self->showCards();
			print "\n===================================\n";
			print join ' ',"Player",(@{$self->{player_object_ref}}[$a])->{name},"has",((@{$self->{player_object_ref}}[$a])->numCards()),"cards after deal.\n\n";
			#for my $c(0..scalar(@{$self->{player_object_ref}})-1){
				if ((@{$self->{player_object_ref}}[$a])->numCards() == 0){
					print "Player ",(@{$self->{player_object_ref}}[$a])->{name}," has no card, out!\n\n";
					splice (@{$self->{player_object_ref}},$a,1);# if that array numcard is 0, then remove that object from the array.
					$a = $a +1;#
				}
			#}
		#	print @{$self->{player_object_ref}};
		$self->{userremain} = scalar (@{$self->{player_object_ref}});
		if ($self->{userremain} == 1){
			last;
		}
	}
		$self->{counter} = $self->{counter} + 1;
		if ($self->{userremain} == 1){
			print "Winner is ",@{$self->{player_object_ref}}[0]->{name}, " in game ",$self->{counter};
			last;
	}
	}
}
return 1;
