#include <string>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string& filepath);
	void Use();
	void setUniform(const std::string& part, float v1, float v2, float v3, float v4);
	void setUniform(const std::string& part, int slot);
	void setUniform(const std::string& part, int number, int* array);
	inline int getId() { return programId; }
	~Shader();
private:
	int getUniform(const std::string& part);
	int Create(const std::string& shade, int type);
	int programId;
	std::unordered_map<std::string, int> map;
};