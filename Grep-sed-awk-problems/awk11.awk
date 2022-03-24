BEGIN{
s=0;
}

{
	s = s + $2;
	nr_linii++;
}

END{
	print s/NR;
}
