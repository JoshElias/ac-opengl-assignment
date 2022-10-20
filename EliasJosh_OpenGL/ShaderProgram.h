#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

typedef std::map< std::string, GLuint > ShaderAttributeMap;

class ShaderProgram
{
public:
	ShaderProgram(std::string);

	const std::string& GetName();

	void AttachShader(std::shared_ptr<Shader>);
	void Link();
	void Unbind();

	void BindAttributes(GLuint, const std::string&);
	GLint GetUniformLocation(const std::string&) const;

	void SetUniform1f(const std::string&, float) const;
	void SetUniform2f(const std::string&,float,float) const;
	void SetUniform3f(const std::string&,float,float,float) const;
	void SetUniform4f(const std::string&,float,float,float,float) const;

	void SetUniform1fv(const std::string&,size_t,const float*) const;
	void SetUniform2fv(const std::string&,size_t,const float*) const;
	void SetUniform3fv(const std::string&,size_t,const float*) const;
	void SetUniform4fv(const std::string&,size_t,const float*) const;

	void SetUniform1i(const std::string&,GLint) const;
	void SetUniform2i(const std::string&,GLint,GLint) const;
	void SetUniform3i(const std::string&,GLint,GLint,GLint) const;
	void SetUniform4i( const std::string&,GLint,GLint,GLint,GLint) const;

	void SetUniform1iv(const std::string&,size_t,const GLint*) const;
	void SetUniform2iv(const std::string&,size_t,const GLint*) const;
	void SetUniform3iv(const std::string&,size_t, const GLint*) const;
	void SetUniform4iv(const std::string&,size_t ,const GLint*) const;

	void SetUniformMatrix2fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix3fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix4fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix2x3fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix2x4fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix3x2fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix3x4fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix4x2fv(const std::string&,size_t,bool,const float*) const;
	void SetUniformMatrix4x3fv(const std::string&, size_t,bool,const float*) const;
	
	void GetUniformfv(const std::string&,float*) const;
	void GetUniformiv(const std::string&,int32_t*) const;
	
	void EnableAttributeArray(const std::string&) const;
	void DisableAttributeArray(const std::string&) const;
	
	void VertexAttributePointer(const std::string&,GLint,GLenum,GLsizei,const GLvoid *,bool) const;
	
	void VertexAttribute1f(const std::string&,GLfloat) const;
	void VertexAttribute2f(const std::string&,GLfloat,GLfloat) const;
	void VertexAttribute3f(const std::string&,GLfloat,GLfloat,GLfloat) const;
	void VertexAttribute4f(const std::string&,GLfloat,GLfloat,GLfloat,GLfloat) const;
	
	void VertexAttribute1fv(const std::string&,const GLfloat *) const;
	void VertexAttribute2fv(const std::string&,const GLfloat *) const;
	void VertexAttribute3fv(const std::string&,const GLfloat *) const;
	void VertexAttribute4fv(const std::string&, const GLfloat*) const;
	
	void VertexAttribute4iv(const std::string&,const GLint *) const;
	void VertexAttribute4uiv(const std::string&,const GLuint *) const;
	void VertexAttribute4Niv(const std::string&,const GLint *) const;
	void VertexAttribute4Nuiv(const std::string&,const GLuint *) const;


private:
	std::string m_Name;
	GLuint m_Handle;

	std::vector< std::shared_ptr<Shader> > m_Shaders;
	ShaderAttributeMap m_Attributes;

	bool m_IsLinked;



};


#endif