#include <stdio.h>

int main()
{
int a, b;
FILE *in, *out;
in = fopen("aplusb.in", "r");
out = fopen("aplusb.out", "w");
fscanf(in, "%d", &a);
fscanf(in, "%d", &b);
fprintf(out, "%d", a + b);

fclose(in);
fclose(out);
return 0;
}