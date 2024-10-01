#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

// Function prototypes
void displaySeatingChart(const std::vector<std::vector<bool>>& seatingChart);
bool assignSeat(std::vector<std::vector<bool>>& seatingChart, int row, int seat);
void displayFinalResults(const std::vector<std::vector<bool>>& seatingChart,
                         const std::vector<std::pair<int, int>>& takenSeats);

int main() {
    int numRows, seatsPerRow;

    // Prompt user for number of rows and seats per row
    std::cout << "Enter the number of rows: ";
    std::cin >> numRows;
    std::cout << "Enter the number of seats per row: ";
    std::cin >> seatsPerRow;

    if (numRows <= 0 || seatsPerRow <= 0) {
        std::cerr << "Number of rows and seats per row must be positive integers." << std::endl;
        return 1;
    }

    // Initialize seating chart
    std::vector<std::vector<bool>> seatingChart(numRows, std::vector<bool>(seatsPerRow, false));
    std::vector<std::pair<int, int>> takenSeats;

    bool continueBooking = true;
    while (continueBooking) {
        // Display initial seating assignment
        displaySeatingChart(seatingChart);

        int row, seat;
        std::cout << "Enter the row and seat number to assign (or -1 -1 to exit): ";
        std::cin >> row >> seat;

        if (row == -1 && seat == -1) {
            continueBooking = false;
        } else {
            try {
                if (row < 0 || row >= numRows || seat < 0 || seat >= seatsPerRow) {
                    throw std::out_of_range("Invalid seat number.");
                }
                if (assignSeat(seatingChart, row, seat)) {
                    takenSeats.push_back({row, seat});
                } else {
                    std::cout << "Seat already taken. Please choose another seat." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    // Display final seating chart and results
    displaySeatingChart(seatingChart);
    displayFinalResults(seatingChart, takenSeats);

    return 0;
}

void displaySeatingChart(const std::vector<std::vector<bool>>& seatingChart) {
    std::cout << "\nSeating Chart:\n";
    std::cout << "  ";
    for (int i = 0; i < seatingChart[0].size(); ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < seatingChart.size(); ++row) {
        std::cout << row << " ";
        for (bool seat : seatingChart[row]) {
            std::cout << (seat ? "X " : "O ");
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

bool assignSeat(std::vector<std::vector<bool>>& seatingChart, int row, int seat) {
    if (seatingChart[row][seat] == false) {
        seatingChart[row][seat] = true;
        return true;
    }
    return false;
}

void displayFinalResults(const std::vector<std::vector<bool>>& seatingChart,
                         const std::vector<std::pair<int, int>>& takenSeats) {
    int availableSeats = 0;
    for (const auto& row : seatingChart) {
        for (bool seat : row) {
            if (!seat) {
                ++availableSeats;
            }
        }
    }

    std::cout << "\nFinal Seating Chart:\n";
    displaySeatingChart(seatingChart);

    std::cout << "Number of seats still available: " << availableSeats << std::endl;
    std::cout << "Seats taken in the order they were assigned:\n";
    for (const auto& seat : takenSeats) {
        std::cout << "Row " << seat.first << ", Seat " << seat.second << std::endl;
    }
}

