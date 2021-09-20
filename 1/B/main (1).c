#include <stdio.h>

int main()
{
     long long a, b;
FILE *in, *out;
in = fopen("aplusbb.in", "r");
out = fopen("aplusbb.out", "w");
fscanf(in, "%lli", &a);
fscanf(in, "%lli", &b);
fprintf(out, "%lli", a + b*b);

fclose(in);
fclose(out);
return 0;
}