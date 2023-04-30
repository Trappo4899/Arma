#pragma once

class CTab;
class CGroup;
class CColourPicker;
class CKeybind;
class CText;

class CSettings
{
protected:

	CTab* m_tab;
	int m_tab_id;
	const char* m_name;

protected:

	virtual void init() = 0;
};

class CAimbotSettings : public CSettings
{
public:

	CAimbotSettings();
	~CAimbotSettings();

public: /* groups 1 */

	CGroup* m_main_group;

	CCheckbox* m_enabled;
	CKeybind* m_key;
	CSlider* m_fov;
	CDropdown* m_hitbox;
	CSlider* m_smoothing;
	CColourPicker* m_visualize_col;
	CCheckbox* m_only_visualize;
	CCheckbox* m_ignore_team;

public: /* group 2 */

	CGroup* m_weapon_group;

	CCheckbox* m_instant_scope;
	CSlider* m_weapon_inertia;
	CSlider* m_weapon_caliber;

public: /* group 3 */

	CGroup* m_group3;

public:

	void init() override;
};

extern std::unique_ptr<CAimbotSettings> g_pAimbotSettings;

class CEspSettings : public CSettings
{
public:

	CEspSettings();
	~CEspSettings();

public: /* groups 1 */

	CGroup* m_players_group;

	CCheckbox* m_players_enabled;

	CCheckbox* m_show_box;
	CCheckbox* m_show_name;
	CColourPicker* m_name_colour;
	CDropdown* m_name_pos;
	CCheckbox* m_show_distance;
	CColourPicker* m_distance_colour;
	CDropdown* m_distance_pos;
	CCheckbox* m_show_weapon;
	CColourPicker* m_weapon_colour;
	CDropdown* m_weapon_pos;
	CCheckbox* m_show_healthbar;
	CColourPicker* m_health_start;
	CDropdown* m_health_type;
	CColourPicker* m_health_end;
	CDropdown* m_health_pos;
	CCheckbox* m_show_flags;
	CDropdown* m_flags_pos;
	CCheckbox* m_hide_team;
	CCheckbox* m_hide_invis;

public: /* group 2 */

	CGroup* m_vehicles_group;

	CCheckbox* m_vehicles_enabled;

	CCheckbox* m_veh_show_name;
	CCheckbox* m_veh_show_distance;
	CCheckbox* m_veh_hide_team;
	CCheckbox* m_veh_hide_inactive;

public: /* group 3 */

	CGroup* m_group3;

	void init() override;
};

extern std::unique_ptr<CEspSettings> g_pEspSettings;

class CMiscSettings : public CSettings
{
public:

	CMiscSettings();
	~CMiscSettings();

public: /* settings */

	CGroup* m_group_settings;

	CColourPicker* m_accent;
	CText* m_accent_name;
	CKeybind* m_menu_key;
	CText* m_menu_key_name;

	CGroup* m_fov_group;

	CSlider* m_fov;
	CSlider* m_width;
	CSlider* m_height;
	CSlider* m_zoom_amount;
	CKeybind* m_zoom;

public: /* misc */

	CGroup* m_misc;

public:

	void init() override;
};

extern std::unique_ptr<CMiscSettings> g_pMiscSettings;