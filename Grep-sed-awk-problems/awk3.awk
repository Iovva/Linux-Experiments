{
if($1 ~ "^m")
	if($3 % 7 == 0)
		 print $5
}
