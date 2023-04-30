#include "includes.h"

#define MIN_BOX_SIZE 10.f

void CVisuals::DrawBox(const Entity& ent)
{
	auto col = ImColor(ent.m_color.Value.x, ent.m_color.Value.y, ent.m_color.Value.z, 100.f / 255.f);

	g_pRender->background.rect(ent.m_box.x, ent.m_box.y, ent.m_box.w, ent.m_box.h, 3, ImColor(0, 0, 0, 100));
	g_pRender->background.rect(ent.m_box.x, ent.m_box.y, ent.m_box.w, ent.m_box.h, 1, ent.m_color);
}

void CVisuals::DrawBar(Box box, float value, float max, ImColor colour, ImColor colour2, BOX_POSITION boxPos)
{
	static const float padding = 8.5f;

	if (value == 0.f || max == 0.f)
	{
		return;
	}

	float percent = value / max;

	if (percent <= 0.f)
	{
		return;
	}

	auto col = ImColor(colour.Value.x, colour.Value.y, colour.Value.z, 200.f / 255.f);
	auto col2 = ImColor(colour2.Value.x, colour2.Value.y, colour2.Value.z, 200.f / 255.f);

	switch (boxPos)
	{
	case BOX_POSITION::TOP:
		g_pRender->background.rect_filled(box.x - 1, box.y - m_padding_top.y - 7, box.w + 2, 4, ImColor(0, 0, 0, 100));
		g_pRender->background.rect_filled(box.x + box.w - (box.w - (box.w * percent)), box.y - m_padding_top.y - 6, -(box.w * percent), 2, util::ColourInterpolation(col, col2, 0.f, max, value));

		m_padding_top.y += padding;
		break;
	case BOX_POSITION::BOTTOM:
		g_pRender->background.rect_filled(box.x - 1, box.y + box.h + m_padding_bottom.y + 6, box.w + 2, 4, ImColor(0, 0, 0, 100));
		g_pRender->background.rect_filled(box.x + box.w - (box.w - (box.w * percent)), box.y + box.h + m_padding_bottom.y + 7, -(box.w * percent), 2, util::ColourInterpolation(col, col2, 0.f, max, value));

		m_padding_bottom.y += padding;
		break;
	case BOX_POSITION::LEFT:
		g_pRender->background.rect_filled(box.x - m_padding_left.x -  6, box.y - 1, 4, box.h + 2, ImColor(0, 0, 0, 100));
		g_pRender->background.rect_filled(box.x - m_padding_left.x - 5, box.y + (box.h - (box.h * percent)), 2, (box.h * percent), util::ColourInterpolation(col, col2, 0.f, max, value));

		m_padding_left.x += padding;
		break;
	case BOX_POSITION::RIGHT:
		g_pRender->background.rect_filled(box.x + box.w + m_padding_right.x + 3, box.y - 1, 4, box.h + 2, ImColor(0, 0, 0, 100));
		g_pRender->background.rect_filled(box.x + box.w + m_padding_right.x + 4, box.y + (box.h - (box.h * percent)), 2, (box.h * percent), util::ColourInterpolation(col, col2, 0.f, max, value));

		m_padding_right.x += padding;
		break;
	}
}

void CVisuals::DrawGradientBar(Box box, float value, float max, ImColor colour, ImColor colour2, BOX_POSITION boxPos)
{
	static const float padding = 7.5f;

	if (value == 0.f || max == 0.f)
	{
		return;
	}

	float percent = value / max;

	if (percent <= 0.f)
	{
		return;
	}

	auto col = ImColor(colour.Value.x, colour.Value.y, colour.Value.z, 200.f / 255.f);
	auto col2 = ImColor(colour2.Value.x, colour2.Value.y, colour2.Value.z, 200.f / 255.f);

	switch (boxPos)
	{
	case BOX_POSITION::TOP:
		g_pRender->background.rect_filled(box.x - 1, box.y - m_padding_top.y - 7, box.w + 2, 4, ImColor(0, 0, 0, 100));

		g_pRender->background.gradient2(box.x + box.w - (box.w - (box.w * percent)), box.y - m_padding_top.y - 6, -(box.w * percent), 2, util::ColourInterpolation(col, col2, 0.f, max, value), col2);
	
		m_padding_top.y += padding;
		break;
	case BOX_POSITION::BOTTOM:
		g_pRender->background.rect_filled(box.x - 1, box.y + box.h + m_padding_bottom.y + 6, box.w + 2, 4, ImColor(0, 0, 0, 100));

		g_pRender->background.gradient2(box.x + box.w - (box.w - (box.w * percent)), box.y + box.h + m_padding_bottom.y + 7, -(box.w * percent), 2, util::ColourInterpolation(col, col2, 0.f, max, value), col2);

		m_padding_bottom.y += padding;
		break;
	case BOX_POSITION::LEFT:
		g_pRender->background.rect_filled(box.x - m_padding_left.x - 6, box.y - 1, 4, box.h + 2, ImColor(0, 0, 0, 100));

		g_pRender->background.gradient(box.x - m_padding_left.x - 5, box.y + (box.h - (box.h * percent)), 2, (box.h * percent), util::ColourInterpolation(col, col2, 0.f, max, value), col2);

		m_padding_left.x += padding;
		break;
	case BOX_POSITION::RIGHT:
		g_pRender->background.rect_filled(box.x + box.w + m_padding_right.x + 3, box.y - 1, 4, box.h + 2, ImColor(0, 0, 0, 100));

		g_pRender->background.gradient(box.x + box.w + m_padding_right.x + 4, box.y + (box.h - (box.h * percent)), 2, (box.h * percent), util::ColourInterpolation(col, col2, 0.f, max, value), col2);

		m_padding_right.x += padding;
		break;
	}
}

void CVisuals::DrawText(Box box, const char* text, ImColor _colour, int fontFlags, BOX_POSITION boxPos, bool pixel)
{
	static float padding = 10.5f;

	ImColor colour = ImColor(_colour.Value.x, _colour.Value.y, _colour.Value.z, 1.f);

	switch (boxPos)
	{
	case BOX_POSITION::TOP:
		!pixel ? g_pRender->foreground.normal_text(	text,
													box.x + (box.w / 2) - m_padding_top.x,
													box.y - m_padding_top.y - 10.5f,
													colour,
													fontFlags)
			:
				g_pRender->foreground.pixel_text(	text,
													box.x + (box.w / 2) - m_padding_top.x,
													box.y - m_padding_top.y - 10.5f,
													colour,
													fontFlags);

		m_padding_top.y += !pixel ? padding : padding - 2.f;
		break;

	case BOX_POSITION::BOTTOM:
		!pixel ? g_pRender->foreground.normal_text(	text,
													box.x + (box.w / 2) - m_padding_bottom.x,
													box.y + box.h + m_padding_bottom.y + 0.75f,
													colour,
													fontFlags)

			:	g_pRender->foreground.pixel_text(	text,
													box.x + (box.w / 2) - m_padding_bottom.x,
													box.y + box.h + m_padding_bottom.y + 0.75f,
													colour,
													fontFlags);

		m_padding_bottom.y += !pixel ? padding : padding - 2.f;
		break;

	case BOX_POSITION::RIGHT:

		fontFlags & FONT_CENTERED ? fontFlags = fontFlags & ~FONT_CENTERED : fontFlags = fontFlags;

		!pixel ? g_pRender->foreground.normal_text(

											text,
											box.x + box.w + m_padding_right.x + 5.f,
											box.y + m_padding_right.y + 1.5f,
											colour,
											fontFlags
		)

			: g_pRender->foreground.pixel_text(text,
				box.x + box.w + m_padding_right.x + 5.f,
				box.y + m_padding_right.y + 1.5f,
				colour,
				fontFlags);

		m_padding_right.y += !pixel ? padding : padding - 2.f;
		break;

	case BOX_POSITION::LEFT:

		fontFlags & FONT_CENTERED ? fontFlags = fontFlags & ~FONT_CENTERED : fontFlags = fontFlags;


		!pixel ? g_pRender->foreground.normal_text(	text,
											box.x - m_padding_left.x,
											box.y + m_padding_left.y + 1.5f,
											colour,
											fontFlags | FONTFLAGS::FONT_RIGHT)
			: 
			g_pRender->foreground.pixel_text(text,
				box.x - m_padding_left.x - 5.f,
				box.y + m_padding_left.y + 1.5f,
				colour,
				fontFlags | FONTFLAGS::FONT_RIGHT);

		m_padding_left.y += !pixel ? padding : padding - 2.f;
		break;
	}
}

BOX_POSITION CVisuals::GetBoxPos(int option)
{
	switch (option)
	{
	case 0:
		return BOX_POSITION::TOP;
	case 1:
		return BOX_POSITION::BOTTOM;
	case 2:
		return BOX_POSITION::LEFT;
	case 3:
		return BOX_POSITION::RIGHT;
	}
}

void CVisuals::handle_players(Entity ent)
{
	if ((ent.m_invisible && g_pEspSettings->m_hide_invis->active()) || 
	   ((ent.m_entity.GetTeam() == g_pClient->m_local.m_local.GetTeam()) && g_pEspSettings->m_hide_team->active()))
	{
		return;
	}

	if (g_pEspSettings->m_show_box->active())
	{
		DrawBox(ent);
	}

	/* do this here so bars are drawn before anything else because text then bar looks haram */
	if (!ent.m_entity.IsDead())
	{
		if (g_pEspSettings->m_show_healthbar->active())
		{
			switch (g_pEspSettings->m_health_type->get_selected())
			{
			case 0:
				DrawBar(ent.m_box, ent.m_health, 100.f, g_pEspSettings->m_health_start->get_colour(), g_pEspSettings->m_health_end->get_colour(), GetBoxPos(g_pEspSettings->m_health_pos->get_selected()));
				break;

			case 1:
				DrawGradientBar(ent.m_box, ent.m_health, 100.f, g_pEspSettings->m_health_start->get_colour(), g_pEspSettings->m_health_end->get_colour(), GetBoxPos(g_pEspSettings->m_health_pos->get_selected()));
				break;
			}
		}
	}

	if (g_pEspSettings->m_show_distance->active())
	{
		DrawText(ent.m_box, std::string(std::to_string(ent.m_distance) + "m").c_str(), g_pEspSettings->m_distance_colour->get_colour(), FONT_OUTLINED | FONT_CENTERED, GetBoxPos(g_pEspSettings->m_distance_pos->get_selected()), true);
	}

	if (!ent.m_entity.IsDead())
	{
		if (g_pEspSettings->m_show_name->active())
		{
			DrawText(ent.m_box, ent.m_is_ai ? "AI" : ent.m_player_identity.GetName().c_str(), g_pEspSettings->m_name_colour->get_colour(), FONT_OUTLINED | FONT_CENTERED, GetBoxPos(g_pEspSettings->m_name_pos->get_selected()));
		}

		if (g_pEspSettings->m_show_weapon->active())
		{
			if (_stricmp("(null)", ent.m_active_weapon.GetWeaponType().GetName().c_str()) && _stricmp("Throw", ent.m_active_weapon.GetWeaponType().GetName().c_str()))
			{
				DrawText(ent.m_box, ent.m_active_weapon.GetWeaponType().GetName().c_str(), g_pEspSettings->m_weapon_colour->get_colour(), FONT_OUTLINED | FONT_CENTERED, GetBoxPos(g_pEspSettings->m_weapon_pos->get_selected()), true);
			}
		}
	}

	if (g_pEspSettings->m_show_flags->active())
	{
		if (ent.m_invisible)
		{
			DrawText(ent.m_box, "Invis", ImColor(194, 37, 123, 255), FONT_OUTLINED | FONT_CENTERED, GetBoxPos(g_pEspSettings->m_flags_pos->get_selected()));
		}
	}
}

void CVisuals::handle_vehicles(Vehicle veh)
{
	if (((veh.m_inactive && g_pEspSettings->m_veh_hide_inactive->active()) ||
		((veh.m_driver.m_entity.GetTeam() == g_pClient->m_local.m_local.GetTeam()) && g_pEspSettings->m_veh_hide_team->active())))
	{
		return;
	}

	if (g_pEspSettings->m_veh_show_name->active())
	{
		DrawText(veh.m_box, veh.m_entity_type.GetPrint().c_str(), veh.m_color, FONT_OUTLINED | FONT_CENTERED, BOX_POSITION::BOTTOM);
	}

	if (!veh.m_inactive)
	{
		DrawText(veh.m_box, veh.m_driver.m_is_ai ? "AI" : veh.m_driver.m_player_identity.GetName().c_str(), veh.m_driver.m_color, FONT_OUTLINED | FONT_CENTERED, BOX_POSITION::BOTTOM);
	}

	if (g_pEspSettings->m_veh_show_distance->active())
	{
		DrawText(veh.m_box, std::string(std::to_string(veh.m_distance) + "m").c_str(), veh.m_color, FONT_OUTLINED | FONT_CENTERED, BOX_POSITION::BOTTOM);
	}
}

void CVisuals::handle_wildlife(Entity ent)
{

}

bool CVisuals::GetBox(Entity ent, Box& box)
{				  
	Vector3 min = { };
	Vector3 max = { };

	FLOAT dist = ent.m_visual_state.GetOrigin().Distance(ent.m_visual_state.GetHead()) + 0.02f;

	if (ent.m_entity.IsDead() && dist < 1.f)
	{
		ent.m_stance = PRONE;
	}

	switch (ent.m_stance)
	{
	case AISTANDING:
		min = { -0.25f,			0.f,			-0.25f };
		max = { 0.25f,		dist * 1.1f,		 0.25f };
		break;

	case STANDING:
		min = { -0.25f, 0.f,			-0.25f };
		max = { 0.25f, dist * 1.1f,  0.25f };
		break;

	case CROUCHING:
		min = { -0.25f, 0.f,        -0.55f };
		max = {  0.25f, dist * 1.15f, 0.25f };
		break;

	case PRONE:
		min = { 0.15f, 0.35f,         1.54f };
		max = { -0.15f, 0.0f,		   -1.0f };
		break;

	default:
	{
		min = { -0.25f,			0.f,			-0.25f };
		max = { 0.25f,		dist * 1.1f,		 0.25f };
	}
	}

	Vector3 points[] = {	Vector3(min.x, min.y, min.z),		//	back	-	left	-	back
							Vector3(min.x, max.y, min.z),		//	back	-	right	-	back
							Vector3(max.x, max.y, min.z),		//	front	-	right	-	back
							Vector3(max.x, min.y, min.z),		//	front	-	left	-	back
							Vector3(max.x, max.y, max.z),		//	front	-	right	-	top
							Vector3(min.x, max.y, max.z),		//	back	-	right	-	top
							Vector3(min.x, min.y, max.z),		//	back	-	left	-	top
							Vector3(max.x, min.y, max.z)		//	front	-	left	-	top
	};

	Vector3 pointsTransformed[8];

	for (int i = 0; i < 8; i++)
	{
		pointsTransformed[i] = Math::model_to_world(points[i], ent.m_visual_state.GetRotationMatrix(), ent.m_visual_state.GetOrigin());
	}

	Vector2 flb;
	Vector2 brt;
	Vector2 blb;
	Vector2 frt;
	Vector2 frb;
	Vector2 brb;
	Vector2 blt;
	Vector2 flt;

	if (	!g_pClient->m_camera.WorldToScreen(pointsTransformed[3], flb) || !g_pClient->m_camera.WorldToScreen(pointsTransformed[5], brt)
		||	!g_pClient->m_camera.WorldToScreen(pointsTransformed[0], blb) || !g_pClient->m_camera.WorldToScreen(pointsTransformed[4], frt)
		||	!g_pClient->m_camera.WorldToScreen(pointsTransformed[2], frb) || !g_pClient->m_camera.WorldToScreen(pointsTransformed[1], brb)
		||	!g_pClient->m_camera.WorldToScreen(pointsTransformed[6], blt) || !g_pClient->m_camera.WorldToScreen(pointsTransformed[7], flt))
		return false;

	Vector2 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	//for (int i = 0; i < 8; i++)
	//{
	//	g_pRender->foreground.rect_filled(arr[i].x - 2.5f, arr[i].y - 2.5f, 5, 5, ImColor(0, 0, 0, 255));
	//	g_pRender->foreground.rect_filled(arr[i].x, arr[i].y, 3, 3, ImColor(255, 255, 255, 255));
	//}

	float left		= flb.x;	// left
	float top		= flb.y;	// top
	float right		= flb.x;	// right
	float bottom	= flb.y;	// bottom

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
		{
			left = arr[i].x;
		}

		if (top < arr[i].y)
		{
			top = arr[i].y;
		}

		if (right < arr[i].x)
		{
			right = arr[i].x;
		}

		if (bottom > arr[i].y)
		{
			bottom = arr[i].y;
		}
	}

	box.w = right - left;
	box.h = top - bottom;
	box.x = left;
	box.y = bottom;

	float Scale = ent.m_distance;

	Scale = std::clamp<float>(Scale, 0.f, 6.5f);

	box.x -= Scale * 1.5f;
	box.y -= Scale * 1.5f;
	box.w += Scale * 1.25f;
	box.h += Scale;

	return true;
}

void CVisuals::think(const EntityList& entityList)
{
	const auto& ents = entityList.m_entities;
	const auto& vehs = entityList.m_vehicles;

	if (g_pEspSettings->m_players_enabled->active())
	{
		for (auto ent : ents)
		{
			handle_players(ent);

			m_padding_top		= { };
			m_padding_bottom	= { };
			m_padding_left		= { };
			m_padding_right		= { };
		}
	}

	if (g_pEspSettings->m_vehicles_enabled->active())
	{
		for (auto veh : vehs)
		{
			handle_vehicles(veh);

			m_padding_top		= { };
			m_padding_bottom	= { };
			m_padding_left		= { };
			m_padding_right		= { };
		}
	}
}