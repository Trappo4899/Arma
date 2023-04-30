#include "includes.h"

//class CTab {};
//class CGroup {};
//class CColourPicker {};
//class CKeybind {};
//class CText {};

void CSettings::init()
{

}

CAimbotSettings::CAimbotSettings()
{
	m_name = "Aimbot";
	m_tab_id = 0;

	m_tab = (new CTab(m_name, m_tab_id));

	m_main_group  = (new CGroup("main", { 0, 0 }, { (g_pMenu->m_size.x / 2.f) - 12.f, ((g_pMenu->m_size.y / 1.15f) + 10.f) }));

	m_enabled = (new CCheckbox("Enabled", true));
	m_key = (new CKeybind(5));
	m_fov = (new CSlider("Fov", "", 360.f, 5.f, 0.f));
	m_hitbox = (new CDropdown("Hitbox", { "Head", "Chest" }, 0));
	m_smoothing = (new CSlider("Smoothing", "%", 100.f, 0.f, 1.75f));
	m_visualize_col = (new CColourPicker("", ImColor(66, 135, 245)));
	m_only_visualize = (new CCheckbox("Only Visualize", false));
	m_ignore_team = (new CCheckbox("Ignore Team", false));

	m_weapon_group = (new CGroup("weapon", { (g_pMenu->m_size.x / 2.f) - 10.f, 0.f }, { (g_pMenu->m_size.x / 2.f) - 14.f, 175.f }));
	m_instant_scope = (new CCheckbox("instant scope", false));
	m_weapon_inertia = (new CSlider("intertia", "", 100.f, -1.f, -1.f));
	m_weapon_caliber = (new CSlider("caliber", "", 100.f, -1.f, -1.f));
}

CAimbotSettings::~CAimbotSettings()
{
	delete m_tab;

	delete m_main_group;
	delete m_enabled;
	delete m_key;
	delete m_fov;
	delete m_hitbox;
	delete m_smoothing;
	delete m_visualize_col;
	delete m_only_visualize;
	delete m_ignore_team;

	delete m_weapon_group;
	delete m_instant_scope;
	delete m_weapon_inertia;
	delete m_weapon_caliber;
}

void CAimbotSettings::init()
{
	m_main_group->add_element(m_key);
	m_main_group->add_element(m_enabled);
	m_main_group->add_element(m_fov);
	m_main_group->add_element(m_hitbox);
	m_main_group->add_element(m_smoothing);
	m_main_group->add_element(m_visualize_col);
	m_main_group->add_element(m_only_visualize);
	m_main_group->add_element(m_ignore_team);

	m_tab->add_group(m_main_group);

	m_weapon_group->add_element(m_instant_scope);
	m_weapon_group->add_element(m_weapon_inertia);
	m_weapon_group->add_element(m_weapon_caliber);

	m_tab->add_group(m_weapon_group);

	g_pMenu->m_tabs.push_back(*m_tab);
}

CEspSettings::CEspSettings()
{
	m_name = "Esp";
	m_tab_id = 1;

	m_tab = (new CTab(m_name, m_tab_id));

	m_players_group = (new CGroup("players", { 0, 0 }, { (g_pMenu->m_size.x / 2.f) - 10.f, ((g_pMenu->m_size.y / 1.75f) - 46.f) }));

	m_players_enabled	= (new CCheckbox("Enabled", true));

	m_show_box			= (new CCheckbox("Show Box", true));
	m_show_name			= (new CCheckbox("Show Names", true));
	m_name_colour		= (new CColourPicker("Names Colour", ImColor(255, 255, 255, 255)));
	m_name_pos			= (new CDropdown("Name Position", { "Top", "Bottom", "Left", "Right" }, 0));
	m_show_distance		= (new CCheckbox("Show Distance", true));
	m_distance_colour	= (new CColourPicker("Distance Colour", ImColor(255, 255, 255, 255)));
	m_distance_pos		= (new CDropdown("Distance Position", { "Top", "Bottom", "Left", "Right" }, 1));
	m_show_weapon		= (new CCheckbox("Show Weapons", true));
	m_weapon_colour		= (new CColourPicker("Weapons Colour", ImColor(255, 255, 255, 255)));
	m_weapon_pos		= (new CDropdown("Weapon Position", { "Top", "Bottom", "Left", "Right" }, 1));
	m_health_start		= (new CColourPicker("", ImColor(137, 245, 3)));
	m_show_healthbar	= (new CCheckbox("Show Healthbar", true));
	m_health_type		= (new CDropdown("Healthbar Type", { "Normal", "Gradient" }, 0));
	m_health_end		= (new CColourPicker("", ImColor(235, 73, 73)));
	m_health_pos		= (new CDropdown("Healthbar Position", { "Top", "Bottom", "Left", "Right" }, 2));
	m_show_flags		= (new CCheckbox("Show Flags", true));
	m_flags_pos			= (new CDropdown("Flags Position", { "Top", "Bottom", "Left", "Right" }, 3));
	m_hide_team			= (new CCheckbox("Hide Team", false));
	m_hide_invis		= (new CCheckbox("Hide Invisible", true));

	m_vehicles_group = (new CGroup("vehicles", { (g_pMenu->m_size.x / 2.f) - 8.f, 0 }, { (g_pMenu->m_size.x / 2.f) - 16.f, ((g_pMenu->m_size.y / 1.75f) - 46.f) }));

	m_vehicles_enabled = (new CCheckbox("Enabled", true));

	m_veh_show_name = (new CCheckbox("Show Name", true));
	m_veh_show_distance = (new CCheckbox("Show Distance", true));
	m_veh_hide_team = (new CCheckbox("Hide Team", false));
	m_veh_hide_inactive = (new CCheckbox("Hide Inactive", false));
}

CEspSettings::~CEspSettings()
{
	delete m_tab;
	delete m_players_enabled;
	delete m_show_box;
	delete m_show_name;
	delete m_name_colour;
	delete m_show_distance;
	delete m_distance_colour;
	delete m_show_weapon;
	delete m_weapon_colour;
	delete m_show_healthbar;
	delete m_health_start;
	delete m_health_end;
	delete m_health_type;
	delete m_show_flags;
	delete m_hide_team;
	delete m_hide_invis;
	delete m_name_pos;
	delete m_distance_pos;
	delete m_health_pos;
	delete m_weapon_pos;
	delete m_flags_pos;
}

void CEspSettings::init()
{
	m_players_group->add_element(m_players_enabled);
	m_players_group->add_element(m_show_box);
	m_players_group->add_element(m_name_colour);
	m_players_group->add_element(m_show_name);
	m_players_group->add_element(m_name_pos);
	m_players_group->add_element(m_distance_colour);
	m_players_group->add_element(m_show_distance);
	m_players_group->add_element(m_distance_pos);
	m_players_group->add_element(m_weapon_colour);
	m_players_group->add_element(m_show_weapon);
	m_players_group->add_element(m_weapon_pos);
	m_players_group->add_element(m_health_start);
	m_players_group->add_element(m_show_healthbar);
	m_players_group->add_element(m_health_end);
	m_players_group->add_element(m_health_type);
	m_players_group->add_element(m_health_pos);
	m_players_group->add_element(m_show_flags);
	m_players_group->add_element(m_flags_pos);
	m_players_group->add_element(m_hide_team);
	m_players_group->add_element(m_hide_invis);

	m_vehicles_group->add_element(m_vehicles_enabled);
	m_vehicles_group->add_element(m_veh_show_name);
	m_vehicles_group->add_element(m_veh_show_distance);
	m_vehicles_group->add_element(m_veh_hide_team);
	m_vehicles_group->add_element(m_veh_hide_inactive);

	m_tab->add_group(m_players_group);
	m_tab->add_group(m_vehicles_group);

	g_pMenu->m_tabs.push_back(*m_tab);
}

CMiscSettings::CMiscSettings()
{
	m_name = "Misc";
	m_tab_id = 2;

	m_tab = (new CTab(m_name, m_tab_id));

	/* settings group */
	m_group_settings = (new CGroup("settings", { 0, 0 }, { (g_pMenu->m_size.x / 2.f) - 12.f, ((g_pMenu->m_size.y / 4.f) - 46.f) }));

	m_accent = (new CColourPicker("menu accent", ImColor(164, 146, 243, 255)));
	m_accent_name = (new CText("Menu Accent"));
	m_menu_key = (new CKeybind(VK_INSERT, CKeybind::TOGGLE, false));
	m_menu_key_name = (new CText("Menu Key"));

	m_fov_group = (new CGroup("Fov", { 0, ((g_pMenu->m_size.y / 4.f) - 46.f) + 5.5f }, { (g_pMenu->m_size.x / 2.f) - 12.f, 160.f }));

	m_fov = (new CSlider("Fov", "", 180.f, 5.f, 60.f));
	m_width = (new CSlider("Width", "", 21.f, 0.f, 16.f));
	m_height = (new CSlider("Height", "", 9.f, 0.f, 9.f));
	m_zoom = (new CKeybind(4, CKeybind::HOLD, true));
	m_zoom_amount = (new CSlider("Zoom Amount", "", 45.f, 5.f, 15.f));
}

CMiscSettings::~CMiscSettings()
{
	delete m_accent;
	delete m_accent_name;
	delete m_menu_key;
	delete m_menu_key_name;
	delete m_tab;
	delete m_group_settings;
	delete m_fov_group;
	delete m_fov;
	delete m_width;
	delete m_height;
	delete m_zoom;
	delete m_zoom_amount;
}

void CMiscSettings::init()
{
	m_group_settings->add_element(m_accent);
	m_group_settings->add_element(m_accent_name);

	m_group_settings->add_element(m_menu_key);
	m_group_settings->add_element(m_menu_key_name);

	m_fov_group->add_element(m_fov);
	m_fov_group->add_element(m_width);
	m_fov_group->add_element(m_height);
	m_fov_group->add_element(m_zoom);
	m_fov_group->add_element(m_zoom_amount);

	m_tab->add_group(m_group_settings);
	m_tab->add_group(m_fov_group);

	g_pMenu->m_tabs.push_back(*m_tab);
}