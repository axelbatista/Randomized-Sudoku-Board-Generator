#pragma once

struct Vertex;

class VertexBuffer {
public:
	VertexBuffer(Vertex* structure, int size);
	void unBind();
	void setLayout(int index, int number, int stride, int offset);
	~VertexBuffer();
private:
	unsigned int renderId;
};


class IndexBuffer {
public:
	IndexBuffer(unsigned int* structure, int indices);
	void unBind();
	~IndexBuffer();
private:
	unsigned int renderId;
};
