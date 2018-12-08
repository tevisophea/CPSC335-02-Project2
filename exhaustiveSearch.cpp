// Assignment 2: Topology recognition problem                                   
// Doina Bein                                                                   
// Given a network with n>3 nodes and a weight matrix W[0..n−1, 0..n−1] of      
// positive integers, of a weighted, connected undirected graph modeling        
// a network, decide whether the network is one of the topologies, if any:      
// ring, star, fully connected mesh. Note: represent infinity by the value 100.
// INPUT: a positive integer n and a list of n^2 positive values          
// OUTPUT: message "ring" or "star" or "complete" or "neither"                  

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>

using namespace std;

int main() {
	int n, i, j, count=0, center=0;
	int W[100][100];
	bool cond;

	// display the header                                                         
	cout << endl << "CPSC 335-03 - Programming Assignment #2" << endl;
	cout << "Joshua Marvel, Tevisophea Heng" << endl;
	cout << "Topology recognition algorithm" << endl;
	cout << "Enter the number of nodes in the topology" << endl;

	// read the number of nodes                                                   
	cin >> n;

	// read the weight matrix                                                     
	cout << "Enter the positive weights, 100 for infinity" << endl;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			cin >> W[i][j];

	// Start the chronograph to time the execution of the algorithm               
	auto start = chrono::high_resolution_clock::now();

	cout << "The topology is" << endl;
	cond = true;

	//loop to check whether the topology is a ring   
	//each vertex must exactly connect to two other vertices
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
		//keep increment count if count is not equal to 100 
			if (W[i][j] != 100)
				count++;
		}

		//count should be equal to 3, 2 vertices and 0, not connected to anything
		if (count != 3) {
			cond = false;
			break;
		}
		//reset count = 0 again so it can keep checking each row 
		count = 0; 
	}

	if (cond) {
		cout << "ring" << endl;
		auto end = chrono::high_resolution_clock::now();

		// Print the elapsed time in seconds and fractions of seconds
		// Displaying the output is NOT part of the algorithm so the timer ends before displaying the output    
		int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
		double seconds = microseconds / 1E6;
		cout << "elapsed time: " << seconds << " seconds" << endl;
		return EXIT_SUCCESS;
	}

	//reset count to 0 again to keep count for the star
	count = 0;
	cond = true;
	 //loop to check whether the topology is a star      
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
		//keep count of the number of vertex with weight that is not 0 or 100
			if ((W[i][j] != 0) && (W[i][j] != 100))
				count++;
		}

		//n-1 must connect to one other vertex
		//center vertex must connect to n -1 other vertices
		if (count == (n - 1))
				center++;
		if (count > 1 && count != (n - 1))
		{
			cond = false; 
			break;
		}

		//reset count = 0 again so it can keep checking each row 
		count = 0;
	}

	//set count = 0 again
	if (cond && (center == 1)) {
		cout << "star" << endl;
		auto end = chrono::high_resolution_clock::now();
		int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
		double seconds = microseconds / 1E6;
		cout << "elapsed time: " << seconds << " seconds" << endl;
		return EXIT_SUCCESS;
	}

	cond = true;


	//loop to check whether the topology is a fully connected mesh     
	//Each vertex connect to exactly n-1 other vertices 
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
		//check if there is an infinite weight
			if (W[i][j] == 100) {
				cond = false;
				break;
			}
			//check for zero weight and the weight must correspond as it connects with all n-1 vertices
			else if ((W[i][j] == 0) && W[i][n - 1 - j] == (W[n - 1 - j][i]))
				cond = true;
		}
	}

	if (cond)
		cout << "fully connected mesh" << endl;
	else
		cout << "neither" << endl;

	// End the chronograph to time the loop                                       
	auto end = chrono::high_resolution_clock::now();   
	int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
	double seconds = microseconds / 1E6;
	cout << "elapsed time: " << seconds << " seconds" << endl;

	return EXIT_SUCCESS;
}
