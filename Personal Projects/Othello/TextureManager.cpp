#include "TextureManager.h"
#include "utility.h"
TextureManager* TextureManager::m_instance = 0;

TextureManager* TextureManager::GetInstance()
{
	if(m_instance == 0)
		m_instance = new TextureManager();
	return m_instance;
}

TextureManager::TextureManager() : m_useVBO(false) 
{
}

bool TextureManager::LoadTexture(std::string name, std::string file)
{
	if(m_textures.find(name) != m_textures.end())
	{
		// Check if the application is trying to load the same file into the same nameslot
		if(m_textures[name]->GetFileName() != file) 
		{
			throw std::exception(FormatString("Texture name already occupied by file \"%s\"", m_textures[name]->GetFileName()).c_str()); // If not, throw an exception
			return false;
		}
		return true; // otherwise, return that the texture has been successfully loaded.
	}
	m_textures[name] = new Texture();
	m_textures[name]->LoadTexture(file);
	if(m_textures[name] == NULL)
	{
		m_textures.erase(m_textures.find(name));
		return false;
	}
	return true;
}

Texture* TextureManager::getTexture(std::string name)
{
	if(m_textures.find(name) == m_textures.end())
	{
		throw std::exception(FormatString("Texture Not Found: '%s'", name.c_str()).c_str());
		return NULL;
	}
	if(!m_textures[name]->isInit())
		return NULL;
	m_textures[name]->addRef();
	return m_textures[name];
}

bool TextureManager::ReleaseTexture(std::string name)
{
	if(m_textures.find(name) == m_textures.end())
	{
		throw std::exception(FormatString("Texture Not Found: '%s'", name.c_str()).c_str());
		return false;
	}
	if(!m_textures[name]->isInit())
	{
		m_textures.erase(m_textures.find(name));
		return false;
	}
	m_textures[name]->Release();
	if(m_textures[name]->isInit())
		return true;
	m_textures.erase(m_textures.find(name));
	return false;
}

void TextureManager::DrawAll()
{
	// Loop through the textures and call the DrawTexture on them.
	for(std::list<Texture*>::iterator it = m_DrawQueue.begin(); it != m_DrawQueue.end(); it++)//map<std::string, Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		if((*it) != NULL)
			DrawTexture((*it));
	}
	m_DrawQueue.clear();
}

void TextureManager::ReleaseAll()
{
	map<std::string, Texture*>::iterator it;
	for(it = m_textures.begin(); it != m_textures.end(); it++)
	{
		while(it->second->isInit())
		{
			it->second->Release();
		}
	}
	m_textures.clear();
}
void TextureManager::UnloadTexture(std::string TextureName)
{
	if(m_textures.find(TextureName) == m_textures.end())
	{
		throw std::exception(FormatString("Texture Not Found: '%s'", TextureName.c_str()).c_str());
		return;
	}
	Texture* tex = m_textures[TextureName];
	while(tex->isInit())
		tex->Release();
	delete tex;
	m_textures.erase(m_textures.find(TextureName));
}
void TextureManager::AddToDrawQueue(Texture* texture)
{
	m_DrawQueue.push_back(texture);
}
void TextureManager::DrawTexture(Texture* texture)
{
	//gather all the drawinfo-data and build a vertex array for each.
	if(!m_useVBO)
	{
		std::list<DrawInfo> drawInfo = texture->GetInstances();
		if(drawInfo.empty())
			return;
		size_t diSize = drawInfo.size();
		std::list<DrawInfo>::iterator dit;
		Vertex* vertices = new Vertex[diSize*4];
		VertexIndex* indices = new VertexIndex[diSize*6];
		int indexCount = 0;
		int vertexCount = 0;
		for(dit = drawInfo.begin(); dit != drawInfo.end(); dit++)
		{
			// Add a textured quad to the arrays
			// TL-BR-Bl-TR
			DrawInfo di = *(dit);

			vertices[vertexCount].x =	di.p1.first;
			vertices[vertexCount].y =	di.p1.second;
			vertices[vertexCount].u =	texture->getU();
			vertices[vertexCount].v =	0.0f;
			vertices[vertexCount].r =	di.r;
			vertices[vertexCount].g =	di.g;
			vertices[vertexCount].b =	di.b;
			vertices[vertexCount].a =	di.a;

			vertices[vertexCount+1].x =	di.p2.first;
			vertices[vertexCount+1].y =	di.p2.second;
			vertices[vertexCount+1].u =	0.0f;
			vertices[vertexCount+1].v =	0.0f;
			vertices[vertexCount+1].r =	di.r;
			vertices[vertexCount+1].g =	di.g;
			vertices[vertexCount+1].b =	di.b;
			vertices[vertexCount+1].a =	di.a;

			vertices[vertexCount+2].x =	di.p3.first;
			vertices[vertexCount+2].y =	di.p3.second;
			vertices[vertexCount+2].u =	0.0f;
			vertices[vertexCount+2].v =	texture->getV();
			vertices[vertexCount+2].r =	di.r;
			vertices[vertexCount+2].g =	di.g;
			vertices[vertexCount+2].b =	di.b;
			vertices[vertexCount+2].a =	di.a;

			vertices[vertexCount+3].x =	di.p4.first;
			vertices[vertexCount+3].y =	di.p4.second;
			vertices[vertexCount+3].u =	texture->getU();
			vertices[vertexCount+3].v =	texture->getV();
			vertices[vertexCount+3].r =	di.r;
			vertices[vertexCount+3].g =	di.g;
			vertices[vertexCount+3].b =	di.b;
			vertices[vertexCount+3].a =	di.a;
			
			indices[indexCount++] = vertexCount;
			indices[indexCount++] = vertexCount+1;

			indices[indexCount++] = vertexCount+2;
			indices[indexCount++] = vertexCount;

			indices[indexCount++] = vertexCount+2;
			indices[indexCount++] = vertexCount+3;
			vertexCount += 4;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertices);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &((float*)vertices)[2]);
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), &((float*)vertices)[4]);
		glBindTexture(GL_TEXTURE_2D, texture->getTexture());
		if(pglDrawRangeElements)
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, indices);
		else
			pglDrawRangeElements(GL_TRIANGLES, 0, indexCount, indexCount, GL_UNSIGNED_SHORT, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		delete[] vertices;
		delete[] indices;
		

		vertices = 0; indices = 0;
	}
	else
	{
		std::list<DrawInfo> drawInfo = texture->GetInstances();
		if(drawInfo.empty())
			return;
		size_t diSize = drawInfo.size();
		std::list<DrawInfo>::iterator dit;
		Vertex*		vertices = new Vertex[diSize*4];
		VertexIndex* indices = new VertexIndex[diSize*6];
		int indexCount = 0;
		int vertexCount = 0;
		for(dit = drawInfo.begin(); dit != drawInfo.end(); dit++)
		{
			// Add a textured quad to the arrays
			// TR-TL-BL, TL-BL-BR

			DrawInfo di = *(dit);

			vertices[vertexCount].x =	di.p1.first;
			vertices[vertexCount].y =	di.p1.second;
			vertices[vertexCount].u =	texture->getU();
			vertices[vertexCount].v =	0.0f;
			vertices[vertexCount].r =	di.r;
			vertices[vertexCount].g =	di.g;
			vertices[vertexCount].b =	di.b;
			vertices[vertexCount].a =	di.a;

			vertices[vertexCount+1].x =	di.p2.first;
			vertices[vertexCount+1].y =	di.p2.second;
			vertices[vertexCount+1].u =	0.0f;
			vertices[vertexCount+1].v =	0.0f;
			vertices[vertexCount+1].r =	di.r;
			vertices[vertexCount+1].g =	di.g;
			vertices[vertexCount+1].b =	di.b;
			vertices[vertexCount+1].a =	di.a;

			vertices[vertexCount+2].x =	di.p3.first;
			vertices[vertexCount+2].y =	di.p3.second;
			vertices[vertexCount+2].u =	0.0f;
			vertices[vertexCount+2].v =	texture->getV();
			vertices[vertexCount+2].r =	di.r;
			vertices[vertexCount+2].g =	di.g;
			vertices[vertexCount+2].b =	di.b;
			vertices[vertexCount+2].a =	di.a;

			vertices[vertexCount+3].x =	di.p4.first;
			vertices[vertexCount+3].y =	di.p4.second;
			vertices[vertexCount+3].u =	texture->getU();
			vertices[vertexCount+3].v =	texture->getV();
			vertices[vertexCount+3].r =	di.r;
			vertices[vertexCount+3].g =	di.g;
			vertices[vertexCount+3].b =	di.b;
			vertices[vertexCount+3].a =	di.a;
			
			indices[indexCount++] = vertexCount;
			indices[indexCount++] = vertexCount+1;

			indices[indexCount++] = vertexCount+2;
			indices[indexCount++] = vertexCount;

			indices[indexCount++] = vertexCount+2;
			indices[indexCount++] = vertexCount+3;
			vertexCount += 4;
		}
		GLuint vbuffer, ibuffer;
		pglGenBuffersARB(1, &vbuffer);
		pglGenBuffersARB(1, &ibuffer);
		pglBindBufferARB(GL_ARRAY_BUFFER_ARB, vbuffer);
		pglBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, ibuffer);
		pglBufferDataARB(GL_ARRAY_BUFFER_ARB, 32*vertexCount, vertices, GL_STATIC_DRAW_ARB);
		pglBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 2*indexCount, indices, GL_STATIC_DRAW_ARB);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_FLOAT,	32,	BUFFER_OFFSET(0));
		glTexCoordPointer(2, GL_FLOAT,  32,	BUFFER_OFFSET(sizeof(float)*2));
		glColorPointer(4, GL_FLOAT,		32,	BUFFER_OFFSET(sizeof(float)*4));
		glBindTexture(GL_TEXTURE_2D, texture->getTexture());
		pglDrawRangeElements(GL_TRIANGLES, 0, indexCount, indexCount, GL_UNSIGNED_SHORT, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		pglBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		pglBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
		pglDeleteBuffersARB(1, &vbuffer);
		pglDeleteBuffersARB(1, &ibuffer);
		delete[] vertices;
		delete[] indices;
		

		vertices = 0; indices = 0;

	}
	texture->RemoveFromDrawQueue();
}

void TextureManager::UseVBO(bool useVBO)
{
	m_useVBO = useVBO;
}
void TextureManager::LoadScript(std::string name, std::string file)
{
	std::ifstream f(file.c_str());
	if(!f.is_open())
	{
		throw std::exception(FormatString("Filename %s couldn't be opened.", file.c_str()).c_str());
		return;
	}
	char line[1024];
	std::string stline;
	f.getline(line, 1024);
	stline = std::string(line);
	if(stline != "[Textures]")
	{
		f.close();
		throw std::exception(FormatString("File %s is not a texture loadscript.", file.c_str()).c_str());
		return;
	}
	std::list<std::string> nameList;
	while(!f.eof())
	{
		f.getline(line, 1024);
		stline = std::string(line);
		std::string name2(""), file2("");
		name2 = stline.substr(0, stline.find('='));
		file2 = stline.substr(stline.find('=')+1, stline.length()-stline.find('='));
		if(name2 != "" && file2 != "")
		{
			nameList.push_back(name2);
			LoadTexture(name2, file2);
		}
	}
	f.close();
	m_LoadScripts[name] = std::list<std::string>(nameList);
	nameList.clear();
}

void TextureManager::UnloadScript(std::string name)
{
	if(m_LoadScripts.find(name) != m_LoadScripts.end())
	{
		for(std::list<std::string>::iterator it = m_LoadScripts[name].begin(); it != m_LoadScripts[name].end(); it++)
		{
			UnloadTexture((*it));
		}
		m_LoadScripts[name].clear();
		m_LoadScripts.erase(m_LoadScripts.find(name));
	}
}
void TextureManager::Destroy()
{
	delete TextureManager::m_instance;
}