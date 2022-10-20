#include "Common.h"

ShaderManager::ShaderManager()
{
	try {

		// Create shareable pointer to a NUllProgram 
		m_NullProgram = std::make_shared<ShaderProgram>("NULL");

	}  catch( std::exception& err ) {
		fprintf(stdout, "Exception Found: %s", err.what());
	} catch ( ... ) {
		fprintf(stdout,"Unknown Exception");
	}
}


void ShaderManager::CreateShaderProgram( const std::string& _name )
{
	m_ShaderPrograms[_name] = std::make_shared<ShaderProgram>(_name);
}

void ShaderManager::LoadShaderSource( const std::string& _shaderName, const std::string& _sourceFileName)
{
	// See if we have a valid shader
	ShaderMap::const_iterator shader = m_Shaders.find(_shaderName);
	if( shader != m_Shaders.end() ) {
		// Compile Shader Source of current shader
		shader->second->Load(_sourceFileName);
	} else 
		throw std::runtime_error( std::string("Error Loading/Compiling Shader: %s", shader->second->GetHandle()) );
}

void ShaderManager::AddShader( const std::string& _name, SHADERTYPE _type)
{
	m_Shaders[_name] = std::make_shared<Shader>(_name, _type);
}

void ShaderManager::AttachShaderToProgram(const std::string& _programName, const std::string& _shaderName)
{
	// Get iterators to the Shader and Shader Program Maps
	ShaderMap::const_iterator shaderIterator = m_Shaders.find(_shaderName);
	ShaderProgramMap::const_iterator shaderProgramIterator = m_ShaderPrograms.find(_programName);
	

	// Verify both objects
	if ( shaderIterator != m_Shaders.end() && shaderProgramIterator != m_ShaderPrograms.end() ) {
		//Attach the shader to the program
		shaderProgramIterator->second->AttachShader( shaderIterator->second );
	} else 
		throw std::runtime_error("Error Attaching Shader to Program");
		//throw std::runtime_error("Error Attaching Shader: %s to Program: %s",
		//							shaderIterator->second->GetHandle,
		//							shaderProgramIterator->second->GetName().c_str() );
}

void ShaderManager::CompileShader( const std::string& _name )
{
  ShaderMap::const_iterator shader = m_Shaders.find(_name);
  // make sure we have a valid shader
	if(shader != m_Shaders.end())
  {
    // grab the pointer to the shader and call compile
    shader->second->Compile();
  }
  else 
	  throw std::runtime_error("Warning shader not know in compile");

}

void ShaderManager::LinkShaderProgram( const std::string& _name )
{
	ShaderProgramMap::const_iterator shaderProgramMapIterator = m_ShaderPrograms.find(_name);
	if( shaderProgramMapIterator != m_ShaderPrograms.end() ) {
		fprintf(stdout, "Linking ShaderProgram: %s", _name);
		shaderProgramMapIterator->second->Link();
	}
	else 
		throw std::runtime_error( std::string("Error linking ShaderProgram: %s", _name.c_str()) );

}

void ShaderManager::BindAttribute(const std::string& _name, GLuint _index, const std::string& _attributeName)
{
	ShaderProgramMap::const_iterator shaderProgramMapIterator = m_ShaderPrograms.find(_name);
	if( shaderProgramMapIterator != m_ShaderPrograms.end() )
	{
		shaderProgramMapIterator->second->BindAttributes(_index,_attributeName);
	}
	else 
		throw std::runtime_error( std::string("Error Binding Attribute in Program: %s", _name.c_str()) );
}

// Override operator[] so we can get ShaderPrograms by std::string
std::shared_ptr<ShaderProgram> ShaderManager::operator[](const std::string& _programName)
{
	ShaderProgramMap::const_iterator shaderProgramIterator = m_ShaderPrograms.find(_programName);
	// Verify Shader Program
	if( shaderProgramIterator != m_ShaderPrograms.end() ) {
		return shaderProgramIterator->second;
	} else {
		fprintf(stdout, "No ShaderProgram %s exists", _programName.c_str());
		return m_NullProgram; // Lord help us all...
	}
}