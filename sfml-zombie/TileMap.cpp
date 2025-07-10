#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	rs.setSize({ (count.x - 3) * size.x, (count.y - 3) * size.x });
	Utils::SetOrigin(rs, Origins::MC);
	rs.setFillColor(sf::Color::Red);
	cellCount = count;
	cellSize = size;
	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(cellCount.x * cellCount.y * 4);
	sf::Vector2f posOffset[4] =
	{
		{0.f,0.f},
		{size.x,0.f},
		{size.x,size.y},
		{0.f,size.y},
	};

	sf::Vector2f texCoordinate[4] =
	{	{0.f,0.f},
		{50.f,0.f},
		{50.f,50.f},
		{0.f,50.f}
	};
	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIdx = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIdx = 3;
				
			}
			int quadIdx = i * count.x + j;
			
			sf::Vector2f quadPos = { j * size.x,i * size.y };
			
			for (int k = 0; k < 4; k++)
			{
				int vertexIdx = quadIdx * 4 + k;
				va[vertexIdx].position = quadPos + posOffset[k];
				//std::cout << va[vertexIdx].position.x << " : " << va[vertexIdx].position.y << std::endl;
				va[vertexIdx].texCoords = texCoordinate[k];
				va[vertexIdx].texCoords.y += texIdx * 50.f;
				//std::cout << va[vertexIdx].texCoords.x << " : " << va[vertexIdx].texCoords.y << std::endl;
			}
			//std::cout <<  std::endl;



		}
	}
	

}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransForm();
	
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransForm();
	
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransForm();
	
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransForm();
	
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
}

void TileMap::UpdateTransForm()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::Init()
{
	//layer위치 지정
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
	
	

}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	Set({ Variable::wave * 10, Variable::wave * 10 }, { 50.f, 50.f });
	
	texture = &TEXTURE_MGR.Get(spriteSheetId);
	
	
	SetOrigin(Origins::MC);
	SetScale({ 1.f, 1.f });
	//SetRotation(45);
	SetPosition({ 0.f, 0.f });
	

}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
	window.draw(rs);
	

	
}