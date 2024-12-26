#include <iostream>
#include <string>
#include <fstream>
#include <vector> //bc of its dynamic size
#include <algorithm> //for min() function
#include <climits> //for INT_MAX to represent a very large number

using namespace std;

struct Process {
	string name;
	int arrival_time;
	int processing_time;
	int rank;
	int response_time;
	int turnaround_time;
	int delay;
	int index;
	bool process_done = false; //flag to track if the process was ordered successfully
};

vector<Process> readProcessesFromFile(const string& filename) {
	ifstream infile(filename);

	if (!infile) {
		cerr << "File " << filename << " couldn't open." << endl;
		return {}; //{} returns empty vector
	}

	int n;
	infile >> n; //number of processes
	infile.ignore(); //ignore newline after n

	vector<Process> allprocesses;
	for (int i = 0; i < n; ++i) {
		Process p;
		infile >> p.name >> p.arrival_time >> p.processing_time >> p.rank;
		p.index = i;
		allprocesses.push_back(p);
	}
	return allprocesses;
}

bool compareProcesses(const Process& a, const Process& b) {
	//const is to make sure that a & b are read-only within the function (no modifying)
	//& (reference) bc we're not making a new copy of the objects, to save memory
	if (a.rank != b.rank)
		return a.rank < b.rank;
	if (a.arrival_time != b.arrival_time)
		return a.arrival_time < b.arrival_time;
	return a.index < b.index; //if both rank and arrival are the same, go by index
}

void calculateProcessTimes(vector<Process>& allprocesses, vector<Process>& order) {
	int current_time = 0;

	while (order.size() < allprocesses.size()) { //loop until all processes are processed
		int best_process = -1; //flag to track the best process to execute first

		for (int i = 0; i < allprocesses.size(); ++i) { //loop over all processes
			Process& p = allprocesses[i];

			if (!p.process_done && p.arrival_time <= current_time) { //proccess must have arrived & is not done yet
				if (best_process == -1)
					best_process = i; //set the current process as the initial reference
				else if (compareProcesses(p, allprocesses[best_process])) //compare with the current best process
					best_process = i;
			}
		}

		//if no process is ready, move current time to the closest next arrival time of any process
		//processes listed in (`in.txt`) aren't guaranteed to be in any specific order by arrival time, we must search for it
		if (best_process == -1) {
			int next_arrival_time = INT_MAX;

			for (int i = 0; i < allprocesses.size(); ++i) {
				Process& p = allprocesses[i];
				if (!p.process_done && p.arrival_time > current_time)
					next_arrival_time = min(next_arrival_time, p.arrival_time);
			}

			current_time = next_arrival_time;
			continue; //jump back to the beginning of the while loop
		}

		Process& selected_p = allprocesses[best_process];

		selected_p.response_time = current_time - selected_p.arrival_time; //1st start - arrival
		current_time += selected_p.processing_time; //to find current end time of the selected process
		selected_p.turnaround_time = current_time - selected_p.arrival_time; //end - arrival
		selected_p.delay = selected_p.turnaround_time - selected_p.processing_time; //turnaround - processing

		selected_p.process_done = true; //process is scheduled now
		order.push_back(selected_p); //add to the vector<order>
	}
}

void outputProcessesToFile(const vector<Process>& allprocesses, const string& filename, const vector<Process>& order) {
	ofstream outfile(filename);
	if (!outfile) {
		cerr << "File " << filename << " couldn't be created." << endl;
		return; //bc its void
	}

	for (int i = 0; i < order.size(); ++i) {
		const Process& p = order[i];

		outfile << p.name << ": (response=" << p.response_time
			<< ", turnaround=" << p.turnaround_time
			<< ", delay=" << p.delay << ")" << endl;
	}

	for (int i=0; i < order.size(); ++i) {
		outfile << order[i].name; //only process names in order
	}

	outfile << endl;
	outfile.close();
}


int main() {
	
	vector<Process> allprocesses = readProcessesFromFile("in.txt");
	
	if (allprocesses.empty()) {
		cerr << "Error reading from file.\n";
		return 1;
	}

	vector<Process> order; //to store ordered processes
	calculateProcessTimes(allprocesses, order);
	outputProcessesToFile(allprocesses, "out.txt", order);

	return 0;
}
