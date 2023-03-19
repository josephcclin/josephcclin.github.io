#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "political_game.h"

#define num_simu 100000000

int main(int argc, char ** argv) {
	double tmpPoA = 0, maxPoA = 0, maxSW, worstPNESW;
	int worstPNEdimOne, worstPNEdimTwo;
	int OPTdimOne, OPTdimTwo;
	int NoPNE_EXIST = 0;
	int available_count = 0;
	string funcType = "";	
	if (argc != 2) { 
		cerr << "Usage: \n\t" << "political_game [MODEL]\n" << "MODEL:\n\t" 
		<< "\"-S (softmax)\", \"-L (linear-link)\" or\"-B (Bradley-Terry)\"\n" << endl;
		return 1;
	} else { 
		funcType = argv[1]; 
		if (funcType == "-h") {
			cerr << "Usage: \n\t" << "political_game [MODEL]\n" << "MODEL:\n\t" 
			<< "\"-S (softmax)\", \"-L (linear-link)\" or\"-B (Bradley-Terry)\"\n" << endl;
			return 1;
		}
	} 
	vector<vector<double>> SW_MAT, SW_MAT_ALL; 
	map<string,string> funcName { 
		{"-B", "Bradley-Terry"}, 
		{"-L", "linear-link"}, 
		{"-S", "softmax"}, 
		{"Bradley-Terry", "Bradley-Terry"}, 
		{"linear-link", "linear-link"}, 
		{"softmax", "softmax"} 
	};

	for (size_t i=0; i<num_simu; i++) { 
		Game g; 
		// skip the instance that is not egoistic
		if (!g.egoismCheck(g.A, g.B) || !g.betterThanSwing(g.A, g.B)) continue;
		
		g.A.reOrder(); 
		g.B.reOrder();
		available_count += 1;
		
		SetExpUti(g.A.cand1, g.B.cand1, funcType);
		SW_MAT.push_back({g.A.cand1.get_expUti(), g.B.cand1.get_expUti()});
		SW_MAT_ALL.push_back({g.A.cand1.get_expSW(), g.B.cand1.get_expSW()});
		
		SetExpUti(g.A.cand1, g.B.cand2, funcType);
		SW_MAT.push_back({g.A.cand1.get_expUti(), g.B.cand2.get_expUti()});
		SW_MAT_ALL.push_back({g.A.cand1.get_expSW(), g.B.cand2.get_expSW()});

		SetExpUti(g.A.cand2, g.B.cand1, funcType);
		SW_MAT.push_back({g.A.cand2.get_expUti(), g.B.cand1.get_expUti()});
		SW_MAT_ALL.push_back({g.A.cand2.get_expSW(), g.B.cand1.get_expSW()});

		SetExpUti(g.A.cand2, g.B.cand2, funcType);
		SW_MAT.push_back({g.A.cand2.get_expUti(), g.B.cand2.get_expUti()});
		SW_MAT_ALL.push_back({g.A.cand2.get_expSW(), g.B.cand2.get_expSW()});

		//tmpPoA = PoA(SW_MAT); 
		tmpPoA = PoA(SW_MAT_ALL); 
		auto [OPTdimOne, OPTdimTwo, maxSW] = maxSocWel(SW_MAT_ALL);
		auto [worstPNEdimOne, worstPNEdimTwo, worstPNESW] = worstPNE(SW_MAT_ALL);
		
		if (!checkNE(SW_MAT) || maxPoA < tmpPoA) { 
			cout << "# iteration " << i+1; 
			if (!checkNE(SW_MAT)) { 
				NoPNE_EXIST += 1; 
				cout << " (NoPNE!)";
			} 
			cout <<  ": " << OPTdimOne << ", " << OPTdimTwo << ": " << maxSW << " (max social welfare)" << endl << endl;
			cout << "Party A's candidates: " << "(" << g.A.cand1.get_sup() << ", " << g.A.cand1.get_opp() << ", ";
			cout << g.A.cand1.get_swi() << "), "; // << g.A.cand1.uti_sum();
			cout << "(" << g.A.cand2.get_sup() <<", " << g.A.cand2.get_opp() << ", ";
		        cout << g.A.cand2.get_swi() << ") " << endl; // << g.A.cand2.uti_sum() << endl;
			cout << "Party B's candidates: " << "(" << g.B.cand1.get_sup() << ", " << g.B.cand1.get_opp() << ", ";
			cout << g.B.cand1.get_swi() << "), "; // << g.B.cand1.uti_sum(); 
			cout << "(" << g.B.cand2.get_sup() <<", " << g.B.cand2.get_opp() << ", "; 
			cout << g.B.cand2.get_swi() << ") " << endl << endl; //g.B.cand2.uti_sum() << endl << endl;

			//cout.precision(10);  
			cout << setw(12) << SW_MAT[0][0] << left << ", " << right << setw(12) << SW_MAT[0][1] << "\t" 
				 << setw(12) << SW_MAT[1][0] << left << ", " << right << setw(12) << SW_MAT[1][1] << endl; 
			cout << setw(12) << SW_MAT[2][0] << left << ", " << right << setw(12) << SW_MAT[2][1] << "\t" 
				 << setw(12) << SW_MAT[3][0] << left << ", " << right << setw(12) << SW_MAT[3][1] << endl; 
			if (maxPoA < tmpPoA) { 
				cout << "PoA updated: " << tmpPoA << "\n";
				cout << "PNE state: " << worstPNEdimOne << ", " << worstPNEdimTwo << ": " << worstPNESW << endl << endl;
				maxPoA = tmpPoA;
			} else cout << endl;
		}
		
		SW_MAT.clear();
		SW_MAT_ALL.clear();
	}
	cout << "## Model: " << (funcName.find(funcType))->second << endl;
	if (NoPNE_EXIST > 0) cout << "## Found an instance of No PNE." << " (ratio: " << (float)NoPNE_EXIST*100/available_count << "\%)" << endl;
	else cout << "## Every instance gets a PNE." << endl;
	cout << "## Worst PoA: " << maxPoA << endl; 
   	return 0;
}
