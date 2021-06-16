

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
std::random_device rng;
std::mt19937 mt(rng());                     //necessary containers, mersenne twister, and boolean to check if we filled out the whole grid.
std::vector<int> container(9);
std::vector<std::vector<bool>> row(9, std::vector<bool>(9));
std::vector<std::vector<bool>> column(9, std::vector<bool>(9));
std::vector<int> matrix(81);
bool subBox[3][3][9];
bool finished = false;

void startUp() {                        //the container needs to be inputted with random values, so we only do it here initially before calling
    for (int i = 1; i < 10; i++) {      //sudokuGenerator because the container needs to be initialized here, where every other instance upon entry
        container[i - 1] = i;           //into a new row can just be done with a call to std::shuffle.
    }
    std::shuffle(container.begin(), container.end(), mt);
}

void sudokuGenerator(int x, int y) {
    if (y == 9) {
        if (!finished) {
            for (int h = 0; h < 13; h++) {

                std::cout << "- ";
            }
            std::cout << '\n';
            for (int j = 0; j < 9; j++) {
                for (int i = 0; i < 9; i++) {
                    if (i == 8) {
                        std::cout << matrix[j * 9 + i] << " |\n";
                        if ((j + 1) % 3 == 0 && j != 8) {
                            for (int h = 0; h < 13; h++) {
                                if (h == 0 || h == 12) {
                                    std::cout << "| ";
                                }
                                else {
                                    std::cout << "- ";
                                }
                            }
                            std::cout << '\n';
                        }
                    }
                    else if (i == 0) {
                        std::cout << "| " << matrix[j * 9 + i] << ' ';
                    }
                    else if ((i + 1) % 3 == 0) {
                        std::cout << matrix[j * 9 + i] << " | ";
                    }
                    else {
                        std::cout << matrix[j * 9 + i] << ' ';
                    }
                }
            }
            for (int h = 0; h < 13; h++) {
                std::cout << "- ";
            }
        }
        finished = true;
        return;
    }

    //the above part is just for printing believe it or not, this part below is the actual algorithm for generating the randomized sudoku board
    //the algorithm goes that out of a randomized container, we pick elligible values to be put down from left to right, up and down through the board.
    //anything elligible is marked down accordingly to be checked within any one individual state for elligibility, and then we recurse upon every position on the board
    //there being 9^2 places on the board so that we can go back to any one position on the board and revert/change it if need be so as to come up
    //with a valid configuration. Since we transition between states through a function call rather than through an iterator, it requires us to
    //do the proper bounds checking so that we don't get an out of bounds exception. This is for the most part just doing x++ where we sometimes
    //do y++ on the occasion that we're on the last value on any one row.
    if (!finished) {
        for (int each : container) {
            if (!column[x][each - 1] && !row[y][each - 1] && !subBox[x / 3][y / 3][each - 1]) {
                column[x][each - 1] = row[y][each - 1] = subBox[x / 3][y / 3][each - 1] = true;
                matrix[y * 9 + x] = each;
                if (x == 8) {
                    std::shuffle(container.begin(), container.end(), mt);
                    sudokuGenerator(0, y + 1);
                    column[x][each - 1] = row[y][each - 1] = subBox[x / 3][y / 3][each - 1] = false;
                }
                else {
                    sudokuGenerator(x + 1, y);
                    column[x][each - 1] = row[y][each - 1] = subBox[x / 3][y / 3][each - 1] = false;
                }
            }
        }
    }
}

int main()
{
    startUp();
    sudokuGenerator(0, 0);
}


