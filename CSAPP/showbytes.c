void showbytes(unsigned char * s, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++)
	{
		printf(" %.2x",s[i]);
	}
	printf("\n");
}
