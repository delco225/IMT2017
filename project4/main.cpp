
#include "binomialengine.hpp"
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/methods/lattices/binomialtree.hpp>
#include <iostream>

using namespace QuantLib;

int main() {

    try {

        // add your code here

        // GeneralizedBlackScholesProcess process argument (5) 
        		
				// const Handle<Quote>& x0  , 
       			// Handle<YieldTermStructure>& dividendTS , 
                // Handle<YieldTermStructure>& riskFreeTS,
                // Handle<BlackVolTermStructure>& blackVolTS,
                //const boost::shared_ptr<discretization>& d =boost::shared_ptr<discretization>()

        // instaciate a GeneralizedBlackscholes process with the 5 arguments   
           GeneralizedBlackScholesProcess * prr = new GeneralizedBlackScholesProcess () ; 
		// add the stocastique process 
    boost::shared_ptr<GeneralizedBlackScholesProcess>  process (prr); 
        // initialised a wanted timestep 
    Size timeSteps (30) ;
        // initialised the Binomial engine 
    BinomialVanillaEngine_2 B2eng  = new  BinomialVanillaEngine_2 ( process , timeSteps) ; 
        // call the calculate method   
    B2eng->calculate() ; 
        // evaluate the result 

      



        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

