#include<qauadmath.h> // can be found in the gfortran package
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__float128 rad2deg(__float128 rad){
    return (180.0/M_PIq) * rad;
}

__float128 deg2rad(__float128 deg){
    return (M_PIq/180.0Q) * deg;
}

void printResult(__float128 result){
  int  prec = 20;
  int  width = 46;
  char buf[128];
  int n = quadmath_snprintf (NULL, 0, "%+-#46.*Qe", prec, result );
  if (n > -1)
  {
    char *str = malloc (n + 1);
    if (str)
    {
      quadmath_snprintf (str, n + 1, "%+-#46.*Qe", prec, result );
      printf ("%s\n", str);
    }
    free (str);
  }
}

int main(int argc, char **argv){
  __float128 deg = 0.0Q;
  __float128 rad = 0.0Q;
  if (argc == 3 && strcmp(argv[1],"-d") == 0){
    rad = strtoflt128(argv[2],NULL);
    deg = rad2deg(rad);
    printResult(deg);
    return 0;
  }
  if (argc == 3 && strcmp(argv[1],"-r") == 0){
    deg = strtoflt128(argv[2],NULL);
    rad = deg2rad(deg);
    printResult(rad);
    return 0;
  }
  printf("Please use the form ./is_close -d 2.12 or ")
  return 1;
}
