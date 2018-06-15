#pragma once
#pragma once
struct dlight_t
{
	int		flags;
	Vector	origin;
	float	radius;
	Color	color;
	float	die;
	float	decay;
	float	minlight;
	int		key;
	int		style;
	Vector	m_Direction;
	float	m_InnerAngle;
	float	m_OuterAngle;
	float GetRadius() const
	{
		return radius;
	}
	float GetRadiusSquared() const
	{
		return radius * radius;
	}
	float IsRadiusGreaterThanZero() const
	{
		return radius > 0.0f;
	}
};
class CEffects
{
public:
	dlight_t* CL_AllocDlight(int key)
	{
		typedef dlight_t*(__thiscall* Fn)(PVOID, int);
		return getvfunc<Fn>(this, 4)(this, key);
	}
	dlight_t* CL_AllocElight(int key)
	{
		typedef dlight_t*(__thiscall* Fn)(PVOID, int);
		return getvfunc<Fn>(this, 5)(this, key);
	}
	dlight_t* GetElightByKey(int key)
	{
		typedef dlight_t*(__thiscall* Fn)(PVOID, int);
		return getvfunc<Fn>(this, 8)(this, key);
	}
};