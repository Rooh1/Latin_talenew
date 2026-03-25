#include "stdafx.h"
#include "CDropItemAreaHandler.h"

namespace
{
DWORD GetDropAreaRarityColor( EItemRarity eRarity )
{
	switch ( eRarity )
	{
		case ITEMRARITY_Uncommon:	return D3DCOLOR_ARGB( 255, 24, 255, 96 );
		case ITEMRARITY_Rare:		return D3DCOLOR_ARGB( 255, 32, 160, 255 );
		case ITEMRARITY_Epic:		return D3DCOLOR_ARGB( 255, 196, 64, 255 );
		case ITEMRARITY_Legendary:	return D3DCOLOR_ARGB( 255, 255, 132, 16 );
		default:					return D3DCOLOR_ARGB( 220, 255, 215, 0 );
	}
}

DX::SelectGlow * GetDropAreaRarityGlow( EItemRarity eRarity )
{
	switch ( eRarity )
	{
		case ITEMRARITY_Uncommon:	return &DX::cSelectGlowLootUncommon;
		case ITEMRARITY_Rare:		return &DX::cSelectGlowLootRare;
		case ITEMRARITY_Epic:		return &DX::cSelectGlowLootEpic;
		case ITEMRARITY_Legendary:	return &DX::cSelectGlowLootLegendary;
		default:					return NULL;
	}
}
}

CDropItemAreaHandler::CDropItemAreaHandler()
{
}

CDropItemAreaHandler::~CDropItemAreaHandler()
{
	Clear();
}

void CDropItemAreaHandler::Init()
{
	EXEModel::SetBone( nullptr );
    pcModel = EXEModel::ReadModel( "game\\meshes\\droparea\\circle.ASE" );
    iRadius = 256;
}

void CDropItemAreaHandler::Clear()
{
	for ( auto ps : vCircles )
		DELET( ps );

	vCircles.clear();
}

void CDropItemAreaHandler::AddCircle( int iID, Point3D sPosition, int iRadius, bool bNoTime, EItemRarity eRarity )
{
	if ( auto psCircle = GetCircle( iID ) )
	{
		psCircle->sPosition = sPosition;
		psCircle->iRadius = iRadius;
		psCircle->eRarity = eRarity;
		psCircle->fTimeUpdate = 10000.0f;
		psCircle->bNoTime = bNoTime;
	}
	else
	{
		auto psNewCircle = new CircleArea();
		psNewCircle->iID = iID;
		psNewCircle->sPosition = sPosition;
		psNewCircle->iRadius = iRadius;
		psNewCircle->eRarity = eRarity;
		psNewCircle->fTimeEase = 1000.0f;
		psNewCircle->fTimeUpdate = 10000.0f;
		psNewCircle->bNoTime = bNoTime;
		vCircles.push_back( psNewCircle );
	}
}

void CDropItemAreaHandler::Render3D()
{
	auto SetRadius = []( int _iRadius )-> void
	{
		RENDERER->iObjectVertexScale = _iRadius;
	};

	auto RenderModel = []( PTModel * _pcModel, Point3D sPosition )-> void
	{
		Point3D sCameraPosition;
		sCameraPosition.iX = UNITTARGETPOSITION_X;
		sCameraPosition.iY = UNITTARGETPOSITION_Y;
		sCameraPosition.iZ = UNITTARGETPOSITION_Z;

		Point3D sCameraAngle;
		sCameraAngle.iX = UNITTARGETANGLE_X;
		sCameraAngle.iY = UNITTARGETANGLE_Y;
		sCameraAngle.iZ = UNITTARGETANGLE_Z;

		_pcModel->SetPosition( &sPosition, &Point3D( 0, 0, 0 ) );
		_pcModel->Render( &sCameraPosition, &sCameraAngle );
	};

	int iAlphaOld = RENDERER->a;
	RENDERER->a = -160;

	int iObjectScale = RENDERER->iObjectVertexScale;

	for ( UINT i = 0; i < pcModel->uMeshCount; i++ )
		pcModel->paMesh[i]->dwUnused = 0x3F;

	RENDERER->bNoClipFaceRender = TRUE;

	auto RenderCircles = [&]( auto fnMatch )-> void
	{
		for ( auto ps : vCircles )
		{
			if ( ps && fnMatch( ps ) )
			{
				SetRadius( (int)X3D::easeInOutCircf( 1.0f, (float)ps->iRadius, (1000.0f - ps->fTimeEase) / 1000.0f ) * 256 / 10 );
				RenderModel( pcModel, ps->sPosition );
			}
		}
	};

	auto RenderGlowGroup = [&]( DX::SelectGlow * pcGlow, D3DCOLOR dwColor, auto fnMatch )-> void
	{
		if ( pcGlow == NULL )
			return;

		if ( pcGlow->Begin( dwColor, TRUE ) )
		{
			RenderCircles( fnMatch );
			pcGlow->End( TRUE );

			if ( pcGlow->Begin( dwColor, FALSE ) )
			{
				RenderCircles( fnMatch );
				pcGlow->End( FALSE );
			}
		}
	};

	auto HasCirclesForRarity = [&]( EItemRarity eRarity )-> BOOL
	{
		for ( auto ps : vCircles )
		{
			if ( ps && ( ps->eRarity == eRarity ) )
				return TRUE;
		}

		return FALSE;
	};

	DX::cSelectGlow3.SetSizeGlow( 256.0f );

	if ( HasCirclesForRarity( ITEMRARITY_None ) )
	{
		RenderGlowGroup( &DX::cSelectGlow3, D3DCOLOR_ARGB( 220, 255, 215, 0 ), []( CircleArea * ps ) { return ps->eRarity == ITEMRARITY_None; } );
	}

	for ( int iRarity = ITEMRARITY_Uncommon; iRarity <= ITEMRARITY_Legendary; iRarity++ )
	{
		const EItemRarity eRarity = static_cast<EItemRarity>( iRarity );
		if ( HasCirclesForRarity( eRarity ) )
			RenderGlowGroup( GetDropAreaRarityGlow( eRarity ), GetDropAreaRarityColor( eRarity ), [eRarity]( CircleArea * ps ) { return ps->eRarity == eRarity; } );
	}

	RENDERER->bNoClipFaceRender = FALSE;

	RENDERER->iObjectVertexScale = iObjectScale;

	RENDERER->a = iAlphaOld;
}

void CDropItemAreaHandler::Update( float fTime )
{
	for ( auto ps : vCircles )
	{
		if ( ps->fTimeUpdate > 0.0f )
		{
			if ( ps->fTimeEase > 0.0f )
			{
				ps->fTimeEase -= fTime;

				if ( ps->fTimeEase <= 0.0f )
					ps->fTimeEase = 0.0f;
			}

			if ( ps->bNoTime == false )
			{
				ps->fTimeUpdate -= fTime;
				if ( ps->fTimeUpdate <= 0.0f )
					ps->fTimeUpdate = 0.0f;
			}
		}
	}

	for ( auto it = vCircles.begin(); it != vCircles.end(); )
	{
		auto ps = (*it);
		if ( ps->fTimeUpdate == 0.0f )
		{
			DELET( ps );
			it = vCircles.erase( it );
		}
		else
			it++;
	}
}

void CDropItemAreaHandler::HandlePacket( PacketItemAreaDrop * psPacket )
{
	for ( int i = 0; i < psPacket->iCount; i++ )
		AddCircle( psPacket->saArea[i].iUserID, psPacket->saArea[i].sPosition, psPacket->saArea[i].iRadius, true );
}

void CDropItemAreaHandler::KillCircle( int iID )
{
	for ( auto it = vCircles.begin(); it != vCircles.end(); )
	{
		auto ps = (*it);
		if ( ps->iID == iID )
		{
			DELET( ps );
			it = vCircles.erase( it );
		}
		else
			it++;
	}
}

CDropItemAreaHandler::CircleArea * CDropItemAreaHandler::GetCircle( int iID )
{
	for ( auto ps : vCircles )
		if ( ps->iID == iID )
			return ps;

	return nullptr;
}
