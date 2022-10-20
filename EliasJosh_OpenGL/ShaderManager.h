#ifndef _SHADER_MANAGER_H
#define _SHADER_MANAGER_H

typedef std::map< std::string, std::shared_ptr<ShaderProgram> > ShaderProgramMap;
typedef std::map< std::string, std::shared_ptr<Shader> > ShaderMap;

class ShaderManager
{
public:
	static ShaderManager& Instance() { static ShaderManager sm; return sm; }

	std::shared_ptr<ShaderProgram> m_NullProgram;

	GLuint GetProgramID(const std::string&);

	void CreateShaderProgram(const std::string& );
	void LoadShaderSource(const std::string&,const std::string&);
	void AddShader(const std::string&,SHADERTYPE);
	void AttachShaderToProgram(const std::string&,const std::string&);
	void CompileShader(const std::string&);
	void LinkShaderProgram(const std::string&);
	void BindAttribute(const std::string&,GLuint,const std::string&);
	void UseProgram(const std::string&);

	std::shared_ptr<ShaderProgram> operator[](const std::string&);

private:
	ShaderManager();
	//ShaderManager(ShaderManager&) = delete;

	ShaderProgramMap m_ShaderPrograms;
	ShaderMap m_Shaders;

};

#endif