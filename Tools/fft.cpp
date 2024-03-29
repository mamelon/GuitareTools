#include "fft.h"

#define signum(i) (i < 0 ? -1 : i == 0 ? 0 : 1)
#define PI	3.141592653589
#define PI8 0.392699081698724 /* PI / 8.0 */
#define RT2 1.4142135623731  /* sqrt(2.0) */
#define IRT2 0.707106781186548  /* 1.0/sqrt(2.0) */

static void FR2TR(int, double*, double*);
static void FR4TR(int, int, double*, double*, double*, double*);
static void FORD1(int, double*);
static void FORD2(int, double*);
static int fastlog2(int n);

int Fft::fastpurelog2(int n)
{
    int power = 0;

    if ((n < 2) || (n & 1)) return 0;
    while(power <= 32)
    {
        n >>= 1;
        power++;
        if (n & 1)
        {
            return (n > 1) ? 0 : power;
        }
    }
    return(0);
}

int Fft::_FFT(double b[], int n)
{
    double fn;
    int i, in, nn, n2pow, n4pow;

    if((n2pow = fastpurelog2(n)) <= 0) return 0;
    fn = (double)n;
    n4pow = n2pow / 2;

    /* radix 2 iteration required; do it now */
    if (n2pow % 2)
    {
        nn = 2;
        in = n / nn;
        FR2TR(in, b, b + in );
    }
    else nn = 1;

    /* perform radix 4 iterations */
    for(i = 1; i <= n4pow; i++)
    {
        nn *= 4;
        in = n / nn;
        FR4TR(in, nn, b, b + in, b + 2 * in, b + 3 * in);
    }

    /* perform inplace reordering */
    FORD1(n2pow, b);
    FORD2(n2pow, b);

    return 1;
}

/* radix 2 subroutine */
void Fft::FR2TR(int in, double*b0, double *b1)
{
    int k;
    double t;
    for (k = 0; k < in; k++)
    {
        t = b0[k] - b1[k];
        b0[k] += b1[k];
        b1[k] = t;
    }
}

/* radix 4 subroutine */
void Fft::FR4TR(int in, int nn, double *b0, double *b1, double *b2, double* b3)
{
  double arg, piovn, th2;
  double *b4 = b0, *b5 = b1, *b6 = b2, *b7 = b3;
  double t0, t1, t2, t3, t4, t5, t6, t7;
  double r1, r5, pr, pi;
  double c1, c2, c3, s1, s2, s3;

  int j, k, jj, kk, jthet, jlast, ji, jl, jr, int4;
  int L[16], L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13, L14, L15;
  int j0, j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14;
  int k0, kl;

  L[1] = nn / 4;
  for(k = 2; k < 16; k++) {  /* set up L's */
    switch (signum(L[k-1] - 2)) {
    case -1:
      L[k-1]=2;
    case 0:
      L[k]=2;
      break;
    case 1:
      L[k]=L[k-1]/2;
    }
  }

  L15=L[1]; L14=L[2]; L13=L[3]; L12=L[4]; L11=L[5]; L10=L[6]; L9=L[7];
  L8=L[8];  L7=L[9];  L6=L[10]; L5=L[11]; L4=L[12]; L3=L[13]; L2=L[14];
  L1=L[15];

  piovn = double(PI / nn);
  ji=3;
  jl=2;
  jr=2;

  for(j1=2;j1<=L1;j1+=2)
  for(j2=j1;j2<=L2;j2+=L1)
  for(j3=j2;j3<=L3;j3+=L2)
  for(j4=j3;j4<=L4;j4+=L3)
  for(j5=j4;j5<=L5;j5+=L4)
  for(j6=j5;j6<=L6;j6+=L5)
  for(j7=j6;j7<=L7;j7+=L6)
  for(j8=j7;j8<=L8;j8+=L7)
  for(j9=j8;j9<=L9;j9+=L8)
  for(j10=j9;j10<=L10;j10+=L9)
  for(j11=j10;j11<=L11;j11+=L10)
  for(j12=j11;j12<=L12;j12+=L11)
  for(j13=j12;j13<=L13;j13+=L12)
  for(j14=j13;j14<=L14;j14+=L13)
  for(jthet=j14;jthet<=L15;jthet+=L14)
    {
      th2 = double(jthet - 2);
      if(th2<=0.0)
    {
      for(k=0;k<in;k++)
        {
          t0 = b0[k] + b2[k];
          t1 = b1[k] + b3[k];
          b2[k] = b0[k] - b2[k];
          b3[k] = b1[k] - b3[k];
          b0[k] = t0 + t1;
          b1[k] = t0 - t1;
        }
      if(nn-4>0)
        {
          k0 = in*4 + 1;
          kl = k0 + in - 1;
          for (k=k0;k<=kl;k++)
        {
          kk = k-1;
          pr = double(IRT2 * (b1[kk]-b3[kk]));
          pi = double(IRT2 * (b1[kk]+b3[kk]));
          b3[kk] = b2[kk] + pi;
          b1[kk] = pi - b2[kk];
          b2[kk] = b0[kk] - pr;
          b0[kk] = b0[kk] + pr;
        }
        }
    }
      else
    {
      arg = th2*piovn;
      c1 = cosf(arg);
      s1 = sinf(arg);
      c2 = c1*c1 - s1*s1;
      s2 = c1*s1 + c1*s1;
      c3 = c1*c2 - s1*s2;
      s3 = c2*s1 + s2*c1;

      int4 = in*4;
      j0=jr*int4 + 1;
      k0=ji*int4 + 1;
      jlast = j0+in-1;
      for(j=j0;j<=jlast;j++)
        {
          k = k0 + j - j0;
          kk = k-1; jj = j-1;
          r1 = b1[jj]*c1 - b5[kk]*s1;
          r5 = b1[jj]*s1 + b5[kk]*c1;
          t2 = b2[jj]*c2 - b6[kk]*s2;
          t6 = b2[jj]*s2 + b6[kk]*c2;
          t3 = b3[jj]*c3 - b7[kk]*s3;
          t7 = b3[jj]*s3 + b7[kk]*c3;
          t0 = b0[jj] + t2;
          t4 = b4[kk] + t6;
          t2 = b0[jj] - t2;
          t6 = b4[kk] - t6;
          t1 = r1 + t3;
          t5 = r5 + t7;
          t3 = r1 - t3;
          t7 = r5 - t7;
          b0[jj] = t0 + t1;
          b7[kk] = t4 + t5;
          b6[kk] = t0 - t1;
          b1[jj] = t5 - t4;
          b2[jj] = t2 - t7;
          b5[kk] = t6 + t3;
          b4[kk] = t2 + t7;
          b3[jj] = t3 - t6;
        }
      jr += 2;
      ji -= 2;
      if(ji-jl <= 0)
      {
        ji = 2*jr - 1;
        jl = jr;
      }
    }
    }
}

/* an inplace reordering subroutine */
void Fft::FORD1(int m, double *b)
{
    int j, k = 4, kl = 2, n = 1 << m;
    double t;

    for(j = 4; j <= n; j += 2)
    {
        if (k > j)
        {
            t = b[j-1];
            b[j-1] = b[k-1];
            b[k-1] = t;
        }
        k -= 2;
        if (k <= kl)
        {
            k = 2*j;
            kl = j;
        }
    }
}

/*  the other inplace reordering subroutine */
void Fft::FORD2(int m, double *b)
{
  double t;

  int n = 0x1<<m, k, ij, ji, ij1, ji1;

  int l[16], l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15;
  int j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14;


  l[1] = n;
  for(k=2;k<=m;k++) l[k]=l[k-1]/2;
  for(k=m;k<=14;k++) l[k+1]=2;

  l15=l[1];l14=l[2];l13=l[3];l12=l[4];l11=l[5];l10=l[6];l9=l[7];
  l8=l[8];l7=l[9];l6=l[10];l5=l[11];l4=l[12];l3=l[13];l2=l[14];l1=l[15];

  ij = 2;

  for(j1=2;j1<=l1;j1+=2)
  for(j2=j1;j2<=l2;j2+=l1)
  for(j3=j2;j3<=l3;j3+=l2)
  for(j4=j3;j4<=l4;j4+=l3)
  for(j5=j4;j5<=l5;j5+=l4)
  for(j6=j5;j6<=l6;j6+=l5)
  for(j7=j6;j7<=l7;j7+=l6)
  for(j8=j7;j8<=l8;j8+=l7)
  for(j9=j8;j9<=l9;j9+=l8)
  for(j10=j9;j10<=l10;j10+=l9)
  for(j11=j10;j11<=l11;j11+=l10)
  for(j12=j11;j12<=l12;j12+=l11)
  for(j13=j12;j13<=l13;j13+=l12)
  for(j14=j13;j14<=l14;j14+=l13)
  for(ji=j14;ji<=l15;ji+=l14)
  {
    ij1 = ij-1; ji1 = ji - 1;
    if(ij-ji<0)
    {
      t = b[ij1-1];
      b[ij1-1]=b[ji1-1];
      b[ji1-1] = t;
      t = b[ij1];
      b[ij1]=b[ji1];
      b[ji1] = t;
    }
    ij += 2;
  }
}



int Fft::fastlog2(int n)
{
    int num_bits, power = 0;

    if ((n < 2) || (n % 2 != 0)) return(0);
    num_bits = sizeof(int) * 8;	/* How big are ints on this machine? */

    while(power <= num_bits) {
    n >>= 1;
    power += 1;
    if (n & 0x01) {
        if (n > 1)	return(0);
        else return(power);
    }
    }
    return(0);
}
