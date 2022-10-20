#include "Common.h"


Shader::Shader(std::string _name, SHADERTYPE _shaderType)
	: m_Name(_name),m_Type(_shaderType),m_Source(nullptr),m_Handle(-1)
{
	try {

		if(m_Name != "NULL") {

			switch (_shaderType)
			{
			case VERTEX		: { m_Handle = glCreateShader(GL_VERTEX_SHADER_ARB);		break; }
			case FRAGMENT		: { m_Handle = glCreateShader(GL_FRAGMENT_SHADER_ARB);	break; }
			case GEOMETRY		: { m_Handle = glCreateShader(GL_GEOMETRY_SHADER_EXT);	break; }
			}

			m_IsCompiled = false;
		}

	}  catch( std::exception& err ) {
		fprintf(stdout, "Exception Found: %s", err.what());
	} catch ( ... ) {
		fprintf(stdout,"Unknown Exception");
	}
}
Shader::~Shader()
{
	glDeleteShader(m_Handle); // Annoying C Library making me destroy it explicitly
}

void Shader::Load(std::string _name)
{
	// See if there's any source attached
	if(m_Source)
		fprintf(stdout, "Source is being replaced.\n");

	std::ifstream shaderSource(_name.c_str());
	if(!shaderSource.is_open()) 
		throw std::runtime_error( std::string("Failed to find file at location: %s", _name.c_str()) );

	// Read in the data
	m_Source = std::make_shared<std::string>( std::string((std::istreambuf_iterator<char>(shaderSource)), 
		std::istreambuf_iterator<char>()) );
	shaderSource.close();
	// Add the null character at the end of the string
	*m_Source += "\0";

	// Pass the data to the GPU
	const char* data = m_Source->c_str();
	glShaderSource(m_Handle, 1, &data, NULL);
	m_IsCompiled = false;

	// Check for Errors in OpenGL
	if( glGetError() )
		throw std::runtime_error("Error found copying shader source to GPU");

}


void Shader::Compile()
{
	if(m_Source == nullptr)
		throw std::runtime_error("No Source to Compile Shader");

	glCompileShader(m_Handle);
	if( glGetError() ) {
		PrintLog(m_Handle);
		throw std::runtime_error("Error Compiling Shader");
	}
	m_IsCompiled = true;
}

const GLuint& Shader::GetHandle()
{
	return m_Handle;
}

void Shader::PrintLog( const GLuint& _Handle )
{
	GLint logLength = 0;
	GLint charsWritten = 0;
	std::unique_ptr<char[]> log;

	glGetShaderiv(_Handle, GL_OBJECT_INFO_LOG_LENGTH_ARB,&logLength);
	fprintf(stdout, "Shader: %s Info Log Length: %s", _Handle, logLength);
	
	if(logLength > 0) {
		log = std::unique_ptr<char[]>(new char[logLength]);
		glGetProgramInfoLog(_Handle, logLength, &charsWritten, log.get());
		// I was gonna keep a pointer to the input log, but it might get pretty big,
		// so lets not store it unless we want to print it
		fprintf(stdout, "ShaderProgram: %s, Log: %s", _Handle, log);

		glGetShaderiv(_Handle, GL_COMPILE_STATUS, &logLength);
		if(!logLength) // aka GL_FALSE or anything else negative...why not be GENERIC~!!!
			throw std::runtime_error( std::string("Shader: %s Failed to Compile!", _Handle) );
	}
}