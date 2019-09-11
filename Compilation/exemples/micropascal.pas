program toto;
var i		    : integer;
   k,variablelongue : integer;
begin
   i:=20;
   variablelongue:=-10;
   k:=i+2*3+4;
   variablelongue:=pow(2,3);
   if (NOT (1>2)) then i:=20;
   
   while (i> 10) do
   begin
      printf('i = %d\n', i+3);
      if (i=2) then puts('i=2');
      i:=i-1;
   end;
end.
