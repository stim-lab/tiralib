#pragma once

#include "../volume.h"
#include "glTexture.h"

namespace tira{

	template<class T>
	class glVolume : public volume<T> {

	protected:
		glTexture _texture;

	public:
		void generate_rgb(unsigned int X = 32, unsigned int Y = 32, unsigned int Z = 32, unsigned int boxes = 1){
			volume<T>::generate_rgb(X, Y, Z, boxes);
			GLint external_type = glTexture::type2gl<T>();
			_texture.AssignImage((unsigned char*)&volume<T>::_data[0], X, Y, Z, GL_RGB, GL_RGB, external_type);
		}

		void generate_grid(unsigned int X = 32, unsigned int Y = 32, unsigned int Z = 32, unsigned int boxes = 1){
			volume<T>::generate_grid(X, Y, Z, boxes);
			GLint external_type = glTexture::type2gl<T>();
			_texture.AssignImage((unsigned char*)&volume<T>::_data[0], X, Y, Z, GL_RED, GL_RED, external_type);
		}

		void setData(void* volData, unsigned int X, unsigned int Y, unsigned int Z, GLenum internalFormat, GLenum externalFormat, GLenum externalDataType){
			_texture.AssignImage((unsigned char*)volData, X, Y, Z, internalFormat, externalFormat, externalDataType);
		}

		template<typename D = T>
		void load_npy(std::string filename) : load_npy<D>(filename)
		{
			//volume<t>::template load_npy<D>(filename);
			size_t xn = volume<T>::X();
			size_t yn = volume<T>::Y();
			size_t zn = volume<T>::Z();
			setData(field<T>::_data.data(), xn, yn, zn, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
		}

		void setFilter(GLenum filter_type){
			_texture.SetFilter(filter_type);
		}

		GLuint getTextureID(){
			return _texture.ID();
		}

		void Bind(){
			_texture.Bind();
		}

		void Unbind(){
			_texture.Unbind();
		}

	};
}