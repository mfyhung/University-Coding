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

package Player;
sub new {
  my $class = shift @_;
  my $name = shift @_;
  my $cardref = shift @_;#get the name and bect for this object
  my $object = bless{"name"=>$name,"cardref" =>$cardref},$class;#bless
  return $object;
}

sub getCards {
  my $self = shift @_;
  my $add = shift @_;
push @{$self->{cardref}},$add;#get the value and input to the user deck array
}

sub dealCards {
  my $self = shift @_;
  return shift @{$self->{cardref}}; #deal the card to the stack
}

sub numCards {
  my $self = shift @_;
  return (scalar @{$self->{cardref}}); #return the number of cards
}

return 1;
