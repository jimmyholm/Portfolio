#ifndef SFMLG_PIECES_H
#define SFMLG_PIECES_H
#include <SFML\Graphics.hpp>
#include "CSTextureManager.h"
#include <random>
// Define the pieces as a 17 byte array; the first byte contains the index of the 'center' of the piece, then 16 bytes make up the block.
/* Colours:		0 = empty
				1 = Red
				2 = Blue
				3 = Green
				4 = Yellow
				5 = Cyan
				6 = Orange
				7 = Purple
				8 = Gold

	Rotations: xPiece0 =   0 degrees
			   xPiece1 =  90 degrees
			   xPiece2 = 180 degrees
			   xPiece3 = 270 degrees
*/

static sf::Color Orange = sf::Color(255, 127,   0);
static sf::Color Purple = sf::Color(128,   0, 128);
static sf::Color Gold	= sf::Color(255, 215,   0);
// Cyan
static sf::Vector2i IPiece[16] =	{	sf::Vector2i(0,-1), sf::Vector2i(0,0), sf::Vector2i(0,1), sf::Vector2i(0,2),
										sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(2,0),
										sf::Vector2i(0,-1), sf::Vector2i(0,0), sf::Vector2i(0,1), sf::Vector2i(0,2),
										sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(2,0)
									};
// Red
static sf::Vector2i JPiece[16] =	{	sf::Vector2i(-2,0), sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,1),
										sf::Vector2i(-1,0), sf::Vector2i(0,0),  sf::Vector2i(0,-1), sf::Vector2i(0,-2),
										sf::Vector2i(0,-1), sf::Vector2i(0,0),  sf::Vector2i(1,0), sf::Vector2i(2,0),
										sf::Vector2i(0,0),  sf::Vector2i(1,0),  sf::Vector2i(0,1), sf::Vector2i(0,2)
									};
// Blue
static sf::Vector2i LPiece[16] =	{	sf::Vector2i(-2,0), sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1),
										sf::Vector2i(0,-2), sf::Vector2i(0,-1), sf::Vector2i(0,0), sf::Vector2i(1,0),
										sf::Vector2i(0,0),  sf::Vector2i(0,1),  sf::Vector2i(1,0), sf::Vector2i(2,0),
										sf::Vector2i(0,0),  sf::Vector2i(-1,0),  sf::Vector2i(0,1), sf::Vector2i(0,2)																				
									};	
// Green
static sf::Vector2i OPiece[16] =	{	sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1), sf::Vector2i(-1,-1),
										sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1), sf::Vector2i(-1,-1),
										sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1), sf::Vector2i(-1,-1),
										sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1), sf::Vector2i(-1,-1)
									};
// Yellow
static sf::Vector2i SPiece[16] =	{	sf::Vector2i(-1,0), sf::Vector2i(0,0),  sf::Vector2i(0,-1), sf::Vector2i(1,-1),
										sf::Vector2i(0,0),  sf::Vector2i(1,0),  sf::Vector2i(1,1), sf::Vector2i(0,-1),
										sf::Vector2i(-1,0), sf::Vector2i(0,0),  sf::Vector2i(0,-1), sf::Vector2i(1,-1),
										sf::Vector2i(0,0),  sf::Vector2i(1,0),  sf::Vector2i(1,1), sf::Vector2i(0,-1)
									};
// Orange
static sf::Vector2i TPiece[16] =	{	sf::Vector2i(-1,0), sf::Vector2i(0,0),  sf::Vector2i(0,-1), sf::Vector2i(1,0),
										sf::Vector2i(0,0), sf::Vector2i(0,-1), sf::Vector2i(0,1), sf::Vector2i(1,0),
										sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(1,0), sf::Vector2i(0,1),
										sf::Vector2i(-1,0), sf::Vector2i(0,-1),  sf::Vector2i(0,0), sf::Vector2i(0,1)
									};

// Purple
static sf::Vector2i ZPiece[16] =	{	sf::Vector2i(-1,-1), sf::Vector2i(0,-1), sf::Vector2i(0,0), sf::Vector2i(1,0),
										sf::Vector2i(-1,1), sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1),
										sf::Vector2i(-1,-1), sf::Vector2i(0,-1), sf::Vector2i(0,0), sf::Vector2i(1,0),
										sf::Vector2i(-1,1), sf::Vector2i(-1,0), sf::Vector2i(0,0), sf::Vector2i(0,-1),
									};

class CShape
{
	public:
		enum EShapes {
			SHAPE_EMPTY,
			SHAPE_J,
			SHAPE_L,
			SHAPE_O,
			SHAPE_S,
			SHAPE_I,
			SHAPE_T,
			SHAPE_Z,
			SHAPE_CLEAR // Indicates a complete line.
		};
	private:
		void CopyOffsets(sf::Vector2i* v);
		sf::Vector2i	m_Offsets[4];
		unsigned char	m_Rotation;
		sf::VertexArray m_Vertices;
		void BuildVertices();
		sf::Color		m_Color;
		EShapes			m_ShapeType;
	public:
		CShape(EShapes Shape);
		CShape() : m_Rotation(0) {}
		void RotateLeft();
		void RotateRight();
		const sf::VertexArray& GetVertices();
		const sf::Vector2i* GetOffsets();
		~CShape();
		unsigned char GetRotation() { return m_Rotation; }
		CShape::EShapes GetShape()  { return m_ShapeType;}
};



class CPiece
{
	private:
		sf::Vector2i m_Pos;
		CShape m_Shape;
		static std::mt19937 rnd;
		static CShape::EShapes lastPiece;
	public:
		static void SeedRandomizer();
		CPiece::CPiece();
		CPiece::CPiece(CShape::EShapes Shape);
		sf::Vector2i* GetPositions(sf::Vector2i* ret);
		void MoveLeft();
		void MoveRight();
		void MoveDown();
		void MoveUp();
		void Draw(sf::RenderTarget& target, sf::RenderStates states);
		void SetPosition(sf::Vector2i Pos) { m_Pos = Pos; }
		void RotateLeft()  { m_Shape.RotateLeft();  }
		void RotateRight() { m_Shape.RotateRight(); }
		void SetPiece(CShape::EShapes Shape);
		CShape::EShapes GetShape()  { return m_Shape.GetShape();}
}; 
#endif