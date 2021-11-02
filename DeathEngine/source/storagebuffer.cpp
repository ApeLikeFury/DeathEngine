#include <GL/glew.h>
#include "storagebuffer.h"

storagebuffer::storagebuffer(std::vector<float> buffer_data, unsigned int location)
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer_id);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size(buffer_data)*sizeof(float), buffer_data.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, location, buffer_id);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
