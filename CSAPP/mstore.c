long mult2(long a,long b);

void multstore(long a, long b,long* dest)
{
    long t=mult2(a,b);
    *dest=t;
}