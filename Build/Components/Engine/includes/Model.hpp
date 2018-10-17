#ifndef MODEL_HPP
#define MODEL_HPP

# include <glad/glad.h> 
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <map>
# include <vector>
# include "Mesh.hpp"
# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>
# include <stb_image.h>

class Model {
public:	
	Model( void );
	Model( std::string const &path );

	void init( std::string const &path );
	void Draw(Shader shader);

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

private:
	void loadModel( std::string const &path );
	void processNode( aiNode *node, const aiScene *scene );
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, std::string typeName );
	unsigned int TextureFromFile( const char *path, const std::string &directory );
};

#endif // !MODEL_HPP