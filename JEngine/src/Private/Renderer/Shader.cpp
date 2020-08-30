#include "JE_PCH.h"
#include "Renderer/Shader.h"

#include "glad/glad.h"

namespace JEngine
{

	Shader::Shader(const std::string vertexSrc, const std::string fragmentSrc)
	{
		// Create empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		
		// Send the vertex shader source code to GL
		// Note that std::string.c_str() is NULL character terminate.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
	
		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			// This is a dynamic vector with fixed length so it's not the most efficiency way
			// But this is just a debug code so it does not matter for now
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore
			glDeleteShader(vertexShader);


			JE_CORE_ERROR("{0}", infoLog.data());
			JE_CORE_ASSERT(false, "Vertex Shader compile failed!");
			return;
		}

		// Create empty vertex shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string.c_str() is NULL character terminate.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(fragmentShader);

		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			// This is a dynamic vector with fixed length so it's not the most efficiency way
			// But this is just a debug code so it does not matter for now
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need these shaders anymore
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);


			JE_CORE_ERROR("{0}", infoLog.data());
			JE_CORE_ASSERT(false, "Fragment Shader compile failed!");
			return;
		}

		// VS and FS compile finished
		// Now time to link them together into a program
		// glCreateProgram() gets a program object

		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different func() here: glGetProgram* instead of glGetShader*
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			// This is a dynamic vector with fixed length so it's not the most efficiency way
			// But this is just a debug code so it does not matter for now
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program and shaders anymore
			glDeleteProgram(m_RendererID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			JE_CORE_ERROR("{0}", infoLog.data());
			JE_CORE_ASSERT(false, "Fragment Shader compile failed!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

}