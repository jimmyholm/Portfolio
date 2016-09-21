#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

#define DIR_UP		glm::vec3( 0.0f,  1.0f,  0.0f)
#define DIR_RIGHT	glm::vec3( 1.0f,  0.0f,  0.0f)
#define DIR_DOWN	glm::vec3( 0.0f, -1.0f,  0.0f)
#define DIR_LEFT	glm::vec3(-1.0f,  0.0f,  0.0f)
#define DIR_IN		glm::vec3( 0.0f,  0.0f, -1.0f)
#define DIR_OUT		glm::vec3( 0.0f,  0.0f,  1.0f)
typedef unsigned int uint32;
class ISceneNode
{
  protected:
    glm::mat4 m_Transform;
    std::map<unsigned int, ISceneNode*> m_Children;
    glm::vec3 m_Scale;
    ISceneNode* m_Parent;
    char* m_Name;
    /*
      sdbm hashing function, O(|str|), found at http://www.cse.yorku.ca/~oz/hash.html
    */
    unsigned long Hash(const char* str);
  public:
    void Translate(glm::vec3 Vector);
    void Rotate(float X, float Y, float Z);
    void Scale(glm::vec3 scale);

    ISceneNode();
    ISceneNode(const char* Name, ISceneNode* Parent, glm::mat4 Transform);
    ISceneNode(ISceneNode* Node);

    // Allow for updating the node; travels down the graph and should be called in the derivative classes' update functions.
    virtual void Update(uint32 ElapsedTime);

    // Virtual rendering function; base-class functionality simply passes rendering command down to the children of the node. Should be called in derivative classes' render function.
    virtual void Render(glm::mat4 View, glm::mat4 Projection, glm::mat4 Transform);

    // Add node into the scene, given a path (i.e. "/group1/house/floor" etc.)
    void AddNode(const char* Path, ISceneNode* Node);

    // Retreive a node given a path.
    ISceneNode* GetNode(const char* Path); 

    // Grab position of object (For DoF)
    glm::vec3 GetPosition() const { return glm::vec3(m_Transform[3]);}
    virtual ~ISceneNode();
};
