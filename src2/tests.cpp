#include "num.hpp"
#include "rat.hpp"
#include <assert.h>
#include <stdio.h>


#define a(x,y) (A[x][y])
#define b(x,y) (B[x][y])

/*
 *      a1  a2  a3 a4
 *      a2  a5  a6 a7
 *      a3  a6  a8 a9
 *      a4  a7  a9 a10
 */
#define a1 a(0, 0)
#define a2 a(0, 1)
#define a3 a(0, 2)
#define a4 a(0, 3)
#define a5 a(1, 1)
#define a6 a(1, 2)
#define a7 a(1, 3)
#define a8 a(2, 2)
#define a9 a(2, 3)
#define a10 a(3, 3)

#define b1 b(0, 0)
#define b2 b(0, 1)
#define b3 b(0, 2)
#define b4 b(0, 3)
#define b5 b(1, 1)
#define b6 b(1, 2)
#define b7 b(1, 3)
#define b8 b(2, 2)
#define b9 b(2, 3)
#define b10 b(3, 3)





#include    <math.h>
#ifndef M_PI
#define M_PI          3.14159265358979323846
#endif

/* epsilon surrounding for near zero values */

#define     EQN_EPS     1e-9
#define	    IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

#ifdef NOCBRT
#define     cbrt(x)     ((x) > 0.0 ? pow((double)(x), 1.0/3.0) : \
                          ((x) < 0.0 ? -pow((double)-(x), 1.0/3.0) : 0.0))
#endif

int SolveQuadric(double *c, double *s)
{
    double p, q, D;

    /* normal form: x^2 + px + q = 0 */

    p = c[ 1 ] / (2 * c[ 2 ]);
    q = c[ 0 ] / c[ 2 ];

    D = p * p - q;

    if (IsZero(D))
    {
	s[ 0 ] = - p;
	return 1;
    }
    else if (D < 0)
    {
	return 0;
    }
    else /* if (D > 0) */
    {
	double sqrt_D = sqrt(D);

	s[ 0 ] =   sqrt_D - p;
	s[ 1 ] = - sqrt_D - p;
	return 2;
    }
}


int SolveCubic(double *c, double *s)
{
    int     i, num;
    double  sub;
    double  A, B, C;
    double  sq_A, p, q;
    double  cb_p, D;

    /* normal form: x^3 + Ax^2 + Bx + C = 0 */

    A = c[ 2 ] / c[ 3 ];
    B = c[ 1 ] / c[ 3 ];
    C = c[ 0 ] / c[ 3 ];

    /*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

    sq_A = A * A;
    p = 1.0/3 * (- 1.0/3 * sq_A + B);
    q = 1.0/2 * (2.0/27 * A * sq_A - 1.0/3 * A * B + C);

    /* use Cardano's formula */

    cb_p = p * p * p;
    D = q * q + cb_p;

    if (IsZero(D))
    {
	if (IsZero(q)) /* one triple solution */
	{
	    s[ 0 ] = 0;
	    num = 1;
	}
	else /* one single and one double solution */
	{
	    double u = cbrt(-q);
	    s[ 0 ] = 2 * u;
	    s[ 1 ] = - u;
	    num = 2;
	}
    }
    else if (D < 0) /* Casus irreducibilis: three real solutions */
    {
	double phi = 1.0/3 * acos(-q / sqrt(-cb_p));
	double t = 2 * sqrt(-p);

	s[ 0 ] =   t * cos(phi);
	s[ 1 ] = - t * cos(phi + M_PI / 3);
	s[ 2 ] = - t * cos(phi - M_PI / 3);
	num = 3;
    }
    else /* one real solution */
    {
	double sqrt_D = sqrt(D);
	double u = cbrt(sqrt_D - q);
	double v = - cbrt(sqrt_D + q);

	s[ 0 ] = u + v;
	num = 1;
    }

    /* resubstitute */

    sub = 1.0/3 * A;

    for (i = 0; i < num; ++i)
	s[ i ] -= sub;

    return num;
}


int SolveQuartic(double *c, double *s)
{
    double  coeffs[ 4 ];
    double  z, u, v, sub;
    double  A, B, C, D;
    double  sq_A, p, q, r;
    int     i, num;

    /* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

    A = c[ 3 ] / c[ 4 ];
    B = c[ 2 ] / c[ 4 ];
    C = c[ 1 ] / c[ 4 ];
    D = c[ 0 ] / c[ 4 ];

    /*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

    sq_A = A * A;
    p = - 3.0/8 * sq_A + B;
    q = 1.0/8 * sq_A * A - 1.0/2 * A * B + C;
    r = - 3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D;

    if (IsZero(r))
    {
	/* no absolute term: y(y^3 + py + q) = 0 */

	coeffs[ 0 ] = q;
	coeffs[ 1 ] = p;
	coeffs[ 2 ] = 0;
	coeffs[ 3 ] = 1;

	num = SolveCubic(coeffs, s);

	s[ num++ ] = 0;
    }
    else
    {
	/* solve the resolvent cubic ... */

	coeffs[ 0 ] = 1.0/2 * r * p - 1.0/8 * q * q;
	coeffs[ 1 ] = - r;
	coeffs[ 2 ] = - 1.0/2 * p;
	coeffs[ 3 ] = 1;

	(void) SolveCubic(coeffs, s);

	/* ... and take the one real solution ... */

	z = s[ 0 ];

	/* ... to build two quadric equations */

	u = z * z - r;
	v = 2 * z - p;

	if (IsZero(u))
	    u = 0;
	else if (u > 0)
	    u = sqrt(u);
	else
	    return 0;

	if (IsZero(v))
	    v = 0;
	else if (v > 0)
	    v = sqrt(v);
	else
	    return 0;

	coeffs[ 0 ] = z - u;
	coeffs[ 1 ] = q < 0 ? -v : v;
	coeffs[ 2 ] = 1;

	num = SolveQuadric(coeffs, s);

	coeffs[ 0 ]= z + u;
	coeffs[ 1 ] = q < 0 ? v : -v;
	coeffs[ 2 ] = 1;

	num += SolveQuadric(coeffs, s + num);
    }

    /* resubstitute */

    sub = 1.0/4 * A;

    for (i = 0; i < num; ++i)
	s[ i ] -= sub;

    return num;
}

typedef struct {
	Rat  A0;
	Rat  A1;
	Rat  A2;
	Rat  A3;
	Rat  A4;
} Poly4;

void print_poly(Poly4 poly)
{
  std::string str;
  if(poly.A4!=0)
  {
    str += " ";
    if(poly.A4!=1)
    {
      std::vector<char> v;
      poly.A4.print(v);
      std::string aux(v.begin(), v.end());
      str += " ";
      str += aux;
    }
    str += "X^4";
  }
  if(poly.A3!=0)
  {
    str += " ";
    if(poly.A3!=1)
    {
      std::vector<char> v;
      poly.A3.print(v);
      std::string aux(v.begin(), v.end());
      str += aux;
    }
    str += "X^3";
  }
  if(poly.A2!=0)
  {
    str += " ";
    if(poly.A2!=1)
    {
      std::vector<char> v;
      poly.A2.print(v);
      std::string aux(v.begin(), v.end());
      str += aux;
    }
    str += "X^2";
  }
  if(poly.A1!=0)
  {
    str += " ";
    if(poly.A1!=1)
    {
      std::vector<char> v;
      poly.A1.print(v);
      std::string aux(v.begin(), v.end());
      str += aux;
    }
    str += "X";
  }
  if(poly.A0!=0)
  {
    str += " ";
    if(poly.A0!=1)
    {
      std::vector<char> v;
      poly.A0.print(v);
      std::string aux(v.begin(), v.end());
      str += aux;
    }
  }

  std::cout << str << std::endl;
}

double MajZero(Poly4 p)
{
  double r = 0.0;
  r = fmax(r, pow(abs(p.A3.to_double()/p.A4.to_double()), 1.0/1));
  r = fmax(r, pow(abs(p.A2.to_double()/p.A4.to_double()), 1.0/2));
  r = fmax(r, pow(abs(p.A1.to_double()/p.A4.to_double()), 1.0/3));
  r = fmax(r, pow(abs(p.A0.to_double()/p.A4.to_double()), 1.0/4));
  return 2.0*r;
}

double MinZero(Poly4 p)
{
  double r = 0.0;
  r = fmax(r, pow(abs(p.A0.to_double()/p.A0.to_double()), 1.0/1));
  r = fmax(r, pow(abs(p.A1.to_double()/p.A0.to_double()), 1.0/2));
  r = fmax(r, pow(abs(p.A2.to_double()/p.A0.to_double()), 1.0/3));
  r = fmax(r, pow(abs(p.A3.to_double()/p.A0.to_double()), 1.0/4));
  return 1.0/(2.0*r);
}

void prtRat(Rat rat)
{
      std::vector<char> v;
      rat.print(v);
      std::string aux(v.begin(), v.end());
      std::cout << aux << std::endl;
}

void prtNum(Num num)
{
      std::vector<char> v;
      num.print(v);
      std::string aux(v.begin(), v.end());
      std::cout << aux << std::endl;
}


double evalDouble(Poly4 poly, double val)
{
//  print_poly(poly);
 Rat tt = poly.A4*val*val*val*val+poly.A3*val*val*val+poly.A2*val*val+poly.A1*val+poly.A0;
prtRat(tt);
      std::cout << std::endl;
prtRat(poly.A4*val*val*val*val);
      std::cout << std::endl;
prtRat(poly.A4);
      std::cout << std::endl;
      std::cout << val*val*val*val << std::endl;
      std::cout << std::endl;

      std::vector<char> v;
      tt.print(v);
      std::string aux(v.begin(), v.end());
      std::cout << "zzzz " << aux << std::endl;
      std::cout << "xxxx " << tt.to_double() << std::endl;
  return (poly.A4*val*val*val*val+poly.A3*val*val*val+poly.A2*val*val+poly.A1*val+poly.A0).to_double();
}

Rat evalRal(Poly4 poly, Rat val)
{
  return poly.A4*val*val*val*val+poly.A3*val*val*val+poly.A2*val*val+poly.A1*val+poly.A0;
}

#define SIGN(x) (x>=0.0?1:-1)

void prt(int s)
{
  if(s==1)
    std::cout << "+";
  else
    std::cout << "-";
}

int variation(Poly4 *tab, int size, double val)
{
  int var = 0;
  double ret = evalDouble(tab[0], val);
  int s = SIGN(evalDouble(tab[0], val));
  prt(s);
  for(int i=1; i<size; i++)
  {
    double ze = evalDouble(tab[i], val);

    prt(SIGN(ze));

    if( SIGN(ze) == -s )
    {
      s = -s;
      var++;
    }
  } 
  std::cout << std::endl;
  return var;
}

int solve4(Poly4 poly, Poly4 *tab, int size)
{
  int n = 0;
  tab[n] = poly;

  n++;

  // Derivée
  tab[n] = poly;
  tab[n].A0 = tab[n].A1;
  tab[n].A1 = Rat(2, 1)*tab[n].A2;
  tab[n].A2 = Rat(3, 1)*tab[n].A3;
  tab[n].A3 = Rat(4, 1)*tab[n].A4;
  tab[n].A4 = Rat(0, 1);

  print_poly(tab[n]);
  n++;
/*
  if( tab[0].A4 != 0.0 )
  {
    Poly4 p = tab[0];
   print_poly(p);
    tab[n].A0 = -(p.A0-p.A1*p.A3/(Rat(16, 1)*p.A4));
    tab[n].A1 = -(Rat(3, 4)*p.A1-Rat(1,8)*p.A2*p.A3/p.A4);
    tab[n].A2 = -(p.A2*Rat(1, 2)-Rat(3, 16)*p.A3/p.A4);
    tab[n].A3 = -(Rat(0, 1));
    tab[n].A4 = -(Rat(0, 1));
   print_poly(tab[n]);
    n++; 
  }
*/
  if( tab[n-2].A4 != 0.0 )
  {
    Poly4 p = tab[n-2];
    Poly4 l = tab[n-1];
   print_poly(p);
   
   print_poly(l);

    tab[n].A0 = -(p.A0-p.A1*p.A3/(Rat(16, 1)*p.A4));
    tab[n].A1 = -(Rat(3, 4)*p.A1-Rat(1,8)*p.A2*p.A3/p.A4);
    tab[n].A2 = -(p.A2*Rat(1, 2)-Rat(3, 16)*p.A3/p.A4);
    tab[n].A2 = -((p.A2-l.A1*p.A4/l.A3)-(p.A3-p.A4*l.A2/l.A3)*l.A2/l.A3);
    tab[n].A3 = -(Rat(0, 1));
    tab[n].A4 = -(Rat(0, 1));
   print_poly(tab[n]);
    n++; 
  }
  if( tab[n-2].A3 != 0.0 )
  {
    Poly4 p = tab[n-2];
    Poly4 l = tab[n-1];
   print_poly(p);
 
   print_poly(l);

    tab[n].A0 = -(p.A0-l.A0*(p.A2-p.A3*l.A1/l.A2)/l.A2);
    tab[n].A1 = -((p.A1-l.A0*p.A3/l.A2)-(p.A2-p.A3*l.A1/l.A2)*l.A1/l.A2);
    tab[n].A2 = Rat(0, 1);
    tab[n].A3 = Rat(0, 1);
    tab[n].A4 = Rat(0, 1);
   print_poly(tab[n]);
    n++; 
  }
  if( tab[n-2].A2 != 0.0 )
  {
    Poly4 p = tab[n-2];
    Poly4 l = tab[n-1];
   print_poly(p);
 
   print_poly(l);

    tab[n].A0 = -(p.A0-l.A0*(p.A1-p.A2*l.A0/l.A1)/l.A1);
    tab[n].A1 = Rat(0, 1);
    tab[n].A2 = Rat(0, 1);
    tab[n].A3 = Rat(0, 1);
    tab[n].A4 = Rat(0, 1);
   print_poly(tab[n]);
    n++; 
  }
  for(int i = 0; i<n; i++)
  {
    std::cout << i << " : ";
    print_poly(tab[i]);
  }
  return n;
}

int roots_rec(Poly4 *tab, int size, double left, double right)
{
  int var_left, var_right;
  var_right = variation(tab, size, right);
  var_left = variation(tab, size, left);
  int nbr_roots = var_left-var_right;
  switch (nbr_roots)
  {   
   case 0 :
      std::cout << "[" << left << "," << right << " ] Pas de solutions!" << std::endl;
      return 0;
   case 1 :
      std::cout << "[" << left << "," << right << " ] Une solution ici!" << std::endl;
      return 0;
   default :
    double mid = (right+left)/2;
    roots_rec(tab, size, left, mid);
    roots_rec(tab, size, mid, right);
   }
  return 0;
}

int roots(Poly4 poly)
{

  Poly4 tab[10];
  int nb = 0;
  nb = solve4(poly, tab, 10);
  std::cout << " nb = " << nb << std::endl;

  double maj_right = MajZero(poly);
  double maj_left = -MajZero(poly);
  int var_left, var_right;
  var_right = variation(tab, nb, MajZero(poly));
  var_left = variation(tab, nb, -MajZero(poly));
  int nbr_roots = var_left-var_right;
  if (nbr_roots==0)
     std::cout << "[" << maj_left << "," << maj_right << " ] Pas de solutions!" << std::endl;
  else
  { 
    double mid = (maj_right+maj_left)/2;
    roots_rec(tab, nb, maj_left, mid);
    roots_rec(tab, nb, mid, maj_right);
  }
}







void GetRational(double val)
{
    if (val == val+1) // Inf
        throw "Infinite Value";
    if (val != val) // NaN
        throw "Undefined Value";

    bool sign = false;
    Num enumerator = 0;
    Num denominator = 1;

    if (val < 0)
    {
        val = -val;
        sign = true;
    }

    while (val > 0)
    {
        unsigned int intVal = (unsigned int)val;
        val -= intVal;
        enumerator += intVal;
        val *= 2;
        enumerator *= 2;
        denominator *= 2;
    }

//    BigInt gcd = GCD(enumerator,denominator);
//    enumerator /= gcd;
//    denominator /= gcd;
 std::cout << "eeeeeeeeeeeeeeeee" << std::endl;


prtNum(enumerator);
prtNum(denominator);
 Rat r(enumerator,denominator);

prtRat(r);

/*
    Print(sign? "-":"+");
    Print(enumerator);
    Print("/");
    Print(denominator);
*/

    // Or simply return {sign,enumerator,denominator} as you wish
}






#include <iostream>
#include <valarray> 

using namespace std;

void as_fraction(double number, int cycles = 10, double precision = 5e-4){
    int sign  = number > 0 ? 1 : -1;
    number = number * sign; //abs(number);
    double new_number,whole_part;
    double decimal_part =  number - (int)number;
    int counter = 0;
    
    valarray<double> vec_1{double((int) number), 1}, vec_2{1,0}, temporary;
    
    while(decimal_part > precision & counter < cycles){
        new_number = 1 / decimal_part;
        whole_part = (int) new_number;
        
        temporary = vec_1;
        vec_1 = whole_part * vec_1 + vec_2;
        vec_2 = temporary;
        
        decimal_part = new_number - whole_part;
        counter += 1;
    }
    cout<<"x: "<< number <<"\tFraction: " << sign * vec_1[0]<<'/'<< vec_1[1]<<endl;
}












int main(){
{
   Rat A[4][4], B[4][4];

 a1 = 1;
 a2 = 2;
 a3 = 3;
 a4 = 4;
 a5 = 5;
 a6 = 6;
 a7 = 7;
 a8 = 8;
 a9 = 9;
 a10 = 10;

 b1 = 11;
 b2 = 12;
 b3 = 13;
 b4 = 14;
 b5 = 15;
 b6 = 16;
 b7 = 17;
 b8 = 18;
 b9 = 19;
 b10 = 110;
  
 std::cout << " " << a1.to_double() << " " << a2.to_double() << " " << a3.to_double() << " " << a4.to_double() << std::endl;
 std::cout << " " << a2.to_double() << " " << a5.to_double() << " " << a6.to_double() << " " << a7.to_double() << std::endl;
 std::cout << " " << a3.to_double() << " " << a6.to_double() << " " << a8.to_double() << " " << a9.to_double() << std::endl;
 std::cout << " " << a4.to_double() << " " << a7.to_double() << " " << a9.to_double() << " " << a10.to_double() << std::endl;
 std::cout << "----------------------" << std::endl; 
 std::cout << " " << b1.to_double() << " " << b2.to_double() << " " << b3.to_double() << " " << b4.to_double() << std::endl;
 std::cout << " " << b2.to_double() << " " << b5.to_double() << " " << b6.to_double() << " " << b7.to_double() << std::endl;
 std::cout << " " << b3.to_double() << " " << b6.to_double() << " " << b8.to_double() << " " << b9.to_double() << std::endl;
 std::cout << " " << b4.to_double() << " " << b7.to_double() << " " << b9.to_double() << " " << b10.to_double() << std::endl;
 

 Rat C, D, E, F, G, rr(1);


C=a3*a3*a7*a7-a1*a7*a7*a8+a4*a4*(a6*a6-a5*a8)-a10*(a3*a3*a5-Rat(2)*a2*a3*a6+a1*a6*a6+a2*a2*a8-a1*a5*a8)-Rat(2)*a2*a3*a7*a9+Rat(2)*a1*a6*a7*a9+a2*a2*a9*a9-a1*a5*a9*a9-Rat(2)*a4*(a3*a6*a7-a2*a7*a8-a3*a5*a9+a2*a6*a9);
//C=a3*a3*a7*a7-a1*a7*a7*a8+a4*a4*(a6*a6-a5*a8)-a10*(a3*a3*a5-Rat(2)*a2*a3*a6+a1*a6*a6+a2*a2*a8-a1*a5*a8)-Rat(2)*a2*a3*a7*a9+Rat(2)*a1*a6*a7*a9;

//+Rat(2)*a1*a6*a7*a9+a2*a2*a9*a9-a1*a5*a9*a9-Rat(2)*a4*(a3*a6*a7-a2*a7*a8-a3*a5*a9+a2*a6*a9);

//D=-a5*a9*a9*b1-a3*a3*a5*b10+Rat(2)*a2*a3*a6*b10-a1*a6*a6*b10-a2*a2*a8*b10+a1*a5*a8*b10-Rat(2)*a4*a6*a9*b2+Rat(2)*a2*a9*a9*b2+Rat(2)*a4*a5*a9*b3+Rat(2)*a4*a6*a6*b4-Rat(2)*a4*a5*a8*b4+Rat(2)*a3*a5*a9*b4-Rat(2)*a2*a6*a9*b4-a4*a4*a8*b5+Rat(2)*a3*a4*a9*b5-a1*a9*a9*b5+Rat(2)*a4*a4*a6*b6-Rat(2)*a2*a4*a9*b6-Rat(2)*a3*a4*a6*b7+Rat(2)*a2*a4*a8*b7-Rat(2)*a2*a3*a9*b7+Rat(2)*a1*a6*a9*b7-a4*a4*a5*b8-a7*a7*(a8*b1-Rat(2)*a3*b3+a1*b8)+a10*(-a6*a6*b1+a5*a8*b1-Rat(2)*a2*a8*b2-Rat(2)*a3*a5*b3-a3*a3*b5+a1*a8*b5+Rat(2)*a2*a3*b6+Rat(2)*a6*(a3*b2+a2*b3-a1*b6)-a2*a2*b8+a1*a5*b8)+Rat(2)*a3*a4*a5*b9-Rat(2)*a2*a4*a6*b9+Rat(2)*a2*a2*a9*b9-Rat(2)*a1*a5*a9*b9+Rat(2)*a7*(a4*a8*b2-a3*a9*b2-a2*a9*b3+a2*a8*b4-a3*a4*b6+a1*a9*b6+a3*a3*b7-a1*a8*b7+a2*a4*b8-a2*a3*b9+a6*(a9*b1-a4*b3-a3*b4+a1*b9));

D=-a5*a9*a9*b1-a3*a3*a5*b10+Rat(2)*a2*a3*a6*b10-a1*a6*a6*b10-a2*a2*a8*b10+a1*a5*a8*b10-Rat(2)*a4*a6*a9*b2+Rat(2)*a2*a9*a9*b2+Rat(2)*a4*a5*a9*b3+Rat(2)*a4*a6*a6*b4-Rat(2)*a4*a5*a8*b4+Rat(2)*a3*a5*a9*b4-Rat(2)*a2*a6*a9*b4-a4*a4*a8*b5+Rat(2)*a3*a4*a9*b5-a1*a9*a9*b5+Rat(2)*a4*a4*a6*b6-Rat(2)*a2*a4*a9*b6-Rat(2)*a3*a4*a6*b7+Rat(2)*a2*a4*a8*b7-Rat(2)*a2*a3*a9*b7+Rat(2)*a1*a6*a9*b7-a4*a4*a5*b8-a7*a7*(a8*b1-Rat(2)*a3*b3+a1*b8)+a10*(-a6*a6*b1+a5*a8*b1-Rat(2)*a2*a8*b2-Rat(2)*a3*a5*b3-a3*a3*b5+a1*a8*b5+Rat(2)*a2*a3*b6+Rat(2)*a6*(a3*b2+a2*b3-a1*b6)-a2*a2*b8+a1*a5*b8)+Rat(2)*a3*a4*a5*b9-Rat(2)*a2*a4*a6*b9+Rat(2)*a2*a2*a9*b9-Rat(2)*a1*a5*a9*b9+Rat(2)*a7*(a4*a8*b2-a3*a9*b2-a2*a9*b3+a2*a8*b4-a3*a4*b6+a1*a9*b6+a3*a3*b7-a1*a8*b7+a2*a4*b8-a2*a3*b9+a6*(a9*b1-a4*b3-a3*b4+a1*b9));

//E=-Rat(2)*a2*a8*b10*b2-a10*a8*b2*b2+a9*a9*b2*b2-Rat(2)*a7*a9*b2*b3+a7*a7*b3*b3+Rat(2)*a7*a8*b2*b4+a6*a6*(-b1*b10+b4*b4)+a10*a8*b1*b5-a9*a9*b1*b5-a3*a3*b10*b5+a1*a8*b10*b5-Rat(2)*a10*a3*b3*b5+Rat(2)*a4*a9*b3*b5-Rat(2)*a4*a8*b4*b5+Rat(2)*a3*a9*b4*b5+Rat(2)*a7*a9*b1*b6+Rat(2)*a2*a3*b10*b6+Rat(2)*a10*a3*b2*b6-Rat(2)*a4*a9*b2*b6+Rat(2)*a10*a2*b3*b6-Rat(2)*a4*a7*b3*b6-Rat(2)*a3*a7*b4*b6-Rat(2)*a2*a9*b4*b6-a1*a10*b6*b6+a4*a4*b6*b6-Rat(2)*a7*a8*b1*b7+Rat(2)*a4*a8*b2*b7-Rat(2)*a3*a9*b2*b7+Rat(4)*a3*a7*b3*b7-Rat(2)*a2*a9*b3*b7+Rat(2)*a2*a8*b4*b7-Rat(2)*a3*a4*b6*b7+Rat(2)*a1*a9*b6*b7+a3*a3*b7*b7-a1*a8*b7*b7-a7*a7*b1*b8-a2*a2*b10*b8-Rat(2)*a10*a2*b2*b8+Rat(2)*a4*a7*b2*b8+Rat(2)*a2*a7*b4*b8+a1*a10*b5*b8-a4*a4*b5*b8+Rat(2)*a2*a4*b7*b8-Rat(2)*a1*a7*b7*b8-Rat(2)*a3*a7*b2*b9+Rat(4)*a2*a9*b2*b9-Rat(2)*a2*a7*b3*b9+Rat(2)*a3*a4*b5*b9-Rat(2)*a1*a9*b5*b9-Rat(2)*a2*a4*b6*b9+Rat(2)*a1*a7*b6*b9-Rat(2)*a2*a3*b7*b9+a2*a2*b9*b9+Rat(2)*a6*(a3*b10*b2+a2*b10*b3+a10*b2*b3-a9*b2*b4-a7*b3*b4-a10*b1*b6-a1*b10*b6+Rat(2)*a4*b4*b6+a9*b1*b7-a4*b3*b7-a3*b4*b7+a7*b1*b9-a4*b2*b9-a2*b4*b9+a1*b7*b9)+a5*(a8*b1*b10-Rat(2)*a3*b10*b3-a10*b3*b3+Rat(2)*a9*b3*b4-a8*b4*b4+a10*b1*b8+a1*b10*b8-Rat(2)*a4*b4*b8-Rat(2)*a9*b1*b9+Rat(2)*a4*b3*b9+Rat(2)*a3*b4*b9-a1*b9*b9);

E=-Rat(2)*a2*a8*b10*b2-a10*a8*b2*b2+a9*a9*b2*b2-Rat(2)*a7*a9*b2*b3+a7*a7*b3*b3+Rat(2)*a7*a8*b2*b4+a6*a6*(-b1*b10+b4*b4)+a10*a8*b1*b5-a9*a9*b1*b5-a3*a3*b10*b5+a1*a8*b10*b5-Rat(2)*a10*a3*b3*b5+Rat(2)*a4*a9*b3*b5-Rat(2)*a4*a8*b4*b5+Rat(2)*a3*a9*b4*b5+Rat(2)*a7*a9*b1*b6+Rat(2)*a2*a3*b10*b6+Rat(2)*a10*a3*b2*b6-Rat(2)*a4*a9*b2*b6+Rat(2)*a10*a2*b3*b6-Rat(2)*a4*a7*b3*b6-Rat(2)*a3*a7*b4*b6-Rat(2)*a2*a9*b4*b6-a1*a10*b6*b6+a4*a4*b6*b6-Rat(2)*a7*a8*b1*b7+Rat(2)*a4*a8*b2*b7-Rat(2)*a3*a9*b2*b7+Rat(4)*a3*a7*b3*b7-Rat(2)*a2*a9*b3*b7+Rat(2)*a2*a8*b4*b7-Rat(2)*a3*a4*b6*b7+Rat(2)*a1*a9*b6*b7+a3*a3*b7*b7-a1*a8*b7*b7-a7*a7*b1*b8-a2*a2*b10*b8-Rat(2)*a10*a2*b2*b8+Rat(2)*a4*a7*b2*b8+Rat(2)*a2*a7*b4*b8+a1*a10*b5*b8-a4*a4*b5*b8+Rat(2)*a2*a4*b7*b8-Rat(2)*a1*a7*b7*b8-Rat(2)*a3*a7*b2*b9+Rat(4)*a2*a9*b2*b9-Rat(2)*a2*a7*b3*b9+Rat(2)*a3*a4*b5*b9-Rat(2)*a1*a9*b5*b9-Rat(2)*a2*a4*b6*b9+Rat(2)*a1*a7*b6*b9-Rat(2)*a2*a3*b7*b9+a2*a2*b9*b9+Rat(2)*a6*(a3*b10*b2+a2*b10*b3+a10*b2*b3-a9*b2*b4-a7*b3*b4-a10*b1*b6-a1*b10*b6+Rat(2)*a4*b4*b6+a9*b1*b7-a4*b3*b7-a3*b4*b7+a7*b1*b9-a4*b2*b9-a2*b4*b9+a1*b7*b9)+a5*(a8*b1*b10-Rat(2)*a3*b10*b3-a10*b3*b3+Rat(2)*a9*b3*b4-a8*b4*b4+a10*b1*b8+a1*b10*b8-Rat(2)*a4*b4*b8-Rat(2)*a9*b1*b9+Rat(2)*a4*b3*b9+Rat(2)*a3*b4*b9-a1*b9*b9);


//F=-a5*b10*b3*b3-Rat(2)*a3*b10*b3*b5-a10*b3*b3*b5+Rat(2)*a9*b3*b4*b5+Rat(2)*a3*b10*b2*b6+Rat(2)*a2*b10*b3*b6+Rat(2)*a10*b2*b3*b6-Rat(2)*a9*b2*b4*b6-Rat(2)*a7*b3*b4*b6-a10*b1*b6*b6-a1*b10*b6*b6+Rat(2)*a4*b4*b6*b6-Rat(2)*a9*b2*b3*b7+Rat(2)*a7*b3*b3*b7+Rat(2)*a9*b1*b6*b7-Rat(2)*a4*b3*b6*b7-Rat(2)*a3*b4*b6*b7+Rat(2)*a3*b3*b7*b7-a8*(b4*b4*b5+b10*(b2*b2-b1*b5)-Rat(2)*b2*b4*b7+b1*b7*b7)+a5*b1*b10*b8-Rat(2)*a2*b10*b2*b8-a10*b2*b2*b8+Rat(2)*a7*b2*b4*b8-a5*b4*b4*b8+a10*b1*b5*b8+a1*b10*b5*b8-Rat(2)*a4*b4*b5*b8-Rat(2)*a7*b1*b7*b8+Rat(2)*a4*b2*b7*b8+Rat(2)*a2*b4*b7*b8-a1*b7*b7*b8+Rat(2)*a9*b2*b2*b9-Rat(2)*a7*b2*b3*b9+Rat(2)*a5*b3*b4*b9-Rat(2)*a9*b1*b5*b9+Rat(2)*a4*b3*b5*b9+Rat(2)*a3*b4*b5*b9+Rat(2)*a7*b1*b6*b9-Rat(2)*a4*b2*b6*b9-Rat(2)*a2*b4*b6*b9-Rat(2)*a3*b2*b7*b9-Rat(2)*a2*b3*b7*b9+Rat(2)*a1*b6*b7*b9-a5*b1*b9*b9+Rat(2)*a2*b2*b9*b9-a1*b5*b9*b9+Rat(2)*a6*(b10*b2*b3-b1*b10*b6+b4*b4*b6-b3*b4*b7-b2*b4*b9+b1*b7*b9);

F=-a5*b10*b3*b3-Rat(2)*a3*b10*b3*b5-a10*b3*b3*b5+Rat(2)*a9*b3*b4*b5+Rat(2)*a3*b10*b2*b6+Rat(2)*a2*b10*b3*b6+Rat(2)*a10*b2*b3*b6-Rat(2)*a9*b2*b4*b6-Rat(2)*a7*b3*b4*b6-a10*b1*b6*b6-a1*b10*b6*b6+Rat(2)*a4*b4*b6*b6-Rat(2)*a9*b2*b3*b7+Rat(2)*a7*b3*b3*b7+Rat(2)*a9*b1*b6*b7-Rat(2)*a4*b3*b6*b7-Rat(2)*a3*b4*b6*b7+Rat(2)*a3*b3*b7*b7-a8*(b4*b4*b5+b10*(b2*b2-b1*b5)-Rat(2)*b2*b4*b7+b1*b7*b7)+a5*b1*b10*b8-Rat(2)*a2*b10*b2*b8-a10*b2*b2*b8+Rat(2)*a7*b2*b4*b8-a5*b4*b4*b8+a10*b1*b5*b8+a1*b10*b5*b8-Rat(2)*a4*b4*b5*b8-Rat(2)*a7*b1*b7*b8+Rat(2)*a4*b2*b7*b8+Rat(2)*a2*b4*b7*b8-a1*b7*b7*b8+Rat(2)*a9*b2*b2*b9-Rat(2)*a7*b2*b3*b9+Rat(2)*a5*b3*b4*b9-Rat(2)*a9*b1*b5*b9+Rat(2)*a4*b3*b5*b9+Rat(2)*a3*b4*b5*b9+Rat(2)*a7*b1*b6*b9-Rat(2)*a4*b2*b6*b9-Rat(2)*a2*b4*b6*b9-Rat(2)*a3*b2*b7*b9-Rat(2)*a2*b3*b7*b9+Rat(2)*a1*b6*b7*b9-a5*b1*b9*b9+Rat(2)*a2*b2*b9*b9-a1*b5*b9*b9+Rat(2)*a6*(b10*b2*b3-b1*b10*b6+b4*b4*b6-b3*b4*b7-b2*b4*b9+b1*b7*b9);





 G = b3*b3*b7*b7-b1*b7*b7*b8+b4*b4*(b6*b6-b5*b8)-b10*(b3*b3*b5-Rat(2)*b2*b3*b6+b1*b6*b6+b2*b2*b8-b1*b5*b8)-Rat(2)*b2*b3*b7*b9+Rat(2)*b1*b6*b7*b9+b2*b2*b9*b9-b1*b5*b9*b9-Rat(2)*b4*(b3*b6*b7-b2*b7*b8-b3*b5*b9+b2*b6*b9);

 std::cout << "C : " << C.to_double() << std::endl;
 std::cout << "D : " << D.to_double() << std::endl;
 std::cout << "E : " << E.to_double() << std::endl;
 std::cout << "F : " << F.to_double() << std::endl;
 std::cout << "G : " << G.to_double() << std::endl;



return 1;

}






{

   as_fraction(3.142857);
    as_fraction(0.1);
    as_fraction(0.333333);
    as_fraction(514.0/37.0);
    as_fraction(1.17171717);
    as_fraction(-1.17);

}

 GetRational(0.33);


{
  Poly4 poly;
  poly.A0 = 24.0;
  poly.A1 = -50.0;
  poly.A2 = 35.0;
  poly.A3 = -10.0;
  poly.A4 = 1.0;

  Poly4 tab[10];
  int nb = 0;
  nb = solve4(poly, tab, 10);
  std::cout << " nb = " << nb << std::endl;

  roots_rec(tab, nb, 0.0, 1.251);
}

  Poly4 poly;

  poly.A0 = -1.0;
  poly.A1 = -1.0;
  poly.A2 = 0.0;
  poly.A3 = 1.0;
  poly.A4 = 1.0;


  Poly4 tab[10];
  int nb = 0;
  nb = solve4(poly, tab, 10);
  std::cout << " nb = " << nb << std::endl;
  assert(tab[0].A0 == -1);
  assert(tab[0].A1 == -1);
  assert(tab[0].A2 == 0); 
  assert(tab[0].A3 == 1);
  assert(tab[0].A4 == 1);

  assert(tab[1].A0 == -1);
  assert(tab[1].A1 == 0);
  assert(tab[1].A2 == 3); 
  assert(tab[1].A3 == 4);
  assert(tab[1].A4 == 0);

  assert(tab[2].A0 == Rat(15, 16));
  assert(tab[2].A1 == Rat(3, 4));
  assert(tab[2].A2 == Rat(3, 16)); 
  assert(tab[2].A3 == 0);
  assert(tab[2].A4 == 0);

  assert(tab[3].A0 == -64);
  assert(tab[3].A1 == -32);
  assert(tab[3].A2 == 0); 
  assert(tab[3].A3 == 0);
  assert(tab[3].A4 == 0);

  assert(tab[4].A0 == Rat(-3, 16));
  assert(tab[4].A1 == 0);
  assert(tab[4].A2 == 0); 
  assert(tab[4].A3 == 0);
  assert(tab[4].A4 == 0);

  std::cout << " MajZero = " << MajZero(poly) << std::endl;

  poly.A0 = 24.0;
  poly.A1 = -50.0;
  poly.A2 = 35.0;
  poly.A3 = -10.0;
  poly.A4 = 1.0;

  nb = solve4(poly, tab, 10);
  std::cout << " nb = " << nb << std::endl;
  std::cout << "--------------------------------------------------" << std::endl;
  std::cout << " MajZero = " << MajZero(poly) << std::endl;
  std::cout << " MinZero = " << MinZero(poly) << std::endl;
  int var1, var2;
  var1 = variation(tab, nb, MajZero(poly));
  var2 = variation(tab, nb, -MajZero(poly));

  roots(poly);

  assert(tab[0].A0 == 24);
  assert(tab[0].A1 == -50);
  assert(tab[0].A2 == 35); 
  assert(tab[0].A3 == -10);
  assert(tab[0].A4 == 1);

  assert(tab[1].A0 == -50);
  assert(tab[1].A1 == 70);
  assert(tab[1].A2 == -30); 
  assert(tab[1].A3 == 4);
  assert(tab[1].A4 == 0);

  assert(tab[2].A0 == Rat(29, 4));
  assert(tab[2].A1 == Rat(-25, 4));
  assert(tab[2].A2 == Rat(5, 4)); 
  assert(tab[2].A3 == 0);
  assert(tab[2].A4 == 0);

  assert(tab[3].A0 == -8);
  assert(tab[3].A1 == Rat(16, 5));
  assert(tab[3].A2 == 0); 
  assert(tab[3].A3 == 0);
  assert(tab[3].A4 == 0);

  assert(tab[4].A0 == Rat(9, 16));
  assert(tab[4].A1 == 0);
  assert(tab[4].A2 == 0); 
  assert(tab[4].A3 == 0);
  assert(tab[4].A4 == 0);

  poly.A0 = 0.0;
  poly.A1 = 0.0;
  poly.A2 = 0.0;
  poly.A3 = -1.0;
  poly.A4 = 0.0;

  nb = solve4(poly, tab, 10);
  std::cout << " nb = " << nb << std::endl;
/*
  assert(tab[0].A0 == 24);
  assert(tab[0].A1 == -50);
  assert(tab[0].A2 == 35); 
  assert(tab[0].A3 == -10);
  assert(tab[0].A4 == 1);

  assert(tab[1].A0 == -50);
  assert(tab[1].A1 == 70);
  assert(tab[1].A2 == -30); 
  assert(tab[1].A3 == 4);
  assert(tab[1].A4 == 0);

  assert(tab[2].A0 == Rat(29, 4));
  assert(tab[2].A1 == Rat(-25, 4));
  assert(tab[2].A2 == Rat(5, 4)); 
  assert(tab[2].A3 == 0);
  assert(tab[2].A4 == 0);

  assert(tab[3].A0 == -8);
  assert(tab[3].A1 == Rat(16, 5));
  assert(tab[3].A2 == 0); 
  assert(tab[3].A3 == 0);
  assert(tab[3].A4 == 0);

  assert(tab[4].A0 == Rat(9, 16));
  assert(tab[4].A1 == 0);
  assert(tab[4].A2 == 0); 
  assert(tab[4].A3 == 0);
  assert(tab[4].A4 == 0);
*/

  poly.A0 = -1.0;
  poly.A1 = -1.0;
  poly.A2 = 0.0;
  poly.A3 = 1.0;
  poly.A4 = 1.0;

  nb = solve4(poly, tab, 10);
  std::cout << " nb = " << nb << std::endl;
  std::cout << "--------------------------------------------------" << std::endl;
  std::cout << " MajZero = " << MajZero(poly) << std::endl;
  std::cout << " MinZero = " << MinZero(poly) << std::endl;
  var1 = variation(tab, nb, MajZero(poly));
  var2 = variation(tab, nb, -MajZero(poly));

 return(1);

  double c[ 5 ]; 
  double s[ 4 ];

  c[ 0 ] = 0.0; 
  c[ 1 ] = 2.0; 
  c[ 2 ] = -1.0; 
  c[ 3 ] = -2.0; 
  c[ 4 ] = 1.0; 

  int num = SolveQuartic(c, s);

  for(int i=0;i<num; i++)
    std::cout << " " << s[i] << std::endl;


 return 0;

   Rat A[4][4], B[4][4];

 a1 = 1;
 a2 = 2;
 a3 = 3;
 a4 = 4;
 a5 = 5;
 a6 = 6;
 a7 = 7;
 a8 = 8;
 a9 = 9;
 a10 = 10;

 b1 = 11;
 b2 = 12;
 b3 = 13;
 b4 = 14;
 b5 = 15;
 b6 = 16;
 b7 = 17;
 b8 = 18;
 b9 = 19;
 b10 = 110;
  
 std::cout << " " << a1.to_double() << " " << a2.to_double() << " " << a3.to_double() << " " << a4.to_double() << std::endl;
 std::cout << " " << a2.to_double() << " " << a5.to_double() << " " << a6.to_double() << " " << a7.to_double() << std::endl;
 std::cout << " " << a3.to_double() << " " << a6.to_double() << " " << a8.to_double() << " " << a9.to_double() << std::endl;
 std::cout << " " << a4.to_double() << " " << a7.to_double() << " " << a9.to_double() << " " << a10.to_double() << std::endl;
 std::cout << "----------------------" << std::endl; 
 std::cout << " " << b1.to_double() << " " << b2.to_double() << " " << b3.to_double() << " " << b4.to_double() << std::endl;
 std::cout << " " << b2.to_double() << " " << b5.to_double() << " " << b6.to_double() << " " << b7.to_double() << std::endl;
 std::cout << " " << b3.to_double() << " " << b6.to_double() << " " << b8.to_double() << " " << b9.to_double() << std::endl;
 std::cout << " " << b4.to_double() << " " << b7.to_double() << " " << b9.to_double() << " " << b10.to_double() << std::endl;
 

 Rat C, D, E, F, G, rr(1);


C=a3*a3*a7*a7-a1*a7*a7*a8+a4*a4*(a6*a6-a5*a8)-a10*(a3*a3*a5-Rat(2)*a2*a3*a6+a1*a6*a6+a2*a2*a8-a1*a5*a8)-Rat(2)*a2*a3*a7*a9+Rat(2)*a1*a6*a7*a9+a2*a2*a9*a9-a1*a5*a9*a9-Rat(2)*a4*(a3*a6*a7-a2*a7*a8-a3*a5*a9+a2*a6*a9);

D=-a5*a9*a9*b1-a3*a3*a5*b10+Rat(2)*a2*a3*a6*b10-a1*a6*a6*b10-a2*a2*a8*b10+a1*a5*a8*b10-Rat(2)*a4*a6*a9*b2+Rat(2)*a2*a9*a9*b2+Rat(2)*a4*a5*a9*b3+Rat(2)*a4*a6*a6*b4-Rat(2)*a4*a5*a8*b4+Rat(2)*a3*a5*a9*b4-Rat(2)*a2*a6*a9*b4-a4*a4*a8*b5+Rat(2)*a3*a4*a9*b5-a1*a9*a9*b5+Rat(2)*a4*a4*a6*b6-Rat(2)*a2*a4*a9*b6-Rat(2)*a3*a4*a6*b7+Rat(2)*a2*a4*a8*b7-Rat(2)*a2*a3*a9*b7+Rat(2)*a1*a6*a9*b7-a4*a4*a5*b8-a7*a7*(a8*b1-Rat(2)*a3*b3+a1*b8)+a10*(-a6*a6*b1+a5*a8*b1-Rat(2)*a2*a8*b2-Rat(2)*a3*a5*b3-a3*a3*b5+a1*a8*b5+Rat(2)*a2*a3*b6+Rat(2)*a6*(a3*b2+a2*b3-a1*b6)-a2*a2*b8+a1*a5*b8)+Rat(2)*a3*a4*a5*b9-Rat(2)*a2*a4*a6*b9+Rat(2)*a2*a2*a9*b9-Rat(2)*a1*a5*a9*b9+Rat(2)*a7*(a4*a8*b2-a3*a9*b2-a2*a9*b3+a2*a8*b4-a3*a4*b6+a1*a9*b6+a3*a3*b7-a1*a8*b7+a2*a4*b8-a2*a3*b9+a6*(a9*b1-a4*b3-a3*b4+a1*b9));

E=-Rat(2)*a2*a8*b10*b2-a10*a8*b2*b2+a9*a9*b2*b2-Rat(2)*a7*a9*b2*b3+a7*a7*b3*b3+Rat(2)*a7*a8*b2*b4+a6*a6*(-b1*b10+b4*b4)+a10*a8*b1*b5-a9*a9*b1*b5-a3*a3*b10*b5+a1*a8*b10*b5-Rat(2)*a10*a3*b3*b5+Rat(2)*a4*a9*b3*b5-Rat(2)*a4*a8*b4*b5+Rat(2)*a3*a9*b4*b5+Rat(2)*a7*a9*b1*b6+Rat(2)*a2*a3*b10*b6+Rat(2)*a10*a3*b2*b6-Rat(2)*a4*a9*b2*b6+Rat(2)*a10*a2*b3*b6-Rat(2)*a4*a7*b3*b6-Rat(2)*a3*a7*b4*b6-Rat(2)*a2*a9*b4*b6-a1*a10*b6*b6+a4*a4*b6*b6-Rat(2)*a7*a8*b1*b7+Rat(2)*a4*a8*b2*b7-Rat(2)*a3*a9*b2*b7+Rat(4)*a3*a7*b3*b7-Rat(2)*a2*a9*b3*b7+Rat(2)*a2*a8*b4*b7-Rat(2)*a3*a4*b6*b7+Rat(2)*a1*a9*b6*b7+a3*a3*b7*b7-a1*a8*b7*b7-a7*a7*b1*b8-a2*a2*b10*b8-Rat(2)*a10*a2*b2*b8+Rat(2)*a4*a7*b2*b8+Rat(2)*a2*a7*b4*b8+a1*a10*b5*b8-a4*a4*b5*b8+Rat(2)*a2*a4*b7*b8-Rat(2)*a1*a7*b7*b8-Rat(2)*a3*a7*b2*b9+Rat(4)*a2*a9*b2*b9-Rat(2)*a2*a7*b3*b9+Rat(2)*a3*a4*b5*b9-Rat(2)*a1*a9*b5*b9-Rat(2)*a2*a4*b6*b9+Rat(2)*a1*a7*b6*b9-Rat(2)*a2*a3*b7*b9+a2*a2*b9*b9+Rat(2)*a6*(a3*b10*b2+a2*b10*b3+a10*b2*b3-a9*b2*b4-a7*b3*b4-a10*b1*b6-a1*b10*b6+Rat(2)*a4*b4*b6+a9*b1*b7-a4*b3*b7-a3*b4*b7+a7*b1*b9-a4*b2*b9-a2*b4*b9+a1*b7*b9)+a5*(a8*b1*b10-Rat(2)*a3*b10*b3-a10*b3*b3+Rat(2)*a9*b3*b4-a8*b4*b4+a10*b1*b8+a1*b10*b8-Rat(2)*a4*b4*b8-Rat(2)*a9*b1*b9+Rat(2)*a4*b3*b9+Rat(2)*a3*b4*b9-a1*b9*b9);


F=-a5*b10*b3*b3-Rat(2)*a3*b10*b3*b5-a10*b3*b3*b5+Rat(2)*a9*b3*b4*b5+Rat(2)*a3*b10*b2*b6+Rat(2)*a2*b10*b3*b6+Rat(2)*a10*b2*b3*b6-Rat(2)*a9*b2*b4*b6-Rat(2)*a7*b3*b4*b6-a10*b1*b6*b6-a1*b10*b6*b6+Rat(2)*a4*b4*b6*b6-Rat(2)*a9*b2*b3*b7+Rat(2)*a7*b3*b3*b7+Rat(2)*a9*b1*b6*b7-Rat(2)*a4*b3*b6*b7-Rat(2)*a3*b4*b6*b7+Rat(2)*a3*b3*b7*b7-a8*(b4*b4*b5+b10*(b2*b2-b1*b5)-Rat(2)*b2*b4*b7+b1*b7*b7)+a5*b1*b10*b8-Rat(2)*a2*b10*b2*b8-a10*b2*b2*b8+Rat(2)*a7*b2*b4*b8-a5*b4*b4*b8+a10*b1*b5*b8+a1*b10*b5*b8-Rat(2)*a4*b4*b5*b8-Rat(2)*a7*b1*b7*b8+Rat(2)*a4*b2*b7*b8+Rat(2)*a2*b4*b7*b8-a1*b7*b7*b8+Rat(2)*a9*b2*b2*b9-Rat(2)*a7*b2*b3*b9+Rat(2)*a5*b3*b4*b9-Rat(2)*a9*b1*b5*b9+Rat(2)*a4*b3*b5*b9+Rat(2)*a3*b4*b5*b9+Rat(2)*a7*b1*b6*b9-Rat(2)*a4*b2*b6*b9-Rat(2)*a2*b4*b6*b9-Rat(2)*a3*b2*b7*b9-Rat(2)*a2*b3*b7*b9+Rat(2)*a1*b6*b7*b9-a5*b1*b9*b9+Rat(2)*a2*b2*b9*b9-a1*b5*b9*b9+Rat(2)*a6*(b10*b2*b3-b1*b10*b6+b4*b4*b6-b3*b4*b7-b2*b4*b9+b1*b7*b9);





 G = b3*b3*b7*b7-b1*b7*b7*b8+b4*b4*(b6*b6-b5*b8)-b10*(b3*b3*b5-Rat(2)*b2*b3*b6+b1*b6*b6+b2*b2*b8-b1*b5*b8)-Rat(2)*b2*b3*b7*b9+Rat(2)*b1*b6*b7*b9+b2*b2*b9*b9-b1*b5*b9*b9-Rat(2)*b4*(b3*b6*b7-b2*b7*b8-b3*b5*b9+b2*b6*b9);

 std::cout << "C : " << C.to_double() << std::endl;
 std::cout << "D : " << D.to_double() << std::endl;
 std::cout << "E : " << E.to_double() << std::endl;
 std::cout << "F : " << F.to_double() << std::endl;
 std::cout << "G : " << G.to_double() << std::endl;

 return 0;
}
