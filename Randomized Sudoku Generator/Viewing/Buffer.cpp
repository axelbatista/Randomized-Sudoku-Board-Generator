#include "Buffer.h"
#include <GL/glew.h>



VertexBuffer::VertexBuffer(Vertex* structure, int size) {
	glCreateBuffers(1, &renderId);
	glBindBuffer(GL_ARRAY_BUFFER, renderId);
	glBufferData(GL_ARRAY_BUFFER, size, structure, GL_STATIC_DRAW);
}

void VertexBuffer::setLayout(int index, int number, int stride, int offset) {
	glEnableVertexArrayAttrib(renderId, index);
	glVertexAttribPointer(index, number, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
}

void VertexBuffer::unBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &renderId);
}


IndexBuffer::IndexBuffer(unsigned int* structure, int indices) {
	glCreateBuffers(1, &renderId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices * sizeof(unsigned int), structure, GL_STATIC_DRAW);
}

void IndexBuffer::unBind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &renderId);
}