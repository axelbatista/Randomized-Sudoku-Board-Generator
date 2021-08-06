#pragma once


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
