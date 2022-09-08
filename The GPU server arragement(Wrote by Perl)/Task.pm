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

package Task;
our $pid = -1;
sub new {
  my $class = shift @_;
  $pid = $pid +1;
  my $name = shift @_;
  my $time = shift @_;
  my $object = bless {"pid"=>$pid,"name"=>$name,"time"=>$time}
}
sub pid{
  my $self = shift @_;
  return $self->{pid};
}
sub name{
  my $self = shift @_;
  return $self->{name};
}
sub time{
  my $self = shift @_;
  return $self->{time};
}
return 1;
