
#include "binomialengine.hpp"
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/methods/lattices/binomialtree.hpp>
#include <ql/quantlib.hpp>
#ifdef BOOST_MSVC
#endif
#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace QuantLib;

int main() {

  std::cout << "\n        C++ Quantlib project 4           \n"  ;
  std::cout << "\n        Fixed Oscillation in Binomial Engine   \n"  ;
  std::cout << "\n Authors    :             \n"  ;
  std::cout << "          SAY Ahousi Armand            \n"  ;
  std::cout << "          Sami BENABIDALLAH            \n"  ;
  std::cout << "          Mohamed KAFFEL               \n"  ;
  std::cout << "          Julien BEAUVOIS              \n"  ;
  std::cout << "\n Guide lines :   \n "  ;
  std::cout << " The results of the execution will be stored :  \n "  ;
  std::cout << " for the simple Cox Ross Rubinstein model in the file  data_bt.txt   \n "  ;
std::cout   << " for the Binomial Black-Scholes model in the file  data_bbt.txt   \n "  ;
std::cout   << " You can then use the analyse the data  with R or ipython notebook     \n "  ;
std::cout   << " each line of the files represent the Option : call price for a corresponding \n "  ;
std::cout   << " time step . data are comma separated \"timestep , price \"  \n "  ;

    try {
Real strike = 110;
Real underying =100; 
DayCounter dayCounter = Actual365Fixed() ; 
 Date settlementDate(01,March, 2017);
 Date maturity(31, March , 2017);
Rate riskFreeRate = 0.03 ;  
Spread dividendYield = 0.00;
Calendar calendar = TARGET();
Volatility volatility = 0.20;
Option::Type type(Option::Call);      
        std::cout << "\nUnderlying price = " <<  underying  << std::endl;

        std::cout << "\nStrike  =  " << strike  << std::endl;
        std::cout << "Risk-free interest rate = " << io::rate(riskFreeRate) << std::endl;

                
        std::cout << "Dividend yield = " << io::rate(dividendYield) << std::endl ; 
                

        std::cout << "Volatility = " << io::volatility(volatility)  << std::endl;  
   
  int i = 0 ;                 
  int i_min = 20 ; 
  int i_max = 400 ;  

        // add your code here

        // GeneralizedBlackScholesProcess process argument (5) 
        		
				// const Handle<Quote>& 
                 
                 Handle<Quote> qt (boost::shared_ptr<Quote>(new SimpleQuote(underying)));

       			// Handle<YieldTermStructure>& dividendTS , 

                Handle<YieldTermStructure> termStructure (boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, riskFreeRate, dayCounter))) ; 

                // Handle<YieldTermStructure>& riskFreeTS,

                Handle<YieldTermStructure> dividend(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, dividendYield, dayCounter)));


                // Handle<BlackVolTermStructure>& blackVolTS,
                Handle<BlackVolTermStructure> flatVolTS(boost::shared_ptr<BlackVolTermStructure>(new BlackConstantVol(settlementDate, calendar, volatility,dayCounter)));
         

		// add the stocastique process 
   	 boost::shared_ptr<GeneralizedBlackScholesProcess> process  =  boost::shared_ptr<GeneralizedBlackScholesProcess> ( new GeneralizedBlackScholesProcess (qt,termStructure , dividend ,flatVolTS )) ; 
        // initialised a wanted timestep 

// Add file to get the results of the  execution 
		std::ofstream data_output ;   
        int n = 0 ; 
        std::cout << "press  1  for Binomial Cox Ross Rubinstein values     : \n";
        std::cout << "press  2  for Binomial Black-Scholes  values          : \n";
        std::cin >> n;
		
       switch (n) {
      
      	case 1 : 
data_output.open ("data_bt.txt");
for ( i = i_min ; i<i_max +1  ; i++) {
        
          Size timeSteps (i) ;

        // create an instrument and pass the Engine to the instrument 
                       //instrument parametters 
      boost::shared_ptr<StrikedTypePayoff> payoff (new PlainVanillaPayoff(type, strike)); 
      boost::shared_ptr<Exercise> europeanExercise (new EuropeanExercise(maturity));
	                   // instrument instanciation 
      VanillaOption europeanOption(payoff, europeanExercise);
                       // pass the engine to the instrument 
      europeanOption.setPricingEngine(boost::shared_ptr< BinomialVanillaEngine<CoxRossRubinstein> >(new  BinomialVanillaEngine<CoxRossRubinstein> ( process , timeSteps) )); 
        // evaluate the result redirected to  data_bt.txt
    data_output << i <<"," << europeanOption.NPV() << "\n "  ; 
		}
  data_output.close() ; 

     	break ;
 
     	case 2 :
  data_output.open ("data_bbt.txt");
  for ( i = i_min ; i<i_max +1  ; i++) {
          Size timeSteps (i) ;

        // create an instrument and pass the Engine to the instrument 
                       //instrument parametters 
      boost::shared_ptr<StrikedTypePayoff> payoff (new PlainVanillaPayoff(type, strike)); 
      boost::shared_ptr<Exercise> europeanExercise (new EuropeanExercise(maturity));
	                   // instrument instanciation 
      VanillaOption europeanOption(payoff, europeanExercise);
                       // pass the engine to the instrument 
      europeanOption.setPricingEngine(boost::shared_ptr< BinomialVanillaEngine_2<CoxRossRubinstein> >(new  BinomialVanillaEngine_2 <CoxRossRubinstein> ( process , timeSteps) ));  
        // evaluate the result redirect to data_bbt.txt
    data_output << i <<"," << europeanOption.NPV() << "\n "  ; 
		}
  data_output.close() ; 
      	break ;
      	default: 
      
      std::cout << " terminating unknow choice  ";
       return 0;
}

std::cout   << " \n Analyse the data in the files depending of your choice \n  "  ;

        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what()  << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

