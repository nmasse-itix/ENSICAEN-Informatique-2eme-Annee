program while1;
var var1        : integer;
begin
   var1 := 10;
   while (var1 * 2) > 0 do
   begin
     var1 := var1 - 1;
     printf('%d\n', var1);
   end;
end.
