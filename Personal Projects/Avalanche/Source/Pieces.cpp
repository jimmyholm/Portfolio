#include "pieces.h"

void CShape::BuildVertices()
{
	int x; int y;
	for(int o = 0; o < 4; o++)
	{
		x = m_Offsets[o].x*32;
		y = m_Offsets[o].y*32;
		m_Vertices[(o*4)].position = sf::Vector2f((float)x, (float)y);
		m_Vertices[(o*4)].texCoords = sf::Vector2f(0.0f, 0.0f);
		m_Vertices[(o*4)+1].position = sf::Vector2f((float)x+32.0f, (float)y);
		m_Vertices[(o*4)+1].texCoords = sf::Vector2f(32.0f, 0.0f);
		m_Vertices[(o*4)+2].position = sf::Vector2f((float)x+32.0f, (float)y+32.0f);
		m_Vertices[(o*4)+2].texCoords = sf::Vector2f(32.0f, 32.0f);
		m_Vertices[(o*4)+3].position = sf::Vector2f((float)x, (float)y+32.0f);
		m_Vertices[(o*4)+3].texCoords = sf::Vector2f(0.0f, 32.0f);
		switch(m_ShapeType)
		{
			case SHAPE_I:
				m_Vertices[(o*4)].color   = sf::Color::Cyan;
				m_Vertices[(o*4)+1].color = sf::Color::Cyan;
				m_Vertices[(o*4)+2].color = sf::Color::Cyan;
				m_Vertices[(o*4)+3].color = sf::Color::Cyan;
				break;
			case SHAPE_L:
				m_Vertices[(o*4)].color   = sf::Color::Blue;
				m_Vertices[(o*4)+1].color = sf::Color::Blue;
				m_Vertices[(o*4)+2].color = sf::Color::Blue;
				m_Vertices[(o*4)+3].color = sf::Color::Blue;
				break;
			case SHAPE_J:
				m_Vertices[(o*4)].color   = sf::Color::Red;
				m_Vertices[(o*4)+1].color = sf::Color::Red;
				m_Vertices[(o*4)+2].color = sf::Color::Red;
				m_Vertices[(o*4)+3].color = sf::Color::Red;
				break;
			case SHAPE_S:
				m_Vertices[(o*4)].color   = sf::Color::Yellow;
				m_Vertices[(o*4)+1].color = sf::Color::Yellow;
				m_Vertices[(o*4)+2].color = sf::Color::Yellow;
				m_Vertices[(o*4)+3].color = sf::Color::Yellow;
				break;
			case SHAPE_Z:
				m_Vertices[(o*4)].color   = sf::Color(Purple);
				m_Vertices[(o*4)+1].color = sf::Color(Purple);
				m_Vertices[(o*4)+2].color = sf::Color(Purple);
				m_Vertices[(o*4)+3].color = sf::Color(Purple);
				break;
			case SHAPE_O:
				m_Vertices[(o*4)].color   = sf::Color::Green;
				m_Vertices[(o*4)+1].color = sf::Color::Green;
				m_Vertices[(o*4)+2].color = sf::Color::Green;
				m_Vertices[(o*4)+3].color = sf::Color::Green;
				break;
			default: //SHAPE_T
				m_Vertices[(o*4)].color   = sf::Color(Orange);
				m_Vertices[(o*4)+1].color = sf::Color(Orange);
				m_Vertices[(o*4)+2].color = sf::Color(Orange);
				m_Vertices[(o*4)+3].color = sf::Color(Orange);
		}
	}
}

void CShape::CopyOffsets(sf::Vector2i* offset)
{
	int x = 0;
	for(int i = m_Rotation*4; x != 4; i++,x++)
	{
		m_Offsets[x] = offset[i];
	}
}
CShape::CShape(CShape::EShapes Shape) : m_Rotation(0), m_Color(sf::Color::White), m_ShapeType(Shape)
{
	m_Vertices.resize(16);
	m_Vertices.setPrimitiveType(sf::Quads);
	switch(m_ShapeType)
	{
		case SHAPE_I:
			CopyOffsets(IPiece);
			break;
		case SHAPE_L:
			CopyOffsets(LPiece);
			break;
		case SHAPE_J:
			CopyOffsets(JPiece);
			break;
		case SHAPE_S:
			CopyOffsets(SPiece);
			break;
		case SHAPE_Z:
			CopyOffsets(ZPiece);
			break;
		case SHAPE_O:
			CopyOffsets(OPiece);
			break;
		default: //SHAPE_T
			CopyOffsets(TPiece);
	}
	BuildVertices();
}

void CShape::RotateLeft()
{
	(m_Rotation == 0) ? m_Rotation = 3 : m_Rotation--;
	switch(m_ShapeType)
	{
		case SHAPE_I:
			CopyOffsets(IPiece);
			break;
		case SHAPE_L:
			CopyOffsets(LPiece);
			break;
		case SHAPE_J:
			CopyOffsets(JPiece);
			break;
		case SHAPE_S:
			CopyOffsets(SPiece);
			break;
		case SHAPE_Z:
			CopyOffsets(ZPiece);
			break;
		case SHAPE_O:
			CopyOffsets(OPiece);
			break;
		default: //SHAPE_T
			CopyOffsets(TPiece);
	}
	BuildVertices();
}
void CShape::RotateRight()
{
	(m_Rotation == 3) ? m_Rotation = 0 : m_Rotation++;
	switch(m_ShapeType)
	{
		case SHAPE_I:
			CopyOffsets(IPiece);
			break;
		case SHAPE_L:
			CopyOffsets(LPiece);
			break;
		case SHAPE_J:
			CopyOffsets(JPiece);
			break;
		case SHAPE_S:
			CopyOffsets(SPiece);
			break;
		case SHAPE_Z:
			CopyOffsets(ZPiece);
			break;
		case SHAPE_O:
			CopyOffsets(OPiece);
			break;
		default: //SHAPE_T
			CopyOffsets(TPiece);
	}
	BuildVertices();
}

CShape::~CShape()
{
	m_Vertices.clear();
}

const sf::VertexArray& CShape::GetVertices()
{
	return m_Vertices;
}

const sf::Vector2i* CShape::GetOffsets()
{
	return m_Offsets;
}

std::mt19937 CPiece::rnd;

CShape::EShapes CPiece::lastPiece = CShape::EShapes::SHAPE_EMPTY;

void CPiece::SeedRandomizer()
{
	rnd.seed((unsigned int)time(NULL));
}

CPiece::CPiece()
{
	std::uniform_int_distribution<int> uid(2, 8);
	std::uniform_int_distribution<int> shape(1,7);
	int r = uid(CPiece::rnd);
	do
	{
		m_Shape = CShape((CShape::EShapes)shape(CPiece::rnd));
	}
	while(m_Shape.GetShape() == CPiece::lastPiece);
	CPiece::lastPiece = m_Shape.GetShape();
	m_Pos = sf::Vector2i(r, -1);
}

CPiece::CPiece(CShape::EShapes Shape) : m_Shape(CShape(Shape))
{
	std::uniform_int_distribution<int> uid(2, 8);
	int r = uid(rnd);
	m_Pos = sf::Vector2i(r, -1);
}

sf::Vector2i* CPiece::GetPositions(sf::Vector2i* ret)
{
	const sf::Vector2i* Offsets = m_Shape.GetOffsets();
	ret[0] = Offsets[0]+m_Pos;
	ret[1] = Offsets[1]+m_Pos;
	ret[2] = Offsets[2]+m_Pos;
	ret[3] = Offsets[3]+m_Pos;
	return ret;
}

void CPiece::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	const sf::VertexArray vertices = m_Shape.GetVertices();
	sf::Vector2f transl((float)(m_Pos.x*32+63),(float)(m_Pos.y*32+62));
	states.transform.translate(transl);
	states.texture = CSTextureManager::GetInstance()->GetTexture("Block").get();
	target.draw(vertices, states);
}

void CPiece::MoveLeft()
{
	if(m_Pos.x != 0)
		m_Pos.x--;
}
void CPiece::MoveRight()
{
	if(m_Pos.x != 9)
		m_Pos.x++;
}

void CPiece::MoveDown()
{
	if(m_Pos.y != 19)
		m_Pos.y++;
}
void CPiece::MoveUp()
{
	if(m_Pos.y != 0)
		m_Pos.y--;
}

void CPiece::SetPiece(CShape::EShapes shape)
{
	unsigned char r = m_Shape.GetRotation();
	m_Shape = CShape(shape);
	while(r != m_Shape.GetRotation())
	{
		m_Shape.RotateLeft();
		r = m_Shape.GetRotation();
	}
}