#include "Common.h"

ShaderProgram::ShaderProgram(std::string _name)
{
	// if name is NULL, make a null object
	if(_name != "NULL")
		m_Handle = glCreateProgram();
	else 
		m_Handle = 0;

	fprintf(stdout,"Shader Program %s Created", m_Handle);

	m_IsLinked=false;
}

const std::string& ShaderProgram::GetName() { return m_Name; }

void ShaderProgram::AttachShader( std::shared_ptr<Shader> _shader)
{
	m_Shaders.push_back( _shader);
	glAttachShader(m_Handle, _shader->GetHandle());
}

void ShaderProgram::Link()
{
	try {
		glLinkProgram(m_Handle);

		if( glGetError() != GL_NO_ERROR ) 
			throw std::runtime_error( std::string("Error Compiling ShaderProgram: %s", m_Handle) );

		GLint infologLength = 0;
		// Get Length of Shader's log length
		glGetProgramiv(m_Handle,GL_INFO_LOG_LENGTH,&infologLength);
		if(infologLength > 0)
		{
			std::unique_ptr<char> infoLog( new char[infologLength] );
			GLint charsWritten  = 0;
			// Copy Info Log
			glGetProgramInfoLog(m_Handle, infologLength, &charsWritten, infoLog.get() );

			fprintf(stdout, "ShaderProgram Linked: %s", infoLog);

			glGetProgramiv(m_Handle, GL_LINK_STATUS,&infologLength);
			if( infologLength == 0) // ShaderProgram ins't in the GPU
				throw std::runtime_error("Program link failed");

		}
		m_IsLinked=true;

	}  catch( std::exception& err ) {
		fprintf(stdout, "Exception Found: %s", err.what());
	} catch ( ... ) {
		fprintf(stdout,"Unknown Exception");
	}
}

void ShaderProgram::BindAttributes(GLuint _index, const std::string& _attributeName)
{
	if(m_IsLinked == true)
		std::runtime_error("Don't Bind Attributes After Linking...yet...");

	m_Attributes[_attributeName] = _index;
	glBindAttribLocation(m_Handle, _index, _attributeName.c_str());

	fprintf(stdout,"Binding Attributes of ShaderProgram: %s", m_Handle);

	if( glGetError() )
		std::runtime_error( std::string("Open(L Error After Binding Attributes on ShaderProgram: %s", m_Handle ));
}

GLint ShaderProgram::GetUniformLocation( const std::string& _name ) const
{
	GLint uniformLocation = glGetUniformLocation( m_Handle, _name.c_str() );
	if( uniformLocation = -1 ) 
		throw std::runtime_error( std::string("Trying To get invalid Uniform Location: %s", m_Handle) );

	return uniformLocation;
}


void ShaderProgram::EnableAttributeArray(const std::string& _name ) const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);

	if(attributeIterator != m_Attributes.end())
	{
		fprintf(stdout, "Enable attribute: %s ",attributeIterator->second);
		glEnableVertexAttribArray( attributeIterator->second  );
	}
}
void ShaderProgram::DisableAttributeArray(const std::string& _name ) const
{
	glDisableVertexAttribArray(GetUniformLocation(_name));

}

void ShaderProgram::VertexAttributePointer(const std::string& _name, GLint _size, GLenum _type,
										   GLsizei _stride, const GLvoid *_data, bool _normalise ) const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name.c_str());

	if( attributeIterator == m_Attributes.end() ) 
		throw std::runtime_error( std::string("Tried to access a pointer of invalid Program: %s", m_Handle) );

	glVertexAttribPointer(attributeIterator->second,_size,_type,_normalise,_stride,_data);
}

// Set Uniform floats
void ShaderProgram::SetUniform1f(const std::string& _name,float _v0) const
{
	glUniform1f(GetUniformLocation(_name),_v0);
}
void ShaderProgram::SetUniform2f(const std::string& _name,float _v0,float _v1 ) const
{
	glUniform2f(GetUniformLocation(_name),_v0,_v1);
}
void ShaderProgram::SetUniform3f(const std::string& _name,float _v0,float _v1,float _v2) const
{
	glUniform3f(GetUniformLocation(_name),_v0,_v1,_v2);
}
void ShaderProgram::SetUniform4f(const std::string& _name,float _v0,float _v1,float _v2,float _v3) const
{
	glUniform4f(GetUniformLocation(_name),_v0,_v1,_v2,_v3);
}

void ShaderProgram::SetUniform1fv(const std::string& _name,size_t _count, const float* _value) const
{
	glUniform1fv(GetUniformLocation(_name),_count,_value);
}
void ShaderProgram::SetUniform2fv(const std::string& _name,size_t _count,const float* _value) const
{
	glUniform2fv(GetUniformLocation(_name),_count,_value);
}
void ShaderProgram::SetUniform3fv(const std::string& _name,size_t _count,const float* _value) const
{
	glUniform3fv(GetUniformLocation(_name),_count,_value);
}
void ShaderProgram::SetUniform4fv(const std::string& _name,size_t _count, const float* _value ) const
{
	glUniform4fv(GetUniformLocation(_name),_count,_value);

}

void ShaderProgram::SetUniform1i(const std::string& _name,GLint _v0) const
{
	glUniform1i(GetUniformLocation(_name),_v0);
}
void ShaderProgram::SetUniform2i(const std::string& _name,GLint _v0,GLint _v1) const
{
	glUniform2i(GetUniformLocation(_name),_v0,_v1);
}
void ShaderProgram::SetUniform3i(const std::string& _name,GLint _v0,GLint _v1,GLint _v2 ) const
{
	glUniform3i(GetUniformLocation(_name),_v0,_v1,_v2);
}
void ShaderProgram::SetUniform4i(const std::string& _name,GLint _v0,GLint _v1,GLint _v2,GLint _v3 ) const
{
	glUniform4i(GetUniformLocation(_name),_v0,_v1,_v2,_v3);
}

void ShaderProgram::SetUniform1iv(const std::string& _name,size_t _count,const GLint* _value ) const
{
	glUniform1iv(GetUniformLocation(_name),_count,_value);
}
void ShaderProgram::SetUniform2iv(const std::string& _name, size_t _count, const GLint* _value) const
{
	glUniform2iv(GetUniformLocation(_name),_count,_value);
}
void ShaderProgram::SetUniform3iv(const std::string& _name, size_t _count, const GLint* _value ) const
{
	glUniform3iv(GetUniformLocation(_name),_count,_value);
}
void ShaderProgram::SetUniform4iv(const std::string& _name, size_t _count, const GLint* _value ) const
{
	glUniform4iv(GetUniformLocation(_name),_count,_value);
}

void ShaderProgram::SetUniformMatrix2fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix2fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix3fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix3fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix4fv(const std::string& _name, size_t _count, bool _transpose, const float* _value) const
{
	glUniformMatrix4fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix2x3fv(const std::string& _name,size_t _count,bool _transpose,const float* _value ) const
{
	glUniformMatrix2x3fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix2x4fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix2x4fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix3x2fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix3x2fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix3x4fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix3x4fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix4x2fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix4x2fv(GetUniformLocation(_name),_count,_transpose,_value);
}
void ShaderProgram::SetUniformMatrix4x3fv(const std::string& _name, size_t _count, bool _transpose, const float* _value ) const
{
	glUniformMatrix4x3fv(GetUniformLocation(_name),_count,_transpose,_value);
}

void ShaderProgram::GetUniformfv(const std::string& _name, float* o_values ) const
{
	glGetUniformfv(m_Handle, GetUniformLocation(_name),o_values);
}
void ShaderProgram::GetUniformiv(const std::string& _name, int32_t* o_values ) const
{
	glGetUniformiv( m_Handle,GetUniformLocation(_name),o_values);
}

void ShaderProgram::VertexAttribute1f(const std::string& _name,GLfloat  	_v0) const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib1f(attributeIterator->second, _v0);
	}
}
void ShaderProgram::VertexAttribute2f(const std::string& _name,GLfloat  	_v0, GLfloat  	_v1 )const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib2f(attributeIterator->second, _v0,_v1);
	}
}
void ShaderProgram::VertexAttribute3f(const std::string& _name,GLfloat  	_v0, GLfloat  	_v1,GLfloat  	_v2)const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib3f(attributeIterator->second, _v0,_v1,_v2);
	}
}
void ShaderProgram::VertexAttribute4f(const std::string& _name,GLfloat _v0,GLfloat _v1,GLfloat _v2,GLfloat _v3 )const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib4f(attributeIterator->second, _v0,_v1,_v2,_v3);
	}
}

void ShaderProgram::VertexAttribute1fv(const std::string& _name,const GLfloat * _v)const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib1fv(attributeIterator->second, _v);
	}
}
void ShaderProgram::VertexAttribute2fv(const std::string& _name,const GLfloat* _v )const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib2fv(attributeIterator->second, _v);
	}
}
void ShaderProgram::VertexAttribute3fv(const std::string& _name,const GLfloat * _v)const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib3fv(attributeIterator->second, _v);
	}
}
void ShaderProgram::VertexAttribute4fv(const std::string& _name,const GLfloat * _v)const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib4fv(attributeIterator->second, _v);
	}
}

void ShaderProgram::VertexAttribute4iv(const std::string& _name,const GLint* _v)const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib4iv(attributeIterator->second, _v);
	}
}
void ShaderProgram::VertexAttribute4uiv(const std::string& _name,const GLuint* _v) const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib4uiv(attributeIterator->second, _v);
	}
}
void ShaderProgram::VertexAttribute4Niv(const std::string&_name,const GLint * _v) const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib4Niv(attributeIterator->second, _v);
	}

}
void ShaderProgram::VertexAttribute4Nuiv(const std::string& _name, const GLuint * _v )const
{
	ShaderAttributeMap::const_iterator attributeIterator = m_Attributes.find(_name);
	if(attributeIterator != m_Attributes.end() )
	{
		glVertexAttrib4Nuiv(attributeIterator->second, _v);
	}
}
