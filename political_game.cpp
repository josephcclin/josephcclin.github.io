/* Enumerate instances of the Two Party Election Game by random sampling 
 * Each party has two candidates. 
 * 
 * The program can check if there is any instance with no pure Nash equilibrium
 * and also compute the worst price of anarchy (PoA) among the instances.
 *
 * Author: Joseph Chuang-Chieh Lin
 * Email: josephcclin@gmail.com
 * Date: November 27, 2019
 */
#include <cstddef>
#include <random>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <tuple>
#include "political_game.h"


void Candidate::init_uti() 
{	
	//int n1, n2;
	int n1, n2, n3;
	random_device rd;
	static default_random_engine eng(rd());
	static uniform_int_distribution<unsigned> uni(0, Candidate::utUB);
	while(1) { 
		n1 = uni(eng);
		n2 = uni(eng);
		n3 = uni(eng);
		if (n1+n2+n3 <= Candidate::utUB) break;
	}
	utSup = n1;
	utOpp = n2;
	utSwi = n3;
}

void Candidate::set_uti(int uts, int uto, int utswi) 
{
	utSup = uts;
	utOpp = uto;
	utSwi = utswi;
}

int Candidate::get_sup() 
{
    return utSup;
}

int Candidate::get_opp() 
{
    return utOpp;
}

int Candidate::get_swi()
{
	return utSwi;
}	

int Candidate::uti_sum() 
{	
	return utSup+utOpp+utSwi; 
}

double Candidate::get_expUti() 
{
	return expUti;
}

double Candidate::get_expSW() 
{
	return expSW;
}

void Party::reOrder() 
{
	int ut_sup, ut_opp, ut_swi; 
	if (cand2.get_sup() > cand1.get_sup()) { 
		ut_sup = cand1.get_sup(); 
		ut_opp = cand1.get_opp();
        	ut_swi = cand1.get_swi();
		cand1.set_uti(cand2.get_sup(), cand2.get_opp(), cand2.get_swi());
		cand2.set_uti(ut_sup, ut_opp, ut_swi);  
	}
}

bool Game::egoismCheck(Party & pA, Party & pB)
{
	if ((pA.cand1.get_opp()+pA.cand1.get_swi() >= min(pB.cand1.get_sup(), pB.cand2.get_sup()))  
		|| (pA.cand2.get_opp()+pA.cand2.get_swi() >= min(pB.cand1.get_sup(), pB.cand2.get_sup()))  
		|| (pB.cand1.get_opp()+pB.cand1.get_swi() >= min(pA.cand1.get_sup(), pA.cand2.get_sup()))  
		|| (pB.cand2.get_opp()+pB.cand2.get_swi() >= min(pA.cand1.get_sup(), pA.cand2.get_sup()))) {
		return 0;
	} else { 
		return 1;
	}
}

bool Game::betterThanSwing(Party & pA, Party & pB)
{
	if ((pA.cand1.get_swi() >= min(pA.cand1.get_sup(), pA.cand2.get_sup()))  
		|| (pA.cand2.get_swi() >= min(pA.cand1.get_sup(), pA.cand2.get_sup()))  
		|| (pB.cand1.get_swi() >= min(pB.cand1.get_sup(), pB.cand2.get_sup()))  
		|| (pB.cand2.get_swi() >= min(pB.cand1.get_sup(), pB.cand2.get_sup()))) {
		return 0;
	} else { 
		return 1;
	}
}

void SetExpUti(Candidate & cA, Candidate & cB)
{
	// This is the Bradley-Terry model
	double prob_cAw = static_cast<double>(cA.uti_sum())/(cA.uti_sum() + cB.uti_sum());
	cA.expUti = prob_cAw * cA.utSup + (1-prob_cAw) * cB.utOpp;
	cB.expUti = (1-prob_cAw) * cB.utSup + prob_cAw * cA.utOpp;
	cA.expSW = prob_cAw * cA.uti_sum();
	cB.expSW = (1-prob_cAw) * cB.uti_sum();
}

void SetExpUti(Candidate & cA, Candidate & cB, string type)
{
	double prob_cAw = 0;
	if (type == "softmax" || type == "-S") { 
		prob_cAw = exp(static_cast<double>(cA.uti_sum())/Candidate::utUB)/ 
		(exp(static_cast<double>(cA.uti_sum())/Candidate::utUB) + exp(static_cast<double>(cB.uti_sum())/Candidate::utUB));
	} else if (type == "linear-link" || type == "-L") { 
		prob_cAw = static_cast<double>(cA.uti_sum()-cB.uti_sum())/(2*Candidate::utUB) + 0.5;
	} else { // try the naive model
		prob_cAw = static_cast<double>(cA.uti_sum())/(cA.uti_sum() + cB.uti_sum());
	}
	cA.expUti = prob_cAw * cA.utSup + (1-prob_cAw) * cB.utOpp;
    cA.expSW = prob_cAw * cA.uti_sum();
	cB.expUti = (1-prob_cAw) * cB.utSup + prob_cAw * cA.utOpp;
	cB.expSW = (1-prob_cAw) * cB.uti_sum();
}

//check if the game instance has any pure NE
bool checkNE(vector<vector<double>> & sw)
{
	/*            B1                   B2          
	 * A1  (sw_a11, sw_b11)  |  (sw_a12, sw_b12)
	 * A2  (sw_a21, sw_b21)  |  (sw_a22, sw_b22)
	 */
 	const double &sw_a11 = sw[0][0], &sw_b11 = sw[0][1]; 
	const double &sw_a12 = sw[1][0], &sw_b12 = sw[1][1];
	const double &sw_a21 = sw[2][0], &sw_b21 = sw[2][1];
	const double &sw_a22 = sw[3][0], &sw_b22 = sw[3][1];

	if (sw_a11 < sw_a21 && sw_b21 < sw_b22 && \
		sw_a22 < sw_a12 && sw_b12 < sw_b11) { 
		return 0; 
	} else if (sw_b11 < sw_b12 && sw_a12 < sw_a22 && \
		sw_b22 < sw_b21 && sw_a21 < sw_a11) { 
		return 0; 
	} else { 
		return 1;
	} 
}

//Compute the PoA of the game instance
double PoA(vector<vector<double>> &sw)
{ 
	/*            B1                   B2          
	 * A1  (sw_a11, sw_b11)  |  (sw_a12, sw_b12)
	 * A2  (sw_a21, sw_b21)  |  (sw_a22, sw_b22)
	 */
	double swOPT = 0, swPNE = 0; 
	const double &sw_a11 = sw[0][0], &sw_b11 = sw[0][1]; 
	const double &sw_a12 = sw[1][0], &sw_b12 = sw[1][1];  
	const double &sw_a21 = sw[2][0], &sw_b21 = sw[2][1]; 
	const double &sw_a22 = sw[3][0], &sw_b22 = sw[3][1]; 

	swOPT = max(max(max(sw_a11+sw_b11, sw_a12+sw_b12), sw_a22+sw_b22), sw_a21+sw_b21);
	if (sw_a11 >= sw_a21 && sw_b11 >= sw_b12) { 
		swPNE = sw_a11 + sw_b11;
	}
	if (sw_a21 >= sw_a11 && sw_b21 >= sw_b22) {
		if (sw_a21 + sw_b21 < swPNE) { 
			swPNE = sw_a21 + sw_b21; 
		} 
	}
	if (sw_a22 >= sw_a12 && sw_b22 >= sw_b21) {
		if (sw_a22 + sw_b22 < swPNE) { 
			swPNE = sw_a22 + sw_b22; 
		} 
	}
	if (sw_a12 >= sw_a22 && sw_b12 >= sw_b11) {
		if (sw_a12 + sw_b12 < swPNE) { 
			swPNE = sw_a12 + sw_b12; 
		} 
	}  
	if (swPNE == 0) return 0; 
	else return swOPT/swPNE;
}

//Compute the max social welfare of the game instance
std::tuple<int, int, double> maxSocWel(vector<vector<double>> &sw)
{ 
    /*            B1                   B2          
     * A1  (sw_a11, sw_b11)  |  (sw_a12, sw_b12)
     * A2  (sw_a21, sw_b21)  |  (sw_a22, sw_b22)
     */
    double swOPT = 0, swPNE = 0; 
    int OPTdimOne = 0, OPTdimTwo = 0;
    const double &sw_a11 = sw[0][0], &sw_b11 = sw[0][1]; 
    const double &sw_a12 = sw[1][0], &sw_b12 = sw[1][1];  
    const double &sw_a21 = sw[2][0], &sw_b21 = sw[2][1]; 
    const double &sw_a22 = sw[3][0], &sw_b22 = sw[3][1]; 
    if (sw_a11+sw_b11 > sw_a12+sw_b12 && sw_a11+sw_b11 > max(sw_a21+sw_b21, sw_a22+sw_b22)) {
	OPTdimOne = 1;
	OPTdimTwo = 1;
    } else if (sw_a12+sw_b12 > sw_a11+sw_b11 && sw_a12+sw_b12 > max(sw_a21+sw_b21, sw_a22+sw_b22)) {
	OPTdimOne = 1;
	OPTdimTwo = 2;
    } else if (sw_a21+sw_b21 > sw_a11+sw_b11 && sw_a21+sw_b21 > max(sw_a12+sw_b12, sw_a22+sw_b22)) {
	OPTdimOne = 2;
	OPTdimTwo = 1;
    } else {
	OPTdimOne = 2;
	OPTdimTwo = 2;
    }
    swOPT = max(max(max(sw_a11+sw_b11, sw_a12+sw_b12), sw_a22+sw_b22), sw_a21+sw_b21);
    return std::make_tuple(OPTdimOne, OPTdimTwo, swOPT);
}

//Compute the worst PNE state and its social welfare
std::tuple<int, int, double> worstPNE(vector<vector<double>> &sw)
{ 
	/*            B1                   B2          
	 * A1  (sw_a11, sw_b11)  |  (sw_a12, sw_b12)
	 * A2  (sw_a21, sw_b21)  |  (sw_a22, sw_b22)
	 */
	double swPNE = 0; 
	int stateDimOne = 0;
	int stateDimTwo = 0;
	const double &sw_a11 = sw[0][0], &sw_b11 = sw[0][1]; 
	const double &sw_a12 = sw[1][0], &sw_b12 = sw[1][1];  
	const double &sw_a21 = sw[2][0], &sw_b21 = sw[2][1]; 
	const double &sw_a22 = sw[3][0], &sw_b22 = sw[3][1]; 

	if (sw_a11 >= sw_a21 && sw_b11 >= sw_b12) { 
		swPNE = sw_a11 + sw_b11;
		stateDimOne = 1;
		stateDimTwo = 1;
	}
	if (sw_a21 >= sw_a11 && sw_b21 >= sw_b22) {
		if (sw_a21 + sw_b21 < swPNE) { 
			swPNE = sw_a21 + sw_b21; 
			stateDimOne = 2;
			stateDimTwo = 1;
		} 
	}
	if (sw_a22 >= sw_a12 && sw_b22 >= sw_b21) {
		if (sw_a22 + sw_b22 < swPNE) { 
			swPNE = sw_a22 + sw_b22; 
			stateDimOne = 2;
			stateDimTwo = 2;
		} 
	}
	if (sw_a12 >= sw_a22 && sw_b12 >= sw_b11) {
		if (sw_a12 + sw_b12 < swPNE) { 
			swPNE = sw_a12 + sw_b12; 
			stateDimOne = 1;
			stateDimTwo = 2;
		} 
	}  
	return std::make_tuple(stateDimOne, stateDimTwo, swPNE);
}

