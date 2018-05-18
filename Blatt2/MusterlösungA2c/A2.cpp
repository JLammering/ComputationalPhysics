#include <fstream>
#include <cmath>
#include <chrono>
#include <random>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

typedef double(*CallbackType)(double);

double variance = 1;
double factor = 1/sqrt(2*M_PI*variance);   // in order to calculate this only once

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// F^(-1)(x) = asin(x) is the inverse distribution function for a)
double inverse_distribution(const double &x){
  return asin(x);
}

// F^(-1)(x) = -ln(|x|) is the inverse distribution function for c)
double inverse_distribution_exp(const double &x){
    if (x==0)
        return 1e16;
    return -sgn(x)*log(x*sgn(x))+3.0;
}

// gauss distribution for variance 4, mean 3
static double gauss(double x){
    return factor*exp(-(x-3)*(x-3)/(2*variance));
}

static double exponential(double x){
    return exp(-(x-3)*sgn(x-3))/2;
}

// gives two gaussian-distributed values z1 and z2 each with mean moment1 and variance moment2
void boxMuller(const double &u1, const double &u2, double &z1, double &z2, const double &moment1, const double &moment2){
    z1 = sqrt(-2*log(u1))*cos(2*M_PI*u2);
    z2 = sqrt(-2*log(u1))*sin(2*M_PI*u2);

    // parametrization .. you can convert back and forth between a standard normal value Z to a general Gaussian X
    z1 = moment1 + sqrt(moment2)*z1;
    z2 = moment1 + sqrt(moment2)*z2;
}

// returns true if rnd_exp has to be put into list of random numbers for distribution p
bool neumannRueckweisung(double &y,                 // <- y* : uniformly distributed in [0,1]
                         const double &x,           // <- x : from distribution g(x)=1/2exp(-|x|)
                         CallbackType p,
                         CallbackType g,
                         double k)
{
    y *= k*g(x);      // <- y : uniformly distributed in [0,k*g(x)]
    double test = p(x);
    return y<p(x);
}

int main()
{
  // Declarations;
    std::ofstream f;
  double rnd1,rnd2;
  unsigned N = (unsigned int)1e6;
  unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator (seed);

  // Part a)
  // File for plotting with python
  // i)
  f.open("./build/A2a_i");
  std::uniform_real_distribution<double> dis1(0., 1.);
  for(unsigned int i=0; i<N; ++i){
    rnd1 = dis1(generator);
    f << inverse_distribution(rnd1) << "\n";
  }
  f.close();
  // ii)
  f.open("./build/A2a_ii");
  std::uniform_real_distribution<double> dis2(-1., 1.);
  for(unsigned int i=0; i<N; ++i){
    rnd1 = dis2(generator);
    f << inverse_distribution(rnd1) << "\n";
  }
  f.close();

  // Part b)
  f.open("./build/A2b");

  double z1 = 0.;
  double z2 = 0.;
  double mu = 3.;
  double variance = 4.;

  for(unsigned int i = 0; i < N/2; i++){    // we generate 2 variables, so only half of N needed
    rnd1 = dis1(generator);                 // random numbers in [0,1]
    rnd2 = dis1(generator);
    boxMuller(rnd1, rnd2, z1, z2, mu, variance);
    f << z1 << "\n";
    f << z2 << "\n";
  }

  f.close();

  // Part c)
  f.open("./build/A2c");
  N = (unsigned  int)1e5;
  double k=1.5;     // for this choice k*g(x) > p(x) holds
  std::uniform_real_distribution<double> dis3(-1., 1.);
  std::uniform_real_distribution<double> dis4(0, 1.);
  double rnd_uniform1, rnd_uniform2, rnd_exponential;
  for(unsigned  int i=0; i<N; ++i){
    rnd_uniform1 = dis3(generator);     // <- x : first uniformly distributed random number for input to transform algorithm
    rnd_uniform2 = dis4(generator);     // <- y_2 : second uniformly distributed random number for input to rejection algorithm
    rnd_exponential = inverse_distribution_exp(rnd_uniform1);   //<- y_1 : generate exponential distributed random number for input to rejection algorithm
    if (neumannRueckweisung(rnd_uniform2, rnd_exponential, gauss, exponential, k))
    {
        f << rnd_exponential << "\n";   // supposed to be gaussian distributed now
    }
  }
  f.close();

  // Bonus c)
  f.open("./build/A2c_distribution");
  std::uniform_real_distribution<double> dis5(-1., 1.);
  for(unsigned int i=0; i<N; ++i){
    rnd1 = dis5(generator);
    f << inverse_distribution_exp(rnd1) << "\n";
  }
  f.close();

    return 0;
}
