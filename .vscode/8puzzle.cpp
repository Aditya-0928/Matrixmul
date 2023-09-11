#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// Structure to represent the state of the problem
struct State {
    int missionaries; // Number of missionaries on the left side
    int cannibals;    // Number of cannibals on the left side
    bool boat;        // Represents the side of the boat: true for left, false for right

    // Constructor
    State(int m, int c, bool b) : missionaries(m), cannibals(c), boat(b) {}
};

// Function to check if a state is valid
bool isValidState(const State& state) {
    // Check if the number of missionaries is greater than or equal to the number of cannibals on both sides
    if (state.missionaries < 0 || state.missionaries > 3 || state.cannibals < 0 || state.cannibals > 3 ||
        (state.missionaries != 0 && state.missionaries < state.cannibals) ||
        (state.missionaries != 3 && (3 - state.missionaries) < (3 - state.cannibals)))
        return false;

    return true;
}

// Function to check if a state is the goal state
bool isGoalState(const State& state) {
    return state.missionaries == 0 && state.cannibals == 0 && !state.boat;
}

// Function to generate successor states
vector<State> generateSuccessors(const State& state) {
    vector<State> successors;

    // Generate all possible combinations of missionaries and cannibals to move from one side to the other
    for (int m = 0; m <= state.missionaries; m++) {
        for (int c = 0; c <= state.cannibals; c++) {
            // Ignore the case when there are more cannibals than missionaries on either side
            if ((m == 0 && c == 0) || (m + c <= 2 && m + c >= 1)) {
                // Generate the successor state based on the side of the boat
                if (state.boat) {
                    successors.push_back(State(state.missionaries - m, state.cannibals - c, !state.boat));
                } else {
                    successors.push_back(State(state.missionaries + m, state.cannibals + c, !state.boat));
                }
            }
        }
    }

    return successors;
}

// Function to solve the problem using breadth-first search
bool solveBFS() {
    queue<State> states;
    set<State> visited;
    State initial(3, 3, true);
    states.push(initial);

    while (!states.empty()) {
        State current = states.front();
        states.pop();

        // Check if the current state is the goal state
        if (isGoalState(current)) {
            cout << "Goal state reached!" << endl;
            return true;
        }

        // Check if the current state has been visited
        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);

        // Generate and enqueue successor states
        vector<State> successors = generateSuccessors(current);
        for (const auto& successor : successors) {
            if (isValidState(successor) && visited.find(successor) == visited.end()) {
                states.push(successor);
            }
        }
    }

    cout << "Goal state not reachable!" << endl;
    return false;
}

int main() {
    cout << "Solving Missionaries and Cannibals problem using Breadth-First Search:" << endl;

    if (solveBFS()) {
        cout << "Solution found!" << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
