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

package Gpu;
use Task;
sub new {
  my $class = shift @_;
  my $time = 0;
  my $state = 0;
  my $task = 0;
  my $id = shift @_;
  my $object = bless {"time"=>$time,"state"=>$state,"task"=>$task,"id"=>$id}, $class;
  return $object;
}

sub assign_task {#input the task into this gpu,then the state will busy and time = 0
  my $self = shift @_;
  $self->{task} = shift @_;
  $self->{state} = 1;
  $self->{time} = 0;
}

sub release {# when the gpu time == the task time everything will reset to 0
  my $self = shift @_;
  $self->{task} = 0;
  $self->{time} = 0;
  $self->{state} = 0;
}

sub execute_one_time {#the gpu time will add up one
  my $self = shift @_;
  $self->{time} = $self->{time} + 1;
}
#return functions
sub id{
  my $self = shift @_;
  return $self->{id};
}

sub state{
  my $self = shift @_;
  return $self->{state};
}

sub task{
  my $self = shift @_;
  return $self->{task};
}

sub time{
  my $self = shift @_;
  return $self->{time}
}

return 1;
