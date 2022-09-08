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

package Server;
use Gpu;
use Task;
our $task;
our $gpu;
sub new {#make the array for record the gpu object and the wait list and their reference in order to pass to another place
  my $class = shift @_;
  my $gpus_amount = shift @_;
  my @gpus = ();
  my $gpus_ref = \@gpus;
  my @waitq = ();
  my $waitq_ref = \@waitq;
  for $a(0..$gpus_amount-1){
    my $gpu = Gpu->new($a);
    push @{$gpus_ref},$gpu;
  }
  my $object = bless {"gpus_ref"=>$gpus_ref,"waitq_ref"=>$waitq_ref,"gpus_amount"=>$gpus_amount}, $class;
  return $object;
}
#standard function cannot be changed
sub task_info {
	return "task(user: ".$task->name().", pid: ".$task->pid().", time: ".$task->time().")";
}
sub task_attr {
	return $task->name(), $task->pid(), $task->time();
}
sub gpu_info {
	return "gpu(id: ".$gpu->id().")";
}
sub submit_task {#submit the task to the gpu
  my $self = shift @_;
  my $name = shift @_;
  my $time = shift @_;
  my $check = 0;
  local $task = Task->new($name,$time);#assign the task
  for $a(0..($self->{gpus_amount}-1)){#check the ideal gpu, if we found that the task will put in that object and break the loop
    if(@{$self->{gpus_ref}}[$a]->state() == 0){
      local $gpu = @{$self->{gpus_ref}}[$a];
      @{$self->{gpus_ref}}[$a]->assign_task($task);
      print &task_info();
      print " => ",&gpu_info();
      print "\n";
      $check = 1;
      last;
    }
  }
  if ($check != 1){#if the above function didn't fulfil which mean it cannot find a ideal gpu then put the task into the waiting queue
    push @{$self->{waitq_ref}},$task;
    print "\n";
    print &task_info();
    print " => waiting queue\n";
  }
}
sub deal_waitq {#a function for shift a wait queue and push into the gpu
  my $self = shift @_;
  return shift @{$self->{waitq_ref}};
}
sub kill_task {
  my $self = shift @_;
  my $name = shift @_;
  my $pid = shift @_;
  my $check = 0;
  for $a(0..$self->{gpus_amount}-1){#check all the gpu and find out the related name and pid, if it match, it will kill the task
    if ($self->{gpus_ref}[$a]->state() == 1){
      if (($self->{gpus_ref}[$a]->task())->name() eq $name and ($self->{gpus_ref}[$a]->task())->pid() == $pid){
        local $task = ($self->{gpus_ref}[$a]->task());
        print "user ",$name," kill ";
        print &task_info;
        print "\n";
        $check = 1;
        ($self->{gpus_ref}[$a])->release();
        if ((scalar @{$self->{waitq_ref}}) != 0){
          local $task = $self->deal_waitq();
          local $gpu = @{$self->{gpus_ref}}[$a];
          @{$self->{gpus_ref}}[$a]->assign_task($task);
          print &task_info()," ";
          print " => ",&gpu_info();
          print "\n";
        }
      }
    }
  }

  if ((scalar @{$self->{waitq_ref}}) != 0){#if can't find that task in the gpu then check them in the wait queue and kill it
    for $b(0..(scalar @{$self->{waitq_ref}})-1){
      if ((@{$self->{waitq_ref}}[$b]->name() eq $name) and (@{$self->{waitq_ref}}[$b]->pid() == $pid)){
        local $task = ($self->{waitq_ref}[$b]);
        print "user ",$name," kill ";
        print &task_info;
        print "\n";
        $check = 1;
        splice (@{$self->{waitq_ref}},$b,1); #we cannot use the deal_waitq function here, because we cannot ensure that the function will be the firest element in the array
        last;
      }
    }
  }
  if ($check == 0 ){# if the above two function cannot be fulfil then print out the failure message
    print "user ",$name," kill task(pid ",$pid,")";
    print "fail ";
    print "\n";
  }
}
sub execute_one_time {#call the gpu function excute one time, and check any one gpu time is equal to their task time, if the situation occur, then print out the message,release the gpu and put a new task in the waiting list into that gpu
  my $self = shift @_;
  print "excute_one_time.. \n";
  for $a(0..($self->{gpus_amount}-1)){
    if ($self->{gpus_ref}[$a]->state() == 1){
      @{$self->{gpus_ref}}[$a]->execute_one_time();
      if ((($self->{gpus_ref}[$a]->task())->time()) eq (@{$self->{gpus_ref}}[$a]->time())){
        local $gpu = @{$self->{gpus_ref}}[$a];
        print "task in ";
        print &gpu_info," finished\n";
        ($self->{gpus_ref}[$a])->release();
        if ((scalar @{$self->{waitq_ref}}) != 0){
          local $task = $self->deal_waitq();
          local $gpu = @{$self->{gpus_ref}}[$a];
          @{$self->{gpus_ref}}[$a]->assign_task($task);
          print &task_info();
          print " => ",&gpu_info();
          print "\n";
        }
      }
    }
  }
}
sub show {#show the situation
  my $self = shift @_;
  print "==============Server Message================\n";
  print join " ","gpu-id","state","user","pid","tot-time","cur_time","\n";
  for $a(0..($self->{gpus_amount}-1)){
    local $task = @{$self->{gpus_ref}}[$a]->task();
    print "   ",$a,"   ";
    if (@{$self->{gpus_ref}}[$a]->state() == 0){
      print "idle\n";
    }
    else{
      print "busy  ";
      print join "    ",&task_attr();
      print "      ",@{$self->{gpus_ref}}[$a]->time(),"\n";
    }
  }
  if ((scalar @{$self->{waitq_ref}}) != 0){
    print "       wait  ";
    for $b(0..(scalar @{$self->{waitq_ref}})-1){
      local $task = @{$self->{waitq_ref}}[$b];
      print join "    ",&task_attr();
    }
    print "\n";
  }
  print "============================================\n\n";
}
return 1;
