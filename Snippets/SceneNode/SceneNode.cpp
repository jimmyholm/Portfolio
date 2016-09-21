#include "SceneNode.h"
#include <cstring>

void ISceneNode::Update(uint32 ElapsedTime)
{
  for(std::map<uint32, ISceneNode*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
  {
    (*it).second->Update(ElapsedTime);
  }
}

void ISceneNode::Render(glm::mat4 View, glm::mat4 Projection, glm::mat4 Transform)
{
  glm::mat4 combTrans = Transform * m_Transform;
  for(std::map<uint32, ISceneNode*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
  {
    (*it).second->Render(View, Projection, combTrans);
  }
}

unsigned long ISceneNode::Hash(const char* str)
{
  unsigned long hash = 0;
  int c;
  
  while (c = *str++)
    hash = c + (hash << 6) + (hash << 16) - hash;

  return hash;
}

// Path extraction helper function
const char* ExtractFirst(const char* Path, char*& ret)
{
  if(ret == NULL)
    ret = new char[64];
  memset(ret, '\0', sizeof(char)*64);
  const char* pos = strstr(Path, "/");
  if(pos == NULL)
  {
    strcpy(ret, Path);
    return "";
  }
  size_t offset = pos - Path;
  strncpy(ret, Path, offset);
  return Path+offset+1;
}

ISceneNode* ISceneNode::GetNode(const char* Path)
{
  if(strlen(Path) == 0)
  {
    return NULL; // We didn't reach the requested leaf.
  }
  if(Path[0] == '/') // We're looking into the root - discard the first slash.
    Path = Path+1;
  char* first = NULL;
  Path = ExtractFirst(Path, first);
  uint32 hash = Hash(first);
  delete first;
  if(m_Children.find(hash) == m_Children.end())
    return NULL; // The path does not exist.
  if(strlen(Path) == 0) // There's no more path - the child we're looking for is here.
    return m_Children[hash];
  return m_Children[hash]->GetNode(Path);
}

void ISceneNode::AddNode(const char* Path, ISceneNode* Node)
{
  if(strlen(Path) == 0)
  {
    return; // We've added all the nodes we need to!
  }
  if(Path[0] == '/') // We're looking into the root - discard the first slash.
    Path = Path+1;
  char* first = NULL;
  Path = ExtractFirst(Path, first);
  uint32 hash = Hash(first);
  if(strlen(Path) == 0)
  {
    m_Children[hash] = Node;
    Node->m_Parent = this;
    Node->m_Name = new char[strlen(first)+1];
    memset(Node->m_Name, '\0', strlen(first)+1);
    strcpy(Node->m_Name, first);
    delete first;
    return;
  }
  if(m_Children.find(hash) == m_Children.end()) // We don't have this path - build it up.
    m_Children[hash] = new ISceneNode(first, this, glm::mat4(1.0f));
  delete first;
  m_Children[hash]->AddNode(Path, Node);
}

void ISceneNode::Translate(glm::vec3 Vector)
{
  m_Transform *= glm::translate(glm::mat4(1.0f), Vector);
}

void ISceneNode::Rotate(float X, float Y, float Z)
{
  m_Transform = glm::rotate(m_Transform, X, glm::vec3(1.0f, 0.0f, 0.0f));
  m_Transform = glm::rotate(m_Transform, Y, glm::vec3(0.0f, 1.0f, 0.0f));
  m_Transform = glm::rotate(m_Transform, Z, glm::vec3(0.0f, 0.0f, 1.0f));
}	

void ISceneNode::Scale(glm::vec3 scale)
{
  m_Transform = glm::scale(m_Transform, 1.0f/m_Scale);
  m_Transform = glm::scale(m_Transform, scale);
  m_Scale = scale;
}

ISceneNode::ISceneNode() : m_Scale(glm::vec3(1.0f)), m_Transform(glm::mat4(1.0f)), m_Parent(NULL), m_Name((char*)"") {}

ISceneNode::ISceneNode(const char* Name, ISceneNode* Parent, glm::mat4 Transform) : m_Transform(glm::mat4(1.0f)), m_Scale(glm::vec3(1.0f)), m_Parent(Parent)
{
	
  m_Name = new char[strlen(Name)];
  strcpy(m_Name, Name);
}

// Copy a node
ISceneNode::ISceneNode(ISceneNode* Node) : m_Scale(glm::vec3(1.0f)), m_Transform(glm::mat4(1.0f)), m_Parent(Node->m_Parent)
{
  m_Name = new char[strlen(Node->m_Name)];
  strcpy(m_Name, Node->m_Name);
  for(std::map<uint32, ISceneNode*>::iterator it = Node->m_Children.begin(); it != Node->m_Children.end(); it++)
    m_Children[(*it).first] = (*it).second;
}

ISceneNode::~ISceneNode()
{
  for(std::map<uint32, ISceneNode*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
  {
    ISceneNode* node = (*it).second;
    delete node;
  }
  m_Children.clear();
}
