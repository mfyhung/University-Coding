use strict;
use warnings;

package GPUManagementServer;
use Server;

my @try = ("1","2","3");
print @try,"\n";
print scalar @try;
splice @try,1,1;
print @try,"\n";
print scalar @try;
