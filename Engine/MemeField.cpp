#include "MemeField.h"
#include <assert.h>
#include <random>
#include "Vei2.h"
#include "SpriteCodex.h"

void MemeField::Tile::SpawnMeme()
{
	assert( !hasMeme );
	hasMeme = true;
}

bool MemeField::Tile::HasMeme() const
{
	return hasMeme;
}

void MemeField::Tile::Draw( const Vei2& screenPos, Graphics& gfx ) const
{
	switch( state )
	{
	case MemeField::Tile::State::Hidden:
		SpriteCodex::DrawTileButton( screenPos, gfx );
		break;
	case MemeField::Tile::State::Flagged:
		SpriteCodex::DrawTileButton( screenPos, gfx );
		SpriteCodex::DrawTileFlag( screenPos, gfx );
		break;
	case MemeField::Tile::State::Revealed:
		if( !HasMeme() )
		{
			SpriteCodex::DrawTile0( screenPos, gfx );
		}
		else
		{
			SpriteCodex::DrawTileBomb( screenPos, gfx );
		}
		break;
	default:
		break;
	}
}

MemeField::MemeField( int nMemes )
{
	assert( nMemes > 0 && nMemes < width * height );
	std::random_device rd;
	std::mt19937 rng( rd() );
	std::uniform_int_distribution<int> xDist( 0, width - 1 );
	std::uniform_int_distribution<int> yDist( 0, height - 1 );

	for( int nSpawned = 0; nSpawned < nMemes; ++nSpawned )
	{
		Vei2 spawnPos;
		do
		{
			spawnPos = { xDist( rng ), yDist( rng ) };
		} 
		while( TileAt( spawnPos ).HasMeme() );

		TileAt( spawnPos ).SpawnMeme();
	}
}

void MemeField::Draw( Graphics& gfx ) const
{
	for( Vei2 gridPos = { 0, 0 }; gridPos.y < height - 1; gridPos.y++ )
	{
		for( ; gridPos.x < width - 1; gridPos.x++ )
		{
			TileAt( gridPos ).Draw( gridPos * SpriteCodex::tileSize, gfx );
		}
	}
}

MemeField::Tile& MemeField::TileAt( const Vei2& gridPos )
{
	return field[gridPos.y * width + gridPos.x];
}

const  MemeField::Tile & MemeField::TileAt( const Vei2 & gridPos ) const
{
	return field[gridPos.y * width + gridPos.x];
}
