#pragma once


//for the contiguous chunk of floats in our vertex buffer.
//we assign every single float this way because the first
//20 * sizeof(float) chunk of memory corresponds to the empty sudoku board.
//which is entirely different than the other quadrilaterals that we set up
//there after. It also has a unique texture slot identifier that is not
//dependent on our sudoku board configuration, but it is hard to set up preemptively
//because it resides in a contiguous chunk of memory.
//the function underneath is for every individual cell in our grid, which has different values
//each for their x, y positions, texture coordinates and it's texture slot.

struct Vertex {
    float f1, f2, f3, f4, f5;
};

static void setSudokuStage(Vertex*& start) {
    start->f1 = -0.5f;
    start->f2 = -0.5f;
    start->f3 = 0.0f;
    start->f4 = 0.0f;
    start->f5 = 0.0f;
    start++;
    start->f1 = 0.5f;
    start->f2 = -0.5f;
    start->f3 = 1.0f;
    start->f4 = 0.0f;
    start->f5 = 0.0f;
    start++;
    start->f1 = 0.5f;
    start->f2 = 0.5f;
    start->f3 = 1.0f;
    start->f4 = 1.0f;
    start->f5 = 0.0f;
    start++;
    start->f1 = -0.5f;
    start->f2 = 0.5f;
    start->f3 = 0.0f;
    start->f4 = 1.0f;
    start->f5 = 0.0f;
    start++;
}

static void getBackThing(Vertex*& start, float x, float y, float particularNumber) {
    start->f1 = x;
    start->f2 = y - 0.07f;
    start->f3 = 0.0f;
    start->f4 = 0.0f;
    start->f5 = particularNumber;
    start++;
    start->f1 = x + 0.05f;
    start->f2 = y - 0.07f;
    start->f3 = 1.0f;
    start->f4 = 0.0f;
    start->f5 = particularNumber;
    start++;
    start->f1 = x + 0.05f;
    start->f2 = y;
    start->f3 = 1.0f;
    start->f4 = 1.0f;
    start->f5 = particularNumber;
    start++;
    start->f1 = x;
    start->f2 = y;
    start->f3 = 0.0f;
    start->f4 = 1.0f;
    start->f5 = particularNumber;
    start++;
}
