#pragma once
#include "StdAfx.h"
#include "CryRenderer\IRenderAuxGeom.h"


namespace DebugDraw{
	const ColorF defaultColor = 0xFF0000FF;

	static void RenderDebugCubeFromAABB(const AABB& aabb, const Matrix34& matWorld, bool showInGame = false ,const ColorF& color = defaultColor){
		IRenderAuxGeom* pRenderAuxGeom = gEnv->pRenderer->GetIRenderAuxGeom();
		if ((!showInGame && gEnv->IsEditor()) || showInGame)
		{			
			pRenderAuxGeom->DrawAABB(aabb, matWorld, false, color, EBoundingBoxDrawStyle::eBBD_Faceted);
		}	
	}

	static void RenderDebugLine(const Vec3& p0, const Vec3& p1, bool showInGame = false, const ColorF& color = defaultColor, float thick = 1.0f) {
		IRenderAuxGeom* pRenderAuxGeom = gEnv->pRenderer->GetIRenderAuxGeom();
		if ((!showInGame && gEnv->IsEditor()) || showInGame)
		{			
			pRenderAuxGeom->DrawLine(p0, color,p1, color,thick);
		}
	}

	static void DrawDebugText(const char* text, float x, float y, float size, bool showInGame = false, const ColorF& color = defaultColor)
	{
		IRenderAuxGeom* pRenderAuxGeom = gEnv->pRenderer->GetIRenderAuxGeom();
		if ((!showInGame && gEnv->IsEditor()) || showInGame)
		{
			pRenderAuxGeom->Draw2dLabel(x, y, size, color, false, "%s", text);
		}
	}

}
