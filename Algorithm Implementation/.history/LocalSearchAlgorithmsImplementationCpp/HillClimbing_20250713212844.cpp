#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <limits>

class HillClimbing {
private:
    std::vector<int> current_solution;
    int current_cost;
    int max_iterations;
    std::function<int(const std::vector<int>&)> cost_function;

public:
    HillClimbing() : current_cost(std::numeric_limits<int>::max()), max_iterations(1000) {}

    void setInitialSolution(const std::vector<int>& solution) {
        current_solution = solution;
        current_cost = cost_function(current_solution);
    }

    void setCostFunction(const std::function<int(const std::vector<int>&)>& func) {
        cost_function = func;
    }

    void setMaxIterations(int max_iter) {
        max_iterations = max_iter;
    }

    std::vector<int> getCurrentSolution() const {
        return current_solution;
    }

    int getCurrentCost() const {
        return current_cost;
    }

    void run() {
        if (!cost_function) {
            std::cerr << "Cost function not set!" << std::endl;
            return;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        int iteration = 0;

        while (iteration < max_iterations) {
            std::vector<int> neighbor = current_solution;
            // Generate a neighbor by randomly modifying one element
            std::uniform_int_distribution<> dis_index(0, neighbor.size() - 1);
            int idx = dis_index(gen);
            std::uniform_int_distribution<> dis_value(-10, 10);
            neighbor[idx] += dis_value(gen);

            int neighbor_cost = cost_function(neighbor);
            if (neighbor_cost < current_cost) {
                current_solution = neighbor;
                current_cost = neighbor_cost;
            }
            iteration++;
        }
    }
};

// Example usage
int main() {
    HillClimbing hc;

    // Define a simple cost function: sum of squares
    hc.setCostFunction([](const std::vector<int>& solution) {
        int cost = 0;
        for (int x : solution) {
            cost += x * x;
        }
        return cost;
    });

    // Initial solution
    std::vector<int> initial_solution = {5, -3, 2, 7};
    hc.setInitialSolution(initial_solution);
    hc.setMaxIterations(1000);

    hc.run();

    std::vector<int> best_solution = hc.getCurrentSolution();
    int best_cost = hc.getCurrentCost();

    std::cout << "Best solution found: ";
    for (int x : best_solution) {
        std::cout << x << " ";
    }
    std::cout << "\nCost: " << best_cost << std::endl;

    return 0;
}
