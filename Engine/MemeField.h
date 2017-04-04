#pragma once

#include "Graphics.h"
#include "SpriteCodex.h"

class MemeField
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMeme();
		bool HasMeme() const;
		void Draw( const Vei2& screenPos,bool fucked,Graphics& gfx ) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		void SetNeighborMemeCount( int memeCount );
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
	};
public:
	MemeField( int nMemes );
	void Draw( Graphics& gfx ) const;
	void DrawWin( Graphics& gfx ) const;
	RectI GetRect() const;
	void OnRevealClick( const Vei2& screenPos );
	void OnFlagClick( const Vei2& screenPos );
	bool HasWon() const;
private:
	void CheckIfWon();
	Tile& TileAt( const Vei2& gridPos );
	const Tile& TileAt( const Vei2& gridPos ) const;
	Vei2 ScreenToGrid( const Vei2& screenPos );
	int CountNeighborMemes( const Vei2& gridPos );
private:
	static constexpr int width = 5;
	static constexpr int height = 5;
	static constexpr int xOffset = Graphics::ScreenWidth / 2 - width / 2 * SpriteCodex::tileSize;
	static constexpr int yOffset = Graphics::ScreenHeight / 2 - height / 2 * SpriteCodex::tileSize;
	const Vei2 offset = { xOffset, yOffset };
	bool isFucked = false;
	bool isWon = false;
	Tile field[width * height];
};