
#include "binomialengine.hpp"
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/methods/lattices/binomialtree.hpp>
#include <ql/quantlib.hpp>
#ifdef BOOST_MSVC
#endif
#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>
using namespace QuantLib;

int main() {



    try {
Real strike = 20;
Real underying =50; 
DayCounter dayCounter = Actual365Fixed() ; 
Date settlementDate(20,February, 2017);
 Date maturity(10, May, 2017);
Rate riskFreeRate = 0.3 ;  
Spread dividendYield = 0.00;
Calendar calendar = TARGET();
Volatility volatility = 0.20;
Option::Type type(Option::Call);      
        std::cout << "Underlying price = " <<  underying << std::endl << std::endl;


        std::cout << "Risk-free interest rate = " << io::rate(riskFreeRate) << std::endl;

                
        std::cout << "Dividend yield = " << io::rate(dividendYield) << std::endl ; 
                

        std::cout << "Volatility = " << io::volatility(volatility)  << std::endl;  
                  
  

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
    Size timeSteps (55) ;

        // create an instrument and pass the Engine to the instrument 
                       //instrument parametters 
      boost::shared_ptr<StrikedTypePayoff> payoff (new PlainVanillaPayoff(type, strike)); 
      boost::shared_ptr<Exercise> europeanExercise (new EuropeanExercise(maturity));
	                   // instrument instanciation 
      VanillaOption europeanOption(payoff, europeanExercise);
                       // pass the engine to the instrument 
      europeanOption.setPricingEngine(boost::shared_ptr< BinomialVanillaEngine_2<JarrowRudd> >(new  BinomialVanillaEngine_2 <JarrowRudd> ( process , timeSteps) ));  
        // evaluate the result 
    std::cout << "evaluation  price  = " << europeanOption.NPV()  << "\n " ; 

        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what()  << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

