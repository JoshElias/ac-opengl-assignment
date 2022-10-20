#ifndef _SHADER_H_
#define _SHADER_H_


enum SHADERTYPE {
			VERTEX,
			FRAGMENT,
			GEOMETRY
};

class Shader
{
public:
	Shader(std::string, SHADERTYPE);
	~Shader();

	const GLuint& GetHandle();
	void Load(std::string);
	void PrintLog(const GLuint&);
	void Compile();

	

private:
	std::string m_Name;
	SHADERTYPE m_Type;

	std::shared_ptr< std::string > m_Source;
	GLuint m_Handle;
	bool m_IsCompiled;
};


#endif
